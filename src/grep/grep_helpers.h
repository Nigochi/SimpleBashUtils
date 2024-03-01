#include <stdio.h>

#ifndef GREP_HELPERS_C
#define GREP_HELPERS_C

int regcomp_and_regexec(char *pattern, char *output, int flag_to_compil);
int c_helper(FILE *file, grep_info *info, char **patterns, int patterns_number);
int o_helper(FILE *file, grep_info *info, char **pattern, int patterns_number,
             bool flag, char *file_name);
int v_helper_for_c(FILE *file, grep_info *info, char **patterns,
                   int patterns_number);
int n_helper(FILE *file, grep_info *info, char **patterns, int patterns_number,
             bool flag, char *file_name, bool last_file);
int v_helper_for_n(FILE *file, grep_info *info, char **patterns,
                   int pattern_number, bool flag, char *file_name,
                   bool last_file);
void h_helper(FILE *file, grep_info *info, char **patterns,
              int patterns_number);
void i_helper(FILE *file, grep_info *info, char **patterns, int patterns_number,
              bool flag, char *file_name, bool last_file);
void v_helper(FILE *file, grep_info *info, char **patterns, int patterns_number,
              bool flag, char *file_name, bool last_file);
void e_helper(FILE *file, grep_info *info, char **patterns, int patterns_number,
              bool flag, char *file_name);
void without_flags_helper(FILE *file, pattern *patterns, count *count_patt,
                          char *file_name, bool flag, bool last_file);
bool l_helper(FILE *file, grep_info *info, char **patterns,
              int patterns_number);

#endif  // GREP_HELPERS_C