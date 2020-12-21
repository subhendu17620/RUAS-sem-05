#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void checkReceivedData(char *);
void crc(char *, char *);
void divide(char *, char *, char *);
void xor (char *, char *, char *);
void leftShift(char *);
void appendZeros(char *, char *, int);

int main()
{
    // defining variables to store user input
    int choice;
    char *data = malloc(100 * sizeof(*data));

    // defining generating polynomials
    char crc8[] = "100000111";
    char crc10[] = "11000110101";
    char crc16[] = "10001000000100001";
    char crc32[] = "100000100110000010001110110110111";

    // gathering input from user
    printf("Choose the generator polynomial:\n1) CRC-8\n2) CRC-10\n3) CRC-16\n4) CRC-32\nEnter choice: ");
    scanf("%d", &choice);

    printf("Enter data: ");
    scanf("%s", data);

    // calculating CRC based on user input
    switch (choice)
    {
    case 1:
        crc(data, crc8);
        checkReceivedData(crc8);
        break;
    case 2:
        crc(data, crc10);
        checkReceivedData(crc10);
        break;
    case 3:
        crc(data, crc16);
        checkReceivedData(crc16);
        break;
    case 4:
        crc(data, crc32);
        checkReceivedData(crc32);
        break;
    default:
        printf("Enter valid Choice !!");
        exit(-1);
    }
}

/**
 * Calculates the CRC and prints the resulting data that has to be
 * transmitted.
 * @param src the data for which the CRC has to be calculated.
 * @param gp the generating polynomial that has to be used for
 * calculating the CRC
 */
void crc(char *src, char *gp)
{
    // appending zeros to the data
    int dataLen = strlen(src) + strlen(gp) - 1;
    char *data = malloc(dataLen * sizeof(*data));
    appendZeros(src, data, dataLen);

    // defining the variable that will store remainder at the end of the
    // division and initializing it.
    // the length of the dividend is the length of the generating polynomial
    char *dividend = malloc(strlen(gp) * sizeof(*dividend));

    // copying the first few bits of data to dividend. the number of
    // bits copied is the length of the generating polynomial
    strncpy(dividend, data, strlen(gp));

    // dividing the data with gp using pen and paper approach
    // the remainder is stored in the `dividend`
    divide(data, gp, dividend);

    // printing result
    printf("data to be transmitted: %s%s\n", src, dividend);
}

/**
 * Divides the data with the generating polynomial.
 * 
 * @param data the data to be divided
 * @param poly the generating polynomial
 * @param dividend contains the first n bits of data, where
 * n is the length of the generating polynomial. At the end
 * of the division process, it contains the remainder.
 */
void divide(char *data, char *poly, char *dividend)
{

    // calculating remainder by dividing the data with the polynomial
    // if the first bit of the dividend is 1, then the bits of the dividend
    // and the generating polynomial is XORed, and the result is stored in the
    // dividend. the dividend is then left shifted.
    // if the first bit of the dividend is 0, the dividend is left shifted.
    // at the end, the last bit of the dividend is replaced with the next
    // bit of the data.
    // this approach is the same as the pen and paper approach in dividing
    // two bit strings.
    for (int i = 0; i < strlen(data) - strlen(poly) + 1; i++)
    {
        // first bit is 1, XORing
        if (dividend[0] == '1')
        {
            xor(dividend, poly, dividend);
        }

        // left shifting (to make space to bring the next bit down,
        // in the pen and paper approach)
        leftShift(dividend);

        // bringing the next bit down.
        dividend[strlen(poly) - 1] = data[i + strlen(poly)];
    }
}

/**
 * Performs XOR between two bit strings.
 * 
 * @param a the first bit string.
 * @param b the second bit string.
 * @param res the result is stored here.
 */
void xor (char *a, char *b, char *res) {
    int x, y;
    for (int i = 0; i < strlen(b); i++)
    {
        // converting a[i] char to corresponding int
        x = a[i] - '0';

        // converting b[i] char to corresponding int
        y = b[i] - '0';

        // applying xor (xor operator can only be applied on int)
        res[i] = (x ^ y);

        // converting the int back into a char
        res[i] += '0';
    }
}

    /**
 * Left shifts a bitstring by 1 bit.
 * 
 * @param input the bitstring to left shift
 */

    void leftShift(char *input)
{
    // left shifting
    for (int i = 1; i < strlen(input); i++)
    {
        input[i - 1] = input[i];
    }

    // the last element in the bit string should be 0
    input[strlen(input) - 1] = 0;
}

/**
 * Appends zeros to a bit string
 * 
 * @param src the bit string containing the data.
 * @param dest the bit string which will contain the 
 * appended data.
 * @param dataLen the length of the final data (`dest`)
 */
void appendZeros(char *src, char *dest, int dataLen)
{
    // copying src to the dest
    strcpy(dest, src);

    // appending the remaining space in dest with 0
    for (int i = strlen(src); i < dataLen; i++)
    {
        dest[i] = '0';
    }
}

/**
 * Asks the user for the recieved data and checks if 
 * it is correct or not.
 * 
 * @param gp the generating polynomial to use.
 */
void checkReceivedData(char *gp)
{
    // getting user input
    char *receivedData = malloc(100 * sizeof(*receivedData));
    printf("Enter the received data: ");
    scanf("%s", receivedData);

    // calculating CRC
    // defining the variable that will store remainder at the end of the
    // division and initializing it.
    // the length of the dividend is the length of the generating polynomial
    char *dividend = malloc(strlen(gp) * sizeof(*dividend));

    // copying the first few bits of data to dividend. the number of
    // bits copied is the length of the generating polynomial
    strncpy(dividend, receivedData, strlen(gp));

    // dividing the data with gp using pen and paper approach
    // the remainder is stored in the `dividend`
    divide(receivedData, gp, dividend);

    // checking if the resultant remainder (which is stored in `dividend`)
    // is 0 or not. the string is converted to an int using the function
    // `atoi`.
    if (atoi(dividend) == 0)
        printf("Received data is correct\n");
    else
        printf("Received data is incorrect\n");
}
