#include "grep_func.h"

// gfhcbyu
int flag_parc(int argc, char *argv[], struct flag *flags, char *ones_flag,
              struct option long_options[], char *E_arg[], char *F_arg[],
              int *e_arg, int *f_arg) {
  int rez, i = 1, index = 0, size = 0;
  while (i < argc && argv[i][0] == '-') {
    size += strlen(argv[i]) - 1;
    if (argv[i][1] == 'e' || argv[i][1] == 'f') i++;
    i++;
  }
  while ((rez = getopt_long(argc, argv, ones_flag, long_options, NULL)) !=
             '?' &&
         rez != -1 && index != size) {
    if (rez == '?') break;
    if (optarg) {
      if (rez == 'e') {
        E_arg[*e_arg] = optarg;
        (*e_arg)++;
      } else if (rez == 'f') {
        FILE *file = fopen(optarg, "r");
        if (file) {
          F_arg[*f_arg] = optarg;
          (*f_arg)++;
          fclose(file);
        } else {
          printf("_grep: %s: No such file or directory\n", optarg);
        }
      }
    }
    for (int j = 0; j < 10; j++)
      if (flags[j].name == rez) {
        flags[j].value = 1;
      }
    index++;
  }
  if (rez == '?') i = -1;
  return i;
}

//поиск по файлу всех шаблонов
//на вход имя файла, паттерны и флаги
void find_pattern_in_file(char *filename, char *pattern[], int p_n,
                          char *files[], int f_n, struct flag *fl,
                          int many_files) {
  FILE *file = fopen(filename, "r");
  char *str_tmp = NULL;
  int find = 0, str_ind = 0, attract_lines = 0, print_ent = 0, result = 0;
  size_t buffsize = 0;
  if (file) {
    result = getline(&str_tmp, &buffsize, file);
    while (result != -1) {
      str_ind++;
      pattern_handler(&find, str_tmp, pattern, p_n, files, f_n, fl, many_files,
                      filename);
      printer_grep_inline(str_tmp, filename, find, fl, str_ind, &attract_lines,
                          many_files, &print_ent);
      if (fl[4].value && find && !fl[2].value) break;
      result = getline(&str_tmp, &buffsize, file);
    }
    printer_grep_outline(filename, fl, attract_lines, many_files);
    fclose(file);
    if (print_ent) printf("\n");
  } else if (!fl[7].value)
    printf("_grep: %s: No such file or directory\n", filename);
  free(str_tmp);
}

//на вход строка, паттерн и флаги
int grep_line(char *tmp, char *pattern, int iflag) {
  regex_t rx;
  int regcomp_rez = 0, error = 0;
  iflag ? regcomp(&rx, pattern, REG_ICASE) : regcomp(&rx, pattern, 0);
  regcomp_rez = regexec(&rx, tmp, 0, NULL, 0);
  if (regcomp_rez != 0 && regcomp_rez != 1) error = 1;
  regcomp_rez = regcomp_rez ? 0 : 1;
  regfree(&rx);
  return (error) ? -1 : regcomp_rez;
}

//всякие выводы
void printer_grep_inline(char *str, char *filename, int find, struct flag *fl,
                         int str_ind, int *attract_lines, int many_files,
                         int *print_ent) {
  if ((!fl[2].value && find == 1) || (fl[2].value && find == 0)) {  // v-флаг
    (*attract_lines)++;  //увеличение счетчика "привлекательных строк"
    if (!fl[4].value &&
        !fl[3].value) {  // если нажат l или c флаги --- не выводить
      if (many_files && !fl[6].value)
        printf("%s:", filename);  // h-флаг --- вывод имени файла
      if (fl[5].value) printf("%d:", str_ind);  // n-флаг --- номер строки
      if (!fl[9].value) printf("%s", str);
      *print_ent = (str[strlen(str) - 1] != '\n');
    }
  }
}
void printer_grep_outline(char *filename, struct flag *fl, int attract_lines,
                          int many_files) {
  if (fl[3].value) {  // c флаг ----  вывод количества совпадений
    if (many_files && !fl[6].value)
      printf("%s:", filename);  // h-флаг --- вывод имени файла
    printf("%d\n", attract_lines);
  }
  if (fl[4].value && attract_lines)
    printf("%s\n", filename);  // l-флаг  ---  вывод только совпавших файлов
}

//обработка шаблонов
void pattern_handler(int *find, char *str_tmp, char *pattern[], int p_n,
                     char *files[], int f_n, struct flag *fl, int many_f,
                     char *file) {
  *find = 0;
  FILE *file_pat = NULL;
  char *pat_tmp = NULL;
  size_t buffsize = 0;
  int result = 0;

  //проход по паттернам
  for (int i = 0; i < p_n; i++) {
    *find = (fl[9].value && !fl[3].value && !fl[4].value)
                ? grep_line_o(str_tmp, pattern[i], file, fl[6].value, many_f)
                : grep_line(str_tmp, pattern[i], fl[1].value);
    if (*find) break;
  }
  //проход по файлам с паттернами
  if (!(*find)) {
    for (int i = 0; i < f_n; i++) {
      file_pat = fopen(files[i], "r");
      result = getline(&pat_tmp, &buffsize, file_pat);
      while (result != -1) {  //Я НЕ ОЧЕНЬ ЛЮБЛЮ ЭТУ ЧЕРТОВУ ПАМЯТЬ - НИКАКОГО
                              //БУФЕРА ХАХАХХАХАХА
        if ((pat_tmp[strlen(pat_tmp) - 1] == '\n') &&
            (strlen(pat_tmp) != 1))  // дурацкие \n и их поиск
          pat_tmp[strlen(pat_tmp) - 1] = 0;
        *find = (fl[9].value && !fl[3].value && !fl[4].value)
                    ? grep_line_o(str_tmp, pat_tmp, file, fl[6].value, many_f)
                    : grep_line(str_tmp, pat_tmp, fl[1].value);
        if (*find) break;
        result = getline(&pat_tmp, &buffsize, file_pat);
      }
      free(pat_tmp);
      fclose(file_pat);
      pat_tmp = NULL;
      if (*find) break;
    }
  }
}

int grep_line_o(char *source, char *pattern, char *filename, int hflag,
                int many_files) {
  size_t maxGroups = 1000;
  regex_t regexCompiled;
  regmatch_t groupArray[1000];
  char *cursor;
  int find = 0;
  if (regcomp(&regexCompiled, pattern, REG_EXTENDED)) {
    printf("Could not compile regular expression.\n");
  } else {
    cursor = source;
    while (!regexec(&regexCompiled, cursor, maxGroups, groupArray, 0)) {
      unsigned int offset = 0;
      offset = groupArray[0].rm_eo;
      char cursorCopy[strlen(cursor) + 1];
      strcpy(cursorCopy, cursor);
      cursorCopy[groupArray[0].rm_eo] = 0;
      if (many_files && !hflag) printf("%s:", filename);
      printf("%s\n", cursorCopy + groupArray[0].rm_so);
      cursor += offset;
      find = 1;
    }
  }
  regfree(&regexCompiled);
  return find;
}