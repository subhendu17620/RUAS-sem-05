
#include <stdio.h>

int oddParity(int);
int evenParity(int);

void main()
{
    int n, ch, parity, count = 0;

    // getting number of data bits
    printf("Enter number of data bits: ");
    scanf("%d", &n);

    int input[n];

    // getting data bits and storing it in an array
    printf("Enter data bits: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &input[i]);
    }

    // getting parity option
    printf(" Choose Parity: ");
    printf("\n 1. Odd Parity \n 2. Even Parity");
    printf("\nEnter option: ");
    scanf("%d", &ch);

    // calculating number 1's in the data bit
    for (int i = 0; i < n; i++)
    {
        if (input[i] == 1)
        {
            count++;
        }
    }

    switch (ch)
    {
    case 1:
        // getting parity bit for Odd
        parity = oddParity(count);
        break;
    case 2:
        // getting parity bit for Even
        parity = evenParity(count);
        break;

    default:
        printf("Enter a Valid Option!!");
        break;
    }

    printf("Parity Bit: %d", parity);

    // appending parity bit to the data
    input[n] = parity;

    //printing Data to be transmitted
    printf("\nMessage to be sent: ");
    for (int i = 0; i < n + 1; i++)
    {
        printf("%d ", input[i]);
    }
    printf("\n");
}

/*
* Calculates the Odd-Parity bits for the given number of 1's in a data
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