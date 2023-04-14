#include <iostream>
using namespace std;

int main()
{
    float cole;
    int num_stu;
    cin >> cole >> num_stu;
    int cup = 2 * num_stu;
    float ave_cole = cole / num_stu;
    printf("%.3f\n%d\n", ave_cole, cup);
    system("pause");
    return 0;
}