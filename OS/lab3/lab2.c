#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void main()
{
    char buff[100];

    int inFile = open("file1.txt", O_RDONLY);
    int outFile = open("file2.txt", O_WRONLY);

    int bytesRead, bytesWritten;

    while ((bytesRead = read(inFile, buff, 100)) != 0)
        bytesWritten = write(outFile, buff, bytesRead);

    if (bytesWritten >= 0)
        printf("Contents copied successfully.\n");
}

