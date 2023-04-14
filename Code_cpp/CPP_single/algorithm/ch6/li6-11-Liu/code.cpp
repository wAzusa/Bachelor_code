#include <iostream>
#include <cstring>

using namespace std;

const int maxn = 2000;
const int len = 32;
char s[maxn];
int buf[maxn][maxn], cnt;

// 将字符串s[p...]导出到以（r，c）为左上角，边长为w的缓冲区
// 2 1
// 3 4
void draw(const char *s, int &p, int r, int c, int w)
{
    char x = s[p++];
    if (x == 'p')
    {
        draw(s, p, r, c + w / 2, w / 2);
        draw(s, p, r, c, w / 2);
        draw(s, p, r + w / 2, c, w / 2);
        draw(s, p, r + w / 2, c + w / 2, w / 2);
    }
    else if (x == 'f')
    {
        for (int i = r; i < r + w; i++)
            for (int j = c; j < c + w; j++)
            {
                if (buf[i][j] == 0)
                {
                    buf[i][j] = 1;
                    cnt++;
                }
            }
    }
}

int main()
{
    int N;
    cin >> N;
    while (N--)
    {
        cnt = 0;
        memset(buf, 0, sizeof(buf));
        for (int m = 0; m < 2; m++)
        {
            cin >> s;
            int pos = 0;
            draw(s, pos, 0, 0, len);
        }
        cout << "Pixel:  " << cnt << endl;
    }
    system("pause");
    return 0;
}