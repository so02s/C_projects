#include "fms.h"

void game() {
  State_t *state = getState();

  if (state->action == Terminate) {
    state->level = -1;
    updateCurrentState();
    return;
  }

  if (state->status == START) start();

  if (state->status == SPAWN) spawn(state->action);

  if (state->status == SHIFT) shift();

  if (state->status == PAUSE) pauseGame();

  if (state->status == STEP) step();

  if (state->status == ATTACH) attachFig();

  if (state->status == GAMEOVER) gameOver(state);
};

void shift() {
  State_t *state = getState();
  if (state->action == Pause) {
    state->action = None;
    state->status = PAUSE;
    state->pause = 1;
  } else {
    shiftFig();
    state->status = STEP;
  }
}

void start() {
  State_t *state = getState();
  initState(state);
  updateCurrentState();
  if (state->action == Start) state->status = SPAWN;
}

void pauseGame() {
  State_t *state = getState();
  if (state->action == Pause) {
    state->pause = 0;
    state->status = SHIFT;
  }
}

void step() {
  State_t *state = getState();
  stepDown();
  drawFigInField();
  state->status = ATTACH;
  updateCurrentState();
}

void gameOver(State_t *state) {
  state->level = -1;
  updateCurrentState();
}

GameInfo_t updateCurrentState() {
  GameInfo_t *info = getInfo();
  State_t *state = getState();
  copyToInfo(info, state);
  info->high_score = state->high_score;
  info->pause = state->pause;
  info->score = state->score;
  info->speed = state->speed;
  info->level = state->level;
  return *info;
};

State_t *getState() {
  static State_t state;
  return &state;
}

void copyToInfo(GameInfo_t *info, State_t *state) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      info->field[i][j] = state->field[i][j];

      if (i < FIG_SIZE && j < FIG_SIZE) {
        info->next[i][j] = state->next.field[i][j];
      }
    }
  }
}

int initInfo(GameInfo_t *info) {
  int error = 0;
  info->field = (int **)calloc(ROWS, sizeof(int *));
  info->next = (int **)calloc(FIG_SIZE, sizeof(int *));
  if (!info->field || !info->next) {
    error = 1;
  } else {
    for (int i = 0; i < ROWS; i++) {
      info->field[i] = (int *)calloc(ROWS, sizeof(int));
      if (!info->field[i]) error = 1;
    }
    for (int i = 0; i < FIG_SIZE; i++) {
      info->next[i] = (int *)calloc(FIG_SIZE, sizeof(int));
      if (!info->next[i]) error = 1;
    }
  }
  info->level = 1;
  info->score = -1;
  return error;
}

void clearInfo(GameInfo_t *info) {
  for (int i = 0; i < ROWS; i++) free(info->field[i]);
  for (int i = 0; i < FIG_SIZE; i++) free(info->next[i]);
  free(info->field);
  free(info->next);
}

GameInfo_t *getInfo() {
  static GameInfo_t info;
  return &info;
}