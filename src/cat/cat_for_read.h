#include <fcntl.h>
#include <stdio.h>

#include "cat_info.h"

#ifndef CAT_FOR_READ_C
#define CAT_FOR_READ_C

void cat_read(FILE *file, cat_info flags, char *table[static 256]);

#endif  // CAT_FOR_READ_C