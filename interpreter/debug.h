#ifndef JN_INTERPRETER_DEBUG_H
#define JN_INTERPRETER_DEBUG_H

#include "global.h"

#ifdef DEBUG
    #define _ARGS_00(F, ...) F
    #define _ARGS_01(F, ...) _ARGS_00(__VA_ARGS__,)
    #define _ARGS_02(F, ...) _ARGS_01(__VA_ARGS__)
    #define _ARGS_03(F, ...) _ARGS_02(__VA_ARGS__)
    #define _ARGS_04(F, ...) _ARGS_03(__VA_ARGS__)
    #define _ARGS_05(F, ...) _ARGS_04(__VA_ARGS__)
    #define _ARGS_06(F, ...) _ARGS_05(__VA_ARGS__)
    #define _ARGS_07(F, ...) _ARGS_06(__VA_ARGS__)
    #define _ARGS_08(F, ...) _ARGS_07(__VA_ARGS__)
    #define _ARGS_09(F, ...) _ARGS_08(__VA_ARGS__)
    #define _ARGS_10(F, ...) _ARGS_09(__VA_ARGS__)
    #define _ARGS_11(F, ...) _ARGS_10(__VA_ARGS__)
    #define _ARGS_12(F, ...) _ARGS_11(__VA_ARGS__)
    #define _ARGS_13(F, ...) _ARGS_12(__VA_ARGS__)
    #define _ARGS_14(F, ...) _ARGS_13(__VA_ARGS__)
    #define _ARGS_15(F, ...) _ARGS_14(__VA_ARGS__)
    #define _ARGS_16(F, ...) _ARGS_15(__VA_ARGS__)
    #define _ARGS_17(F, ...) _ARGS_16(__VA_ARGS__)
    #define _ARGS(...) _ARGS_17(__VA_ARGS__,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,)
    #define LOG(...) CAT(_LOG, _ARGS(__VA_ARGS__))(__VA_ARGS__)
    #define _LOG0(msg)  \
        do { fprintf(stderr, "LOG> " msg "\n"); fflush(stderr); } while (0)
    #define _LOG1(msg, ...) \
        do { fprintf(stderr, "LOG> " msg "\n", __VA_ARGS__);    \
        fflush(stderr); } while (0)
#else
    #define LOG(...) do { } while (0)
#endif

#endif
