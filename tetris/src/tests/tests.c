#include <check.h>

#include "../brick_game/tetris/fms.h"
#include "../common.h"

//чертовы тесты

START_TEST(init) {
  int error = 0;
  GameInfo_t *info = getInfo();
  State_t *state = getState();

  error = initInfo(info);
  if (!error) {
    state->action = Start;
    game();
    game();
  }
  ck_assert_int_eq(state->figure.pos.x, 4);
  ck_assert_int_eq(state->figure.pos.y, 1);
  clearInfo(info);
}
END_TEST

START_TEST(gameover) {
  int error = 0;
  GameInfo_t *info = getInfo();
  State_t *state = getState();

  error = initInfo(info);
  if (!error) {
    gameOver(state);
  }
  checkFullLine();
  ck_assert_int_eq(state->level, -1);
  clearInfo(info);
}
END_TEST

START_TEST(pausegame) {
  int error = 0;
  GameInfo_t *info = getInfo();
  State_t *state = getState();

  error = initInfo(info);
  if (!error) {
    state->action = Pause;
    game();
  }
  ck_assert_int_eq(state->figure.pos.x, 4);
  ck_assert_int_eq(state->figure.pos.y, 3);
  clearInfo(info);
}
END_TEST

START_TEST(end_pausegame) {
  int error = 0;
  GameInfo_t *info = getInfo();
  State_t *state = getState();

  error = initInfo(info);
  if (!error) {
    state->action = Pause;
    game();
    state->action = None;
    game();
  }
  ck_assert_int_eq(state->figure.pos.x, 4);
  ck_assert_int_eq(state->figure.pos.y, 4);
  clearInfo(info);
}
END_TEST

START_TEST(terminate) {
  int error = 0;
  GameInfo_t *info = getInfo();
  State_t *state = getState();

  error = initInfo(info);
  if (!error) {
    game();
    state->action = Terminate;
    game();
  }
  saveHighScore(state);
  ck_assert_int_eq(info->level, -1);
  clearInfo(info);
}
END_TEST

START_TEST(rotatefig) {
  int error = 0;
  GameInfo_t *info = getInfo();
  State_t *state = getState();

  error = initInfo(info);
  if (!error) {
    state->action = Action;
    game();
  }
  ck_assert_int_eq(state->figure.pos.x, 4);
  ck_assert_int_eq(state->figure.pos.y, 5);
  clearInfo(info);
}
END_TEST

START_TEST(attachfig) {
  int error = 0;
  GameInfo_t *info = getInfo();
  State_t *state = getState();

  error = initInfo(info);
  if (!error) {
    for (int i = 0; i < 100; ++i) {
      state->action = Down;
      game();
    }
  }
  ck_assert_int_eq(state->figure.pos.x, 4);
  clearInfo(info);
}
END_TEST

START_TEST(figs) {
  int error = 0;
  GameInfo_t *info = getInfo();
  State_t *state = getState();

  error = initInfo(info);
  if (!error) {
    game();
    for (int i = O; i <= I; ++i) {
      state->figure.fig = i;
      rotateFig();
      rotateFig();
      rotateFig();
      rotateFig();
      game();
    }
  }
  ck_assert_int_eq(state->figure.pos.x, 4);
  clearInfo(info);
}
END_TEST

START_TEST(left_move) {
  int error = 0;
  GameInfo_t *info = getInfo();
  State_t *state = getState();

  error = initInfo(info);
  if (!error) {
    state->action = Left;
    game();
  }
  ck_assert_int_eq(state->figure.pos.x, 3);
  ck_assert_int_eq(state->figure.pos.y, 2);
  clearInfo(info);
}
END_TEST

START_TEST(right_move) {
  int error = 0;
  GameInfo_t *info = getInfo();
  State_t *state = getState();

  error = initInfo(info);
  if (!error) {
    state->action = Right;
    game();
  }
  ck_assert_int_eq(state->figure.pos.x, 4);
  ck_assert_int_eq(state->figure.pos.y, 3);
  clearInfo(info);
}
END_TEST

START_TEST(fullline) {
  int error = 0;
  GameInfo_t *info = getInfo();
  State_t *state = getState();

  error = initInfo(info);
  if (!error) {
    for (int i = 0; i < COLUMNS; i++) {
      state->field[3][i] = '*';
      state->field[2][i] = '*';
    }
  }
  checkFullLine();
  ck_assert_int_eq(state->field[0][0], 0);
  clearInfo(info);
}
END_TEST

Suite *suite_tetris(void) {
  Suite *s = suite_create("suite_tetris");
  TCase *tc = tcase_create("case_tetris");

  tcase_add_test(tc, init);
  tcase_add_test(tc, left_move);
  tcase_add_test(tc, right_move);
  tcase_add_test(tc, pausegame);
  tcase_add_test(tc, end_pausegame);
  tcase_add_test(tc, rotatefig);
  tcase_add_test(tc, attachfig);
  tcase_add_test(tc, figs);
  tcase_add_test(tc, terminate);
  tcase_add_test(tc, fullline);
  tcase_add_test(tc, gameover);

  suite_add_tcase(s, tc);
  return s;
}

void run_testcase(Suite *testcase) {
  printf("\n");
  SRunner *sr = srunner_create(testcase);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);
}

int main(void) {
  run_testcase(suite_tetris());
  return 0;
}