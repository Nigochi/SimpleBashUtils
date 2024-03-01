#include <fcntl.h>
#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "21_grep.h"
#include "grep_open.h"
#include "grep_to_decide.h"

void grep_distribution(grep_info *info, char *argv[], int argc, int optind,
                       pattern *patterns, count *count_patt, char *file_name) {
  bool flag = false;
  int count_not_files = 0;
  int count_files = 0;
  for (int i = optind; i < argc; i++) {
    if (strstr(argv[i], ".") == NULL && strcmp(argv[i], "Makefile") != 0) {
      count_not_files++;
    } else {
      count_files++;
    }
  }
  if (count_files > 1) {
    flag = true;
  }
  for (int i = optind + count_not_files; i < argc; i++) {
    bool last_file = false;
    if (i == argc - 1 && count_files > 1) {
      last_file = true;
    }
    file_name = argv[i];
    FILE *file = grep_open(argv, file_name);
    if (!file) {
      continue;
    } else {
      grep_to_decide(grep_open(argv, file_name), info, patterns, count_patt,
                     file_name, flag, last_file);
    }
    fclose(file);
  }
}

bool grep_parse(grep_info *info, char *argv[], int argc, pattern *patterns,
                count *count_patt, char *file_name) {
  struct option long_opt[] = {{NULL, 0, NULL, 0}};
  opterr = 0;
  int res = 0;
  while ((res = getopt_long(argc, argv, "e:ivnlcho", long_opt, NULL)) != -1) {
    switch (res) {
      case 'e':
        info->flag_e = true;
        if (optarg != NULL) {
          patterns->e_patterns[count_patt->e_count] = optarg;
          count_patt->e_count++;
        }
        break;
      case 'i':
        info->flag_i = true;
        info->flag_for_regexcomp = REG_ICASE;
        if (optarg != NULL) {
          patterns->i_patterns[count_patt->i_count] = optarg;
          count_patt->i_count++;
        }
        break;
      case 'l':
        info->flag_l = true;
        if (optarg != NULL) {
          patterns->l_patterns[count_patt->l_count] = optarg;
          count_patt->l_count++;
        }
        break;
      case 'v':
        info->flag_v = true;
        if (optarg != NULL) {
          patterns->v_patterns[count_patt->v_count] = optarg;
          count_patt->v_count++;
        }
        break;
      case 'c':
        info->flag_c = true;
        if (optarg != NULL) {
          patterns->c_patterns[count_patt->c_count] = optarg;
          count_patt->c_count++;
        }
        break;
      case 'n':
        info->flag_n = true;
        if (optarg != NULL) {
          patterns->n_patterns[count_patt->n_count] = optarg;
          count_patt->n_count++;
        }
        break;
      case 'h':
        info->flag_h = true;
        if (optarg != NULL) {
          patterns->h_patterns[count_patt->h_count] = optarg;
          count_patt->h_count++;
        }
        break;
      case 'o':
        info->flag_o = true;
        if (optarg != NULL) {
          patterns->o_patterns[count_patt->o_count] = optarg;
          count_patt->o_count++;
        }
        break;
      default:
        return false;
    }
  }
  if (optind < argc) {
    for (int i = optind; i < argc; i++) {
      if (strstr(argv[i], ".") == NULL && strstr(argv[i], "Makefile") == NULL) {
        if (info->flag_e) {
          patterns->e_patterns[count_patt->e_count] = argv[i];
          count_patt->e_count++;
        } else if (info->flag_v) {
          patterns->v_patterns[count_patt->v_count] = argv[i];
          count_patt->v_count++;
        } else {
          info->flag_free = true;
          patterns->free_patterns[count_patt->free_count] = argv[i];
          count_patt->free_count++;
        }
      }
    }
  }
  grep_distribution(info, argv, argc, optind, patterns, count_patt, file_name);
  return true;
}
