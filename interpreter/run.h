#ifndef JN_INTERPRETER_RUN_H
#define JN_INTERPRETER_RUN_H

#include <stdlib.h>

#include "state.h"

extern word const MAX_VALUE;

int run(_state *state, FILE *infile, FILE *outfile, FILE *errfile);

#endif
