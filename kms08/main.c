#include <stdio.h>
#include <stdlib.h>

#define ROWS    30000
#define COLUMNS 30000
#define SCALAR  7
#define VALUE   56

int main()
{
    // initialize matrix
    //int (*arr) [ROWS] = malloc(ROWS*COLUMNS*sizeof(int));
    int** arr = NULL;
    int* arrData = NULL;
    arr = malloc(sizeof(int *) * ROWS);
    arrData = malloc(sizeof(int) * COLUMNS * ROWS);

    for(int i = 0; i < ROWS; i++)
        arr[i]  = arrData + i * COLUMNS;

    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLUMNS; j++)
        {
            arr[i][j] = VALUE;
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
    free(arrData);
    free(arr);
    return 0;
}
