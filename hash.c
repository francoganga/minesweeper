#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 500

unsigned long hash_function(char *str)
{
    unsigned long i = 0;

    for (int j = 0; str[j]; j++)
    {
        i += str[j];
    }

    return i % CAPACITY;

}

/*
  https://stackoverflow.com/a/682617
*/
unsigned long hash_function2(int x, int y)
{
  unsigned long n = ((x + y)*(x + y + 1)/2) + y;
  return n;
}

typedef struct Ht_item
{
    char *key;
    char *value;
} Ht_item;

typedef struct Hash_table
{
    Ht_item **items;
    int size;
    int count;
} Hash_table;

Ht_item *create_item(char *key, char *value)
{
    Ht_item *item = (Ht_item *)malloc(sizeof(Ht_item));
    item->key = (char *) malloc(strlen(key) + 1);
    item->value = (char *) malloc(strlen(value) + 1);
    strcpy(item->key, key);
    strcpy(item->value, value);

    return item;
}

Hash_table *create_hash_table(int size)
{
    Hash_table *table = (Hash_table *)malloc(sizeof(Hash_table));

    table->size = size;
    table->count = 0;
    table->items = (Ht_item **) calloc(table->size, sizeof(Ht_item *));

    for (int i = 0; i < table->size; i++)
    {
        table->items[i] = NULL;
    }

    return table;
}

void free_item(Ht_item *item)
{
    free(item->key);
    free(item->value);
    free(item);
}

void free_table(Hash_table* table)
{
    for (int i = 0; i < table->size; i++) {
        Ht_item* item = table->items[i];
        if (item != NULL)
            free_item(item);
    }

    free(table->items);
    free(table);
}

void print_table(Hash_table* table)
{
    printf("\nHash Table\n-------------------\n");

    for (int i = 0; i < table->size; i++)
    {
        if (table->items[i])
        {
            printf("Index:%d, Key:%s, Value:%s\n", i, table->items[i] -> key, table->items[i]->value);
        }
    }

    printf("-------------------\n\n");
}

void handle_collision(Hash_table* table, Ht_item *item)
{
    printf("TODO: handle_collission");
    exit(1);
}

void ht_insert(Hash_table* table, char *key, char *value)
{
    Ht_item *item = create_item(key, value);

    int index = hash_function(key);

    Ht_item *current_item = table->items[index];

    if (current_item == NULL) {

        if (table->count == table->size) {
            // HashTable is full.
            printf("Insert Error: Hash Table is full\n");
            free_item(item);
            return;
        }

        table->items[index] = item;
        table->count++;
    } else {
        if (strcmp(current_item->key, key) == 0) {
            strcpy(table->items[index]->value, value);
            return;
        } else {
            handle_collision(table, item);
            return;
        }
    }
}

char* ht_search(Hash_table* table, char *key)
{
    int index = hash_function(key);
    Ht_item *item = table->items[index];

    if (item != NULL) {
        if (strcmp(item->key, key) == 0) {
            return item->value;
        }
    }

    return NULL;
}

void print_search(Hash_table* table, char *key)
{
    char* val;

    if ((val = ht_search(table, key)) == NULL) {
        printf("Key:%s does not exist\n", key);
        return;
    } else {
        printf("Key:%s, Value:%s\n", key, val);
    }
}

int main()
{

  int rows = 8;

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < rows; j++) {
      unsigned long res = hash_function2(i, j);
      printf("%lu\n", res);
    }
  }

}
