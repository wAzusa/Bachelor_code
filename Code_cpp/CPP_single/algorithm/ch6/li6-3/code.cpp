#include <iostream>
#include <stack>
#include <string>
using namespace std;

struct Matrix
{
    int a;
    int b;
    Matrix(int a = 0, int b = 0) : a(a), b(b) {}
} m[26];
// 定义矩阵
stack<Matrix> s; // 定义Matrix类型的栈

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string name; // 矩阵名
        cin >> name;
        int k = name[0] - 'A';
        cin >> m[k].a >> m[k].b;
    } // 给相应矩阵赋值

    string expr;
    while (cin >> expr)
    {
        int sum = 0;
        bool corr = false;
        int len = expr.length();
        for (int i = 0; i < len; i++)
        {
            if (isalpha(expr[i]))
                s.push(m[expr[i] - 'A']);
            else if (expr[i] == ')')
            {
                Matrix M2 = s.top();
                s.pop();
                Matrix M1 = s.top();
                s.pop();
                if (M1.b != M2.a)
                {
                    corr = true;
                    break;
                }
                sum += M1.a * M1.b * M2.b;
                s.push(Matrix(M1.a, M2.b));
            }
        }
        if (corr)
            cout << "wrong" << endl;
        else
            cout << sum << endl;
    }
    return 0;
}
