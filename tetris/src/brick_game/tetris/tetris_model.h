#ifndef _BRICKGAME_TETRIS_MODEL_H
#define _BRICKGAME_TETRIS_MODEL_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "../../common.h"

#define FIG_COUNT 7
#define START_SPEED 600
#define NEXT_LEVEL 600


typedef enum {
  START,
  PAUSE,
  SPAWN,
  SHIFT,
  STEP,
  ATTACH,
  GAMEOVER,
  WAITING
} StateStatus;

typedef enum { O, L, J, S, Z, T, I } Figure;


typedef struct {
  int x;
  int y;
} Coord_t;

typedef struct {
  Coord_t pos;
  int fig;
  int wide;
  int field[FIG_SIZE][FIG_SIZE];
} Figure_t;

typedef struct {
  int field[ROWS][COLUMNS];
  int score;
  int high_score;
  int level;
  int speed;
  int start;
  int pause;
  int crash;
  int next_fig;
  int next_wide;
  int game_over;
  StateStatus status;
  UserAction_t action;
  UserAction_t dir;
  Figure_t figure;
  Figure_t next;
} State_t;

typedef struct {
  int field[ROWS][COLUMNS];
  int figure[FIG_SIZE][FIG_SIZE];
} StateTMP_t;


//внешние
State_t *getState();

//внутренние
State_t *initState(State_t *state);
void spawn(UserAction_t action);
void shiftFig();
int genRandFig();
void updateFig(int random_fig);
void copyFigToTmp();
void checkFullLine();
StateTMP_t *getTmpState();
int stepDown();
int checkCollision();
void drawFigInField();
void emptyFig();
void emptyCurFig();
void rotateFig();
void checkGameOver();
void updateInfo();
void attachFig();

//рекорд
void saveHighScore(State_t *state);
void readHighScore(State_t *state);

#endif