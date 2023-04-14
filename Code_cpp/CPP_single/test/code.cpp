#include <iostream>
#include <string>

using namespace std;

struct node
{
    char color;
    node *n1, *n2, *n3, *n4;
    node() : color('e'), n1(NULL), n2(NULL), n3(NULL), n4(NULL) {}
};

node *build(string &s, int &pos)
{
    node *root = new node();
    root->color = s[pos];
    if (s[pos] == 'p')
    {
        pos++;
        root->n1 = build(s, pos);
        pos++;
        root->n2 = build(s, pos);
        pos++;
        root->n3 = build(s, pos);
        pos++;
        root->n4 = build(s, pos);
    }
    return root;
}

void merge(node *tree1, node *tree2)
{
    if (tree2->color == 'f')
    {
        tree1->color = 'f';
        tree1->n1 = tree1->n2 = tree1->n3 = tree1->n4 = NULL;
    }
    else if (tree2->color == 'p' && tree1->color != 'f')
    {
        if (tree1->color == 'e')
        {
            tree1->n1 = tree2->n1;
            tree1->n2 = tree2->n2;
            tree1->n3 = tree2->n3;
            tree1->n4 = tree2->n4;
        }
        tree1->color = 'p';
        merge(tree1->n1, tree2->n1);
        merge(tree1->n2, tree2->n2);
        merge(tree1->n3, tree2->n3);
        merge(tree1->n4, tree2->n4);
    }
}

int cnt(node *tree, int level)
{
    int sum = 0;
    if (tree == NULL)
        return 0;
    if (tree->color == 'f')
        sum += 1024 / level;
    sum += cnt(tree->n1, level * 4);
    sum += cnt(tree->n2, level * 4);
    sum += cnt(tree->n3, level * 4);
    sum += cnt(tree->n4, level * 4);
    return sum;
}

int main()
{
    int n;
    cin >> n;
    while (n--)
    {
        string s;
        cin >> s;
        int pos = 0;
        node *tree1 = build(s, pos);
        cin >> s;
        pos = 0;
        node *tree2 = build(s, pos);
        merge(tree1, tree2);
        cout << "There are " << cnt(tree1, 1) << " black pixels." << endl;
    }
    system("pause");
    return 0;
}