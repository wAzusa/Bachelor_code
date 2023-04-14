#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, a[1001] = {0}, b[1001] = {0};
    cin >> n;
    a[0] = 1;
    b[0] = 1;
    for (int i = 2; i <= n; ++i)
    {
        for (int j = 0; j < 100; ++j)
            b[j] *= i;
        for (int j = 0; j < 100; ++j)
        {
            if (b[j] > 9)
            {
                b[j + 1] += b[j] / 10;
                b[j] %= 10;
            }
        }
        for (int j = 0; j < 100; ++j)
        {
            a[j] += b[j];
            if (a[j] > 9)
            {
                a[j + 1] += a[j] / 10;
                a[j] %= 10;
            }
        }
    }
    int exp = 100;
    while (!a[exp])
        --exp;
    for (int i = exp; i >= 0; --i)
        printf("%d", a[i]);
    system("pause");
    return 0;
}