#ifndef LINKED_LIST
#define LINKED_LIST

typedef struct linked_list_ linked_list;

struct linked_list_
{
    linked_list *prev;
    void* value;
    linked_list *next;
};

linked_list* linked_list_create(void* n);

void backtrack(linked_list **l);

void push(linked_list *l, void* n);

int count_occurrences(linked_list *l, void* n);

void delete_int(linked_list **l, void* n, short rmAll);

void fusion(linked_list *lA, linked_list *lB);

int length(linked_list *l);

void swap_next(linked_list *l);

void print_float(linked_list *l);

void print_string(linked_list *l);

void print_int(linked_list *l);

void delete(linked_list **l);

void forward(linked_list **l, int n);

void backward(linked_list **l, int n);

#endif