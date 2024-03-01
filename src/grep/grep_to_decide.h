#include <stdbool.h>

#ifndef GREP_TO_DECIDE_C
#define GREP_TO_DECIDE_C

void grep_to_decide(FILE *file, grep_info *info, pattern *patterns,
                    count *count_patt, char *file_name, bool flag,
                    bool last_file);

#endif  // GREP_TO_DECIDE_C