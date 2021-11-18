/* 
 * Implementation of the hash table.
 * largely based on the hash table in 
 * https://www.ks.uiuc.edu/Research/vmd/plugins/doxygen/hash_8c-source.html
 */
#ifndef HASH_H
#define HASH_H

typedef struct hash_t {
  struct hash_node_t **bucket;      /* array of hash nodes */
  int size;                         /* size of the array */
  int entries;                      /* number of entries in table */
  int downshift;                    /* shift count, used in hash function */
  int mask;                         /* used to select bits for hashing */
} hash_t;

#define HASH_FAIL -251199

#if defined(VMDPLUGIN_STATIC)
#define VMDEXTERNSTATIC static
#include "hash.c"
#else

#define VMDEXTERNSTATIC 

#ifdef __cplusplus
extern "C" {
#endif

void hash_init(hash_t *, int);

int hash_lookup (const hash_t *, const char *);

int hash_insert (hash_t *, const char *, int);

int hash_delete (hash_t *, const char *);

void hash_destroy(hash_t *);

#ifdef __cplusplus
}
#endif

#endif

#endif