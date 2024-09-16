#include "cat_func.h"

// парсинг флагов
int flag_parc(int argc, char* argv[], struct flag* flags, char* ones_flag,
              struct option long_options[]) {
  int i = 1, index = 0, size = 0, rez = 0;
  rez = getopt_long(argc, argv, ones_flag, long_options, NULL);
  while (argv[i][0] == '-') {
    size += strlen(argv[i]) - 1;
    i++;
  }
  while (rez != '?' && rez != -1 && index != size) {
    if (rez == '?') break;
    for (int j = 0; j < 6; j++) {
      if (flags[j].name == rez) flags[j].value = 1;
      if (rez == 't')
        if (flags[j].name == 'T' || flags[j].name == 'v') flags[j].value = 1;
      if (rez == 'e')
        if (flags[j].name == 'E' || flags[j].name == 'v') flags[j].value = 1;
    }
    index++;
    rez = getopt_long(argc, argv, ones_flag, long_options, NULL);
  }
  if (rez == '?') i = -1;
  return i;
}

// проверка на возможность откыть файл
void print_file(char* name, struct flag* fl) {
  FILE* file;
  file = fopen(name, "rt");
  if (file == NULL)
    printf("_cat: %s: No such file or directory\n", name);
  else {
    print_with_flag(file, fl[0].value, fl[1].value, fl[2].value, fl[3].value,
                    fl[4].value, fl[5].value);
    fclose(file);
  }
}

// собственно, печать файла с флагами
void print_with_flag(FILE* file, int flag_n, int flag_b, int flag_s, int flag_v,
                     int flag_e, int flag_t) {
  int begin_line = 1, index_line = 1, print = 1, ch = 0, enter = 0,
      no_index = 0;
  while ((ch = fgetc(file)) != EOF) {
    print = 1;
    no_index = 0;
    enter = (ch == '\n') ? enter + 1 : 0;
    if (flag_s && (enter == 3)) {
      begin_line = 1;
      print = 0;
      enter = 2;
      no_index = 1;
    } else if ((flag_b && begin_line && !enter) ||
               (!flag_b && flag_n && begin_line)) {
      printf("%6d\t", index_line);
      begin_line = 0;
    }
    if (flag_e && enter && print) {
      begin_line = 1;
      printf("$");
    }
    if (flag_t && (ch == 9)) {
      printf("^I");
      print = 0;
    }
    if (flag_v) {
      if (ch > 127 && ch < 160) printf("M-^");
      if ((ch < 32 && !enter && ch != '\t') || ch == 127) printf("^");
      if ((ch < 32 || (ch > 126 && ch < 160)) && !enter && ch != '\t')
        ch = ch > 126 ? ch - 128 + 64 : ch + 64;
    }
    if (enter && (!flag_b || (enter == 1)) && !no_index) {
      begin_line = 1;
      index_line++;
    }
    if (print) printf("%c", ch);
  }
}