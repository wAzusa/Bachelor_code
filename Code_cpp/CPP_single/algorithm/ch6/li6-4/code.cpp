#include <cstdio>
#include <string.h>
using namespace std;

const int maxn = 10000 + 50;
char s[maxn];
int cur, last, NEXT[maxn];

int main()
{
    while (scanf("%s", s + 1) == 1)
    {
        cur = 0;
        NEXT[0] = 0;
        int n = strlen(s + 1);
        for (int i = 1; i <= n; i++)
        {
            char ch = s[i];
            if (ch == '[')
                cur = 0;

            else if (ch == ']')

                cur = last;

            else
            {
                NEXT[i] = NEXT[cur];
                NEXT[cur] = i;
                if (last == cur)
                    last = i;
                cur = i;
            }
        }
        for (int i = NEXT[0]; i != 0; i = NEXT[i])

            printf("%c", s[i]);

        printf("\n");
    }
    return 0;
}