#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>

#include "cat_info.h"

cat_info cat_parse(int argc, char *argv[]) {
  struct option long_opt[] = {{"number-nonblank", 0, NULL, 'b'},
                              {"number", 0, NULL, 'n'},
                              {"squeeze-blank", 0, NULL, 's'},
                              {NULL, 0, NULL, 0}};
  opterr = 0;
  int res;
  cat_info flags = {false, false, false, false, false, false};
  while ((res = getopt_long(argc, argv, "bevEnstT", long_opt, NULL)) != -1) {
    switch (res) {
      case 'b':
        flags.flag_b = true;
        break;
      case 'e':
        flags.flag_e = true;
        flags.flag_v = true;
        break;
      case 'v':
        flags.flag_v = true;
        break;
      case 'E':
        flags.flag_e = true;
        break;
      case 'n':
        flags.flag_n = true;
        break;
      case 's':
        flags.flag_s = true;
        break;
      case 't':
        flags.flag_tab = true;
        flags.flag_v = true;
        break;
      case 'T':
        flags.flag_v = true;
        flags.flag_tab = true;
        break;
      default:
        break;
    }
  }
  return flags;
}