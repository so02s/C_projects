#ifndef _COMMON_H
#define _COMMON_H

#define ROWS 20
#define COLUMNS 10
#define FIG_SIZE 4
#define WIDTH COLUMNS + 13
#define HEIGTH 24
#define ENTER 10

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action,
  None,
} UserAction_t;

void userInput(UserAction_t action, int hold);
GameInfo_t updateCurrentState();
GameInfo_t *getInfo();

#endif