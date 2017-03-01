/*
 * SurgeScript
 * A lightweight programming language for computer games and interactive apps
 * Copyright (C) 2017  Alexandre Martins <alemartf(at)gmail(dot)com>
 *
 * compiler/codegen.c
 * SurgeScript Compiler: Code Generator
 */

#include "codegen.h"
#include "symtable.h"
#include "../runtime/program.h"
#include "../runtime/program_pool.h"

#ifdef F
#undef F
#endif
#ifdef U
#undef U
#endif
#ifdef B
#undef B
#endif
#ifdef I
#undef I
#endif
#define _SSASMX(_0, _1, _2, X, ...)     X
#define _SSASM2(op, a, b)               surgescript_program_add_line(context.program, (op), (a), (b))
#define _SSASM1(op, a)                  surgescript_program_add_line(context.program, (op), (a), U(0))
#define _SSASM0(op)                     surgescript_program_add_line(context.program, (op), U(0), U(0))

/* utility macros */
#define SSASM(...)                      _SSASMX(__VA_ARGS__, _SSASM2, _SSASM1, _SSASM0)(__VA_ARGS__)
#define TEXT(text)                      U(surgescript_program_add_text(context.program, (text)))
#define LABEL(label)                    surgescript_program_add_label(context.program, (label))
#define NEWLABEL()                      surgescript_program_new_label(context.program)
#define F(x)                            surgescript_program_operand_f(x)
#define U(x)                            surgescript_program_operand_u(x)
#define B(x)                            surgescript_program_operand_b(x)
#define I(x)                            surgescript_program_operand_i(x)
#define T0                              U(0)
#define T1                              U(1)
#define T2                              U(2)


/* objects */
void emit_object_header(surgescript_nodecontext_t context, surgescript_program_label_t start, surgescript_program_label_t end)
{
    SSASM(SSOP_JMP, U(end));
    LABEL(start);
}

void emit_object_footer(surgescript_nodecontext_t context, surgescript_program_label_t start, surgescript_program_label_t end)
{
    surgescript_program_label_t aloc = NEWLABEL();

    SSASM(SSOP_RET);
    LABEL(end);
        SSASM(SSOP_MOVF, T2, F(surgescript_symtable_count(context.symbol_table)));
        SSASM(SSOP_JE, U(start));
        LABEL(aloc);
            SSASM(SSOP_ALOC);
            SSASM(SSOP_DEC, T2);
            SSASM(SSOP_JNE, U(aloc));
        SSASM(SSOP_JMP, U(start));
}


/* constants */
void emit_null(surgescript_nodecontext_t context)
{
    SSASM(SSOP_MOVN, T0);
}

void emit_bool(surgescript_nodecontext_t context, bool value)
{
    SSASM(SSOP_MOVB, T0, B(value));
}

void emit_number(surgescript_nodecontext_t context, float value)
{
    SSASM(SSOP_MOVF, T0, F(value));
}

void emit_string(surgescript_nodecontext_t context, const char* value)
{
    SSASM(SSOP_MOVS, T0, TEXT(value));
}