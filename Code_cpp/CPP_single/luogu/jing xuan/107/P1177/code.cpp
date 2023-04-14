//传统快排有三个问题
//1.标兵量选取随机
//2.小区间效率低
//3.有重复元素开销大
#include <iostream>
using namespace std;

void quick_sort(int *a, int begin, int end)
{
    int left = begin, right = end;
    int tmp = a[begin];
    if (begin > end)
        return;
    while (left < right)
    {
        while (a[right] >= tmp && right > left)
            --right;
        while (a[left] <= tmp && left < right)
            ++left;
        if (right > left)
        {
            int cha = a[right];
            a[right] = a[left];
            a[left] = cha;
        }
    }
    a[begin] = a[right];
    a[right] = tmp;
    quick_sort(a, begin, right - 1);
    quick_sort(a, right + 1, end);
    return;
}

int main()
{
    int N, a[10000000];
    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> a[i];
    int b = 0, e = N - 1;
    quick_sort(a, b, e);
    for (int i = 0; i < N; ++i)
        cout << a[i] << " ";
    cout << endl;
    system("pause");
    return 0;
}