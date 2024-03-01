#include <stdlib.h>
#include <string.h>

#include "21_grep.h"
#include "grep_free.h"
#include "grep_parse_distribute.h"

void set_NULL(pattern *patterns);

int main(int argc, char *argv[]) {
  grep_info info = {false, false, false, false, false,
                    false, false, false, false, false};
  count count_patt = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  pattern patterns = {
      malloc(sizeof(char *) * (argc + 1)), malloc(sizeof(char *) * (argc + 1)),
      malloc(sizeof(char *) * (argc + 1)), malloc(sizeof(char *) * (argc + 1)),
      malloc(sizeof(char *) * (argc + 1)), malloc(sizeof(char *) * (argc + 1)),
      malloc(sizeof(char *) * (argc + 1)), malloc(sizeof(char *) * (argc + 1)),
      malloc(sizeof(char *) * (argc + 1))};
  set_NULL(&patterns);
  char *file_name = NULL;
  grep_parse(&info, argv, argc, &patterns, &count_patt, file_name);
  free(file_name);
  free_patterns(&patterns);
  return 0;
}

void set_NULL(pattern *patterns) {
  patterns->c_patterns[0] = NULL;
  patterns->e_patterns[0] = NULL;
  patterns->free_patterns[0] = NULL;
  patterns->h_patterns[0] = NULL;
  patterns->i_patterns[0] = NULL;
  patterns->l_patterns[0] = NULL;
  patterns->n_patterns[0] = NULL;
  patterns->o_patterns[0] = NULL;
  patterns->v_patterns[0] = NULL;
}