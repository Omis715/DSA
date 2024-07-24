#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node* initialise (int number) {
   Node *item = (Node*)malloc(sizeof(Node));
   item->value = number;
   item->next = NULL;
    
}

void print_linked_list (Node* LL) {
    Node *current = LL;
    while(current->next != NULL){
        printf("%d \n",current->value);
        current = current->next;
    }
    printf("%d\n",current->value);
}

void append (Node* LL, int number) {
   Node *current = LL;
   Node *item = (Node*)malloc(sizeof(Node));
   item->next = NULL;
   item->value = number;
   while(current->next !=NULL)
   {
       current = current->next;
   }
   current->next = item;
    
}

void removeByValue (Node** LL, int value){
    Node *current = *LL;
    Node *previous = NULL;
    if (current->value == value) {
        Node* temp = *LL;
        *LL = (*LL)->next;
        free(temp);
        return;
    }
    while(current->value != value && current != NULL)
    {
        previous = current;
        current = current->next;
    }
    if(current->value == value)
    {
        previous->next = current->next;
        free(current);
        return;
    }
    else{
        printf("Element non trouvé\n");
    }
    
}
int main () {
    Node* ll = initialise(12);
    append(ll,5);
    print_linked_list(ll);
    removeByValue(&ll,12);
    print_linked_list(ll);
}
