#include <alloca.h>
#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "debug.h"
#include "state.h"
#include "run.h"

#define LOGA0(msg) LOG(msg)
#define LOGA1(msg) LOG(msg " %d", arg1)
#define LOGA2(msg) LOG(msg " %d %d", arg1, arg2)
#define LOGA3(msg) LOG(msg " %d %d %d", arg1, arg2, arg3)

#define IFEQ(A, B, T, F) CAT(CAT(IFEQ, A), B)(T, F)
#define IFEQ00(T, F) T
#define IFEQ01(T, F) F
#define IFEQ02(T, F) F
#define IFEQ10(T, F) F
#define IFEQ11(T, F) T
#define IFEQ12(T, F) F
#define IFEQ20(T, F) F
#define IFEQ21(T, F) F
#define IFEQ22(T, F) T
#define ARG_T_2(N) word CAT(arg, N) = readIPLiteralAndAdvance(state);
#define ARG_T_1(N) word CAT(arg, N) = readIPAndAdvance(state);
#define ARG(N, A) \
    IFEQ(A, 2, DEFER(ARG_T_2), EMPTY)(N) \
    IFEQ(A, 1, DEFER(ARG_T_1), EMPTY)(N)
#define ZERO(...) 0
#define ONE(...) 1
#define CT1(C) \
    IFEQ(C, 0, 2, 3)
#define CT2(B, C) \
    IFEQ(B, 0, ONE, CT1)(C)
#define CT(A, B, C) \
    IFEQ(A, 0, ZERO, CT2)(B, C)
#define PROLOGUE(NAME, A, B, C) \
    ARG(1, A)   \
    ARG(2, B)   \
    ARG(3, C)   \
    CAT(LOGA, CT(A, B, C))(STR(NAME));
#define EPILOGUE(...) return 1;


word const MAX_VALUE = 32767;
word const MOD_VALUE = 32768;


void * memoryAddress(_state *state, void_ptr addr) {
    return (word *)state->memory + addr;
}
void writeMemory(_state *state, void_ptr addr, word val) {
    *((word *)memoryAddress(state, addr)) = val;
}
word readMemory(_state *state, void_ptr addr) {
    return *((word *)memoryAddress(state, addr));
}

void * registerAddress(_state *state, word reg) {
    return (word *)state->registers + reg - MAX_VALUE;
}
void writeRegister(_state *state, word reg, word val) {
    *((word *)registerAddress(state, reg)) = val;
}
word readRegister(_state *state, word reg) {
    return *((word *)registerAddress(state, reg));
}

int pushStack(_state *state, word val) {
    if (state->sp >= state->stack_size) {
        state->stack_size <<= 1;
        state->stack = realloc(state->stack, state->stack_size);
        if (!state->stack) {
            return -1;
        }
    }

    *((word *)state->stack + state->sp) = val;
    ++state->sp;

    return 0;
}
word popStack(_state *state) {
    --state->sp;
    return *((word *)state->stack + state->sp);
}

word getLiteral(_state *state, word val) {
    if (val > MAX_VALUE) {
        val = readRegister(state, (void_ptr)val);
    }

    return val;
}
word readLiteral(_state *state, void_ptr addr) {
    word val;

    val = readMemory(state, addr);

    return getLiteral(state, val);
}


word readIP(_state *state) {
    return readMemory(state, state->ip);
}
word readIPAndAdvance(_state *state) {
    word val;

    val = readIP(state);
    ++state->ip;

    return val;
}

word readIPLiteral(_state *state) {
    return readLiteral(state, state->ip);
}
word readIPLiteralAndAdvance(_state *state) {
    word val;

    val = readIPLiteral(state);
    ++state->ip;

    return val;
}


_Pragma("GCC diagnostic push")
_Pragma("GCC diagnostic ignored \"-Wunused-parameter\"")
int halt(_state *state, FILE *infile, FILE *outfile, FILE *errfile) {
_Pragma("GCC diagnostic pop")
    PROLOGUE(halt, 0, 0, 0)
    return 0;
}


_Pragma("GCC diagnostic push")
_Pragma("GCC diagnostic ignored \"-Wunused-parameter\"")
int set(_state *state, FILE *infile, FILE *outfile, FILE *errfile) {
_Pragma("GCC diagnostic pop")
    PROLOGUE(set, 1, 2, 0)
    writeRegister(state, arg1, arg2);
    EPILOGUE(set, 1, 2, 0)
}


