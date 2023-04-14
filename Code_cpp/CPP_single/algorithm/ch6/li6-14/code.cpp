#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// 将方向和转向编号“0~3”和“0~2”
const char *dirs = "NESW"; // 顺时针
const char *turns = "FLR";
int dir_id(char c) { return strchr(dirs, c) - dirs; }
int turn_id(char c) { return strchr(turns, c) - turns; }

const int N = 10;

bool has_edge[N][N][4][4]; // 判断状态(r,c,dir)在turn是能否转向；

int d[N][N][4]; // 初始态到(r,c,dir)的距离；

struct Node
{
    int r;
    int c;
    int dir;
    Node(int r, int c, int dir) : r(r), c(c), dir(dir) {}
    Node() {}
};

Node p[N][N][4]; // 记录当前节点在BFS树中的父节点；

// 行走函数,产生后继节点

const int dr[] = {-1, 0, 1, 0};
const int dc[] = {0, 1, 0, -1};

Node walk(const Node &u, int turn)
{
    int dir = u.dir;
    if (turn == 1)
        dir = (dir + 3) % 4;
    if (turn == 2)
        dir = (dir + 1) % 4;
    return Node(u.r + dr[dir], u.c + dc[dir], dir);
}

// 输入函数
int r0, c0, r1, dir, c1, r2, c2;
string maze;
bool input()
{
    cin >> maze;
    if (maze == "END")
        return false;
    char op;
    cin >> r0 >> c0 >> op >> r2 >> c2;
    dir = dir_id(op);
    r1 = r0 + dr[dir];
    c1 = c0 + dc[dir];

    // 输入
    int r, c;
    string tmp;
    memset(has_edge, 0, sizeof(has_edge));
    while (cin >> r, r)
    {
        cin >> c;
        while (cin >> tmp, tmp != "*")
        {
            for (int i = 1; i < (int)tmp.size(); ++i)
                has_edge[r][c][dir_id(tmp[0])][turn_id(tmp[i])] = true;
        }
    }
    return true;
}

bool inside(int r, int c)
{
    return r >= 1 && r <= 9 && c >= 1 && c <= 9;
}

void print_ans(Node u)
{
    vector<Node> nodes;
    for (;;)
    {
        nodes.push_back(u);
        if (d[u.r][u.c][u.dir] == 0)
            break;
        u = p[u.r][u.c][u.dir];
    }

    nodes.push_back(Node(r0, c0, dir));

    int cnt = 0;
    for (int i = nodes.size() - 1; i >= 0; --i)
    {
        if (cnt % 10 == 0)
            printf(" ");
        printf(" (%d,%d)", nodes[i].r, nodes[i].c);
        if (++cnt % 10 == 0)
            printf("\n");
    }
    if (nodes.size() % 10 != 0)
        printf("\n");
}

// BFS
void solve()
{
    queue<Node> q;
    Node u(r1, c1, dir);
    memset(d, -1, sizeof(d));
    d[u.r][u.c][u.dir] = 0;
    q.push(u);
    while (!q.empty())
    {
        Node u = q.front();
        q.pop();
        if (u.r == r2 && u.c == c2)
        {
            print_ans(u);
            return;
        }
        for (int i = 0; i < 3; ++i)
        {
            Node v = walk(u, i);
            if (has_edge[u.r][u.c][u.dir][i] && inside(v.r, v.c) && d[v.r][v.c][v.dir] < 0)
            {
                q.push(v);
                d[v.r][v.c][v.dir] = d[u.r][u.c][u.dir] + 1;
                p[v.r][v.c][v.dir] = u;
            }
        }
    }
    printf("  No Solution Possible\n");
}

int main()
{
    while (input())
    {
        cout << maze << endl;
        solve();
    }
    return 0;
}
