#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    void *data;
    struct Node * next;
} node_t;

// void compare(node_t * head,char* liste,int length){
//     node_t * current = head;
//     while (current != NULL) {
//         if(current->data->bloc)
//         printf("%)d\n", );
//         current = current->next;
//     }
// }
void push(node_t** head_ref, void *new_data, size_t data_size) 
{
    node_t* new_node = (node_t*)malloc(sizeof(node_t)); 
    new_node->data  = malloc(data_size); 
    new_node->next = (*head_ref);
    int i; 
    for (i=0; i<data_size; i++) {
        *(char *)(new_node->data + i) = *(char *)(new_data + i); 
    }
    (*head_ref)    = new_node; 
}

void* pop(node_t ** head) {
    void* retval = NULL;
    node_t * next_node = NULL;
    if (*head == NULL) {
        return NULL;
    }
    next_node = (*head)->next;
    retval = (*head)->data;
    free(*head);
    *head = next_node;
    return retval;
}
void* remove_last(node_t * head) {
    void* retval = NULL;
    if (head->next == NULL) {
        retval = head->data;
        free(head);
        return retval;
    }
    node_t * current = head;
    while (current->next->next != NULL) {
        current = current->next;
    }
    retval = current->next->data;
    free(current->next);
    current->next = NULL;
    return retval;
}
void update(node_t * head, void *new_data,unsigned int index){
    node_t * current = head;
    for(unsigned int i=0;i<index;i++){
        current = current->next;
    }
    current->data=new_data;
}
void get(node_t * head, unsigned int index){
    node_t * current = head;
    for(unsigned int i=0;i<index;i++){
        current = current->next;
    }
    return current->data;
}