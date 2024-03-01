#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cat_flags.h"
#include "cat_for_table.h"
#include "cat_info.h"
#include "cat_open.h"
#include "cat_parse.h"

int main(int argc, char *argv[]) {
  cat_info flags = cat_parse(argc, argv);
  char *table[256];
  cat_for_table(table);
  if (flags.flag_e) {
    cat_e(table);
  }
  if (flags.flag_tab) {
    cat_tab(table);
  }
  if (flags.flag_v) {
    cat_v(table);
  }
  char **filename = malloc(sizeof(char *));
  char **end = malloc(sizeof(char *));
  cat_open(argc, argv, flags, table, filename, end);
  free(filename);
  free(end);
  return 0;
}
