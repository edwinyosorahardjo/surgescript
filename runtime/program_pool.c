/*
 * SurgeScript
 * A lightweight programming language for computer games and interactive apps
 * Copyright (C) 2016  Alexandre Martins <alemartf(at)gmail(dot)com>
 *
 * util/program_pool.c
 * SurgeScript program pool
 */

#include "program_pool.h"
#include "program.h"
#include "../util/uthash.h"
#include "../util/util.h"

/* types */
typedef struct surgescript_programpool_hashpair_t surgescript_programpool_hashpair_t;
struct surgescript_programpool_hashpair_t
{
    char* signature; /* key */
    surgescript_program_t* program; /* value */
    UT_hash_handle hh;
};

struct surgescript_programpool_t
{
    surgescript_programpool_hashpair_t* hash;
};

static char* generate_signature(const char* object_name, const char* program_name);

/* -------------------------------
 * public methods
 * ------------------------------- */

/*
 * surgescript_programpool_create()
 * Creates a new program pool
 */
surgescript_programpool_t* surgescript_programpool_create()
{
    surgescript_programpool_t* pool = ssmalloc(sizeof *pool);
    pool->hash = NULL;
    return pool;
}

/*
 * surgescript_programpool_destroy()
 * Destroys a program pool
 */
surgescript_programpool_t* surgescript_programpool_destroy(surgescript_programpool_t* pool)
{
    surgescript_programpool_hashpair_t *it, *tmp;
    HASH_ITER(hh, pool->hash, it, tmp) {
        HASH_DEL(pool->hash, it);
        ssfree(it->signature);
        surgescript_program_destroy(it->program);
        ssfree(it);
    }
    return ssfree(pool);
}

/*
 * surgescript_programpool_exists()
 * Does the specified program exist in the pool?
 */
bool surgescript_programpool_exists(surgescript_programpool_t* pool, const char* object_name, const char* program_name)
{
    surgescript_programpool_hashpair_t* pair = NULL;
    char* signature = generate_signature(object_name, program_name);
    HASH_FIND_STR(pool->hash, signature, pair);
    ssfree(signature);
    return pair != NULL;
}

/*
 * surgescript_programpool_put()
 * Puts a program in the pool
 */
bool surgescript_programpool_put(surgescript_programpool_t* pool, const char* object_name, const char* program_name, surgescript_program_t* program)
{
    if(!surgescript_programpool_exists(pool, object_name, program_name)) {
        surgescript_programpool_hashpair_t* pair = ssmalloc(sizeof *pair);
        pair->signature = generate_signature(object_name, program_name);
        pair->program = program;
        HASH_ADD_KEYPTR(hh, pool->hash, pair->signature, strlen(pair->signature), pair);
        return true;
    }
    else {
        ssfatal("Runtime Error: duplicate function \"%s\" in object \"%s\"", program_name, object_name);
        return false;
    }
}

/*
 * surgescript_programpool_get()
 * Gets a program from the pool (returns NULL if not found)
 */
surgescript_program_t* surgescript_programpool_get(surgescript_programpool_t* pool, const char* object_name, const char* program_name)
{
    surgescript_programpool_hashpair_t* pair = NULL;
    char* signature = NULL;
    
    /* find the program */
    signature = generate_signature(object_name, program_name);
    HASH_FIND_STR(pool->hash, signature, pair);
    ssfree(signature);

    /* if there is no such program */
    if(!pair) {
        /* try locating it in a common base for all objects */
        signature = generate_signature("Object", program_name);
        HASH_FIND_STR(pool->hash, signature, pair);
        ssfree(signature);

        /* really, the program doesn't exist */
        if(!pair) {
            ssfatal("Runtime Error: can't find function \"%s\" in object \"%s\"", program_name, object_name);
            return NULL;
        }
    }

    /* found it! */
    return pair->program;
}


/* -------------------------------
 * private methods
 * ------------------------------- */

/* generates a hash signature, given an object name and a program name */
char* generate_signature(const char* object_name, const char* program_name)
{
    char* signature = ssmalloc((strlen(object_name) + strlen(program_name) + 2) * sizeof(*signature));
    strcpy(signature, object_name);
    strcat(signature, ".");
    strcat(signature, program_name);
    return signature;
}
