#ifndef HASTABLE_H
#define HASTABLE_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef uint64_t hashfunction (const char*, size_t);
typedef struct _hash_table hash_table;
typedef void printfn (void*);


hash_table* hash_table_create(uint32_t size, hashfunction* hf);
void hash_table_destroy(hash_table* ht);
void hash_table_print(printfn* fn, hash_table* ht);
bool hash_table_insert(hash_table* ht, const char* key, void* value);
void* hash_table_lookup(hash_table* ht, const char* key);
void hash_table_delete(hash_table* ht, const char* key);
char** hash_table_keys(hash_table* ht);
uint32_t hash_table_count(hash_table* ht);

#endif
