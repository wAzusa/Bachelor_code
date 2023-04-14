#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 1000 + 5;

int main()
{
    int a[maxn];
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    sort(a, a + n);
    double sum = 0;
    for (int i = 1; i < n - 1; ++i)
        sum += a[i];
    double res = sum / (n - 2);
    printf("%.2lf\n", res);
    system("pause");
    return 0;
}