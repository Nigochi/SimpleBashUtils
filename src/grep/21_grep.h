#include <stdbool.h>

#ifndef GREP_H_
#define GREP_H_

typedef struct {
  bool flag_e;
  bool flag_i;
  bool flag_l;
  bool flag_v;
  bool flag_c;
  bool flag_n;
  bool flag_h;
  bool flag_o;
  int flag_for_regexcomp;
  bool flag_free;
} grep_info;

typedef struct {
  char **e_patterns;
  char **i_patterns;
  char **l_patterns;
  char **v_patterns;
  char **c_patterns;
  char **n_patterns;
  char **h_patterns;
  char **o_patterns;
  char **free_patterns;
} pattern;

typedef struct {
  int e_count;
  int i_count;
  int l_count;
  int v_count;
  int c_count;
  int n_count;
  int h_count;
  int o_count;
  int free_count;
} count;

#endif  // 21_GREP_H_