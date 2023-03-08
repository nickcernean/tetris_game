#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "tetris.h"

TetBlock tet_templates[] = {
    0, 0, 1, 0, 0,
    0, 0, 1, 0, 0,
    0, 0, 1, 0, 0,
    0, 0, 1, 0, 0,
    0, 0, 1, 0, 0,

    0, 0, 0, 0, 0,
    0, 0, 1, 0, 0,
    0, 1, 1, 1, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,

    0, 0, 0, 0, 0,
    0, 0, 1, 1, 0,
    0, 0, 1, 0, 0,
    0, 0, 1, 0, 0,
    0, 0, 0, 0, 0,

    0, 0, 0, 0, 0,
    0, 1, 1, 0, 0,
    0, 0, 1, 0, 0,
    0, 0, 1, 0, 0,
    0, 0, 0, 0, 0,

    0, 0, 0, 0, 0,
    0, 0, 1, 1, 0,
    0, 1, 1, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,

    0, 0, 0, 0, 0,
    0, 1, 1, 0, 0,
    0, 0, 1, 1, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0};

void printTetGame(TetGame *tetg)
{
    TetField *tf = tetg->field;
    TetFigure *t = tetg->figure;
    for (int i = 0; i < tf->height; i++)
    {
        for (int j = 0; j < tf->width; j++)
        {
            int sym = 0;
            if (tf->blocks[i * tf->width + j].b != 0)
                sym = 1;
            else
            {
                int x = j - t->x;
                int y = i - t->y;
                if (x >= 0 && x < t->size && y >= 0 && y < t->size)
                    if (t->blocks[y * t->size + x].b != 0)
                        sym = 1;
            };
            printf("%d", sym);
        };
    };
    fflush(stdout);
};

int main(int argc, char *argv[])
{
    struct timespec sp_start, sp_end, ts1, ts2 = {0, 0};

    TetGame *tetg = createTetGame(15, 101, 5, 6, tet_templates);
    TetPlayer player;
    player.action = TET_PLAYER_NOP;
    tetg->player = &player;

    dropNewFigure(tetg);
    while (tetg->playing != TET_GAMEOVER)
    {
        clock_gettime(CLOCK_MONOTONIC, &sp_start);
        calculateTet(tetg);
        printTetGame(tetg);
        clock_gettime(CLOCK_MONOTONIC, &sp_end);
        if (sp_end.tv_sec - sp_start.tv_sec <= 0 &&
            (ts2.tv_nsec = 33000000 - (sp_end.tv_nsec - sp_start.tv_nsec)) > 0)
        {
            nanosleep(&ts2, &ts1);
        }
    };
    freeTetGame(tetg);
    return 0;
}