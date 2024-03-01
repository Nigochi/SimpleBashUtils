#include <fcntl.h>
#include <stdbool.h>

#include "21_grep.h"
#include "grep_flags.h"

void grep_to_decide(FILE *file, grep_info *info, pattern *patterns,
                    count *count_patt, char *file_name, bool flag,
                    bool last_file) {
  if (info->flag_c) {
    grep_c(file, patterns, count_patt, file_name, flag, info);
  }
  if (info->flag_o && !info->flag_l && !info->flag_c && !info->flag_v) {
    grep_o(file, patterns, count_patt, file_name, flag, info);
  }
  if (info->flag_n && (!info->flag_o || info->flag_v) && !info->flag_l &&
      !info->flag_c) {
    grep_n(file, patterns, count_patt, file_name, flag, info, last_file);
  }
  if (info->flag_l) {
    grep_l(file, patterns, count_patt, file_name, info);
  }
  if (info->flag_v && !info->flag_c && !info->flag_l && !info->flag_n) {
    grep_v(file, patterns, count_patt, file_name, flag, info, last_file);
  }
  if (info->flag_c + info->flag_l + info->flag_n + info->flag_o + info->flag_v <
      1) {
    if (info->flag_i) {
      grep_i(file, patterns, count_patt, file_name, flag, info, last_file);
    } else if (info->flag_v) {
      grep_v(file, patterns, count_patt, file_name, flag, info, last_file);
    } else if (info->flag_h) {
      grep_h(file, patterns, count_patt, info);
    } else if (info->flag_e) {
      grep_e(file, patterns, count_patt, file_name, flag, info);
    }
  }
  if (info->flag_c + info->flag_e + info->flag_h + info->flag_i + info->flag_l +
          info->flag_n + info->flag_o + info->flag_v ==
      0) {
    grep_without_flags(file, patterns, count_patt, file_name, flag, last_file);
  }
  fclose(file);
}