#include <iostream>
#include <cstring>
using namespace std;

const int maxn = 1000000;
int sum[maxn];

void build(int p)
{
    int v;
    cin >> v;
    if (v == -1)
        return;
    sum[p] += v;
    build(p - 1);
    build(p + 1);
}

bool init()
{
    int v;
    cin >> v;
    if (v == -1)
        return false;
    memset(sum, 0, sizeof(sum));
    int p = maxn / 2;
    sum[p] += v;
    build(p - 1);
    build(p + 1);
    return true;
}

int main()
{
    while (init())
    {
        int num = 1;
        int fr = 0;
        while (sum[fr] == 0)
            fr++;
        cout << "Case " << num++ << ":" << endl;
        while (sum[fr] != 0)
            cout << sum[fr++] << " ";
        cout << "\n\n";
    }
    return 0;
}