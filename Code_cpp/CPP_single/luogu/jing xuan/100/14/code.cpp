#include <iostream>
using namespace std;

const int pen = 1 * 10 + 9;
int main()
{
    int a, b;
    cin >> a >> b;
    int mon = a * 10 + b;
    int num = mon / pen;
    cout << num << endl;
    system("Pause");
    return 0;
}