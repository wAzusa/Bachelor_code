#include <bits/stdc++.h>
using namespace std;

const double PI = 3.14;

int main()
{
    int h, r;
    cin >> h >> r;
    double v = PI * r * r * h / 1000;
    int num = ceil(20 / v);
    cout << num << endl;
    system("pause");
    return 0;
}