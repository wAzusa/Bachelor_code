#include <iostream>
#include <string>

using namespace std;

const int pixel = 1024;
const int maxn = 10000;
char s[maxn];

struct Node
{
    char color;
    Node *ch1, *ch2, *ch3, *ch4;
    Node() : color('e'), ch1(NULL), ch2(NULL), ch3(NULL), ch4(NULL) {}
};

// 建树，四叉树只需先序遍历就可以确定
Node *build(char *s, int &pos)
{
    Node *root = new Node();
    root->color = s[pos++];
    if (root->color == 'p')
    {
        root->ch1 = build(s, pos);
        root->ch2 = build(s, pos);
        root->ch3 = build(s, pos);
        root->ch4 = build(s, pos);
    }
    return root;
}

// 将两颗四叉树相加至第一棵树
void Plus(Node *Tree1_root, Node *Tree2_root)
{
    if (Tree1_root->color == 'f')
        return;
    else if (Tree2_root->color == 'f')
    {
        Tree1_root->color = 'f';
        Tree1_root->ch1 = Tree1_root->ch2 = Tree1_root->ch3 = Tree1_root->ch4 = NULL;
    }
    else if (Tree2_root->color == 'p')
    {
        if (Tree1_root->color == 'e')
        {
            Tree1_root->ch1 = Tree2_root->ch1;
            Tree1_root->ch2 = Tree2_root->ch2;
            Tree1_root->ch3 = Tree2_root->ch3;
            Tree1_root->ch4 = Tree2_root->ch4;
        }
        Tree1_root->color = 'p';
        Plus(Tree1_root->ch1, Tree2_root->ch1);
        Plus(Tree1_root->ch2, Tree2_root->ch2);
        Plus(Tree1_root->ch3, Tree2_root->ch3);
        Plus(Tree1_root->ch4, Tree2_root->ch4);
    }
}

int Pixel(Node *Tree1, int level)
{
    int sum = 0;
    if (Tree1 == NULL)
        return 0;
    if (Tree1->color == 'f')
        sum += 1024 / level;
    sum += Pixel(Tree1->ch1, level * 4);
    sum += Pixel(Tree1->ch2, level * 4);
    sum += Pixel(Tree1->ch3, level * 4);
    sum += Pixel(Tree1->ch4, level * 4);

    return sum;
}

int main()
{
    int n;
    cin >> n;
    while (n--)
    {
        int p = 0;
        cin >> s;
        Node *Tree1 = build(s, p);
        p = 0;
        cin >> s;
        Node *Tree2 = build(s, p);
        Plus(Tree1, Tree2);
        cout << "Pixel:  " << Pixel(Tree1, 1) << endl;
    }
    system("pause");
    return 0;
}
