/*
 * SurgeScript
 * A lightweight programming language for computer games and interactive apps
 * Copyright (C) 2016  Alexandre Martins <alemartf(at)gmail(dot)com>
 *
 * runtime/variable.c
 * SurgeScript variables
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include "variable.h"
#include "../util/util.h"


/* private stuff */

/* possible variable types */
enum surgescript_vartype_t {
    SSVAR_NULL,
    SSVAR_BOOL,
    SSVAR_NUMBER,
    SSVAR_STRING,
    SSVAR_OBJECTHANDLE
};

/* the variable struct */
struct surgescript_var_t
{
    enum surgescript_vartype_t type;
    union {
        float number;
        bool boolean;
        char* string;
        unsigned handle;
    };
};

/* helpers */
#define RELEASE_DATA(var)       if(var->type == SSVAR_STRING) \
                                    ssfree(var->string);
/*static float string2number(const char* str);*/



/* -------------------------------
 * public methods
 * ------------------------------- */



/* create & destroy variables */

/*
 * surgescript_var_create()
 * Creates an empty, null variable
 */
surgescript_var_t* surgescript_var_create()
{
    surgescript_var_t* var = ssmalloc(sizeof *var);
    var->type = SSVAR_NULL;
    return var;
}

/*
 * surgescript_var_destroy()
 * Destroys an existing variable from memory
 */
surgescript_var_t* surgescript_var_destroy(surgescript_var_t* var)
{
    RELEASE_DATA(var);
    ssfree(var);
    return NULL;
}




/* sets the value of a variable */

/*
 * surgescript_var_set_null()
 * Sets the variable to null
 */
surgescript_var_t* surgescript_var_set_null(surgescript_var_t* var)
{
    RELEASE_DATA(var);
    var->type = SSVAR_NULL;
    return var;
}

/*
 * surgescript_var_set_bool()
 * Sets the variable to a boolean variable
 */
surgescript_var_t* surgescript_var_set_bool(surgescript_var_t* var, bool boolean)
{
    RELEASE_DATA(var);
    var->type = SSVAR_BOOL;
    var->boolean = boolean ? true : false;
    return var;
}

/*
 * surgescript_var_set_number()
 * Sets the variable to a numeric variable
 */
surgescript_var_t* surgescript_var_set_number(surgescript_var_t* var, float number)
{
    RELEASE_DATA(var);
    var->type = SSVAR_NUMBER;
    var->number = number;
    return var;
}

/*
 * surgescript_var_set_string()
 * Sets the variable to a text variable
 */
surgescript_var_t* surgescript_var_set_string(surgescript_var_t* var, const char* string)
{
    RELEASE_DATA(var);
    var->type = SSVAR_STRING;
    var->string = surgescript_util_strdup(string);
    return var;
}

/*
 * surgescript_var_set_objecthandle()
 * Sets the variable to an object handle
 */
surgescript_var_t* surgescript_var_set_objecthandle(surgescript_var_t* var, unsigned handle)
{
    RELEASE_DATA(var);
    var->type = SSVAR_OBJECTHANDLE;
    var->handle = handle;
    return var;
}



/* retrieve the value stored in a variable */

/*
 * surgescript_var_get_bool()
 * Gets the boolean value of a variable
 */
bool surgescript_var_get_bool(const surgescript_var_t* var)
{
    switch(var->type) {
    case SSVAR_BOOL:
        return var->boolean;
    case SSVAR_NUMBER:
        return var->number != 0 ? true : false;
    case SSVAR_STRING:
        return *(var->string) != 0 ? true : false;
    case SSVAR_NULL:
        return false;
    case SSVAR_OBJECTHANDLE:
        return true;
    }

    return false;
}

/*
 * surgescript_var_get_number()
 * Gets the numeric value of a variable
 */
float surgescript_var_get_number(const surgescript_var_t* var)
{
    switch(var->type) {
    case SSVAR_NUMBER:
        return var->number;
    case SSVAR_BOOL:
        return var->boolean ? 1.0f : 0.0f;
    case SSVAR_STRING:
        return atof(var->string);
    case SSVAR_NULL:
        return 0.0f;
    case SSVAR_OBJECTHANDLE:
        return 0.0f;
    }

    return 0.0f;
}

/*
 * surgescript_var_get_string()
 * Gets the contents of a string variable. You have to ssfree() this after use.
 */
char* surgescript_var_get_string(const surgescript_var_t* var)
{
    switch(var->type) {
    case SSVAR_STRING:
        return surgescript_util_strdup(var->string);
    case SSVAR_BOOL:
        return surgescript_util_strdup(var->boolean ? "true" : "false");
    case SSVAR_NULL:
        return surgescript_util_strdup("null");
    default: {
        char buf[128];
        surgescript_var_to_string(var, buf, sizeof(buf) / sizeof(char));
        return surgescript_util_strdup(buf);
    }
    }
}

/*
 * surgescript_var_get_objecthandle()
 * Gets the object handle
 */
unsigned surgescript_var_get_objecthandle(const surgescript_var_t* var)
{
    return var->type == SSVAR_OBJECTHANDLE ? var->handle : 0;
}


/* misc */

/*
 * surgescript_var_copy()
 * Copies src into dst, without creating a new variable.
 * Returns dst. Similar to strcpy()
 */
