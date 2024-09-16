#include "brick_game/tetris/fms.h"
#include "common.h"

int main(void) {
  int error = 0;
  GameInfo_t *info = getInfo();
  
  initscr();
  settingNcurcesGame();
  error = initInfo(info);
  if (!error) {
    while (info->level != -1) {
      userInput(None, 1);
      game();
      gui(*info);
    }
  }
  clearInfo(info);
  endwin();
  return 0;
}

void userInput(UserAction_t action, int hold) {
  State_t *state = getState();
  (void)hold;
  state->action = action;
  int ch = getch();
  if (ch != ERR) {
    switch (ch) {
      case KEY_LEFT:
      case 'A':
      case 'a':
        state->action = Left;
        break;
      case KEY_RIGHT:
      case 'D':
      case 'd':
        state->action = Right;
        break;
      case KEY_DOWN:
      case 'S':
      case 's':
        state->action = Down;
        break;
      case ' ':
        state->action = Action;
        break;
      case 'q':
      case 'Q':
        state->action = Terminate;
        break;
      case 'p':
      case 'P':
        state->action = Pause;
        break;
      case 'e':
      case 'E':
        state->action = Start;
        break;
      default:
        state->action = None;
    }
  }
};