#include <iostream>
#include <cstring>

using namespace std;

const int maxn = 100 + 10;
char pic[maxn][maxn];
int idx[maxn][maxn], m, n;

void dfs(int r, int c, int id)
{
    if (r < 0 || r >= m || c < 0 || c >= n)
        return;
    if (pic[r][c] != '@' || idx[r][c] != 0)
        return;
    idx[r][c] = id; // 为连通分量赋上编号
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            if (i != 0 || j != 0)
                dfs(r + i, c + j, id);
}

int main()
{

    while (scanf("%d%d", &m, &n) == 2 && m && n)
    {
        int id = 0;
        memset(idx, 0, sizeof(idx));
        for (int i = 0; i < m; i++)
            scanf("%s", pic[i]);
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (idx[i][j] == 0 && pic[i][j] == '@')
                    dfs(i, j, ++id);
        cout << id << endl;
    }
    return 0;
}
