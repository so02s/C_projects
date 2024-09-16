#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef GREP_FUNC
#define GREP_FUNC

struct flag {
  int value;
  char name;
};

int flag_parc(int argc, char *argv[], struct flag *flags, char *ones_flag,
              struct option long_options[], char *E_arg[], char *F_arg[],
              int *e_arg, int *f_arg);
int grep_line(char *tmp, char *pattern, int iflag);
void find_pattern_in_file(char *filename, char *pattern[], int pat_n,
                          char *files[], int files_n, struct flag *fl,
                          int many_files);
void printer_grep_outline(char *filename, struct flag *fl, int attract_lines,
                          int many_files);
void printer_grep_inline(char *str, char *filename, int find, struct flag *fl,
                         int str_ind, int *attract_lines, int many_files,
                         int *print_ent);
void pattern_handler(int *find, char *str_tmp, char *pattern[], int p_n,
                     char *files[], int f_n, struct flag *fl, int many_f,
                     char *file);
int grep_line_o(char *source, char *pattern, char *filename, int hflag,
                int many_files);

#endif