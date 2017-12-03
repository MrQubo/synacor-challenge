#ifndef JN_INTERPRETER_STATE_H
#define JN_INTERPRETER_STATE_H

#include <stdlib.h>

extern size_t const MEMORY_SIZE;
extern size_t const REGISTERS_SIZE;

typedef unsigned short word;
typedef unsigned short void_ptr;
typedef size_t stack_ptr;

struct _state_ {
    void *memory;
    void *registers;
    void *stack;
    size_t stack_size;
    stack_ptr sp;
    void_ptr ip;
};
typedef struct _state_ _state;

_state * alloc_state(void);
void free_state(_state *state);

#endif
