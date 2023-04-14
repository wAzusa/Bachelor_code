#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

// 建立有向图，有无环为判断条件，无环有向图可建立拓扑排序

const int maxn = 200;

int c[maxn];       // c用作标记结点bfs过程，c[]为0则未访问，-1为正在访问，1为访问结束
int topo[maxn], t; // 存放拓扑排序
int G[maxn][maxn]; // 存放大小关系
int m, n;

// dfs
bool dfs(int u)
{
    c[u] = -1;
    for (int i = 1; i <= n; i++)
        if (G[u][i])
        {
            if (c[i] == -1) // 表示有环
                return false;
            if (!c[i] && !dfs(i))
                return false;
        }
    c[u] = 1;
    topo[t--] = u;
    return true;
}

bool topo_sort()
{
    t = n;
    memset(c, 0, sizeof(c));
    for (int i = 1; i <= n; ++i)
        if (!c[i])
            if (!dfs(i))
                return false;
    return true;
}

int main()
{
    while (scanf("%d%d", &n, &m) && n)
    {
        int a, b;
        memset(G, 0, sizeof(G));
        for (int i = 1; i <= m; ++i)
        {
            cin >> a >> b;
            G[a][b] = 1;
        }

        topo_sort();

        for (int i = 1; i < n; ++i)
            cout << topo[i] << " ";
        cout << topo[n];
        cout << endl;
    }
    system("pause");
    return 0;
}