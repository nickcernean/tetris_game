#ifndef TETRIS_H
#define TETRIS_H

#define TET_TICKS_START 30
typedef struct TetBlock
{
    int b;
} TetBlock;

typedef struct TetFigure
{
    int x;
    int y;
    int size;
    TetBlock *blocks;
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

void freeTetFiguresT(TetFiguresT *tetft);
TetFiguresT *createTetFiguresT(int count, int figures_size, TetBlock *figures_template);
TetField *createTetField(int width, int height);
void freeTetField(TetField *tetf);
TetGame *createTetGame(int field_width, int field_height, int figures_size, int count, TetBlock *figures_template);
void freeTetGame(TetGame *tetg);
void moveFigureDown(TetGame *tetg);
void moveFigureUp(TetGame *tetg);
void moveFigureRight(TetGame *tetg);
void moveFigureLeft(TetGame *tetg);
int collisionTet(TetGame *tetg);
void plantFigure(TetGame *tetg);
int lineFilledTet(int i, TetField *tfl);
void dropLineTet(int i, TetField *tf);
TetFigure *createTetFigure(TetGame *tetg);
void freeTetFigure(TetFigure *tf);
TetFigure *rotTetFigure(TetGame *tetg);
void dropNewFigure(TetGame *tetg);
int eraseLinesTet(TetGame *tetg);
void calculateTet(TetGame *tetg);

#endif