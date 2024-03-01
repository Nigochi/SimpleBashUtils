#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "21_grep.h"

int regcomp_and_regexec(char *pattern, char *output, int flag_to_compil) {
  regex_t reegex;
  int return_value;
  if (!regcomp(&reegex, pattern, flag_to_compil)) {
    return_value = regexec(&reegex, output, 0, NULL, 0);
  }
  regfree(&reegex);
  return return_value;
}

void without_flags_helper(FILE *file, pattern *patterns, count *count_patt,
                          char *file_name, bool flag, bool last_file) {
  ssize_t for_read;
  size_t len = 0;
  (void)last_file;
  char *output = NULL;
  for (int i = 0; i < count_patt->free_count; i++) {
    rewind(file);
    while ((for_read = getline(&output, &len, file)) != -1) {
      if (!regcomp_and_regexec(patterns->free_patterns[i], output, 0)) {
        if (flag) {
          printf("%s:", file_name);
        }
        printf("%s", output);
      }
    }
  }
  free(output);
}

void h_helper(FILE *file, grep_info *info, char **patterns,
              int patterns_number) {
  ssize_t for_read;
  size_t len = 0;
  char *output = NULL;
  rewind(file);
  while ((for_read = getline(&output, &len, file)) != -1) {
    for (int i = 0; i < patterns_number; i++) {
      if (!regcomp_and_regexec(patterns[i], output, info->flag_for_regexcomp)) {
        printf("%s", output);
      }
    }
  }
  free(output);
}

int v_helper_for_n(FILE *file, grep_info *info, char **patterns,
                   int patten_number, bool flag, char *file_name,
                   bool last_file) {
  ssize_t for_read;
  size_t len = 0;
  int count_all = 1;
  char *output = NULL;
  rewind(file);
  while ((for_read = getline(&output, &len, file)) != -1) {
    bool pattern_found = true;
    for (int i = 0; i < patten_number; i++) {
      if (!regcomp_and_regexec(patterns[i], output, info->flag_for_regexcomp)) {
        if (strstr(output, patterns[i]) != NULL) {
          pattern_found = false;
        }
      }
    }
    if (pattern_found) {
      if (flag && !info->flag_h) {
        printf("%s:", file_name);
      }
      printf("%d:%s", count_all, output);
    }
    count_all++;
  }
  if (last_file) {
    printf("\n");
  } else {
    if (strstr(output, "\n") != NULL) {
      printf("\n");
    }
  }
  free(output);
  return count_all;
}

int n_helper(FILE *file, grep_info *info, char **patterns, int patterns_number,
             bool flag, char *file_name, bool last_file) {
  int count_all = 1;
  if (!info->flag_v) {
    ssize_t for_read;
    size_t len = 0;
    char *output = NULL;
    rewind(file);
    while ((for_read = getline(&output, &len, file)) != -1) {
      bool pattern_found = true;
      for (int i = 0; i < patterns_number; i++) {
        if (!regcomp_and_regexec(patterns[i], output,
                                 info->flag_for_regexcomp)) {
          if (strstr(output, patterns[i]) != NULL) {
            if (flag && !info->flag_h) {
              printf("%s:", file_name);
            }
            if (pattern_found) {
              printf("%d:%s", count_all, output);
              pattern_found = false;
            }
          }
        }
      }
      count_all++;
    }
    if (last_file && !flag) {
      printf("\n");
    }
    free(output);
  } else {
    count_all += v_helper_for_n(file, info, patterns, patterns_number, flag,
                                file_name, last_file);
  }
  return count_all;
}

int v_helper_for_c(FILE *file, grep_info *info, char **patterns,
                   int patterns_number) {
  ssize_t for_read;
  size_t len = 0;
  int count_all = 0;
  char *output = NULL;
  rewind(file);
  bool patterns_found = false;
  while ((for_read = getline(&output, &len, file)) != -1) {
    patterns_found = false;
    for (int i = 0; i < patterns_number; i++) {
      if (!regcomp_and_regexec(patterns[i], output, info->flag_for_regexcomp)) {
        patterns_found = true;
      }
    }
    if (!patterns_found) {
      count_all++;
    }
  }
  free(output);
  return count_all;
}

int c_helper(FILE *file, grep_info *info, char **patterns,
             int patterns_number) {
  int count_all = 0;
  if (!info->flag_v) {
    ssize_t for_read;
    size_t len = 0;
    char *output = NULL;
    rewind(file);
    while ((for_read = getline(&output, &len, file)) != -1) {
      for (int i = 0; i < patterns_number; i++) {
        if (info->flag_v) {
          if (regcomp_and_regexec(patterns[i], output,
                                  info->flag_for_regexcomp)) {
            count_all++;
            break;
          }
        } else {
          if (!regcomp_and_regexec(patterns[i], output,
                                   info->flag_for_regexcomp)) {
            count_all++;
            break;
          }
        }
      }
    }
    free(output);
  } else {
    count_all = v_helper_for_c(file, info, patterns, patterns_number);
  }
  return count_all;
}

