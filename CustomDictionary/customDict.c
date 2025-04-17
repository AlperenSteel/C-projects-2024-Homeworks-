// Name: Yusuf Alperen Çelik
// Date: 29.05.2024
// Project Name: Custom Dictionary
// Description: This file contains the implementation of a custom dictionary data structure.
#include "customDict.h"
/*Create a new custom dictionary*/
CustomDict* create_dict() {
    CustomDict *dict = (CustomDict *)malloc(sizeof(CustomDict));
    dict->items = NULL;
    dict->size = 0;
    dict->capacity = 0;
    return dict;
}

char* copy_string(const char *source) {
    /*Allocate memory for the new string including the null terminator*/
    char *dest = (char *)malloc(strlen(source) + 1); /*for \0 operator*/
    if (dest) {
        strcpy(dest, source);
    }
    return dest;
}

/*Add or update an item in the dictionary*/
void add_item(CustomDict *dict, const char *key, Value *values, int value_count, char type) {
    /*Check if key already exists in the dictionary*/
    int i,j;
    for (i = 0; i < dict->size; i++) {
        if (strcmp(dict->items[i].key, key) == 0) {
            /*If the key exists, merge existing and new values*/
            int new_value_count = dict->items[i].value_count + value_count; /*Calculate the new value count*/
            dict->items[i].values = (Value *)realloc(dict->items[i].values, new_value_count * sizeof(Value)); /*Reallocate memory for the new values array*/
            for (j = 0; j < value_count; ++j) {
                dict->items[i].values[dict->items[i].value_count + j] = values[j]; /*Copy the new values to the end of the existing values*/
            }
            dict->items[i].value_count = new_value_count;
            free(values); /*Free the temporary values array*/
            return;
        }
    }
    /*If the dictionary is full, increase its capacity*/
    if (dict->size == dict->capacity) {
        if (dict->capacity == 0) {
            dict->capacity = 1;
        } else {
            dict->capacity = (2 * dict->capacity);
        }
        dict->items = (Item *)realloc(dict->items, dict->capacity * sizeof(Item));
    }
    /*Add new item*/
    dict->items[dict->size].key = copy_string(key); /*Store the key*/
    dict->items[dict->size].values = values; /*Store the values*/
    dict->items[dict->size].value_count = value_count; /*Store the value count*/
    dict->items[dict->size].type = type; /*Store the data type*/
    dict->size++;
}

/*Delete an item from the dictionary*/
void delete_item(CustomDict *dict, const char *key) 
{
    int i;
    for (i = 0; i < dict->size; i++) 
    {
        if (strcmp(dict->items[i].key, key) == 0) 
        {
            free(dict->items[i].key);
            free(dict->items[i].values);
            dict->items[i] = dict->items[dict->size - 1];
            dict->size--;
            return;
        }
    }
}

/*Set the value for an existing item*/
void set_value(CustomDict *dict, const char *key, Value *values, int value_count, char type) {
    delete_item(dict, key);
    add_item(dict, key, values, value_count, type);
}

/*Search for an item in the dictionary*/
Value* search_item(CustomDict *dict, const char *key) {
    int temp;
    int i;
    for (i = 0; i < dict->size; i++) {
        /*printf("%s\n", dict->items[i].key);*/
        /*printf("KEY IS: %s\n", key);*/
        /*temp = strcmp(dict->items[i].key, key);*/
        /*printf("%d", temp);*/
        if (strcmp(dict->items[i].key, key) == 0) {
            printf("%s", dict->items[i].key);
            return dict->items[i].values;
        }
    }
    return NULL;
}
int Find_index(CustomDict *dict, const char *key) {
    int i;
    for (i = 0; i < dict->size; i++) {
        if (strcmp(dict->items[i].key, key) == 0) {
            return i;
        }
    }
    return -1;
}

/*Swap function to swap two items*/
void swap(Item *a, Item *b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}
/*Sort the dictionary by keys using bubble sort*/
void sort_dict(CustomDict *dict) {
    int i,j;
    int n = dict->size;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (strcmp(dict->items[j].key, dict->items[j+1].key) > 0) 
            {
                swap(&dict->items[j], &dict->items[j+1]);
            }
        }
    }
}

/*Print the dictionary*/
void print_dict(const CustomDict *dict) {
    int i,j;
    for (i = 0; i < dict->size; i++) {
        printf("Key: %s, Values: ", dict->items[i].key);
        Value *values = dict->items[i].values;
        for (j = 0; j < dict->items[i].value_count; ++j) {
            switch (dict->items[i].type) {
                case 'i':
                    printf("%d ", values[j].i);
                    break;
                case 'f':
                    printf("%.2f ", values[j].f);
                    break;
                case 'd':
                    printf("%.2lf ", values[j].d);
                    break;
                case 'c':
                    printf("%c ", values[j].c);
                    break;
            }
        }
        printf("\n");
    }
}
/*Free the memory allocated for the dictionary*/
void free_dict(CustomDict *dict) {
    int i;
    for (i = 0; i < dict->size; i++) {
        free(dict->items[i].key);
        free(dict->items[i].values);
    }
    /*Free the items array and the dictionary itself*/
    free(dict->items);
    free(dict);
}
/*Read CSV file and populate the dictionary*/
int read_csv(CustomDict *dict, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == 0) {
        return 0; /*file cannot be opened*/
    }
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char junkchar;
        char *token = strtok(line, ", ");
        char type = token[0]; /*Read the data type*/
        /*fscanf(file, "%c", &junkchar);*/
        char *key = strtok(NULL, ", "); /*Read the key*/
        int value_count = 0;
        Value *values = NULL;
        while ((token = strtok(NULL, ",")) != NULL) {
            /*Reallocate memory for values array and store the new value*/
            values = (Value *)realloc(values, (value_count + 1) * sizeof(Value));
            switch (type) {
                case 'i':
                    values[value_count].i = atoi(token);
                    break;
                case 'f':
                    values[value_count].f = atof(token);
                    break;
                case 'd':
                    values[value_count].d = atof(token);
                    break;
                case 'c':
                    values[value_count].c = token[1];
                    break;
            }
            value_count++;
        }
        /*Add a null terminator for char arrays*/
        if (type == 'c') {
            values = (Value *)realloc(values, (value_count + 1) * sizeof(Value));
            values[value_count].c = '\0';
            value_count++;
        }
        add_item(dict, key, values, value_count, type);
    }
    fclose(file);
    return 1;
}