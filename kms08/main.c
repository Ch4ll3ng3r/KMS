#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define ROWS    3000
#define COLUMNS ROWS
#define SCALAR  7
#define VALUE   56

int main()
{
    struct timeval start, end;

    int (*arr) [ROWS] = malloc(ROWS*COLUMNS*sizeof(int));
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLUMNS; j++)
        {
            arr[i][j] = VALUE;
        }
    }

    for(int i = 0; i < 10; i++)
    {
        gettimeofday(&start, NULL);
        for(int j = 0; j < ROWS; j++)
        {
            for(int k = 0; k < COLUMNS; k++)
            {
                arr[j][k] *= SCALAR;
            }
        }
        gettimeofday(&end, NULL);
        long long microsecondsStart = start.tv_sec * 1000000 + start.tv_usec;
        long long microsecondsEnd = end.tv_sec * 1000000 + end.tv_usec;
        long long div = microsecondsEnd - microsecondsStart;

        printf("%lld.%06lld\n", div / 1000000, div % 1000000);
    }

    free(arr);
    arr = NULL;
    return 0;
}