bool l_helper(FILE *file, grep_info *info, char **patterns,
              int patterns_number) {
  ssize_t for_read;
  size_t len = 0;
  char *output = NULL;
  bool flag_output = false;
  for (int i = 0; i < patterns_number; i++) {
    rewind(file);
    while ((for_read = getline(&output, &len, file)) != -1) {
      if (info->flag_v) {
        if (regcomp_and_regexec(patterns[i], output,
                                info->flag_for_regexcomp)) {
          flag_output = true;
          break;
        }
      } else {
        if (!regcomp_and_regexec(patterns[i], output,
                                 info->flag_for_regexcomp)) {
          flag_output = true;
          break;
        }
      }
    }
  }
  free(output);
  return flag_output;
}

void i_helper(FILE *file, grep_info *info, char **patterns, int patterns_number,
              bool flag, char *file_name, bool last_file) {
  ssize_t for_read;
  size_t len = 0;
  char *output = NULL;
  for (int i = 0; i < patterns_number; i++) {
    rewind(file);
    while ((for_read = getline(&output, &len, file)) != -1) {
      if (info->flag_v) {
        if (regcomp_and_regexec(patterns[i], output,
                                info->flag_for_regexcomp)) {
          if (flag) {
            printf("%s:", file_name);
          }
          printf("%s", output);
        }
      } else {
        if (!regcomp_and_regexec(patterns[i], output,
                                 info->flag_for_regexcomp)) {
          if (flag) {
            printf("%s:", file_name);
          }
          printf("%s", output);
        }
      }
    }
    if (flag && !last_file) {
      printf("%s:", file_name);
    }
  }
  free(output);
}

void v_helper(FILE *file, grep_info *info, char **patterns, int patterns_number,
              bool flag, char *file_name, bool last_file) {
  ssize_t for_read;
  size_t len = 0;
  char *output = NULL;
  rewind(file);
  bool patterns_found = false;
  while ((for_read = getline(&output, &len, file)) != -1) {
    patterns_found = false;
    for (int i = 0; i < patterns_number; i++) {
      if (!regcomp_and_regexec(patterns[i], output, info->flag_for_regexcomp)) {
        patterns_found = true;
      }
    }
    if (!patterns_found) {
      if (flag & !info->flag_h) {
        printf("%s:", file_name);
      }
      printf("%s", output);
    }
  }
  bool flag_new_line = false;
  for (int i = 0; i < (int)strlen(output); i++) {
    if (output[i] == '\n') {
      flag_new_line = true;
    }
  }
  if (last_file && !flag_new_line) {
    printf("\n");
  } else {
    if ((!flag) && !flag_new_line) {
      printf("\n");
    }
  }
  free(output);
}

int o_helper(FILE *file, grep_info *info, char **patterns, int patterns_number,
             bool flag, char *file_name) {
  ssize_t for_read;
  size_t len = 0;
  char *output = NULL;
  int count_all = 1;
  while ((for_read = getline(&output, &len, file)) != -1) {
    bool flag_for_n = true;
    bool printf_once = true;
    for (int i = 0; i < patterns_number; i++) {
      char *tmp_output = output;
      if (!regcomp_and_regexec(patterns[i], tmp_output,
                               info->flag_for_regexcomp)) {
        while ((tmp_output = strstr(tmp_output, patterns[i])) != NULL) {
          if (flag && !info->flag_h && printf_once) {
            printf("%s:", file_name);
            printf_once = false;
          }
          if (info->flag_n && flag_for_n) {
            printf("%d:", count_all);
            flag_for_n = false;
          }
          puts(patterns[i]);
          tmp_output += strlen(patterns[i]);
        }
      }
    }
    count_all++;
  }
  free(output);
  return count_all;
}

void e_helper(FILE *file, grep_info *info, char **patterns, int patterns_number,
              bool flag, char *file_name) {
  ssize_t for_read;
  size_t len = 0;
  char *output = NULL;
  rewind(file);
  while ((for_read = getline(&output, &len, file)) != -1) {
    bool pattern_found = true;
    for (int i = 0; i < patterns_number; i++) {
      if (!regcomp_and_regexec(patterns[i], output, info->flag_for_regexcomp)) {
        pattern_found = false;
      }
    }
    if (!pattern_found) {
      if (flag && !info->flag_h) {
        printf("%s:", file_name);
      }
      printf("%s", output);
    }
  }
  free(output);
}
