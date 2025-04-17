#ifndef CUSTOMDICT_H
#define CUSTOMDICT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Value union to store different data types*/
typedef union {
    int i;
    float f;
    double d;
    char c;
} Value;

/*Item struct to represent a dictionary item*/
typedef struct {
    char *key;
    Value *values;
    unsigned int value_count;
    char type; /*'i' for int, 'f' for float, 'd' for double, 'c' for char*/
} Item;

/*CustomDict struct to represent the dictionary*/
typedef struct {
    Item *items;
    unsigned int size;
    unsigned int capacity;
} CustomDict;

/*Function prototypes*/
CustomDict* create_dict();
void add_item(CustomDict *dict, const char *key, Value *values, int value_count, char type);
void delete_item(CustomDict *dict, const char *key);
void set_value(CustomDict *dict, const char *key, Value *values, int value_count, char type);
Value* search_item(CustomDict *dict, const char *key);
void sort_dict(CustomDict *dict);
void print_dict(const CustomDict *dict);
void free_dict(CustomDict *dict);
int read_csv(CustomDict *dict, const char *filename);
char* copy_string(const char *source);
int Find_index(CustomDict *dict, const char *key);

#endif /* CUSTOMDICT_H*/