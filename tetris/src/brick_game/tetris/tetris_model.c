#include "tetris_model.h"

void copyFigToTmp() {
  State_t *state = getState();
  StateTMP_t *tmp_state = getTmpState();
  for (int i = 0; i < FIG_SIZE; i++)
    for (int j = 0; j < FIG_SIZE; j++)
      tmp_state->figure[i][j] = state->next.field[i][j];
}

void copyFieldToTmp() {
  State_t *state = getState();
  StateTMP_t *tmp_state = getTmpState();
  for (int i = 0; i < ROWS; i++)
    for (int j = 0; j < COLUMNS; j++)
      tmp_state->field[i][j] = state->field[i][j];
}

void copyFieldFromTmp() {
  State_t *state = getState();
  StateTMP_t *tmp_state = getTmpState();
  for (int i = 0; i < ROWS; i++)
    for (int j = 0; j < COLUMNS; j++)
      state->field[i][j] = tmp_state->field[i][j];
}

int genRandFig() {
  int random = rand() % FIG_COUNT;
  return random;
};

void emptyFig() {
  State_t *state = getState();
  for (int i = 0; i < FIG_SIZE; i++)
    for (int j = 0; j < FIG_SIZE; j++) state->next.field[i][j] = 0;
}

void emptyCurFig() {
  StateTMP_t *tmp_state = getTmpState();
  for (int i = 0; i < FIG_SIZE; i++)
    for (int j = 0; j < FIG_SIZE; j++) tmp_state->figure[i][j] = 0;
}

void updateFig(int random_fig) {
  State_t *state = getState();

  emptyFig();
  state->dir = Right;
  state->next_fig = random_fig;

  if (random_fig == I)
    state->next_wide = 4;
  else if (random_fig == O)
    state->next_wide = 2;
  else
    state->next_wide = 3;

  switch (random_fig) {
    case I:
      for (int i = 0; i < FIG_SIZE; i++) state->next.field[0][i] = '*';
      break;
    case L:
      state->next.field[1][2] = '*';
      for (int i = 0; i < FIG_SIZE - 1; i++) state->next.field[0][i] = '*';
      break;
    case J:
      state->next.field[1][0] = '*';
      for (int i = 0; i < FIG_SIZE - 1; i++) state->next.field[0][i] = '*';
      break;
    case S:
      for (int i = 0; i < FIG_SIZE - 2; i++) state->next.field[0][i] = '*';
      for (int i = 1; i < FIG_SIZE - 1; i++) state->next.field[1][i] = '*';
      break;
    case Z:
      for (int i = 0; i < FIG_SIZE - 2; i++) state->next.field[1][i] = '*';
      for (int i = 1; i < FIG_SIZE - 1; i++) state->next.field[0][i] = '*';
      break;
    case T:
      for (int i = 0; i < FIG_SIZE - 1; i++) state->next.field[0][i] = '*';
      state->next.field[1][1] = '*';
      break;
    case O:
      for (int i = 0; i < FIG_SIZE - 2; i++) {
        state->next.field[i][0] = '*';
        state->next.field[i][1] = '*';
      }
      break;
  }
}

void spawn(UserAction_t action) {
  State_t *state = getState();
  StateTMP_t *tmp_state = getTmpState();

  static int check_gen_figure = 0;
  if (!check_gen_figure) {
    updateFig(genRandFig());
    for (int i = 0; i < FIG_SIZE; i++) {
      for (int j = 0; j < FIG_SIZE; j++) {
        tmp_state->figure[i][j] = state->next.field[i][j];
      }
    }
    state->figure.fig = state->next_fig;
    state->figure.wide = state->next_wide;
    check_gen_figure = 1;
  }
  if (action == Start && !state->start) updateFig(genRandFig());
  state->status = SHIFT;
}

StateTMP_t *getTmpState() {
  static StateTMP_t state;
  return &state;
}

State_t *initState(State_t *state) {
  srand(time(NULL));
  StateTMP_t *tmp_state = getTmpState();
  state->figure.pos.x = (COLUMNS / 2 - 1);
  state->figure.pos.y = -1;
  state->score = 0;
  state->high_score = 0;
  readHighScore(state);
  state->level = 1;
  state->start = 0;
  state->pause = 0;
  state->speed = START_SPEED;
  state->crash = 0;
  state->status = START;
  state->dir = Right;
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      state->field[i][j] = 0;
      tmp_state->field[i][j] = 0;
    }
  }
  return state;
}

int checkCollision() {
  State_t *state = getState();
  StateTMP_t *tmp_state = getTmpState();
  int check = 0;

  for (int i = 0; i < FIG_SIZE; i++) {
    for (int j = 0; j < FIG_SIZE; j++) {
      if (state->figure.pos.y - i >= 0 && tmp_state->figure[i][j] == '*') {
        if (state->figure.pos.y >= ROWS ||
            tmp_state->field[state->figure.pos.y - i]
                            [j + state->figure.pos.x] == '*') {
          check = 1;
        }
      }
    }
  }
  return check;
}

