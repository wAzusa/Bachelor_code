#include <stdio.h>
int main()
{
    int num1, num2, nu1, mu1, tu1, mu2, nu2, tu2;
    int i, j, k = 0, arrow1, arrow2;
    int s1[81][2] = {0}, s2[81][2] = {0}, s[8][8] = {0}, s3[81][2] = {0};
    scanf("%d", &num1);
    for (i = 0; i <= num1 - 1; i++)
        scanf("%d%d%d", &s1[i][0], &s1[i][1], &s1[i][2]);
    scanf("%d", &num2);
    for (i = 0; i <= num2 - 1; i++)
        scanf("%d%d%d", &s2[i][0], &s2[i][1], &s2[i][2]);
    for (arrow1 = 0; arrow1 <= num1 - 1; arrow1++)
    {
        mu1 = s1[arrow1][0];
        nu1 = s1[arrow1][1];
        tu1 = s1[arrow1][2];
        for (arrow2 = 0; arrow2 <= num2 - 1; arrow2++)
        {
            mu2 = s2[arrow2][0];
            nu2 = s2[arrow2][1];
            tu2 = s2[arrow2][2];
            if (nu1 == mu2)
            {
                s[mu1][nu2] += tu1 * tu2;
            }
        }
    }
    for (i = 0; i <= 8; i++)
        for (j = 0; j <= 8; j++)
        {
            if (s[i][j] != 0)
            {
                s3[k][0] = i;
                s3[k][1] = j;
                s3[k][2] = s[i][j];
                k++;
            }
        }
    for (i = 0; i < k; i++)
    {
        printf("%d %d %d\n", s3[i][0], s3[i][1], s[i][2]);
    }
    return 0;
}