//   Name: Yusuf Alperen Çelik
//   Project Name: Custom Dictionary
//   Date: 29.05.2024

//Project Description: 
//      This project is a custom dictionary that allows you to add, delete, set, search, sort, and print items.
//      It also allows you to read from a CSV file and write to a CSV file.

#include "customDict.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    CustomDict *dict = create_dict();
    char choice;
    int menu_flag = 1;
    char key[256];
    char type;
    Value *values;
    unsigned int value_count;
    char filename[256];
    int i, j;

    while (menu_flag) {
        printf("\nMenu:\n");
        printf("1. Add item\n");
        printf("2. Delete item\n");
        printf("3. Set value\n");
        printf("4. Search item\n");
        printf("5. Sort dictionary\n");
        printf("6. Print dictionary\n");
        printf("7. Read CSV file\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);
        switch (choice) {
            case '1':
                printf("Enter key: ");
                scanf("%s", key);
                printf("Enter type (i: int, f: float, d: double, c: char): ");
                scanf(" %c", &type);
                value_count = 0;
                values = NULL;
                char value[256];
                printf("Enter values (enter 'e' to stop): ");
                while (1) {
                    scanf("%s", value);
                    if (strcmp(value, "e") == 0) 
                    {
                        break;
                    }
                    values = (Value *)realloc(values, (value_count + 1) * sizeof(Value));
                    switch (type) {
                        case 'i':
                            values[value_count].i = atoi(value);
                            break;
                        case 'f':
                            values[value_count].f = atof(value);
                            break;
                        case 'd':
                            values[value_count].d = atof(value);
                            break;
                        case 'c':
                            values[value_count].c = value[0];
                            break;
                    }
                    value_count++;
                }
                /*Add a null terminator for char arrays*/
                if (type == 'c') {
                    values = (Value *)realloc(values, (value_count + 1) * sizeof(Value));
                    values[value_count].c = '\0';
                }
                add_item(dict, key, values, value_count, type);
                break;
            case '2':
                printf("Enter key to delete: ");
                scanf("%s", key);
                delete_item(dict, key);
                break;
            case '3':
                printf("Enter key: ");
                scanf("%s", key);
                printf("Enter type (i: int, f: float, d: double, c: char): ");
                scanf(" %c", &type);
                value_count = 0;
                values = NULL;
                printf("Enter values (enter 'e' to stop): ");
                while (1) {
                    scanf("%s", value);
                    if (strcmp(value, "e") == 0) break;
                    values = (Value *)realloc(values, (value_count + 1) * sizeof(Value));
                    switch (type) {
                        case 'i':
                            values[value_count].i = atoi(value);
                            break;
                        case 'f':
                            values[value_count].f = atof(value);
                            break;
                        case 'd':
                            values[value_count].d = atof(value);
                            break;
                        case 'c':
                            values[value_count].c = value[0];
                            break;
                    }
                    value_count++;
                }
                /*Add a null terminator for char arrays*/
                if (type == 'c') {
                    values = (Value *)realloc(values, (value_count + 1) * sizeof(Value));
                    values[value_count].c = '\0';
                }
                set_value(dict, key, values, value_count, type);
                break;
            case '4':
                printf("Enter key to search: ");
                scanf("%s", key);
                i = Find_index(dict, key); /*Find the index of the key*/
                values = search_item(dict, key); /*Search for the item*/
                if (values != NULL) {
                    printf("\nValues: ");
                    for (j = 0; j < dict->items[i].value_count; ++j) { /*Print the values*/
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
                } else {
                    printf("Item not found.\n");
                }
                break;
            case '5':
                sort_dict(dict);
                printf("Dictionary sorted.\n");
                break;
            case '6':
                print_dict(dict);
                break;
            case '7':
                printf("Enter CSV filename: ");
                scanf("%s", filename);
                if (read_csv(dict, filename)) 
                {
                    printf("CSV file read.\n");
                } else {
                    printf("Failed to read file.\n");
                }
                break;
            case '8':
                free_dict(dict);
                printf("Exiting...");
                menu_flag = 0;
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
    return 0;
}