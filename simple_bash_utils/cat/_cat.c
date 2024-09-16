#include <getopt.h>
#include <stdio.h>

#include "cat_func.h"

int main(int argc, char* argv[]) {
  //структурки для флагов
  struct flag fl[] = {{0, 'n'}, {0, 'b'}, {0, 's'},
                      {0, 'v'}, {0, 'E'}, {0, 'T'}};
  static struct option long_options[] = {
      {"number-nonblank", no_argument, 0, 'b'},
      {"number", no_argument, 0, 'n'},
      {"squeeze-blank", no_argument, 0, 's'},
      {0, 0, 0, 0}};
  int i = 0;

  //эти выходы - только при неправильном вводе
  if (argc == 1) {
    printf("no files: _cat [-bnsetvET] [file ...]\n");
    return 1;
  }
  i = flag_parc(argc, argv, fl, "bnsetvET", long_options);
  if (i == -1) {
    printf("usage: _cat [-bnsetvET] [file ...]\n");
    return 1;
  }
  if (i == argc) printf("no files: _cat [-bnsetET] [file ...]\n");

  //тут штука с обрабатыванием флагов
  for (; i < argc; i++) print_file(argv[i], fl);

  return 0;
}