#include <stdlib.h>

#include "21_grep.h"

void free_patterns(pattern *patterns) {
  free(patterns->c_patterns);
  free(patterns->e_patterns);
  free(patterns->free_patterns);
  free(patterns->h_patterns);
  free(patterns->i_patterns);
  free(patterns->l_patterns);
  free(patterns->n_patterns);
  free(patterns->o_patterns);
  free(patterns->v_patterns);
}