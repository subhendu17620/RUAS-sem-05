#include <stdio.h>

#define BLOCK_SIZE 8
#define SIZE 4

int sum[10][20];
int last_index = 0, last_known_len = 0;
int checksum[BLOCK_SIZE];

// function prototypes
void reverse_array(int[], int, int);
long array_joiner(int[], int, int);
long generate_checksum(int);
int binary_adder(int, int, int);

int main()
{
    int data[BLOCK_SIZE * SIZE];

    // getting 32 bit long data
    printf("Enter Data: ");
    for (size_t i = 0; i < (BLOCK_SIZE * SIZE); i++)
    {
        scanf("%d", &data[i]);
    }

    // printing each block
    for (size_t i = 0; i < SIZE; i++)
    {
        printf("Block %ld : ", i + 1);
        for (size_t j = BLOCK_SIZE * i; j < BLOCK_SIZE * (i + 1); j++)
        {
            printf("%d", data[j]);
        }
        printf("\n");
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

    // printing result => last index = index of last inserted value of the sum array
    generate_checksum(last_index);
    printf("Checksum : ");
    for (size_t i = 0; i < BLOCK_SIZE; i++)
    {
        printf("%d ", checksum[i]);
    }

    int transmit_data[BLOCK_SIZE * (SIZE + 1)];

    // creating transmit data which is concatination of checksum and original data
    for (size_t i = 0; i < (BLOCK_SIZE * (SIZE + 1)); i++)
    {
        if (i < BLOCK_SIZE)
        {
            transmit_data[i] = checksum[i];
        }
        else
        {
            transmit_data[i] = data[(i - BLOCK_SIZE)];
        }
    }

    printf("\nData to be transmitted : ");

    //printing data to be transmitted
    for (size_t i = 0; i < (BLOCK_SIZE * (SIZE + 1)); i++)
    {
        printf("%d ", transmit_data[i]);
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
 * calculates complement of the given index in sum array and returns a number (of long type) joining it
 * 
 * @param n: index of sum array whose complement needs to be calculated
 * 
 * return:
 *      - long : complemented value of sum[n]
 * 
 */
long generate_checksum(int n)
{

    for (size_t i = 0; i < BLOCK_SIZE; i++)
    { // if length of last sum value is less than BLOCK_SIZE
        // means, there are (BLOCK_SIZE - len(last_known_index)) 0 before the value
        // hence the complement will be 1
        if (i < (BLOCK_SIZE - last_known_len - 1))
        {
            checksum[i] = 1;
        }
        else
        { // doing complement of each value
            if (sum[last_index - 1][i - (BLOCK_SIZE - last_known_len - 1)] == 0)
            {
                checksum[i] = 1;
            }
            else
            {
                checksum[i] = 0;
            }
        }
    }
    return array_joiner(checksum, 0, BLOCK_SIZE);
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
