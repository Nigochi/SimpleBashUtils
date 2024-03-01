#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>

#include "cat_info.h"

void cat_read(FILE *file, cat_info flags, char *table[static 256]) {
  int c = 0;
  int last = '\n';
  bool squeeze = false;
  int lineno = 0;
  while (fread(&c, 1, 1, file) > 0) {
    if (last == '\n') {
      if (flags.flag_s && c == '\n') {
        if (squeeze) {
          continue;
        }
        squeeze = true;
      } else
        squeeze = false;
      if (flags.flag_b) {
        if (c != '\n') {
          printf("%6i\t", ++lineno);
        }
      } else if (flags.flag_n) {
        printf("%6i\t", ++lineno);
      }
    }
    if (!*table[c])
      printf("%c", '\0');
    else
      printf("%s", table[c]);
    last = c;
  }
}