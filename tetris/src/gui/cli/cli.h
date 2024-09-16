#ifndef _CLI_H
#define _CLI_H

#include <curses.h>
#include <string.h>
#include "../../common.h"

//внешние
void settingNcurcesGame();
void gui(GameInfo_t info);

//внутренние
void settingNcurcesLose();
void gameScreen(GameInfo_t *info);
void gameOverScreen(GameInfo_t *info);
bool userInputButton(GameInfo_t* info);

#endif