void drawFigInField() {
  State_t *state = getState();
  StateTMP_t *tmp_state = getTmpState();
  for (int i = 0; i < FIG_SIZE; i++) {
    for (int j = 0; j < FIG_SIZE; j++) {
      if (state->figure.pos.y - i >= 0 && tmp_state->figure[i][j] == '*') {
        if (state->figure.pos.y < ROWS &&
            tmp_state->field[state->figure.pos.y - i]
                            [j + state->figure.pos.x] != '*') {
          state->field[state->figure.pos.y - i][j + state->figure.pos.x] =
              tmp_state->figure[i][j];
        }
      }
    }
  }
}

void case_I() {
  State_t *state = getState();
  StateTMP_t *tmp_state = getTmpState();
  if (state->dir == Right) {
    state->dir = None;
    state->figure.wide = 1;
    for (int i = 0; i < FIG_SIZE; i++) tmp_state->figure[i][0] = '*';
  } else {
    state->dir = Right;
    state->figure.wide = 4;
    for (int i = 0; i < FIG_SIZE; i++) tmp_state->figure[0][i] = '*';
  }
}

void case_Z() {
  State_t *state = getState();
  StateTMP_t *tmp_state = getTmpState();
  if (state->dir == Right) {
    state->dir = None;
    state->figure.wide = 2;
    for (int i = 0; i < FIG_SIZE - 2; i++) tmp_state->figure[i][0] = '*';
    for (int i = 1; i < FIG_SIZE - 1; i++) tmp_state->figure[i][1] = '*';
  } else {
    state->dir = Right;
    state->figure.wide = 3;
    for (int i = 0; i < FIG_SIZE - 2; i++) tmp_state->figure[1][i] = '*';
    for (int i = 1; i < FIG_SIZE - 1; i++) tmp_state->figure[0][i] = '*';
  }
}

void case_S() {
  State_t *state = getState();
  StateTMP_t *tmp_state = getTmpState();
  if (state->dir == Right) {
    state->dir = None;
    state->figure.wide = 2;
    for (int i = 0; i < FIG_SIZE - 2; i++) tmp_state->figure[i][1] = '*';
    for (int i = 1; i < FIG_SIZE - 1; i++) tmp_state->figure[i][0] = '*';
  } else {
    state->dir = Right;
    state->figure.wide = 3;
    for (int i = 0; i < FIG_SIZE - 2; i++) tmp_state->figure[0][i] = '*';
    for (int i = 1; i < FIG_SIZE - 1; i++) tmp_state->figure[1][i] = '*';
  }
}

void case_T() {
  State_t *state = getState();
  StateTMP_t *tmp_state = getTmpState();
  if (state->dir == Right) {
    state->dir = None;
    state->figure.wide = 2;
    for (int i = 0; i < FIG_SIZE - 1; i++) tmp_state->figure[i][0] = '*';
    tmp_state->figure[1][1] = '*';
  } else if (state->dir == None) {
    state->dir = Left;
    state->figure.wide = 3;
    for (int i = 0; i < FIG_SIZE - 1; i++) tmp_state->figure[1][i] = '*';
    tmp_state->figure[0][1] = '*';
  } else if (state->dir == Left) {
    state->dir = Up;
    state->figure.wide = 2;
    for (int i = 0; i < FIG_SIZE - 1; i++) tmp_state->figure[i][1] = '*';
    tmp_state->figure[1][0] = '*';
  } else {
    state->dir = Right;
    state->figure.wide = 3;
    for (int i = 0; i < FIG_SIZE - 1; i++) tmp_state->figure[0][i] = '*';
    tmp_state->figure[1][1] = '*';
  }
}

void case_L() {
  State_t *state = getState();
  StateTMP_t *tmp_state = getTmpState();
  if (state->dir == Right) {
    state->dir = None;
    state->figure.wide = 2;
    for (int i = 0; i < FIG_SIZE - 1; i++) tmp_state->figure[i][0] = '*';
    tmp_state->figure[0][1] = '*';
  } else if (state->dir == None) {
    state->dir = Left;
    state->figure.wide = 3;
    for (int i = 0; i < FIG_SIZE - 1; i++) tmp_state->figure[1][i] = '*';
    tmp_state->figure[0][0] = '*';
  } else if (state->dir == Left) {
    state->dir = Up;
    state->figure.wide = 2;
    for (int i = 0; i < FIG_SIZE - 1; i++) tmp_state->figure[i][1] = '*';
    tmp_state->figure[2][0] = '*';
  } else {
    state->dir = Right;
    state->figure.wide = 3;
    for (int i = 0; i < FIG_SIZE - 1; i++) tmp_state->figure[0][i] = '*';
    tmp_state->figure[1][2] = '*';
  }
}

