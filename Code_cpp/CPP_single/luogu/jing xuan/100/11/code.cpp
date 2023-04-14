#include <iostream>
#include <iomanip>
using namespace std;

const int gar_cla = 10;

int main()
{
    int s, v;
    cin >> s >> v;
    int sum;
    if (s % v)
        sum = s / v + gar_cla + 1;
    else
        sum = s / v + gar_cla;
    int h, m;
    h = sum / 60;
    m = sum % 60;
    if (!m)
    {
        if (h <= 8)
            h = 8 - h;
        else
            h = 24 - (h - 8);
    }
    else if (m)
    {
        h++;
        if (h <= 8)
            h = 8 - h;
        else
            h = 24 - (h - 8);
    }
    m = 60 - m;

    cout << setfill('0') << setw(2) << h << ":" << setfill('0') << setw(2) << m << endl;
    system("pause");
    return 0;
}