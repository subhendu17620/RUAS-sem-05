#include <stdio.h>

#define BLOCK_SIZE 8
#define SIZE 5

int sum[10][20];
int last_index = 0, last_known_len = 0;

// function prototypes
void reverse_array(int[], int, int);
long array_joiner(int[], int, int);
int binary_adder(int, int, int);

int main()
{
    int data[BLOCK_SIZE * SIZE];

    printf("Enter Received Data: ");
    for (size_t i = 0; i < (BLOCK_SIZE * SIZE); i++)
    {
        scanf("%d", &data[i]);
    }

    // printing each block
    for (size_t i = 0; i < SIZE - 1; i++)
    {
        printf("Block %ld : ", i + 1);
        for (size_t j = BLOCK_SIZE * (i + 1); j < BLOCK_SIZE * (i + 2); j++)
        {
            printf("%d", data[j]);
        }
        printf("\n");
    }

    //printing checksum
    printf("Checksum : ");
    for (size_t i = 0; i < BLOCK_SIZE; i++)
    {
        printf("%d ", data[i]);
    }

    // divding 32 bit data into block size and storing in array
    long blocks[SIZE];
    for (size_t i = 0; i < SIZE; i++)
    {
        blocks[i] = array_joiner(data, BLOCK_SIZE * i, BLOCK_SIZE * (i + 1));
    }

    // adding first two blocks and storing in 0th postion of sum array
    binary_adder(blocks[0], blocks[1], 0);

    // adding remaining block and storing one after another
    for (int i = 2; i < SIZE; i++)
    {
        binary_adder(array_joiner(sum[i - 2], 0, last_known_len + 1), blocks[i], i - 1);
    }

    // depending on the block size adding carry bits with the remaining bits
    binary_adder(array_joiner(sum[last_index - 1], (last_known_len - BLOCK_SIZE + 1), last_known_len + 1), array_joiner(sum[last_index - 1], 0, (last_known_len - BLOCK_SIZE + 1)), last_index);

    int flag = 1;

    printf("\nSum of checksum and all blocks : ");
    for (size_t i = 0; i < BLOCK_SIZE; i++)
    {
        printf("%d ", sum[last_index - 1][i]);

        // checking if any value is other than 1
        // which means theres error in data
        if (sum[last_index - 1][i] == 0)
        {
            flag = 0;
        }
    }

    // if flag=1 , there's no error
    if (flag)
    {
        printf("\n NO ERROR in Data");
    }
    else
    {
        printf("\n ERROR in Data");
    }

    return 0;
}
/**
 * Reverses the array from start to end index
 * 
 * @param arr[]: array which needs to be reversed
 * @param start: start index
 * @param end: end index
 * 
 * return
 *      - 
 */
void reverse_array(int arr[], int start, int end)
{
    int temp;
    while (start < end)
    {
        temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}
/**
 * Returns a number (of long type) value joining from start index to end index from the given array
 * 
 * @param arr[]: array
 * @param start: start index
 * @param end: end index 
 * 
 * return :
 *      long : start - end-1
 * 
 */
long array_joiner(int arr[], int start, int end)
{
    long result = 0;
    for (int i = start; i < end; i++)
    {
        result = result * 10 + arr[i];
    }
    return result;
}

/**
 * Generates and stores the value of two binary number in sum array at given index
 * 
 * @param binary1: 1st binary number
 * @param binary2: 2nd binary number
 * @param n: index of sum array to store the result
 * 
 * return:
 *      - int : 0
 */
int binary_adder(int binary1, int binary2, int n)
{
    last_index++;
    int result[20];
    int i = 0, remainder = 0;

    // calculating binary addition and and storing  in sum[n]
    while (binary1 != 0 || binary2 != 0)
    {
        sum[n][i++] = (binary1 % 10 + binary2 % 10 + remainder) % 2;
        remainder = (binary1 % 10 + binary2 % 10 + remainder) / 2;
        binary1 = binary1 / 10;
        binary2 = binary2 / 10;
    }
    if (remainder != 0)
        sum[n][i++] = remainder;

    --i;
    // reversing the array as the value stored is reversed
    reverse_array(sum[n], 0, i);

    // updating length of last added value
    last_known_len = i;

    return 0;
}
// 1 1 0 1 0 0 1 1 1 1 0 0 1 1 0 0 1 1 1 1 0 0 0 0 1 0 1 0 1 0 1 1 1 1 0 0 0 0 1 0