_Pragma("GCC diagnostic push")
_Pragma("GCC diagnostic ignored \"-Wunused-parameter\"")
int push(_state *state, FILE *infile, FILE *outfile, FILE *errfile) {
_Pragma("GCC diagnostic pop")
    PROLOGUE(push, 2, 0, 0)
    if (pushStack(state, arg1)) {
        return -1;
    }
    EPILOGUE(push, 2, 0, 0)
}

_Pragma("GCC diagnostic push")
_Pragma("GCC diagnostic ignored \"-Wunused-parameter\"")
int pop(_state *state, FILE *infile, FILE *outfile, FILE *errfile) {
_Pragma("GCC diagnostic pop")
    PROLOGUE(pop, 1, 0, 0)
    writeRegister(state, arg1, popStack(state));
    EPILOGUE(pop, 1, 0, 0)
}


_Pragma("GCC diagnostic push")
_Pragma("GCC diagnostic ignored \"-Wunused-parameter\"")
int eq(_state *state, FILE *infile, FILE *outfile, FILE *errfile) {
_Pragma("GCC diagnostic pop")
    PROLOGUE(eq, 1, 2, 2)
    writeRegister(state, arg1, arg2 == arg3 ? 1 : 0);
    EPILOGUE(eq, 1, 2, 2)
}

_Pragma("GCC diagnostic push")
_Pragma("GCC diagnostic ignored \"-Wunused-parameter\"")
int gt(_state *state, FILE *infile, FILE *outfile, FILE *errfile) {
_Pragma("GCC diagnostic pop")
    PROLOGUE(eq, 1, 2, 2)
    writeRegister(state, arg1, arg2 > arg3 ? 1 : 0);
    EPILOGUE(eq, 1, 2, 2)
}


_Pragma("GCC diagnostic push")
_Pragma("GCC diagnostic ignored \"-Wunused-parameter\"")
int jmp(_state *state, FILE *infile, FILE *outfile, FILE *errfile) {
_Pragma("GCC diagnostic pop")
    PROLOGUE(jmp, 2, 0, 0)
    state->ip = arg1;
    EPILOGUE(jmp, 2, 0, 0)
}

_Pragma("GCC diagnostic push")
_Pragma("GCC diagnostic ignored \"-Wunused-parameter\"")
int jt(_state *state, FILE *infile, FILE *outfile, FILE *errfile) {
_Pragma("GCC diagnostic pop")
    PROLOGUE(jt, 2, 2, 0)
    if (arg1) { state->ip = arg2; }
    EPILOGUE(jt, 1, 2, 0)
}

_Pragma("GCC diagnostic push")
_Pragma("GCC diagnostic ignored \"-Wunused-parameter\"")
int jf(_state *state, FILE *infile, FILE *outfile, FILE *errfile) {
_Pragma("GCC diagnostic pop")
    PROLOGUE(jf, 2, 2, 0)
    if (!arg1) { state->ip = arg2; }
    EPILOGUE(jf, 1, 2, 0)
}


_Pragma("GCC diagnostic push")
_Pragma("GCC diagnostic ignored \"-Wunused-parameter\"")
int add(_state *state, FILE *infile, FILE *outfile, FILE *errfile) {
_Pragma("GCC diagnostic pop")
    PROLOGUE(add, 1, 2, 2)
    writeRegister(state, arg1, (arg2 + arg3) % MOD_VALUE);
    EPILOGUE(add, 1, 2, 2)
}

_Pragma("GCC diagnostic push")
_Pragma("GCC diagnostic ignored \"-Wunused-parameter\"")
int mult(_state *state, FILE *infile, FILE *outfile, FILE *errfile) {
_Pragma("GCC diagnostic pop")
    PROLOGUE(mult, 1, 2, 2)
    writeRegister(state, arg1, (arg2 * arg3) % MOD_VALUE);
    EPILOGUE(mult, 1, 2, 2)
}

_Pragma("GCC diagnostic push")
_Pragma("GCC diagnostic ignored \"-Wunused-parameter\"")
int mod(_state *state, FILE *infile, FILE *outfile, FILE *errfile) {
_Pragma("GCC diagnostic pop")
    PROLOGUE(mod, 1, 2, 2)
    writeRegister(state, arg1, arg2 % arg3);
    EPILOGUE(mod, 1, 2, 2)
}


_Pragma("GCC diagnostic push")
_Pragma("GCC diagnostic ignored \"-Wunused-parameter\"")
int and(_state *state, FILE *infile, FILE *outfile, FILE *errfile) {
_Pragma("GCC diagnostic pop")
    PROLOGUE(and, 1, 2, 2)
    writeRegister(state, arg1, arg2 & arg3);
    EPILOGUE(and, 1, 2, 2)
}

