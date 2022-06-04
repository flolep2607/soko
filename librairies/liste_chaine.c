#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#ifndef LEVEL_C
#include "level.c"
#define LEVEL_C
#endif

// void push(node_t** head_ref, void *new_data, size_t data_size) 
// {
//     node_t* new_node = (node_t*)malloc(sizeof(node_t)); 
//     new_node->data  = malloc(data_size); 
//     new_node->next = (*head_ref);
//     int i; 
//     for (i=0; i<data_size; i++) {
//         *(char *)(new_node->data + i) = *(char *)(new_data + i); 
//     }
//     (*head_ref)    = new_node; 
// }
void push(node_t** head_ref, void *new_data, size_t data_size)
{
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref)    = new_node;
}
void push_queue(node_t** head_ref, void *new_data, size_t data_size)
{
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    node_t* last_node = (node_t*)malloc(sizeof(node_t));
	if (new_node == NULL || head_ref == NULL || last_node == NULL) {
		fprintf(stderr, "Chained list empty");
		exit(EXIT_FAILURE);
	}
	last_node = *head_ref;
	while (last_node->next != NULL) {
		last_node = last_node->next;
	}
	new_node->data = new_data;
	new_node->next = NULL;
	last_node->next = new_node;
	//free(lastNode); //we should free the memory space but it's bug
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
void* get(node_t * head, unsigned int index){
    node_t * current = head;
    for(unsigned int i=0;i<index;i++){
        current = current->next;
    }
    return current->data;
}
void print(node_t *head) {
    node_t *current_node = head;
   	while ( current_node != NULL) {
        printf("%d ", ((case_t *)current_node->data)->bloc);
        current_node = current_node->next;
    }
}