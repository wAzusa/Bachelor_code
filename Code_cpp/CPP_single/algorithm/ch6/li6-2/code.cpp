#include <iostream>
#include <stack>
using namespace std;
const int MAX = 10000;
int n, target[MAX];
int main()
{
    while (scanf("%d", &n) == 1)
    {
        //注意scanf函数的返回值
        stack<int> s;
        int a = 1, b = 1;
        for (int i = 1; i <= n; i++)
            scanf("%d", &target[i]);
        int ok = 1;
        while (b <= n)
        {
            if (a == target[b])
            {
                a++;
                b++;
            }
            else if (!s.empty() && s.top() == target[b])
            {
                s.pop();
                b++;
            }
            else if (a <= n)
            {
                s.push(a++);
            }
            else
            {
                ok = 0;
                break;
            }
        }
        printf("%s\n", ok ? "yes" : "no");
    }
    return 0;
}