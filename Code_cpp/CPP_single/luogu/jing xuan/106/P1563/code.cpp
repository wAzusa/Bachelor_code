#include <iostream>
#include <string>
using namespace std;

struct toy
{
    int dir;
    string occu;
} t[100000 + 5];

int r[2] = {1, -1}, l[2] = {-1, 1};

int main()
{
    int n, m;
    // 接收指令
    int a[100000 + 5], b[100000 + 5];
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
    {
        cin >> t[i].dir >> t[i].occu;
    }
    for (int i = 1; i <= m; ++i)
    {
        cin >> a[i] >> b[i];
    }
    int res = 1;
    for (int i = 1; i <= m; ++i)
    {
        int dir = a[i], num = b[i], ward, tmp;
        if (dir == 0)
        {
            ward = t[res].dir;
            tmp = res + l[ward] * num;
            if (tmp <= 0)
                res = tmp + n;
            else if (tmp > n)
                res = tmp - n;
            else
                res = tmp;
        }
        else if (dir == 1)
        {
            ward = t[res].dir;
            tmp = res + r[ward] * num;
            if (tmp <= 0)
                res = tmp + n;
            else if (tmp > n)
                res = tmp - n;
            else
                res = tmp;
        }
    }
    cout << t[res].occu << endl;
    system("pause");
    return 0;
}