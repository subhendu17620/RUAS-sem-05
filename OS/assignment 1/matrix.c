#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX_BUFFER_SIZE 10000000

typedef struct
{
    char *string;
    char *substring;
    int freq;
} ArgsBundle;

void sequential_read(char *, char *, char *, char *);
void parallel_read(char *, char *, char *, char *);
char *read_file(char *);
ArgsBundle *new_args_bundle(char *, char *);

void *search(void *);
int *compute_LPS(char *, int);

int main(int argc, char *argv[])
{

    // checking if the number of arguments is valid
    if (argc < 6)
    {
        printf("Invalid arguments.");
        exit(-1);
    }

    // // calling the appropriate method
    if (strcmp(argv[1], "--sequential") == 0)
    {
        printf("Running in sequential mode.\n");
        sequential_read(argv[2], argv[3], argv[4], argv[5]);
    }
    else
    {
        printf("Running in parallel mode.\n");
        parallel_read(argv[2], argv[3], argv[4], argv[5]);
    }
}

/**
 * Reads and sums the frequencies of the substring in the files 
 * parallely, using threads.
 * 
 * @param substring The substring to search for.
 * @param file1 The path to the first file.
 * @param file2 The path to the second file.
 * @param file3 The path to the third file.
 */
void parallel_read(char *substring, char *file1, char *file2, char *file3)
{
    // defining variables to calculate time
    struct timespec start, end;

    // reading the files and storing their contents
    char *file1Contents = read_file(file1);
    char *file2Contents = read_file(file2);
    char *file3Contents = read_file(file3);

    // creating the argument structs to be passed into the thread
    ArgsBundle *bundle1 = new_args_bundle(substring, file1Contents);
    ArgsBundle *bundle2 = new_args_bundle(substring, file2Contents);
    ArgsBundle *bundle3 = new_args_bundle(substring, file3Contents);

    // creating the thread variables
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;

    // storing start time
    clock_gettime(CLOCK_REALTIME, &start);

    // spawning the threads
    pthread_create(&thread1, NULL, search, bundle1);
    pthread_create(&thread2, NULL, search, bundle2);
    pthread_create(&thread3, NULL, search, bundle3);

    // waiting for the threads to finish execution
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    // storing end time
    clock_gettime(CLOCK_REALTIME, &end);

    // consolidating the frequencies
    int total_freq = bundle1->freq + bundle2->freq + bundle3->freq;

    // calculating time elapsed
    double time_taken;
    time_taken = (end.tv_sec - start.tv_sec) * 1e9;
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;

    // printing the result
    printf("The total number of times '%s' occurs in the files is: %d\n",
           substring, total_freq);
    printf("Time taken to search: %.10f seconds.\n", time_taken);
}

/**
 * Reads and sums the frequencies of the substring in the files 
 * sequentially.
 * 
 * @param substring The substring to search for.
 * @param file1 The path to the first file.
 * @param file2 The path to the second file.
 * @param file3 The path to the third file.
 */
void sequential_read(char *substring, char *file1, char *file2, char *file3)
{
    // defining variables to calculate time
    struct timespec start, end;

    // reading the files and storing their contents
    char *file1Contents = read_file(file1);
    char *file2Contents = read_file(file2);
    char *file3Contents = read_file(file3);

    // creating the argument structs to be passed into the thread
    ArgsBundle *bundle1 = new_args_bundle(substring, file1Contents);
    ArgsBundle *bundle2 = new_args_bundle(substring, file2Contents);
    ArgsBundle *bundle3 = new_args_bundle(substring, file3Contents);

    // storing start time
    clock_gettime(CLOCK_REALTIME, &start);

    // searching for the substring in the file contents
    search((void *)bundle1);
    search((void *)bundle2);
    search((void *)bundle3);
    // storing end time

    clock_gettime(CLOCK_REALTIME, &end);

    // consolidating the frequencies
    int total_freq = bundle1->freq + bundle2->freq + bundle3->freq;

    // calculating time elapsed
    double time_taken;
    time_taken = (end.tv_sec - start.tv_sec) * 1e9;
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;

    // printing the result
    printf("The total number of times '%s' occurs in the files is: %d\n",
           substring, total_freq);
    printf("Time taken to search: %.10f seconds.\n", time_taken);
}

