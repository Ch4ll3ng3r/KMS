#include <stdio.h>
#include <stdlib.h>

struct cell
{
    int value;
    struct cell* right;
    struct cell* down;
};

struct cell* grid_init(unsigned int num_columns, unsigned int num_rows)
{
    struct cell* grid = malloc(sizeof(struct cell));
    grid->value = rand() % 100 + 1;
    if (num_columns <= 1)
        grid->right = NULL;
    else
        grid->right = grid_init(num_columns - 1, num_rows);
    if (num_rows <= 1)
        grid->down = NULL;
    else
        grid->down = grid_init(num_columns, num_rows - 1);
    return grid;
};

void grid_print(struct cell* grid)
{
    while(grid != NULL)
    {
        struct cell* g = grid;
        printf("| ");
        while(g != NULL)
        {
            printf("%d ", g->value);
            g = g->right;
        }
        grid = grid->down;
        printf("|\n");
    }
}

void grid_print_dot(struct cell* grid)
{
    FILE* f;
    f = fopen("pointers.txt", "w");
    fprintf(f, "digraph { \n");
    while(grid != NULL)
    {
        struct cell* g = grid;
        while(g != NULL)
        {
            if (g->down != NULL)
                fprintf(f, "%p -> %p\n", g, g->down);
            if (g->right != NULL)
                fprintf(f, "%p -> %p\n", g, g->right);
            g = g->right;
        }
        grid = grid->down;
    }
    fprintf(f, "}");
    fclose(f);
}

void grid_del(struct cell* grid)
{
    if (grid != NULL)
    {
        struct cell* r = grid->right;
        struct cell* d = grid->down;
        free(grid);
        grid = NULL;
        if (r != NULL)
            grid_del(r);
        if (d != NULL)
            grid_del(d);
    }
}

int main()
{
    struct cell* grid = grid_init(2, 2);
    grid_print(grid);
    grid_print_dot(grid);
    grid_del(grid);
    return 0;
}
