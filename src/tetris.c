#include "tetris.h"
#include <stdlib.h>

#ifndef TETRIS_C
#define TETRIS_C

TetFiguresT *createTetFiguresT(int count, int figures_size, TetBlock *figures_template)
{
    TetFiguresT *tetft = (TetFiguresT *)malloc(sizeof(TetFiguresT));
    tetft->count = count;
    tetft->size = figures_size;
    tetft->blocks = figures_template;
    return tetft;
};

void freeTetFiguresT(TetFiguresT *tetft)
{
    if (tetft)
    {
        free(tetft);
    };
};

TetField *createTetField(int width, int height)
{
    TetField *tetf = (TetField *)malloc(sizeof(TetField));
    tetf->width = width;
    tetf->height = height;
    tetf->blocks = (TetBlock *)malloc(sizeof(TetBlock) * width * height);

    for (int i = 0; i < width * height; i++)
    {
        tetf->blocks[i].b = 0;
        return tetf;
    };
};
void freeTetField(TetField *tetf)
{
    if (tetf)
    {
        if (tetf->blocks)
        {
            free(tetf->blocks)
        };
        free(tetf);
    };
};

TetGame *createTetGame(int field_width, int field_height, int figures_size, int count, TetBlock *figures_template)
{
    TetGame *tetg = (TetGame *)malloc(sizeof(TetGame));
    tetg->field = createTetField(field_width, field_height);
    tetg->figurest = createFiguresT(count, figures_size, figures_template);

    return tetg;
};

void freeTetGame(TetGame *tetg)
{
    if (tetg)
    {
        freeTetField(tetg->field);
        freeTetFiguresT(tetg->figurest);
        free(tetg);
    };
};

void moveFigureDown(TetGame *tetg)
{
    tetg->figure->y++;
}

void moveFigureUp(TetGame *tetg)
{
    tetg->figure->y--;
}

void moveFigureRight(TetGame *tetg)
{
    tetg->figure->x++;
}

void moveFigureLeft(TetGame *tetg)
{
    tetg->figure->x--;
}

int collisionTet(TetGame *tetg)
{
    TetFigure *t = tetg->figure;
    TetField *tf = tetg->field;
    for (int i = 0; i < t->size; i++)
    {
        for (int j = 0; j < t->size; j++)
        {
            if (t->blocks[i * t->size + j].b != 0)
            {
                int fx = t->x + j;
                int fy = t->y + i;
                if (tf->block[fy * tf->width + fx].b != 0)
                {
                    return 1;
                }
                if (fx < 0 || fx >= tf->width || fy < 0 || fy >= tf->height)
                {
                    return 1;
                };
            };
        };
    };
    return 0;
};

void plantFigure(TetGame *tetg)
{
    TetFigure *t = tetg->figure;
    for (int i = 0; i < t->size; i++)
    {
        for (int j = 0; j < t->size; j++)
        {
            if (t->blocks[i * t->size + j].b != 0)
            {
                int fx = t->x + j;
                int fy = t->y + i;
                tetg->field->blocks[fy * tetg->field->width + fx].b = t->blocks[i * t->size + j].b;
            }
        }
    }
}

int lineFilledTet(int i, TetField *tfl)
{
    for (int j = 0; j < tfl->width; j++)
    {
        if (tfl->blocks[i * tfl->width + j].b == 0)
        {
            return 0;
        };
        return 1;
    };
};

void dropLineTet(int i, TetField *tf)
{
    if (i == 0)
    {
        for (int j = 0; j < tfl->width; j++)
        {
            tfl->blocks[j].b = 0;
        }
    }
    else
    {
        for (int k = i; k > 0; k--)
        {
            for (int j = 0; j < tfl->width; j++)
            {
                tfl->blocks[k * tfl->width + j].b = tfl->blocks[(k - 1) * tfl->width + j].b;
            }
        }
    }
};

int eraseLinesTet(TetGame *tetg)
{
    TetField *tfl = tetg->field;
    int count = 0;
    for (int i = tfl->height - 1; i > 0; i--)
    {
        while (lineFilledTet(i, tfl))
        {
            dropLineTet(i, tfl);
            count++;
        };
    };
    return count;
};

void calculateTet(TetGame *tetg)
{
    if (tetg->ticks_left <= 0)
    {
        tetg->ticks_left = tetg->ticks;
        moveFigureDown(tetg);
        if (collisionTet(tetg))
        {
            moveFigureUp(tetg);
            plantfigure(tetg);
            tetg->score += eraseLinesTet(tetg);
            dropNewFigure(tetg);
            if (collisionTet(tetg))
            {
                tetg->playing = TET_GAMEOVER;
                return;
            };
        };
    };
    switch (tetg->player->action)
    {
    case TET_PLAYER_RIGHT:
        moveFigureRight(tetg);
        if (collisionTet(tetg))
        {
            moveFigureLeft(tetg);
        };
        break;
    case TET_PLAYER_LEFT:
        moveFigureLeft(tetg);
        if (collisionTet(tetg))
        {
            moveFigureRight(tetg);
        };
        break;
    case TET_PLAYER_DOWN:
        moveFigureDown(tetg);
        if (collisionTet(tetg))
        {
            moveFigureUp(tetg);
        };
        break;
    case TET_PLAYER_UP:
        TetFigure *t = rotFigure(tetg);
        TetFigure *told = tetg->figure;
        tetg->figure = t;

        if (collisionTet(tetg))
        {
            tetg->figure = told;
            freeFigure(t);
        }
        else
        {
            freeFigure(told);
        };
        break;
    case TET_PLAYER_NOP:
    default:
        break;
    };
    tetg->ticks_left--;
};

#endif