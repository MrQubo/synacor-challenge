#include <alloca.h>
#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "readFile.h"
#include "state.h"
#include "run.h"

int main(int argc, char * argv[]) {
    _state *state;
    int return_code;

    if (argc < 1) {
        fprintf(stderr, "No filename provided");
        return -1;
    }

    state = alloc_state();
    if (!state) {
        perror("Error during allocating the state: ");
        return -1;
    }

    if (!readFile(state->memory, MEMORY_SIZE, argv[1])) {
        perror("Error during reading the file: ");
        free_state(state);
        return -1;
    }

    return_code = run(state, stdin, stdout, stderr);

    free_state(state);
    return return_code;
    return 0;
}
