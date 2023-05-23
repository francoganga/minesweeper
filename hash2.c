#include "hash.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>


typedef struct entry {
    char* key;
    void* value;

    struct entry* next;

} entry;


typedef struct _hash_table {
    uint32_t size;
    hashfunction* hf;

    entry** elements;
} hash_table;

static size_t hash_table_index(hash_table* ht, const char* key) {
    size_t result = (ht->hf(key, strlen(key))) % ht->size;

    return result;
}

static void handle_collission(hash_table* ht, entry* entry) {



    printf("TODO: handle_collission");
    exit(1);
}


hash_table* hash_table_create(uint32_t size, hashfunction* hf){
    hash_table* ht = malloc(sizeof(hash_table));
    ht->size = size;
    ht->hf = hf;
    ht->elements = calloc(size, sizeof(entry*));

    return ht;

}
void hash_table_destroy(hash_table* ht){
    free(ht->elements);
    free(ht);

}
void hash_table_print(printfn* func, hash_table* ht){

    printf("\nHash Table\n-------------------\n");

    for (uint32_t i=0; i<ht->size; i++) {
    
        if (ht->elements[i] != NULL) {
    
            entry* tmp = ht->elements[i];
    
            while (tmp != NULL) {
                if (func != NULL) {
                  func(tmp->value);
                } else {
                  printf("\"%s\": \"%p\"\n", tmp->key, tmp->value);
                }

    
                tmp = tmp->next;
            }
            
        }
    }


    printf("-------------------\n\n");

}
bool hash_table_insert(hash_table* ht, const char* key, void* value){
    if (key == NULL || value == NULL) return false;

    size_t index = hash_table_index(ht, key);

    entry* current_entry = ht->elements[index];

    if (current_entry != NULL ) {
        if (strcmp(current_entry->key, key) == 0) {
            printf("exists, overwrite");
            current_entry->value = value;
            return true;
        } else {
            handle_collission(ht, current_entry);
            // FIXME
            return true;
        }
    }

    // TODO: this part could be extracted to a function
    entry* e = malloc(sizeof(*e));
    e->value = value;
    e->key = malloc(strlen(key) + 1);
    e->key = strcpy(e->key, key);

    e->next = ht->elements[index];
    ht->elements[index] = e;
    /* ht->size++; */

    return true;
}

void* hash_table_lookup(hash_table* ht, const char* key){
    assert(ht != NULL);

    if (key == NULL) return false;

    size_t index = hash_table_index(ht, key);

    entry* tmp = ht->elements[index];

    while (tmp != NULL && strcmp(tmp->key, key) != 0) {
        tmp = tmp->next;
    }

    if (tmp == NULL) return NULL;

    return tmp->value;
}
void hash_table_delete(hash_table* ht, const char* key){

    assert(ht != NULL);

    if (key == NULL) return;

    size_t index = hash_table_index(ht, key);

    entry* tmp = ht->elements[index];
    entry* prev = NULL;

    while (tmp != NULL && strcmp(tmp->key, key) != 0) {
        prev = tmp;
        tmp = tmp->next;
    }

    if (tmp == NULL) return;

    if (prev == NULL) {
        //free(tmp);
        ht->elements[index] = tmp->next;
    } else {
        // deleting from not the head
        prev->next = tmp->next;
    }

    free(tmp);
}