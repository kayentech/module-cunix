#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/vm_filler.h"


elem_t* create_elem()
{
    elem_t *elem;
    pos_t pos, *buff;
    int gen_cells_num, sp;

    elem = (elem_t*)malloc (sizeof(elem_t));
    elem->h = MAX_ELEM_HEIGHT;
    elem->w = MAX_ELEM_WIDTH;
    elem->array = (char**)malloc(elem->h * sizeof(char*));

    for (int i = 0; i < elem->h; i++)
        elem->array[i] = (char*)malloc(elem->w * sizeof(char));

    for (int i = 0; i < elem->h; i++)
        for (int j = 0; j < elem->w; j++)
            elem->array[i][j] = '.';

    elem->array[0][0] = '*';

    // min num of stars in elem is 3, max - (1/3 of dots + 3)
    gen_cells_num = rand() % ((elem->h * elem->w - 1)/3) + 2;

    buff = (pos_t*)malloc(sizeof(pos_t) * 32); // 32 should be enough
    for (int c = 0; c < gen_cells_num; c++)
    {
        sp = 0;
        for (int i = 0; i < elem->h; i++) {
            for (int j = 0; j < elem->w; j++) {
                pos.x = j;
                pos.y = i;
                if (placable(elem, pos) == 0)
                    buff[sp++] = pos;
            }
        }
        pos = buff[rand()%sp];
        elem->array[pos.y][pos.x] = '*';
    }

    free(buff);
    return truncate_elem(elem);
}

elem_t* truncate_elem(elem_t *elem)
{
    int maxi, maxj;
    char **trunc;
    elem_t *new;

    maxi = 0;
    maxj = 0;

    for (int i = 0; i < elem->h; i++)
        for (int j = 0; j < elem->h; j++)
            if (elem->array[i][j] == '*')
            {
                if (i > maxi && (maxi = i)) {}
                if (j > maxj && (maxj = j)) {}
            }

    maxi += 1;
    maxj += 1;

    trunc = (char**)malloc(sizeof(char*) * maxi);
    for (int i = 0; i < maxi; i++)
    {
        trunc[i] = (char*)malloc(sizeof(char) * maxj);
        for (int j = 0; j < maxj; j++)
            trunc[i][j] = elem->array[i][j];
    }

    new = (elem_t*)malloc(sizeof(elem_t));
    new->h = maxi;
    new->w = maxj;
    new->array = trunc;
    free(elem->array);
    free(elem);

    return new;
}

int placable(elem_t *elem, pos_t pos)
{
    if (elem->array[pos.y][pos.x] != '.')
        return 1;
    if (pos.x > 0 && elem->array[pos.y][pos.x - 1] == '*')
        return 0;
    if (pos.x < MAX_ELEM_WIDTH - 1 && elem->array[pos.y][pos.x + 1] == '*')
        return 0;
    if (pos.y > 0 && elem->array[pos.y - 1][pos.x] == '*')
        return 0;
    if (pos.y < MAX_ELEM_HEIGHT - 1 && elem->array[pos.y + 1][pos.x] == '*')
        return 1;
    return 1;
}

