#include "cli.h"

void settingNcurcesGame() {
  noecho();
  nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);
  printf("\033[8;%d;%dt", WIDTH + 2, COLUMNS * 2 + 20);
}

void settingNcurcesLose() {
  echo();
  nodelay(stdscr, FALSE);
}

void gui(GameInfo_t info) {
  if (info.field == NULL || info.next == NULL) {
    settingNcurcesLose();
    printf("error with GameInfo_t");
    return;
  }

  if (info.level == -1) {
    bool game_over = 1;
    settingNcurcesLose();
    while (game_over) {
      gameOverScreen(&info);
      game_over = userInputButton(&info);
    }
    settingNcurcesGame();
  } else
    gameScreen(&info);

  timeout(info.speed);
}

void gameScreen(GameInfo_t *info) {
  WINDOW *win = newwin(HEIGTH, WIDTH * 2, 0, 0);
  WINDOW *playwin = subwin(win, ROWS + 2, COLUMNS * 2 + 2, 1, 1);
  WINDOW *next_figure_win = subwin(win, 6, 10, 1, COLUMNS * 2 + 4);
  WINDOW *dop_info = subwin(win, 10, 10, 8, COLUMNS * 2 + 4);
  char level[10], score[10], high_score[10];
  sprintf(level, "%d", info->level);
  sprintf(score, "%d", info->score);
  sprintf(high_score, "%d", info->high_score);
  box(win, 0, 0);
  box(playwin, 0, 0);
  box(next_figure_win, 0, 0);
  for (int i = 0; i < FIG_SIZE; i++)
    for (int j = 0; j < FIG_SIZE * 2; j++)
      if (info->next == NULL)
        mvwaddch(next_figure_win, j + 1, i + 1,
                 (i + j) % 2 == 1 ? ' ' | A_REVERSE : ' ');
      else
        mvwaddch(next_figure_win, 3 - i + 1, j + 1,
                 (info->next[i][j / 2]) ? ' ' | A_REVERSE : ' ');

  mvwaddstr(dop_info, 0, 0, "level:");
  mvwaddstr(dop_info, 1, 0, level);
  mvwaddstr(dop_info, 4, 0, "score: ");
  mvwaddstr(dop_info, 5, 0, score);
  mvwaddstr(dop_info, 8, 0, "high score: ");
  mvwaddstr(dop_info, 9, 0, high_score);

  for (int i = 0; i < ROWS; i++)
    for (int j = 0; j < COLUMNS * 2; j++) {
      mvwaddch(playwin, i + 1, j + 1,
               (info->field[i][j / 2]) ? ' ' | A_REVERSE : ' ');
    }

  wrefresh(win);
}

void gameOverScreen(GameInfo_t *info) {
  const char *mes_lose = "GAME OVER";
  const char *mes_score = "You're score: ";
  const char *choice = "exit";
  int index_x = WIDTH / 2 + 1, index_y = HEIGTH / 2;
  WINDOW *win = newwin(HEIGTH, WIDTH * 2, 0, 0);
  box(win, 0, 0);
  wattron(win, A_BOLD);
  mvwaddstr(win, index_y - 5, index_x - strlen(mes_lose) / 2, mes_lose);
  wattroff(win, A_BOLD);
  mvwaddstr(win, index_y, index_x - strlen(mes_score), mes_score);
  mvwprintw(win, index_y, index_x, "%d", info->score);
  wattron(win, A_REVERSE);
  mvwaddstr(win, index_y + 6, index_x - strlen(choice) / 2, choice);
  wattroff(win, A_REVERSE);
  wrefresh(win);
}

bool userInputButton(GameInfo_t *info) {
  bool no_exit = 1;
  int ch = getch();
  switch (ch) {
    case 'q':
    case 'Q':
    case ENTER:
      info->level = -1;
      no_exit = 0;
  }
  return no_exit;
}
