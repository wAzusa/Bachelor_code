#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N;
    cin >> N;
    int a[40][40], r[40 * 40], c[40 * 40], col, row; // 标记每个数的行和列
    memset(a, -1, sizeof(a));
    a[1][(1 + N) / 2] = 1;
    r[1] = 1;
    c[1] = (1 + N) / 2;
    for (int i = 2; i <= N * N; ++i)
    {
        if (r[i - 1] == 1 && c[i - 1] != N)
        {
            col = c[i - 1];
            a[N][col + 1] = i;
            r[i] = N;
            c[i] = col + 1;
        }
        else if (r[i - 1] != 1 && c[i - 1] == N)
        {
            row = r[i - 1] - 1;
            a[row][1] = i;
            r[i] = row;
            c[i] = 1;
        }
        else if (r[i - 1] == 1 && c[i - 1] == N)
        {
            row = r[i - 1] + 1;
            col = c[i - 1];
            a[row][col] = i;
            r[i] = row;
            c[i] = col;
        }
        else
        {
            row = r[i - 1];
            col = c[i - 1];
            if (a[row - 1][col + 1] == -1)
            {
                a[row - 1][col + 1] = i;
                r[i] = row - 1;
                c[i] = col + 1;
                continue;
            }
            else
            {
                row = r[i - 1] + 1;
                col = c[i - 1];
                a[row][col] = i;
                r[i] = row;
                c[i] = col;
            }
        }
    }
    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= N; ++j)
            cout << a[i][j] << " ";
        cout << endl;
    }
    system("pause");
    return 0;
}