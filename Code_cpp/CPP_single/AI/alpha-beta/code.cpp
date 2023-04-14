#include <iostream>
#define HUMAN 1
#define COMPUTER 0
#define N 3
using namespace std;
char A[N][N] = {'_', '_', '_', '_', '_', '_', '_', '_', '_'};
int Iswin()
{
    for (int i = 0; i < 3; i++)
    {
        if (A[i][0] == 'X' && A[i][1] == 'X' && A[i][2] == 'X')
        {
            return -1;
        }
        if (A[i][0] == 'O' && A[i][1] == 'O' && A[i][2] == 'O')
        {
            return 1;
        }
        if (A[0][i] == 'X' && A[1][i] == 'X' && A[2][i] == 'X')
        {
            return -1;
        }
        if (A[0][i] == 'O' && A[1][i] == 'O' && A[2][i] == 'O')
        {
            return 1;
        }
    }
    if (A[0][0] == 'X' && A[1][1] == 'X' && A[2][2] == 'X')
        return -1;
    if (A[0][0] == 'O' && A[1][1] == 'O' && A[2][2] == 'O')
        return 1;
    if (A[0][2] == 'X' && A[1][1] == 'X' && A[2][0] == 'X')
        return -1;
    if (A[0][2] == 'O' && A[1][1] == 'O' && A[2][0] == 'O')
        return 1;
    return 0;
}

void print()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            cout << A[i][j] << " ";
        cout << endl;
    }
    cout << endl
         << endl;
}
int Havespace()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            if (A[i][j] == '_')
                return 1;
    }
    return 0;
}

int alphabeta(int Player, int Nextplayer, int alpha, int beta)
{
    int win = Iswin();
    if (win != 0)
        return win;
    if (!Havespace())
        return 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (A[i][j] == '_')
            {
                if (Player == HUMAN)
                    A[i][j] = 'X';
                else
                    A[i][j] = 'O';
                int tmp = alphabeta(Nextplayer, Player, alpha, beta);
                A[i][j] = '_';
                if (Player == COMPUTER)
                { //当前玩家是电脑
                    if (tmp > alpha)
                        alpha = tmp;
                    if (alpha >= beta)
                        return beta; // β剪枝。
                }
                else
                { // 当前玩家是人类
                    if (tmp < beta)
                        beta = tmp;
                    if (beta <= alpha)
                        return alpha; // α剪枝
                }
            }
        }
    }
    if (Player == COMPUTER)
        return alpha;
    else
        return beta;
}

int trans(int i, int j)
{
    if (i == 0 && j == 0)
        return 0;
    else if (i == 0 && j == 1)
        return 1;
    else if (i == 0 && j == 2)
        return 2;
    else if (i == 1 && j == 0)
        return 3;
    else if (i == 1 && j == 1)
        return 4;
    else if (i == 1 && j == 2)
        return 5;
    else if (i == 2 && j == 0)
        return 6;
    else if (i == 2 && j == 1)
        return 7;
    else
        return 8;
}

int Computermove()
{
    int temp = -1000, Y;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (A[i][j] == '_')
            {
                A[i][j] = 'O';
                int tmp = alphabeta(HUMAN, COMPUTER, -2, 2); // tmp={-1,0,1}  //返回-1，代表人类赢   // 返回0，代表平局     //返回1，代表电脑赢
                A[i][j] = '_';
                if (tmp > temp)
                {
                    temp = tmp;
                    Y = trans(i, j);
                }
            }
        }
    }
    return Y;
}

int main()
{
    int m, n;
    int t;
    int Nextmove = HUMAN;
    cout << "输入1你先走，输入O电脑先走:  ";
    cin >> t;
    cout << endl;
    if (t == 1)
        Nextmove = HUMAN;
    else
        Nextmove = COMPUTER;
    while (!Iswin() && Havespace())
    {
        if (Nextmove == HUMAN && Havespace())
        {
            cout << "输入放入棋子的位置:  ";
            cin >> m >> n;
            A[m][n] = 'X';
            print();
            Nextmove = COMPUTER;
        }
        if (Nextmove == COMPUTER && Havespace())
        {
            int key = Computermove();
            if (key == 0)
            {
                A[0][0] = 'O';
                cout << "电脑决定下在: "
                     << "(0,0)" << endl;
            }
            else if (key == 1)
            {
                A[0][1] = 'O';
                cout << "电脑决定下在: "
                     << "(0,1)" << endl;
            }
            else if (key == 2)
            {
                A[0][2] = 'O';
                cout << "电脑决定下在: "
                     << "(0,2)" << endl;
            }
            else if (key == 3)
            {
                A[1][0] = 'O';
                cout << "电脑决定下在: "
                     << "(1,0)" << endl;
            }
            else if (key == 4)
            {
                A[1][1] = 'O';
                cout << "电脑决定下在: "
                     << "(1,1)" << endl;
            }
            else if (key == 5)
            {
                A[1][2] = 'O';
                cout << "电脑决定下在: "
                     << "(1,2)" << endl;
            }
            else if (key == 6)
            {
                A[2][0] = 'O';
                cout << "电脑决定下在: "
                     << "(2,0)" << endl;
            }
            else if (key == 7)
            {
                A[2][1] = 'O';
                cout << "电脑决定下在: "
                     << "(2,1)" << endl;
            }
            else
            {
                A[2][2] = 'O';
                cout << "电脑决定下在: "
                     << "(2,2)" << endl;
            }
            print();
            Nextmove = HUMAN;
        }
    }
    if (Iswin() == 1)
        cout << "失败" << endl;
    if (Iswin() == 0)
        cout << "平局" << endl;
    if (Iswin() == -1)
        cout << "胜利" << endl;

    system("pause");
}
