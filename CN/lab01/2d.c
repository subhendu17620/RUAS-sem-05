#include <stdio.h>
int oddParity(int);
int evenParity(int);

void main()
{
    int n, ch;

    // getting size of data
    printf("Enter size of data: ");
    scanf("%d", &n);

    int input[n + 5][n + 5], countC[n], countR[n];
    // getting data
    printf("Enter data: \n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &input[i][j]);
        }
    }

    // calculating number 1's in rows and columns
    for (int i = 0; i < n; i++)
    {
        countR[i] = 0;
        countC[i] = 0;
        for (int j = 0; j < n; j++)
        {
            if (input[i][j] == 1)
            {
                countR[i]++;
            }
            if (input[j][i] == 1)
            {
                countC[i]++;
            }
        }
    }

    // getting parity option
    printf(" Choose Parity: ");
    printf("\n 1. Odd Parity \n 2. Even Parity");
    printf("\nEnter option: ");
    scanf("%d", &ch);

    switch (ch)
    {
    case 1:
        // inserting parity bits as last row and last column for odd parity
        for (int i = 0; i < n; i++)
        {
            input[i][n] = oddParity(countR[i]);
            input[n][i] = oddParity(countC[i]);
        }

        break;
    case 2:
        // inserting parity bits as last row and last column for even parity
        for (int j = 0; j < n; j++)
        {
            input[j][n] = evenParity(countR[j]);
            input[n][j] = evenParity(countC[j]);
        }

        break;
    default:
        printf("Enter valid options!");
        break;
    }

    
    // output for data to be senr
    printf("Data to be transmitted: \n");
    for (int i = 0; i < n + 1; i++)
    {
        for (int j = 0; j < n + 1; j++)
        {
            printf("%d ", input[i][j]);
        }
        printf("\n");
    }
}

/*
* Calculates the Even-Parity bits for the given number of 1's in a data
* Args:
*   count(int): The number of 1's in a data
* Returns:
*   int: Parity bit
*/
int oddParity(int count)
{

    if (count % 2 == 0)
    {
        return 1;
    }

    return 0;
}
/*
* Calculates the Even-Parity bits for the given number of 1's in a data
* Args:
*   count(int): The number of 1's in a data
* Returns:
*   int: Parity bit
*/
int evenParity(int count)
{

    if (count % 2 == 0)
    {
        return 0;
    }

    return 1;
}