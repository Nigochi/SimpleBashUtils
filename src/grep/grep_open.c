#include <errno.h>
#include <fcntl.h>
#include <stdio.h>

FILE *grep_open(char *argv[], char *file_name) {
  FILE *file = fopen(file_name, "r");
  if (errno) {
    fprintf(stderr, "%s: ", argv[0]);
    perror(file_name);
    errno = 0;
  }
  return file;
}
