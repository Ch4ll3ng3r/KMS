#include <stdio.h>
#include <stdlib.h>

#define ROWS    30000
#define COLUMNS 30000
#define SCALAR  7
#define VALUE   56

int main()
{
    // initialize matrix
    int (*arr) [ROWS] = malloc(ROWS*COLUMNS*sizeof(int));
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLUMNS; j++)
        {
            (*arr)[i][j] = VALUE;
        }
    }
    // multiply by scalar
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLUMNS; j++)
        {
            arr[i][j] *= SCALAR;
        }
    }
    // free memory
    free(arr);
    printf("Hello world!\n");
    return 0;
}
