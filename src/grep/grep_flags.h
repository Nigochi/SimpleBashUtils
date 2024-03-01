#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>

#include "21_grep.h"

#ifndef GREP_FLAGS_C
#define GREP_FLAGS_C

void grep_i(FILE *file, pattern *patterns, count *count_patt, char *file_name,
            bool flag, grep_info *info, bool last_file);
void grep_e(FILE *file, pattern *patterns, count *count_patt, char *file_name,
            bool flag, grep_info *info);
void grep_c(FILE *file, pattern *patterns, count *count_patt, char *file_name,
            bool flag, grep_info *info);
void grep_v(FILE *file, pattern *patterns, count *count_patt, char *file_name,
            bool flag, grep_info *info, bool last_file);
bool grep_l(FILE *file, pattern *patterns, count *count_patt, char *file_name,
            grep_info *info);
void grep_n(FILE *file, pattern *patterns, count *count_patt, char *file_name,
            bool flag, grep_info *info, bool last_file);
void grep_h(FILE *file, pattern *patterns, count *count_patt, grep_info *info);
void grep_o(FILE *file, pattern *patterns, count *count_patt, char *file_name,
            bool flag, grep_info *info);
void grep_without_flags(FILE *file, pattern *patterns, count *count_patt,
                        char *file_name, bool flag, bool last_file);

#endif  // GREP_FLAGS_C