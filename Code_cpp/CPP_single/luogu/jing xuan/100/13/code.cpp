#include <bits/stdc++.h>
using namespace std;

int main()
{
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    int init = a * 60 + b;
    int fin = c * 60 + d;
    int h, m;
    h = (fin - init) / 60;
    m = (fin - init) % 60;
    cout << h << " " << m << endl;
    system("pause");
    return 0;
}