void case_J() {
  State_t *state = getState();
  StateTMP_t *tmp_state = getTmpState();
  if (state->dir == Right) {
    state->dir = None;
    state->figure.wide = 2;
    for (int i = 0; i < FIG_SIZE - 1; i++) tmp_state->figure[i][0] = '*';
    tmp_state->figure[2][1] = '*';
  } else if (state->dir == None) {
    state->dir = Left;
    state->figure.wide = 3;
    for (int i = 0; i < FIG_SIZE - 1; i++) tmp_state->figure[1][i] = '*';
    tmp_state->figure[0][2] = '*';
  } else if (state->dir == Left) {
    state->dir = Up;
    state->figure.wide = 2;
    for (int i = 0; i < FIG_SIZE - 1; i++) tmp_state->figure[i][1] = '*';
    tmp_state->figure[0][0] = '*';
  } else {
    state->dir = Right;
    state->figure.wide = 3;
    for (int i = 0; i < FIG_SIZE - 1; i++) tmp_state->figure[0][i] = '*';
    tmp_state->figure[1][0] = '*';
  }
}

void rotateFig() {
  State_t *state = getState();
  if (state->figure.fig != O) emptyCurFig();
  switch (state->figure.fig) {
    case I:
      case_I();
      break;
    case Z:
      case_Z();
      break;
    case S:
      case_S();
      break;
    case T:
      case_T();
      break;
    case L:
      case_L();
      break;
    case J:
      case_J();
      break;
  }
}

void shiftFig() {
  State_t *state = getState();

  if (state->action == Left) {
    if (state->figure.pos.x > 0) state->figure.pos.x -= 1;
    if (checkCollision()) state->figure.pos.x += 1;

  } else if (state->action == Right) {
    if (state->figure.pos.x < COLUMNS - state->figure.wide)
      state->figure.pos.x += 1;
    if (checkCollision()) state->figure.pos.x -= 1;

  } else if (state->action == Action) {
    rotateFig();
    // if(state->figure.wide == 4){
    //   int x_dep = COLUMNS - state->figure.pos.x;

    // } else
    if (checkCollision() ||
        state->figure.pos.x > COLUMNS - state->figure.wide) {
      rotateFig();
      rotateFig();
      rotateFig();
    }
  } else if (state->action == Down) {
    int go = 1;
    while (go) {
      go = stepDown();
    }
  }
}

void checkFullLine() {
  State_t *state = getState();
  StateTMP_t *tmp_state = getTmpState();
  int count = 0;
  for (int i = ROWS - 1; i >= 0; i--) {
    int check = 1;
    for (int j = 0; (j < COLUMNS) && check; j++) {
      if (state->field[i][j] == 0) check = 0;
    }
    if (check) {
      for (int k = i; k > 0; k--) {
        for (int j = 0; j < COLUMNS; j++)
          tmp_state->field[k][j] = state->field[k - 1][j];
      }
      copyFieldFromTmp();
      i++, count++;
    }
  }
  if (state->score < __INT32_MAX__ - 1500) switch (count) {
      case 1:
        state->score += 100;
        break;
      case 2:
        state->score += 300;
        break;
      case 3:
        state->score += 700;
        break;
      case 4:
        state->score += 1500;
    }
}

void checkGameOver() {
  State_t *state = getState();
  for (int j = 0; j < COLUMNS; j++) {
    if (state->field[0][j] == '*') {
      state->game_over = 1;
      state->status = GAMEOVER;
      return;
    }
  }
}

void updateInfo() {
  State_t *state = getState();
  for (int i = 10; i > 1; i--) {
    if (state->score >= NEXT_LEVEL * (i - 1)) {
      state->level = i;
      state->speed = START_SPEED - START_SPEED / 10 * (i - 1);
      break;
    }
  }
  if (state->score > state->high_score) {
    saveHighScore(state);
    state->high_score = state->score;
  }
}

void saveHighScore(State_t *state) {
  FILE *file = fopen("tetris_score.txt", "w");
  if (file) {
    fprintf(file, "%d", state->score);
    fclose(file);
  }
};

void readHighScore(State_t *state) {
  FILE *file = fopen("tetris_score.txt", "r");
  if (file) {
    int score = 0;
    if (fscanf(file, "%d", &score) == 1) state->high_score = score;
    fclose(file);
  }
};

void attachFig() {
  State_t *state = getState();
  if (state->crash) {
    copyFieldToTmp();
    checkFullLine();
    state->figure.fig = state->next_fig;
    state->figure.wide = state->next_wide;
    copyFigToTmp();
    updateFig(genRandFig());
    state->figure.pos.x = (COLUMNS / 2 - 1);
    state->figure.pos.y = -1;
    state->crash = 0;
    updateInfo();
    checkGameOver();
  } else {
    copyFieldFromTmp();
  }
  if (state->status != GAMEOVER) state->status = SHIFT;
}

int stepDown() {
  int go = 1;
  State_t *state = getState();
  state->figure.pos.y += 1;
  if (checkCollision()) state->crash = 1;
  if (state->crash) {
    state->figure.pos.y -= 1;
    go = 0;
  }
  return go;
}
