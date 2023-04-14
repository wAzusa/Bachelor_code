#include <iostream>
#include <math.h>
using namespace std;

int main()
{
    double a, b, c;
    cin >> a >> b >> c;
    double p, result;
    p = (a + b + c) / 2;
    result = sqrt(p * (p - a) * (p - b) * (p - c));
    printf("%.1lf\n", result);
    system("pause");
    return 0;
}