#ifndef JN_INTERPRETER_GLOBAL_H
#define JN_INTERPRETER_GLOBAL_H

#define EMPTY(...)
#define DEFER(id) id EMPTY(,)
#define DEFER2(id) id DEFER(EMPTY)(,)
#define CATCH(id) DEFER(id) EMPTY
#define CATCH2(id) DEFER2(id) CATCH(EMPTY)

#define _CAT2(A, B) A ## B
#define CAT(A, B) _CAT2(A, B)
#define _STR(...) # __VA_ARGS__
#define STR(...) _STR(__VA_ARGS__)

typedef unsigned char byte;

#endif
