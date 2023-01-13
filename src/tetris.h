#ifndef TETRIS_H
#define TETRIS_H

typedef struct TetBlock
{
    int b;
} TetBlock;

typedef struct TetFigure
{
    int x;
    int y;
    int size;
} TetFigure;

typedef struct TetFiguresT
{
    int count;
    int size;
    TetBlock *blocks;
} TetFiguresT;

typedef struct TetField
{
    int width;
    int height;
    TetBlock *blocks;
    TetBlock *blocks;
} TetField;

typedef struct TetPlayer
{
    int action;

} TetPlayer;
enum
{
    TET_GAMEOVER = 0,
    TET_PLAYING
};
enum
{
    TET_PLAYER_NOP = 0,
    TET_PLAYER_UP,
    TET_PLAYER_DOWN,
    TET_PLAYER_LEFT,
    TET_PLAYER_RIGHT

};

typedef struct TetGame
{
    TetField *field;
    TetFigure *figure;
    TetFiguresT *figurest;
    TetPlayer *player;
    int ticks;
    int ticks_left;
    int playing;
    int score;
} TetGame;

TetGame *createTetGame(int field_width, int field_height, int figure_size, int count, TetBlock *figure_template);

void calculateTet(TetGame *tetg);

#endif