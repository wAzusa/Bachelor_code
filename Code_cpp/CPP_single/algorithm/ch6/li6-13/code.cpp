#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

unordered_map<char, string> tran_Binary{// 将16进制转换为2进制
                                        {'0', "0000"},
                                        {'1', "0001"},
                                        {'2', "0010"},
                                        {'3', "0011"},
                                        {'4', "0100"},
                                        {'5', "0101"},
                                        {'6', "0110"},
                                        {'7', "0111"},
                                        {'8', "1000"},
                                        {'9', "1001"},
                                        {'A', "1010"},
                                        {'B', "1011"},
                                        {'C', "1100"},
                                        {'D', "1101"},
                                        {'E', "1110"},
                                        {'F', "1111"}};

map<int, char> result{{1, 'A'}, {3, 'J'}, {5, 'D'}, {4, 'W'}, {0, 'S'}, {2, 'K'}};

int moveC[][2]{{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

int H, W; // 行，列
int cnt;
vector<string> image;

// 遍历
void BFS(int i, int j, char s, int &ans)
{
    image[i][j] = (char)image[i][j] + 2;
    for (int k = 0; k < 4; ++k)
    {
        int ii = i + moveC[k][0];
        int jj = j + moveC[k][1];
        if (ii < 0 || jj < 0 || ii > H + 2 || jj > 4 * W + 2)
            continue;
        // 找到白洞
        if (image[ii][jj] == '0' && s == '1')
        {
            cnt++;
            BFS(ii, jj, '0', cnt);
        }
        // 继续走连通区域
        else if (s == image[ii][jj])
            BFS(ii, jj, s, cnt);
    }
}

int main()
{
    string line;
    int kase;
    while (scanf("%d%d", &H, &W) == 2 && H)
    {
        image.resize(H + 2);
        image.front() = string(4 * W + 2, '0');
        for (int i = 1; i <= H; ++i)
        {
            image[i] = "0";
            scanf("%s", line);
            for (auto c : line)
                image[i] += tran_Binary[c];
            image[i] += "0";
        }
        image.back() = string(4 * W + 2, '0');
        cnt = 0;
        string res = "";
        BFS(0, 0, '0', cnt);
        for (int i = 0; i < H + 2; ++i)
            for (int j = 0; j < 4 * W + 2; ++j)
            {
                if (image[i][j] == '1')
                    cnt = 0;
                BFS(i, j, '1', cnt);
                res += result[cnt];
            }
        sort(res.begin(), res.end());
        cout << "Case :" << ++kase << " " << res << endl;
    }
}
