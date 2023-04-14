#include <bits/stdc++.h>
using namespace std;

bool prime[10000000];

// 埃式筛选法制造素数表
bool isprime(int b)
{
    memset(prime, true, sizeof(prime));
    prime[1] = false; // 1不是素数；
    int n = sqrt(b);
    for (int i = 2; i <= n; ++i)
    {
        if (prime[i])
        {
            for (int j = 2; j <= b / i; ++j)
                // 质数的倍数绝对不是质数，把所有质数的倍数全部设为false
                prime[i * j] = false;
        }
    }
    return true;
}

bool isHWS(int n)
{
    int num = n, ans = 0;
    while (num)
    {
        ans = ans * 10 + num % 10;
        num /= 10;
    }
    if (n == ans)
        return true;
    else
        return false;
}

int main()
{
    int a, b;
    cin >> a >> b;

    // b<=10000000这个判断条件来自：除了11以外，一个数的位数是偶数的话，不可能为回文数素数。
    //  如果一个回文素数的位数是偶数，则它的奇数位上的数字和与偶数位上的数字和必然相等；
    //  根据数的整除性理论，容易判断这样的数肯定能被11整除，所以它就不可能是素数。
    if (b >= 10000000)
        b = 9999999;
    if (a % 2 == 0)
        ++a;
    if (a > b)
        return 0;
    isprime(b);
    for (int i = a; i <= b; i += 2)
    {
        if (isHWS(i) && prime[i])
            cout << i << endl;
    }
    system("pause");
    return 0;
}