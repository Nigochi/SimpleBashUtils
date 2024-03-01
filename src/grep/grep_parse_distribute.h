#include <stdbool.h>

#include "21_grep.h"

#ifndef GREP_PARSE_DISTRIBUTION_C
#define GREP_PARSE_DISTRIBUTION_C

bool grep_parse(grep_info *info, char *argv[], int argc, pattern *patterns,
                count *count_patt, char *file_name);
void grep_distribution(grep_info *info, char *argv[], int argc, int optind,
                       pattern *patterns, count *count_patt, char *file_name);

#endif  // GREP_PARSE_DISTRIBUTION_C