_Pragma("GCC diagnostic push")
_Pragma("GCC diagnostic ignored \"-Wunused-parameter\"")
int or(_state *state, FILE *infile, FILE *outfile, FILE *errfile) {
_Pragma("GCC diagnostic pop")
    PROLOGUE(or, 1, 2, 2)
    writeRegister(state, arg1, arg2 | arg3);
    EPILOGUE(or, 1, 2, 2)
}

_Pragma("GCC diagnostic push")
_Pragma("GCC diagnostic ignored \"-Wunused-parameter\"")
int not(_state *state, FILE *infile, FILE *outfile, FILE *errfile) {
_Pragma("GCC diagnostic pop")
    PROLOGUE(not, 1, 2, 0)
    writeRegister(state, arg1, ~arg2 & 0x7fff);
    EPILOGUE(not, 1, 2, 0)
}


_Pragma("GCC diagnostic push")
_Pragma("GCC diagnostic ignored \"-Wunused-parameter\"")
int rmem(_state *state, FILE *infile, FILE *outfile, FILE *errfile) {
_Pragma("GCC diagnostic pop")
    PROLOGUE(rmem, 1, 2, 0)
    writeRegister(state, arg1, readMemory(state, arg2));
    EPILOGUE(rmem, 1, 2, 0)
}

_Pragma("GCC diagnostic push")
_Pragma("GCC diagnostic ignored \"-Wunused-parameter\"")
int wmem(_state *state, FILE *infile, FILE *outfile, FILE *errfile) {
_Pragma("GCC diagnostic pop")
    PROLOGUE(wmem, 2, 2, 0)
    writeMemory(state, arg1, arg2);
    EPILOGUE(wmem, 2, 2, 0)
}


_Pragma("GCC diagnostic push")
_Pragma("GCC diagnostic ignored \"-Wunused-parameter\"")
int call(_state *state, FILE *infile, FILE *outfile, FILE *errfile) {
_Pragma("GCC diagnostic pop")
    PROLOGUE(call, 2, 0, 0)
    if (pushStack(state, state->ip)) {
        return -1;
    }
    state->ip = arg1;
    EPILOGUE(call, 2, 0, 0)
}

_Pragma("GCC diagnostic push")
_Pragma("GCC diagnostic ignored \"-Wunused-parameter\"")
int ret(_state *state, FILE *infile, FILE *outfile, FILE *errfile) {
_Pragma("GCC diagnostic pop")
    PROLOGUE(ret, 0, 0, 0)
    state->ip = popStack(state);
    EPILOGUE(ret, 0, 0, 0)
}


_Pragma("GCC diagnostic push")
_Pragma("GCC diagnostic ignored \"-Wunused-parameter\"")
int out(_state *state, FILE *infile, FILE *outfile, FILE *errfile) {
_Pragma("GCC diagnostic pop")
    PROLOGUE(out, 2, 0, 0)
    fprintf(outfile, "%c", arg1);
    EPILOGUE(out, 2, 0, 0)
}

_Pragma("GCC diagnostic push")
_Pragma("GCC diagnostic ignored \"-Wunused-parameter\"")
int in(_state *state, FILE *infile, FILE *outfile, FILE *errfile) {
_Pragma("GCC diagnostic pop")
    PROLOGUE(in, 1, 0, 0)
    fscanf(infile, "%c", (char *)registerAddress(state, arg1));
    EPILOGUE(in, 1, 0, 0)
}


_Pragma("GCC diagnostic push")
_Pragma("GCC diagnostic ignored \"-Wunused-parameter\"")
int noop(_state *state, FILE *infile, FILE *outfile, FILE *errfile) {
_Pragma("GCC diagnostic pop")
    PROLOGUE(noop, 0, 0, 0)
    EPILOGUE(noop, 0, 0, 0)
}


int (* opcodes[22])(_state *, FILE *, FILE *, FILE *) = {
    [0] = halt,
    [1] = set,
    [2] = push, [3] = pop,
    [4] = eq, [5] = gt,
    [6] = jmp, [7] = jt, [8] = jf,
    [9] = add, [10] = mult, [11] = mod,
    [12] = and, [13] = or, [14] = not,
    [15] = rmem, [16] = wmem,
    [17] = call, [18] = ret,
    [19] = out, [20] = in,
    [21] = noop
};


int run(_state *state, FILE *infile, FILE *outfile, FILE *errfile) {
    word instr;
    int return_val;

    while (1) {
        instr = readIPAndAdvance(state);
        LOG("instr: %d \tip: %d", instr, state->ip-1);

        return_val = opcodes[instr](state, infile, outfile, errfile);
        if (return_val != 1) {
            return return_val;
        }
    }
}
