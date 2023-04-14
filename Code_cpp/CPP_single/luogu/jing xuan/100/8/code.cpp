#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s;
    cin >> s;
    int len = s.size();
    for (int i = 0; i < len; ++i)
    {
        cout << s[len - 1 - i];
    }
    cout << endl;
    system("pause");
    return 0;
}