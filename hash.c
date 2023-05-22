#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 500

typedef struct Point
{
  int x;
  int y;
} Point;

int point_cmp(Point* a, Point* b)
{
  printf("(%d == %d) && (%d == %d)", a->x, b->x, a->y, b->y);
  if ((a->x == b->x) && (a->y == b->y)) {
    return 0;
  }

  return 1;
}

/*
  https://stackoverflow.com/a/682617
*/
unsigned long hash_function2(Point *point)
{
  unsigned long n = ((point->x + point->y)*(point->x + point->y + 1)/2) + point->y;
  return n;
}

typedef struct Ht_item
{
    Point *key;
    int *value;
} Ht_item;

typedef struct Hash_table
{
    Ht_item **items;
    int size;
    int count;
} Hash_table;

Ht_item *create_item(Point *key, int *value)
{
    Ht_item *item = (Ht_item *)malloc(sizeof(Ht_item));
    item->key = (Point *) malloc(sizeof(Point));
    item->key = key;
    item->value = (int *) malloc(sizeof(int));
    item->value = value;



    printf("created_item: key(%d, %d) - VALUE: %d\n", item->key->x, item->key->y, *item->value);

    return item;
}

void print_item(Ht_item *item)
{
  printf("ITEM: (%d, %d) - val: %d\n", item->key->x, item->key->y, *item->value);
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
          printf("Index:%d, Key:(%d, %d), Value:%d\n", i, table->items[i]->key->x, table->items[i]->key->y, *table->items[i]->value);
        }
    }

    printf("-------------------\n\n");
}

void handle_collision(Hash_table* table, Ht_item *item)
{
    printf("TODO: handle_collission");
    exit(1);
}

void ht_insert(Hash_table* table, Point *key, int *value)
{
    printf("insert val: %d\n", *value);    
    Ht_item *item = create_item(key, value);

    int index = hash_function2(key);

    Ht_item *current_item = table->items[index];

    if (current_item == NULL) {

        if (table->count == table->size) {
            // HashTable is full.
            printf("Insert Error: Hash Table is full\n");
            free_item(item);
            return;
        }


        print_item(item);
        table->items[index] = item;
        table->count++;
    } else {
      printf("val is: %d\n", *current_item->value);
        if (point_cmp(current_item->key, key) == 0) {
            printf("already exists: %d, %d\n", key->x, key->y);
            printf("val is: %d\n", *current_item->value);
            printf("val to insert is: %d\n", *value);
            table->items[index]->value = value;
            return;
        } else {
            handle_collision(table, item);
            return;
        }
    }

    print_table(table);
}

int* ht_search(Hash_table* table, Point *key)
{
    int index = hash_function2(key);
    Ht_item *item = table->items[index];

    if (item != NULL) {
        if (point_cmp(item->key, key) == 0) {
            return item->value;
        }
    }

    return NULL;
}

void print_search(Hash_table* table, Point *key)
{
    int* val;

    if ((val = ht_search(table, key)) == NULL) {
        printf("Key:(%d, %d) does not exist\n", key->x, key->y);
        return;
    } else {
        printf("Key:(%d, %d), Value:%d\n", key->x, key->y, *val);
    }
}

void test_print(int* test) {
  printf("%d\n", *test);
}


int main()
{

    Hash_table *table = create_hash_table(CAPACITY);
    

    Point p1 = {1, 1};
    Point p2 = {0, 0};

    int val1 = 9;
    int val2 = 1;


    
    ht_insert(table, &p1, &val1);
    ht_insert(table, &p2, &val2);
    
    print_table(table);

}
