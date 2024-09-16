#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef CAT_FUNC
#define CAT_FUNC

struct flag {
  int value;
  char name;
};

int flag_parc(int argc, char* argv[], struct flag* flags, char* ones_flag,
              struct option long_options[]);
void print_file(char* name, struct flag* fl);
void print_with_flag(FILE* file, int flag_n, int flag_b, int flag_s, int flag_v,
                     int flag_e, int flag_t);

#endif