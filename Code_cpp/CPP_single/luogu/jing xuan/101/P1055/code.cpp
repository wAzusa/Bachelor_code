#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s;
    cin >> s;
    int a[10];
    int j = 0;
    for (int i = 0; i < 13; i++)
    {
        a[j++] = s[i] - 48;
        if (s[i] == '-')
            --j;
    }
    int sum = 0;
    for (int i = 1; i <= 9; i++)
        sum += a[i - 1] * i;
    sum = sum % 11;
    if (sum == a[9])
        cout << "Right" << endl;
    else if (sum == 10 && s[12] == 'X')
        cout << "Right" << endl;
    else
    {
        if (sum != 10)
        {
            s[12] = (char)sum + 48;
            cout << s << endl;
        }
        else if (sum == 10)
        {
            s[12] = 'X';
            cout << s << endl;
        }
    }
    system("pause");
    return 0;
}