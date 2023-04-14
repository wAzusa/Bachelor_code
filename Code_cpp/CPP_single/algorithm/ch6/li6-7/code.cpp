#include <iostream>
#include <cstdio>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;

const int maxn = 256;
char s[maxn]; // 输入

struct Node
{
    int val;
    bool have_valued;
    Node *left, *right;
    Node() : have_valued(false), left(NULL), right(NULL) {}
};

Node *root;
bool failed;

Node *newnode()
{
    return new Node();
}

void addnode(int v, char *s)
{
    int n = strlen(s);
    Node *u = root;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == 'L')
        {
            if (u->left == NULL)
                u->left = newnode();
            u = u->left;
        }
        else if (s[i] == 'R')
        {
            if (u->right == NULL)
                u->right = newnode();
            u = u->right;
        }
    }
    if (u->have_valued == true)
        failed = true;
    u->val = v;
    u->have_valued = true;
}

void remove_tree(Node *);
// 读入输入建立结点
bool read_input()
{
    failed = false;
    remove_tree(root);
    root = newnode();
    for (;;)
    {
        if (!scanf("%s", s))
            return false;
        if (!strcmp(s, "()"))
            break;
        int v;
        sscanf(&s[1], "%d", &v);
        addnode(v, strchr(s, ',') + 1);
    }
    return true;
}

// 释放二叉树空间
void remove_tree(Node *root)
{
    if (root == NULL)
        return;
    remove_tree(root->left);
    remove_tree(root->right);
    delete root;
}

// 宽度优先搜索便利；
bool bfs(vector<int> &ans)
{
    queue<Node *> q;
    ans.clear();
    q.push(root);
    while (!q.empty())
    {
        Node *u = q.front();
        q.pop();
        if (!u->have_valued)
            return false;
        ans.push_back(u->val);
        if (u->left != NULL)
            q.push(u->left);
        if (u->right != NULL)
            q.push(u->right);
    }
    return true;
}

int main()
{
    vector<int> ans;
    read_input();
    bfs(ans);
    int n = ans.size();
    if (failed)
        cout << -1;
    for (int i = 0; i < n; i++)
        cout << ans[i] << " ";

    system("pause");
    return 0;
}