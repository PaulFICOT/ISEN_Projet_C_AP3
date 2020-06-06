#include <stdio.h>
#include <stdlib.h>
#include "../includes/linked_list.h"

linked_list* null_linked_list() {
    linked_list *l = malloc(sizeof(linked_list));
    l->prev = NULL;
    l->value = NULL;
    l->next = NULL;
    return l;
}

linked_list* linked_list_create(void* n) {
    linked_list *l = null_linked_list();

    linked_list *head = null_linked_list();
    head->next = l;
    l->prev = head;

    l->value = n;

    linked_list *tail = null_linked_list();
    tail->prev = l;
    l->next = tail;
    
    return l;
}

short is_head(linked_list* l) {
    return l->prev == NULL && l->value == NULL && l->next != NULL;
}

short is_tail(linked_list* l) {
    return l->prev != NULL && l->value == NULL && l->next == NULL;
}

short is_null(linked_list* l) {
    return l == NULL || (l->prev == NULL && l->value == NULL && l->next == NULL);
}

short has_prev(linked_list* l) {
    return !is_null(l) && l->prev != NULL;
}

short has_next(linked_list* l) {
    return !is_null(l) && l->next != NULL;
}

short is_last(linked_list* l) {
    return has_next(l) && l->next->value == NULL;
}

short is_first(linked_list* l) {
    return has_prev(l) && l->prev->value == NULL;
}

void backtrack(linked_list **l) {
    if (*l == NULL) {
        return;
    }
    while (!is_first(*l)) {
        backward(l, 1);
    }
}

void push(linked_list *l, void* n) {
    backtrack(&l);
    while(!is_last(l)) {
        forward(&l, 1);
    }
    linked_list *tmp = null_linked_list();
    tmp->prev = l;
    tmp->value = n;
    tmp->next = l->next;
    l->next = tmp;
}

int count_occurrences(linked_list *l, void* n) {
    backtrack(&l);
    int counter = 0;
    while (has_next(l)) {
        if (l->value == n) {
            counter++;
        }
        forward(&l, 1);
    }
    return counter;
}

void fusion(linked_list *lA, linked_list *lB) {
    while (!is_last(lA)) {
        forward(&lA, 1);
    }
    backtrack(&lB);
    lA->next = lB;
    lB->prev = lA;
}

int length(linked_list *l) {
    backtrack(&l);
    int counter = 0;
    while (has_next(l)) {
        counter++;
        forward(&l, 1);
    }
    return counter;
}

void swap_next(linked_list *l) {
    if (is_last(l)) {
        return;
    }
    void* tmp = l->value;
    l->value = l->next->value;
    l->next->value = tmp;
}

void print_float(linked_list *l) {
    while (has_next(l)) {
        printf("%f\n", *((float*) l->value));
        forward(&l, 1);
    }
}

void print_string(linked_list *l) {
    while (has_next(l)) {
        printf("%s\n", (char*) l->value);
        forward(&l, 1);
    }
}

void print_int(linked_list *l) {
    while (has_next(l)) {
        printf("%i\n", *((int*) l->value));
        forward(&l, 1);
    }
}

void delete(linked_list **l) {
    (*l)->next->prev = (*l)->prev;
    (*l)->prev->next = (*l)->next;
    if (is_first(*l)) {
        *l = (*l)->next;
    } else {
        *l = (*l)->prev;
    }
}

void forward(linked_list **l, int n) {
    while (n > 0 && has_next(*l)) {
        *l = (*l)->next;
        n--;
    }
}

void backward(linked_list **l, int n) {
    while (n > 0 && has_prev(*l)) {
        *l = (*l)->prev;
        n--;
    }
}
