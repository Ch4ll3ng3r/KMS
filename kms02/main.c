#include <stdio.h>
#include <stdlib.h>
#include "support.h"

void game_init ();
void game_run ();
void game_del ();
void draw ();
int collision (unsigned int x, unsigned int y);
int num_collisions (unsigned int x, unsigned int y);
void move ();
void change_direction (unsigned int newdir);
int check_snake_collision ();
int check_level_collision ();
int snake_nearby_nibble ();
void eat ();

struct snake
{
    unsigned int xpos;
    unsigned int ypos;
    unsigned int old_xpos;
    unsigned int old_ypos;
    unsigned int direction; //1 Norden, 2 Osten, 3 Süden, 4 Westen
    struct snake* next;
};

struct snake* s;
struct snake* nibble;

int main()
{
    game_init ();
    game_run ();
    game_del ();
    return 0;
}

void game_init ()
{
    support_init ();
    s = malloc (sizeof (struct snake));
    s->xpos = 8;
    s->ypos = 10;
    s->old_xpos = 0;
    s->old_ypos = 0;
    s->direction = 2;
    struct snake* sn = malloc (sizeof (struct snake));
    s->next = sn;
    int x;
    for (x = 9; x < 12; x++)
    {
        sn->xpos = x;
        sn->ypos = 10;
        sn->direction = 2;
        sn->old_xpos = 0;
        sn->old_ypos = 0;
        sn->next = malloc (sizeof (struct snake));
        sn = sn->next;
    }
    sn->xpos = 12;
    sn->ypos = 10;
    sn->old_xpos = 0;
    sn->old_ypos = 0;
    sn->direction = 2;
    sn->next = NULL;
    sn = s;
    nibble = malloc(sizeof (struct snake));
    nibble->next = NULL;
    nibble->old_xpos = 0;
    nibble->old_ypos = 0;
    nibble->direction = 2;
    nibble->xpos = rand() % 20 + 1;
    nibble->ypos = rand() % 20 + 1;
    draw ();
}

void game_run ()
{
    int run = 1;
    int i = 0;
    while (run == 1)
    {
        switch (support_readkey (300))
        {
            case 119:
            {
               change_direction (1);
            } break;
            case 100:
            {
                change_direction (2);
            } break;
            case 115:
            {
                change_direction (3);
            } break;
            case 97:
            {
                change_direction (4);
            } break;
            case 112:
            {
                run = 0;
            } break;
        }
        move ();
        draw ();
        if (snake_nearby_nibble () == 1)
            eat ();
        if (i < 5)
            i++;
        if ((check_snake_collision () == 1 || check_level_collision () == 1) && i == 5)
            run = 0;
    }
}

void game_del ()
{
    struct snake* sn;
    while (s != NULL)
    {
        sn = s->next;
        free(s);
        s = NULL;
        s = sn;
    }
    if (nibble != NULL)
    {
        free(nibble);
        nibble = NULL;
    }
}

void draw ()
{
    support_clear ();
    int i;
    int j;
    for (i = 0; i < 20; i++)
    {
        for (j = 0; j < 20; j++)
        {
            if (collision (j + 1, i + 1) == 1)
                printf ("o");
            else if (collision (j + 1, i +1) == 2)
                printf ("a");
            else
                printf (" ");
        }
        printf ("|\n");
    }
    printf ("--------------------\n");
}

int collision (unsigned int x, unsigned int y)
{
    struct snake* sn = s;
    while (sn != NULL)
    {
        if (sn->xpos == x && sn->ypos == y)
            return 1;
        sn = sn->next;
    }
    if (nibble->xpos == x && nibble->ypos == y)
        return 2;
    return 0;
}

void move ()
{
    s->old_xpos = s->xpos;
    s->old_ypos = s->ypos;
    switch (s->direction)
    {
        case 1:
        {
            s->ypos--;
        } break;
        case 2:
        {
            s->xpos++;
        } break;
        case 3:
        {
            s->ypos++;
        } break;
        case 4:
        {
            s->xpos--;
        } break;
    }
    struct snake* sn = s;
    while (sn->next != NULL)
    {
        sn->next->old_xpos = sn->next->xpos;
        sn->next->old_ypos = sn->next->ypos;
        sn->next->xpos = sn->old_xpos;
        sn->next->ypos = sn->old_ypos;
        sn = sn->next;
    }
}

void change_direction (unsigned int newdir)
{
    struct snake* sn = s;
    while (sn != NULL)
    {
        sn->direction = newdir;
        sn = sn->next;
    }
}

int num_collisions (unsigned int x, unsigned int y)
{
    struct snake* sn = s;
    int num_col = 0;
    while (sn != NULL)
    {
        if (sn->xpos == x && sn->ypos == y)
            num_col++;
        sn = sn->next;
    }
    return num_col;
}

int check_snake_collision ()
{
    struct snake* sn = s;
    while (sn != NULL)
    {
        if (num_collisions (sn->xpos, sn->ypos) > 1)
            return 1;
        sn = sn->next;
    }
    return 0;
}

int check_level_collision ()
{
    struct snake* sn = s;
    while (sn != NULL)
    {
        if (sn->xpos < 1 || sn->xpos > 20 ||
            sn->ypos < 1 || sn->ypos > 20)
            return 1;
        sn = sn->next;
    }
    return 0;
}

int snake_nearby_nibble ()
{
    struct snake* sn = s;
    while (sn != NULL)
    {
        if (nibble->xpos == sn->xpos)
        {
            if (nibble->ypos == sn->ypos + 1 ||
                nibble->ypos == sn->ypos - 1)
                return 1;
        }
        else if (nibble->ypos == sn->ypos)
        {
            if (nibble->xpos == sn->xpos + 1 ||
                nibble->xpos == sn->xpos - 1)
                return 1;
        }
        sn = sn->next;
    }
    return 0;
}

void eat ()
{
    struct snake* sn = s;
    while (sn->next != NULL)
    {
        sn = sn->next;
    }
    sn->next = nibble;
    nibble->direction = sn->direction;
    nibble = NULL;
    nibble = malloc(sizeof (struct snake));
    nibble->next = NULL;
    nibble->old_xpos = 0;
    nibble->old_ypos = 0;
    nibble->direction = 2;
    nibble->xpos = rand() % 20 + 1;
    nibble->ypos = rand() % 20 + 1;
}
