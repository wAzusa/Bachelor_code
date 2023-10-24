#!/usr/bin/python
#coding=UTF-8

from __future__ import print_function
from bcc import BPF, PerfType, PerfHWConfig
from time import sleep, strftime

bpf_text = """
#include <uapi/linux/ptrace.h>
#include <linux/sched.h>
#include <linux/mm_types.h>
#include <linux/mm_types_task.h>
#include <linux/mm.h>


struct key_t {
    u32 pid;
    char comm[16];
};

struct data_t {
    unsigned long nvcsw;
    unsigned long nivcsw;
    u64 vsize;                        //虚拟内存
    u64 size;                         //物理内存
    long long rssanon;       //匿名页面
    long long rssfile;       //文件页面
    long long rssshmem;      //共享页面
    long long vswap;         //交换页面
    unsigned long long Hpages;        //hugetlbPages
    unsigned long Vdata;              //Private data segments
    unsigned long Vstk;               //User stack
    unsigned long long VPTE;
};

BPF_HASH(dist, struct key_t, struct data_t);

TRACEPOINT_PROBE(sched, sched_switch)
{
    struct mm_rss_stat rss = {};
    struct task_struct *prev = (struct task_struct *)bpf_get_current_task();
    struct key_t key = {};

    key.pid = bpf_get_current_pid_tgid();
    bpf_get_current_comm(&key.comm, sizeof(key.comm));
    

    struct data_t data = {
    .vsize = prev->mm->total_vm,
    .Vdata = prev->mm->data_vm,
    .Vstk = prev->mm->stack_vm,
    .nvcsw = prev->nvcsw,
    .nivcsw = prev->nivcsw
    };

    long long *test;
    bpf_probe_read_kernel(&rss, sizeof(struct mm_rss_stat), &prev->mm->rss_stat);
    test = rss.count;
    data.rssfile = *test;
    data.rssanon = *(test + 1);
    data.vswap =  *(test + 2);
    data.rssshmem = *(test + 3);
    data.size = data.rssanon + data.rssfile + data.rssshmem;


    dist.update(&key, &data); 
}
"""

bpf_text1="""
#include <linux/ptrace.h>
#include <uapi/linux/bpf_perf_event.h>
struct key_t {
    int cpu;
    int pid;
    char name[TASK_COMM_LEN];
};
BPF_HASH(ref_count, struct key_t);
BPF_HASH(miss_count, struct key_t);
static inline __attribute__((always_inline)) void get_key(struct key_t* key) {
    key->cpu = bpf_get_smp_processor_id();
    key->pid = bpf_get_current_pid_tgid() >> 32;
    bpf_get_current_comm(&(key->name), sizeof(key->name));
}
int on_cache_miss(struct bpf_perf_event_data *ctx) {
    struct key_t key = {};
    get_key(&key);
    miss_count.increment(key, ctx->sample_period);
    return 0;
}
int on_cache_ref(struct bpf_perf_event_data *ctx) {
    struct key_t key = {};
    get_key(&key);
    ref_count.increment(key, ctx->sample_period);
    return 0;
}
"""

b = BPF(text=bpf_text)
c = BPF(text=bpf_text1)

c.attach_perf_event(
        ev_type=PerfType.HARDWARE, ev_config=PerfHWConfig.CACHE_MISSES,
        fn_name="on_cache_miss", sample_period=500)
c.attach_perf_event(
        ev_type=PerfType.HARDWARE, ev_config=PerfHWConfig.CACHE_REFERENCES,
        fn_name="on_cache_ref", sample_period=500)

dist = b.get_table("dist")
print("%-15s %-15s %-15s %-15s %-15s %-15s %-15s" % ("PID", "VmSize",  "VmRSS", "RssAnon", "RssFile", "RssShmem", "VmSwap"))

     
while (1):
    try:
        sleep(1)

        miss_count = {}
        for (k, v) in b.get_table('miss_count').items():
            miss_count[(k.pid, k.cpu, k.name)] = v.value

        tot_ref = 0
        tot_miss = 0
 
        for k, v in dist.items():
             for (c, a) in b.get_table('ref_count').items():
                try:
                    miss = miss_count[(c.pid, c.cpu, c.name)]
                except KeyError:
                    miss = 0
                hit = (v.value - miss) if (v.value >= miss) else 0
                if k.pid == c.pid
                    print("%-15d %-15d %-15d %-15d %-15d %-15d %-15d %-15d %-15d %-15d %-15d %-15d %-15d %-15d %-15d" 
                            % (k.pid, v.vsize, v.size, v.rssanon, v.rssfile, v.rssshmem, v.vswap, v.Vdata, v.Vstk, v.VPTE, v.Hpages, v.nvcsw, v.nivcsw, a.value, miss))

    except KeyboardInterrupt:
        exit()
