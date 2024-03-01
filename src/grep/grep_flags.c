#include <fcntl.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "21_grep.h"
#include "grep_helpers.h"

void grep_without_flags(FILE *file, pattern *patterns, count *count_patt,
                        char *file_name, bool flag, bool last_file) {
  if (patterns->free_patterns[0] != NULL) {
    without_flags_helper(file, patterns, count_patt, file_name, flag,
                         last_file);
  }
}

void grep_o(FILE *file, pattern *patterns, count *count_patt, char *file_name,
            bool flag, grep_info *info) {
  int count_all = 1;
  if (patterns->free_patterns[0] != NULL) {
    count_all += o_helper(file, info, patterns->free_patterns,
                          count_patt->free_count, flag, file_name);
  }
  if (patterns->e_patterns[0] != NULL) {
    rewind(file);
    count_all += o_helper(file, info, patterns->e_patterns, count_patt->e_count,
                          flag, file_name);
  }
  if (patterns->i_patterns[0] != NULL) {
    rewind(file);
    count_all += o_helper(file, info, patterns->i_patterns, count_patt->i_count,
                          flag, file_name);
  }
  if (patterns->v_patterns[0] != NULL) {
    rewind(file);
    count_all += o_helper(file, info, patterns->v_patterns, count_patt->v_count,
                          flag, file_name);
  }
}

void grep_h(FILE *file, pattern *patterns, count *count_patt, grep_info *info) {
  if (patterns->free_patterns[0] != NULL) {
    h_helper(file, info, patterns->free_patterns, count_patt->free_count);
  }
  if (patterns->h_patterns[0] != NULL) {
    h_helper(file, info, patterns->h_patterns, count_patt->h_count);
  }
  if (patterns->e_patterns[0] != NULL) {
    h_helper(file, info, patterns->e_patterns, count_patt->e_count);
  }
  if (patterns->i_patterns[0] != NULL) {
    h_helper(file, info, patterns->i_patterns, count_patt->i_count);
  }
  if (patterns->v_patterns[0] != NULL) {
    h_helper(file, info, patterns->v_patterns, count_patt->v_count);
  }
}

void grep_n(FILE *file, pattern *patterns, count *count_patt, char *file_name,
            bool flag, grep_info *info, bool last_file) {
  int count_all = 1;
  if (patterns->free_patterns[0] != NULL) {
    count_all += n_helper(file, info, patterns->free_patterns,
                          count_patt->free_count, flag, file_name, last_file);
  }
  if (patterns->e_patterns[0] != NULL) {
    count_all += n_helper(file, info, patterns->e_patterns, count_patt->e_count,
                          flag, file_name, last_file);
  }
  if (patterns->v_patterns[0] != NULL) {
    count_all +=
        v_helper_for_n(file, info, patterns->v_patterns, count_patt->v_count,
                       flag, file_name, last_file);
    if (last_file) {
      printf("\n");
    }
  }
}

bool grep_l(FILE *file, pattern *patterns, count *count_patt, char *file_name,
            grep_info *info) {
  bool flag_output;
  if (patterns->free_patterns[0] != NULL) {
    flag_output =
        l_helper(file, info, patterns->free_patterns, count_patt->free_count);
  }
  if (patterns->e_patterns[0] != NULL) {
    flag_output =
        l_helper(file, info, patterns->e_patterns, count_patt->e_count);
  }
  if (patterns->i_patterns[0] != NULL) {
    flag_output =
        l_helper(file, info, patterns->i_patterns, count_patt->i_count);
  }
  if (patterns->v_patterns[0] != NULL) {
    flag_output =
        l_helper(file, info, patterns->v_patterns, count_patt->v_count);
  }
  if (flag_output && !info->flag_c) {
    puts(file_name);
  }
  return flag_output;
}

void grep_c(FILE *file, pattern *patterns, count *count_patt, char *file_name,
            bool flag, grep_info *info) {
  int count_all = 0;
  if (patterns->free_patterns[0] != NULL) {
    count_all +=
        c_helper(file, info, patterns->free_patterns, count_patt->free_count);
  }
  if (patterns->v_patterns[0] != NULL) {
    count_all +=
        v_helper_for_c(file, info, patterns->v_patterns, count_patt->v_count);
  }
  if (patterns->e_patterns[0] != NULL) {
    count_all +=
        c_helper(file, info, patterns->e_patterns, count_patt->e_count);
  }
  if (patterns->i_patterns[0] != NULL) {
    count_all +=
        c_helper(file, info, patterns->i_patterns, count_patt->i_count);
  }
  if (flag && !info->flag_h) {
    printf("%s:", file_name);
  }
  if (info->flag_l && grep_l(file, patterns, count_patt, file_name, info)) {
    count_all = 1;
    printf("%d\n", count_all);
    puts(file_name);
  }
  if (info->flag_l && !grep_l(file, patterns, count_patt, file_name, info)) {
    count_all = 0;
    printf("%d\n", count_all);
  }
  if (!info->flag_l) {
    printf("%d\n", count_all);
  }
}

void grep_i(FILE *file, pattern *patterns, count *count_patt, char *file_name,
            bool flag, grep_info *info, bool last_file) {
  if (patterns->i_patterns[0] != NULL) {
    i_helper(file, info, patterns->i_patterns, count_patt->i_count, flag,
             file_name, last_file);
  }
  if (patterns->e_patterns[0] != NULL) {
    i_helper(file, info, patterns->e_patterns, count_patt->e_count, flag,
             file_name, last_file);
  }
  if (patterns->free_patterns[0] != NULL) {
    i_helper(file, info, patterns->free_patterns, count_patt->free_count, flag,
             file_name, last_file);
  }
}

void grep_v(FILE *file, pattern *patterns, count *count_patt, char *file_name,
            bool flag, grep_info *info, bool last_file) {
  if (patterns->free_patterns[0] != NULL) {
    v_helper(file, info, patterns->free_patterns, count_patt->free_count, flag,
             file_name, last_file);
    if (last_file) {
      printf("\n");
    }
  }
  if (patterns->v_patterns[0] != NULL) {
    v_helper(file, info, patterns->v_patterns, count_patt->v_count, flag,
             file_name, last_file);
    if (last_file) {
      printf("\n");
    }
  }
  if (patterns->i_patterns[0] != NULL) {
    v_helper(file, info, patterns->i_patterns, count_patt->i_count, flag,
             file_name, last_file);
    if (last_file) {
      printf("\n");
    }
  }
  if (patterns->e_patterns[0] != NULL) {
    v_helper(file, info, patterns->e_patterns, count_patt->e_count, flag,
             file_name, last_file);
  }
}

void grep_e(FILE *file, pattern *patterns, count *count_patt, char *file_name,
            bool flag, grep_info *info) {
  if (patterns->e_patterns[0] != NULL) {
    e_helper(file, info, patterns->e_patterns, count_patt->e_count, flag,
             file_name);
  }
}
