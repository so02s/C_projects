#include <stdio.h>

#include "grep_func.h"

int main(int argc, char *argv[]) {
  //структурки для флагов
  struct flag fl[] = {{0, 'e'}, {0, 'i'}, {0, 'v'}, {0, 'c'}, {0, 'l'},
                      {0, 'n'}, {0, 'h'}, {0, 's'}, {0, 'f'}, {0, 'o'}};
  static struct option long_options[] = {{0, 0, 0, 0}};
  char *patterns[argc], *files[argc];
  int many_files = 0, pat_n = 0, files_n = 0;
  //выходы при неправильном вводе и парсинг флагов
  if (argc < 3) {
    printf(
        "no files: _grep [-ivclnhso] [-e pattern] [-f file] [pattern] [file "
        "...]\n");
    return 1;
  }
  int i = flag_parc(argc, argv, fl, "ivclnhsoe:f:", long_options, patterns,
                    files, &pat_n, &files_n);
  if (i == -1 || (fl[0].value && (i > argc))) {
    printf(
        "usage: _grep [-ivclnhso] [-e pattern] [-f file] [pattern] [file "
        "...]\n");
    return 1;
  }

  //шаблон и обработка файлов
  if (!fl[0].value && !fl[8].value) {
    patterns[pat_n] = argv[i];
    pat_n++;
    i++;
  }
  if (argc - i > 1) many_files = 1;
  for (; i < argc; i++) {
    find_pattern_in_file(argv[i], patterns, pat_n, files, files_n, fl,
                         many_files);
  }
  return 0;
}
