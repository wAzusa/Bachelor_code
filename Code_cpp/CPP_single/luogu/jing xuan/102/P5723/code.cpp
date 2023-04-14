#include <iostream>
#include <math.h>
using namespace std;

int main()
{
    int l, sum = 0, a[1005] = {0}, exp = 1, num = 0, n = 1, sign = 1;
    cin >> l;
    while (++n && sign)
    {
        exp = 1;
        int n1 = (int)sqrt((double)n);
        for (int i = 2; i <= n1; ++i)
        {
            if (n % i == 0)
            {
                exp = 0;
                break;
            }
        }
        if (exp == 1)
        {
            if ((sum + n) > l)
                sign = 0;
            else
            {
                a[num++] = n;
                sum += n;
            }
        }
    }
    for (int i = 0; i < num; ++i)
        cout << a[i] << endl;
    cout << num << endl;
    system("pause");
    return 0;
}