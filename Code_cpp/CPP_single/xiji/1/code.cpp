#include <iostream>
#include <string>
using namespace std;
class student
{
public:
    string name;
    int m;
    int c;
    int e;
    int sum;
    void addstudent()
    {
        cin >> name >> c >> m >> e;
    }
    void showstudent()
    {
        cout << name << " " << sum;
    }
};
int main()
{
    int K, N;
    cin >> N;
    //为N名同学输入信息
    student s[10000];
    student temp;
    int i,j;
    for (i = 0; i <= N - 1; i++)
    {
        s[i].addstudent();
        s[i].sum = s[i].m + s[i].c + s[i].e;
    }
    cin >> K;
    //根据规则为同学排序
    for (i = 0; i <= N - 1; i++)
        for (j = i + 1; j <= N - 1; j++)
        {
            if (s[j].sum > s[i].sum)
            {
                temp = s[j];
                s[j] = s[i];
                s[i] = temp;
            }
            else if (s[j].sum == s[i].sum)
            {
                if (s[j].c > s[i].c)
                {
                    temp = s[j];
                    s[j] = s[i];
                    s[i] = temp;
                }
                else if (s[j].c == s[i].c)
                {
                    if (s[j].m > s[i].m)
                    {
                        temp = s[j];
                        s[j] = s[i];
                        s[i] = temp;
                    }
                    else if (s[j].m == s[i].m)
                    {
                        if (s[j].e > s[i].e)
                        {
                            temp = s[j];
                            s[j] = s[i];
                            s[i] = temp;
                        }
                        else if (s[j].e == s[i].e)
                        {
                            if (s[j].name < s[i].name)
                            {
                                temp = s[j];
                                s[j] = s[i];
                                s[i] = temp;
                            }
                        }
                    }
                }
            }
        }
    s[K - 1].showstudent();
    return 0;
}