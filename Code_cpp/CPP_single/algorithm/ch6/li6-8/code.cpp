#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

const int maxn = 1000000;
int in_order[maxn], post_order[maxn], lch[maxn], rch[maxn];
int n;

// 输入转换
bool read_list(int *a)
{
    string line;
    if (!getline(cin, line))
        return false;
    stringstream ss(line);
    int x;
    n = 0;
    while (ss >> x)
        a[n++] = x;
    return true;
}

// 建树in_order[L1...R1],post_order[L2...R2]
int build(int L1, int R1, int L2, int R2)
{
    if (L1 > R1)
        return 0; // 空树
    int root = post_order[R2];
    int p = L1;
    while (in_order[p] != root)
        p++;
    int cnt = p - L1;
    lch[root] = build(L1, p - 1, L2, L2 + cnt - 1);
    rch[root] = build(p + 1, R1, L2 + cnt, R2 - 1);
    return root;
}

// 最好的叶子结点和最小的权值和
int best, best_sum;

// 宽度优先搜索
int bfs(int u, int sum)
{
    sum += u;
    if (!lch[u] && !rch[u])
    {
        if (sum < best_sum || (sum == best_sum && u < best))
        {
            best_sum = sum;
            best = u;
        }
    }
    if (lch[u])
        bfs(lch[u], sum);
    if (rch[u])
        bfs(rch[u], sum);
    return best;
}

int main()
{
    while (read_list(in_order))
    {
        read_list(post_order);
        build(0, n - 1, 0, n - 1);
        best_sum = 100000000;
        int sum = 0;
        bfs(post_order[n - 1], sum);
        cout << best << endl;
    }
    return 0;
}
