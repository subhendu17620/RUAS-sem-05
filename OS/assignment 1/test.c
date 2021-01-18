#include <stdio.h>
#include <stdlib.h>

unsigned short m, n;

void rand_matrix(unsigned short a[m][n], unsigned short b[m][n], unsigned short m, unsigned short n)
{

    printf("\nEnter elements of matrix 1:\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            a[i][j] = rand() % 100;
        }
    }
    printf("\nEnter elements of matrix 2:\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            b[i][j] = rand() % 100;
        }
    }
}
void add_matrix(unsigned short s[m][n], unsigned short a[m][n], unsigned short b[m][n], unsigned short m, unsigned short n)
{
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
        {
            s[m][n] = a[m][n] + b[m][n];
        }
}
void print_matrix(unsigned short a[m][n], unsigned short b[m][n], unsigned short s[m][n], unsigned short m, unsigned short n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("\t%hu", a[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("\t%hu", b[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("\t%hu", s[i][j]);
        }
        printf("\n");
    }
}
int main()
{

    printf("Enter the row dimension of the matrix : ");
    scanf("%hu", &m);
    printf("Enter the column dimension of the matrix : ");
    scanf("%hu", &n);
    unsigned short a[m][n], b[m][n], s[m][n];
    rand_matrix(a, b, m, n);
    add_matrix(s, a, b, m, n);
    print_matrix(a, b, s, m, n);
    return (0);
}
