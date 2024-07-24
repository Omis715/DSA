#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct GroceryItem {
    char *name;
    double price;
    struct GroceryItem *next; 
} GroceryItem;

#define TABLE_SIZE 100

typedef struct HashTable {
    GroceryItem *table[TABLE_SIZE];
} HashTable;


unsigned int hash(const char *str) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash << 5) + *str++;
    }
    return hash % TABLE_SIZE;
}

HashTable* createHashTable() {
    HashTable *hashTable = (HashTable *)malloc(sizeof(HashTable));
    if (hashTable == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable->table[i] = NULL;
    }
    return hashTable;
}

void insertItem(HashTable *hashTable, const char *name, double price) {
    unsigned int index = hash(name);
    GroceryItem *newItem = (GroceryItem *)malloc(sizeof(GroceryItem));
    if (newItem == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newItem->name = strdup(name); // Duplicate the string
    if (newItem->name == NULL) {
        fprintf(stderr, "String duplication failed\n");
        free(newItem);
        exit(EXIT_FAILURE);
    }
    newItem->price = price;
    newItem->next = hashTable->table[index]; // Insert at the beginning of the list
    hashTable->table[index] = newItem;
}

// Look up the price of a grocery item by its name
double lookupPrice(HashTable *hashTable, const char *name) {
    unsigned int index = hash(name);
    GroceryItem *item = hashTable->table[index];
    while (item != NULL) {
        if (strcmp(item->name, name) == 0) {
            return item->price;
        }
        item = item->next;
    }
    return -1.0; // Indicate that the item was not found
}

// Free the hash table and its items
void freeHashTable(HashTable *hashTable) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        GroceryItem *item = hashTable->table[i];
        while (item != NULL) {
            GroceryItem *temp = item;
            item = item->next;
            free(temp->name);
            free(temp);
        }
    }
    free(hashTable);
}

// Main function to demonstrate the usage of the hash table
int main() {
    HashTable *hashTable = createHashTable();

    insertItem(hashTable, "Apple", 0.99);
    insertItem(hashTable, "Banana", 0.59);
    insertItem(hashTable, "Orange", 0.79);

    printf("Price of Apple: $%.2f\n", lookupPrice(hashTable, "Apple"));
    printf("Price of Banana: $%.2f\n", lookupPrice(hashTable, "Banana"));
    printf("Price of Orange: $%.2f\n", lookupPrice(hashTable, "Orange"));
    printf("Price of Pear: $%.2f\n", lookupPrice(hashTable, "Pear")); // Not found

    // Free allocated memory
    freeHashTable(hashTable);

    return 0;
}