/**
 * Read the contents of a file.
 * 
 * @param file The path to the file
 * 
 * @return The contents of the file
 */
char *read_file(char *file)
{
    // initalizing the buffer
    char *contents = malloc(MAX_BUFFER_SIZE * sizeof(*contents));
    // opening the file
    FILE *fh = fopen(file, "r");
    // initializing variables
    char ch;
    int i = 0;

    // reading the file
    while ((ch = fgetc(fh)) != EOF)
    {
        // if the character is a new line character, replace it
        // with a space
        if (ch != '\n')
            contents[i++] = ch;
        else
            contents[i++] = ' ';
    }

    // closing the file
    fclose(fh);
    // returning the contents
    return contents;
}

/**
 * Creates a new argument bundle.
 * 
 * @param substring The subtring.
 * @param string The main string.
 * 
 * @return The arugment bundle.
 */
ArgsBundle *new_args_bundle(char *substring, char *string)
{
    // mallocing the bundle
    ArgsBundle *bundle = malloc(sizeof(*bundle));
    // assigning memory to substring and string char pointers
    bundle->substring = malloc(sizeof(*bundle->substring) * strlen(substring));
    bundle->string = malloc(sizeof(*bundle->string) * strlen(string));

    // copying the contents of the substring and string
    // into the bundle
    strcpy(bundle->substring, substring);
    strcpy(bundle->string, string);

    // initializing the freq to 0
    bundle->freq = 0;

    // returning the bundle
    return bundle;
}

/**
 * Searches for the occurence of a substring in a string using 
 * Knuth-Morris-Pratt algorithm.
 * 
 * @param args the `ArgBundle` that contain the arguments.
 */
void *search(void *args)
{
    // extracting arguments
    ArgsBundle *bundle = (ArgsBundle *)args;
    char *substring = bundle->substring;
    char *string = bundle->string;

    // initializing variables
    int m = strlen(substring);
    int n = strlen(string);
    int i = 0;
    int j = 0;

    // computing longest proper prefix which is also suffix array
    int *lps = compute_LPS(substring, m);

    // searching
    while (i < n)
    {
        // if the jth character of the substring match the ith character
        // of the string, increment the indices of both, to check the
        // next character
        if (substring[j] == string[i])
        {
            j++;
            i++;
        }

        // if the index of substring is the same as the length of
        // the substring, match has been found.
        if (j == m)
        {
            // increment the frequency counter
            bundle->freq++;

            // update j to be the longest proper prefix of the second last character
            // of the substring
            j = lps[j - 1];
        }
        // if the jth character of the substring does not match the
        // ith character of the string
        else if (i < n && substring[j] != string[i])
        {
            // if the index of the substring is not 0
            if (j != 0)
                // update substring to the value of the previous character
                // in the substring's lps value
                j = lps[j - 1];
            else
                // increment the string index
                i++;
        }
    }
}

/**
 * Calculates the longest proper prefix that is also a suffix
 * array.
 * 
 * @param substring the string for which the lps should be found
 * @param size the length of the string
 * 
 * @return the lps array
 */
int *compute_LPS(char *substring, int size)
{
    // assigning memory to the array
    int *lps = malloc(sizeof(*lps) * size);
    // initializing variables
    int len = 0;
    int i = 1;
    lps[0] = 0; // lps of the first character is always 0

    // looping till length of the substring
    while (i < size)
    {
        // if there is a match between the characters
        // at index i and len, then increment the indices
        // and assign lps of the ith character as len
        if (substring[i] == substring[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
                len = lps[len - 1];
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }

    // returning the lps array
    return lps;
}
