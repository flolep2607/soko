#pragma once
#include <stdbool.h>

typedef struct node {
    void  *data;
    struct node * next;
} node_t;

void compare(node_t * head,char* liste,int length);
void push(node_t * head, void* val);
void push_preprend(node_t ** head, void* val);
int pop(node_t ** head);
int remove_last(node_t * head);
int remove_by_index(node_t ** head, int n);