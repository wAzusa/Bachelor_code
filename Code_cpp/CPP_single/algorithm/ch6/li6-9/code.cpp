#include <iostream>
using namespace std;

bool solve(int &w)
{
    int w1, l1, w2, l2;
    cin >> w1 >> l1 >> w2 >> l2;
    bool b1 = true, b2 = true;
    if (!w1)
        b1 = solve(w1);
    if (!w2)
        b2 = solve(w2);
    w = w1 + w2;
    return b1 && b2 && (w1 * l1 == w2 * l2);
}

int main()
{
    int N, W = 0;
    cin >> N;
    while (N--)
    {
        if (solve(W))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
        if (N)
            cout << endl;
    }
    system("pause");
    return 0;
}