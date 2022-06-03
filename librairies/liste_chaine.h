typedef struct Case_
{
    unsigned char bloc; // 0->air 1->wall 2->box 3->body
    bool cible;
} case_t;

typedef struct node {
    void  *data;
    struct node * next;
} node_t;

void print_list(node_t * head);
void push(node_t * head, int val);
void push(node_t ** head, int val);
int pop(node_t ** head);
int remove_last(node_t * head);
int remove_by_index(node_t ** head, int n);