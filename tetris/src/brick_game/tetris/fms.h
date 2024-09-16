#ifndef _FMS_TETRIS_H
#define _FMS_TETRIS_H

#include "../../gui/cli/cli.h"
#include "tetris_model.h"

//внешние
int initInfo(GameInfo_t *info);
void game();

//внутренние
//состояния
void start();
void shift();
void pauseGame();
void step();
void gameOver(State_t *state);
//обновление GameInfo_t
void clearInfo(GameInfo_t *info);
void copyToInfo(GameInfo_t *info, State_t *state);

#endif