surgescript_var_t* surgescript_var_copy(surgescript_var_t* dst, const surgescript_var_t* src)
{
    dst->type = src->type;

    switch(src->type) {
    case SSVAR_BOOL:
        dst->boolean = src->boolean;
        break;
    case SSVAR_NUMBER:
        dst->number = src->number;
        break;
    case SSVAR_STRING:
        dst->string = surgescript_util_strdup(src->string);
        break;
    case SSVAR_OBJECTHANDLE:
        dst->handle = src->handle;
        break;
    default:
        break;
    }

    return dst;
}

/*
 * surgescript_var_clone()
 * Creates a copy of a variable
 */
surgescript_var_t* surgescript_var_clone(const surgescript_var_t* var)
{
    surgescript_var_t* copy = ssmalloc(sizeof *copy);
    return surgescript_var_copy(copy, var);
}

/*
 * surgescript_var_typename()
 * Returns the typename of a variable
 */
const char* surgescript_var_typename(const surgescript_var_t* var)
{
    switch(var->type) {
        case SSVAR_NUMBER:
            return "number";
        case SSVAR_BOOL:
            return "boolean";
        case SSVAR_STRING:
            return "string";
        case SSVAR_NULL:
            return "null";
        case SSVAR_OBJECTHANDLE:
            return "object";
    }
}

/*
 * surgescript_var_to_string()
 * Converts a variable of any type to a string to be stored in a buffer of bufsize bytes
 */
char* surgescript_var_to_string(const surgescript_var_t* var, char* buf, size_t bufsize)
{
    switch(var->type) {
        case SSVAR_STRING:
            return surgescript_util_strncpy(buf, var->string, bufsize);
        case SSVAR_BOOL:
            return surgescript_util_strncpy(buf, var->boolean ? "true" : "false", bufsize);
        case SSVAR_NULL:
            return surgescript_util_strncpy(buf, "null", bufsize);
        case SSVAR_NUMBER: {
            char tmp[33];
            if(var->number == (long)(var->number) || var->number <= LONG_MIN || var->number >= LONG_MAX)
                sprintf(tmp, "%ld", (long)(var->number)); /* is integer */
            else
                sprintf(tmp, "%f", var->number);
            return surgescript_util_strncpy(buf, tmp, bufsize);
        }
        case SSVAR_OBJECTHANDLE: {
            char tmp[48];
            sprintf(tmp, "[object @ 0x%x]", var->handle);
            return surgescript_util_strncpy(buf, tmp, bufsize);
        }
    }

    return buf;
}

/*
 * surgescript_var_compare()
 * Compares a to b. Returns:
 * 0   if a == b
 * <0  if a < b
 * >0  if a > b
 */
int surgescript_var_compare(const surgescript_var_t* a, const surgescript_var_t* b)
{
    if(a->type == b->type) {
        switch(a->type) {
        case SSVAR_BOOL:
            return a->boolean != b->boolean ? (a->boolean ? 1 : -1) : 0;
        case SSVAR_NUMBER:
            return fabsf(a->number - b->number) >= FLT_EPSILON ? (a->number > b->number ? 1 : -1) : 0;
        case SSVAR_OBJECTHANDLE:
            return a->handle != b->handle ? (a->handle > b->handle ? 1 : -1) : 0;
        case SSVAR_STRING:
            return strcmp(a->string, b->string);
        default:
            return 0;
        }
    }
    else {
        if(a->type == SSVAR_NULL || b->type == SSVAR_NULL) {
            return a->type != SSVAR_NULL ? 1 : -1; /* null is less than everything else */
        }
        else if(a->type == SSVAR_STRING || b->type == SSVAR_STRING) {
            char buf[128];
            if(a->type == SSVAR_STRING) {
                surgescript_var_to_string(b, buf, sizeof(buf) / sizeof(char));
                return strcmp(a->string, buf);
            }
            else {
                surgescript_var_to_string(a, buf, sizeof(buf) / sizeof(char));
                return strcmp(buf, b->string);
            }
        }
        else if(a->type == SSVAR_NUMBER || b->type == SSVAR_NUMBER) {
            float x = surgescript_var_get_number(a);
            float y = surgescript_var_get_number(b);
            return fabsf(x - y) >= FLT_EPSILON ? (x > y ? 1 : -1) : 0;
        }
        else if(a->type == SSVAR_BOOL || b->type == SSVAR_BOOL) {
            int x = surgescript_var_get_bool(a);
            int y = surgescript_var_get_bool(b);
            return x ^ y ? (x ? 1 : -1) : 0;
        }
        else if(a->type == SSVAR_OBJECTHANDLE || b->type == SSVAR_OBJECTHANDLE) {
            unsigned x = surgescript_var_get_objecthandle(a);
            unsigned y = surgescript_var_get_objecthandle(b);
            return x != y ? (x < y ? -1 : 1) : 0;
        }
        else
            return 0; /* this shouldn't happen */
    }
}



/* -------------------------------
 * private methods
 * ------------------------------- */

/* converts a string to a float */
#if 0
float string2number(const char* str)
{
    float sign = 1.0f, mult = 1.0f;
    float x = 0.0f, y = 0.0f;
    const char* p = str;

    /* skip spaces */
    while(*p && (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r'))
        p++;

    /* minus sign? */
    if(*p && *p == '-') {
        sign = -1.0f;
        p++;
    }

    /* get the integer part of the number */
    while(*p >= '0' && *p <= '9') {
        x = x * 10.0f + (float)(*p - '0');
        p++;
    }

    /* got a decimal point? */
    if(*p && *p == '.') {
        p++;
        while(*p >= '0' && *p <= '9') {
            mult *= 0.1f;
            y = y + (float)(*p - '0') * mult;
            p++;
        }
    }

    /* done! */
    return sign * (x + y);
}
#endif
