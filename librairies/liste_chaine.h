#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define xy2x(X, Y,LONG)  (X + Y * LONG)

#ifndef Node
typedef struct Node {
    void  *data;
    struct Node * next;
} node_t;
#define STRUCT_NODE
#endif

void push(node_t** head_ref, void *new_data, size_t data_size);
void compare(node_t * head,char* liste,int length);
void* pop(node_t ** head);
void* remove_last(node_t * head);
void update(node_t * head, void *new_data,unsigned int index);
void* get(node_t * head, unsigned int index);
