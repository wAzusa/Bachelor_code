#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

const int maxn = 1000 + 5;

// 并查集
int pa[256];
int findset(int u) { return pa[u] != u ? pa[u] = findset(pa[u]) : u; }

int c[256], deg[256];

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int n;
        string w;
        memset(c, 0, sizeof(c));
        memset(deg, 0, sizeof(deg));
        cin >> n;
        for (int ch = 'a'; ch <= 'z'; ch++)
            pa[ch] = ch; // 初始化并查集
        int cc = 26;     // 26个连通块
        for (int i = 0; i < n; i++)
        {
            cin >> w;
            int c1 = w[0], c2 = w[w.size() - 1];
            deg[c1]++;
            deg[c2]--;
            c[c1] = 1;
            c[c2] = 1;
            int s1 = findset(c1), s2 = findset(c2);
            if (s1 != s2)
            {
                pa[s1] = s2;
                cc--;
            }
        }

        vector<int> v;
        for (int ch = 'a'; ch <= 'z'; ch++)
        {
            if (!c[ch])
                cc--;
            else if (deg[ch])
                v.push_back(deg[ch]);
        }
        bool ok = false;
        if (cc == 1 && (v.empty() || (v.size() == 2 && (v[0] == 1 || v[0] == -1))))
            ok = true;
        if (ok)
            cout << "Ordering is possible." << endl;
        else
            cout << "The door cannot be opened." << endl;
    }
    system("pause");
    return 0;
}