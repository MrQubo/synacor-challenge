#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "state.h"

size_t const MEMORY_SIZE = 1 << 16;
size_t const REGISTERS_SIZE = 1 << 4;
size_t const STACK_SIZE = 1 << 10;

_state * alloc_state(void) {
    _state *state;

    state = malloc(sizeof(_state));
    if (!state) {
        return NULL;
    }

    state->memory = malloc(MEMORY_SIZE);
    if (!state->memory) {
        free(state);
        return NULL;
    }

    state->registers = malloc(REGISTERS_SIZE);
    if (!state->registers) {
        free(state->memory);
        free(state);
        return NULL;
    }

    state->stack = malloc(STACK_SIZE);
    if (!state->stack) {
        free(state->registers);
        free(state->memory);
        free(state);
        return NULL;
    }

    state->stack_size = STACK_SIZE;
    state->sp = 0;
    state->ip = 0;

    return state;
}

void free_state(_state *state) {
    free(state->stack);
    free(state->registers);
    free(state->memory);
    free(state);
}
