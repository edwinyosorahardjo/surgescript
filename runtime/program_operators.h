/*
 * SurgeScript
 * A lightweight programming language for computer games and interactive apps
 * Copyright (C) 2016-2017  Alexandre Martins <alemartf(at)gmail(dot)com>
 *
 * runtime/program_operators.h
 * SurgeScript program operators table
 */

#ifndef _SURGESCRIPT_RUNTIME_PROGRAM_OPERATORS_H
#define _SURGESCRIPT_RUNTIME_PROGRAM_OPERATORS_H

/*
    conventions:
        let 'a' and 'b' be the arguments of each operation
        and t[0 .. 3] be temporary values (aka "registers")

    now,
        a, b are constants
        t[0], t[1] are temps holding different values throughout the program
        t[2] holds utilities, such as the results of comparisons
        t[3] holds the return value of the program
*/
#define SURGESCRIPT_PROGRAM_OPERATORS(F) \
    F( SSOP_NOP, "nop" )                                 /* no-operation */ \
    F( SSOP_OUT, "print" )                                 /* print t[a] */ \
    F( SSOP_IN, "read" )                                    /* read t[a] */ \
                                                                            \
    F( SSOP_MOVN, "movn" )                                /* t[a] = null */ \
    F( SSOP_MOVB, "movb" )                             /* t[a] = (bool)b */ \
    F( SSOP_MOVF, "movf" )                           /* t[a] = (number)b */ \
    F( SSOP_MOVS, "movs" )                             /* t[a] = text[b] */ \
    F( SSOP_MOVO, "movo" )                           /* t[a] = (object)b */ \
    F( SSOP_MOVC, "movc" )    /* t[a] = handle to caller object ("this") */ \
    F( SSOP_MOVT, "movt" )                                /* t[a] = t[b] */ \
    F( SSOP_XCHG, "xchg" )                           /* swap(t[a], t[b]) */ \
                                                                            \
    F( SSOP_ALOC, "aloc" )                /* t[a] = allocate memory cell */ \
    F( SSOP_LOAD, "load" )                             /* t[a] = *(t[b]) */ \
    F( SSOP_STORE, "store" )                           /* *(t[b]) = t[a] */ \
    F( SSOP_PEEK, "peek" )                                /* t[a] = (*b) */ \
    F( SSOP_POKE, "poke" )                                /* (*b) = t[a] */ \
                                                                            \
    F( SSOP_PUSH, "push" )                                  /* push t[a] */ \
    F( SSOP_POP, "pop" )                                     /* pop t[a] */ \
    F( SSOP_SPEEK, "speek" )                   /* t[a] = stack[base + b] */ \
    F( SSOP_SPOKE, "spoke" )                   /* stack[base + b] = t[a] */ \
                                                                            \
    F( SSOP_INC, "inc" )                                       /* t[a]++ */ \
    F( SSOP_DEC, "dec" )                                       /* t[a]-- */ \
    F( SSOP_ADD, "add" )                                 /* t[a] += t[b] */ \
    F( SSOP_SUB, "sub" )                                 /* t[a] -= t[b] */ \
    F( SSOP_MUL, "mul" )                                 /* t[a] *= t[b] */ \
    F( SSOP_DIV, "div" )                                 /* t[a] /= t[b] */ \
    F( SSOP_NEG, "neg" )                                 /* t[a] = -t[b] */ \
    F( SSOP_LNOT, "lnot" )                               /* t[a] = !t[b] */ \
    F( SSOP_NOT, "not" )                                 /* t[a] = ~t[b] */ \
    F( SSOP_AND, "and" )                           /* t[a] = t[a] & t[b] */ \
    F( SSOP_OR, "or" )                             /* t[a] = t[a] | t[b] */ \
    F( SSOP_XOR, "xor" )                           /* t[a] = t[a] ^ t[b] */ \
    F( SSOP_CAT, "cat" )                    /* t[a] = strcat(t[a], t[b]) */ \
                                                                            \
    F( SSOP_BOOL, "bool" )                          /* t[a] = bool(t[a]) */ \
    F( SSOP_VAL, "val" )                          /* t[a] = number(t[a]) */ \
    F( SSOP_STR, "str" )                          /* t[a] = string(t[a]) */ \
                                                                            \
    F( SSOP_TEST, "test" )                         /* t[2] = t[a] & t[b] */ \
    F( SSOP_TCHK, "tchk" )               /* t[2] = typecheck(t[a], t[b]) */ \
    F( SSOP_TCHK0, "tchk0" )             /* t[2] = typecheck(t[a], null) */ \
    F( SSOP_TCHKB, "tchkb" )             /* t[2] = typecheck(t[a], bool) */ \
    F( SSOP_TCHKN, "tchkn" )           /* t[2] = typecheck(t[a], number) */ \
    F( SSOP_TCHKS, "tchks" )           /* t[2] = typecheck(t[a], string) */ \
    F( SSOP_TCHKO, "tchko" )           /* t[2] = typecheck(t[a], object) */ \
    F( SSOP_CMP, "cmp" )                   /* t[2] = compare(t[a], t[b]) */ \
                                                                            \
    F( SSOP_JMP, "jmp" )                                    /* jump to a */ \
    F( SSOP_JE, "je" )                    /* jump to line a if t[2] == 0 */ \
    F( SSOP_JNE, "jne" )                  /* jump to line a if t[2] != 0 */ \
    F( SSOP_JG, "jg" )                     /* jump to line a if t[2] > 0 */ \
    F( SSOP_JGE, "jge" )                  /* jump to line a if t[2] >= 0 */ \
    F( SSOP_JL, "jl" )                     /* jump to line a if t[2] < 0 */ \
    F( SSOP_JLE, "jle" )                  /* jump to line a if t[2] <= 0 */ \
                                                                            \
    F( SSOP_CALL, "call" )                 /* call program named text[a] */ \
                                      /* of the object at the top of the */ \
                                 /* stack with n = b parameters, storing */ \
                              /* in t[0] the return value of the program */ \
    F( SSOP_RET, "ret" )                 /* returns, halting the program */

#endif