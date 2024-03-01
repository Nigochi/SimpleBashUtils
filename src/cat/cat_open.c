#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#include "cat_for_read.h"
#include "cat_info.h"

void cat_open(int argc, char *argv[], cat_info flags, char *table[static 256],
              char **filename, char **end) {
  for (filename = &argv[1], end = &argv[argc]; filename != end; ++filename) {
    if (**filename == '-') {
      continue;
    }
    FILE *file = fopen(*filename, "rb");
    if (errno) {
      fprintf(stderr, "%s", argv[0]);
      perror(*filename);
      continue;
    }
    cat_read(file, flags, table);
    fclose(file);
  }
}