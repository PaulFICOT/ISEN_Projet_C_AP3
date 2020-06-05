#include <stdio.h>
#include <stdlib.h>
#include "../includes/linked_list.h"

linked_list* linked_list_create(void* n) {
    linked_list *l = malloc(sizeof(linked_list));
    l->prev = NULL;
    l->value = n;
    l->next = NULL;
    return l;
}

void backtrack(linked_list **l) {
    if (*l == NULL) {
        return;
    }
    while ((*l)->prev != NULL) {
        *l = (*l)->prev;
    }
}

void push(linked_list *l, void* n) {
    while(l->next != NULL) {
        l = l->next;
    }
    linked_list *tmp = linked_list_create(n);
    tmp->prev = l;
    l->next = tmp;
}

int count_occurrences(linked_list *l, void* n) {
    backtrack(&l);
    int counter = 0;
    while (l != NULL) {
        if (l->value == n) {
            counter++;
        }
        l = l->next;
    }
    return counter;
}

void fusion(linked_list *lA, linked_list *lB) {
    backtrack(&lA);
    backtrack(&lB);
    while (lA->next != NULL) {
        lA = lA->next;
    }
    lA->next = lB;
}

int length(linked_list *l) {
    backtrack(&l);
    int counter = 0;
    while (l != NULL) {
        counter++;
        l = l->next;
    }
    return counter;
}

void swap_next(linked_list *l) {
    void* tmp = l->value;
    l->value = l->next->value;
    l->next->value = tmp;
}

void print_float(linked_list *l) {
    while (l != NULL) {
        printf("%f\n", *((float*) l->value));
        l = l->next;
    }
}

void print_string(linked_list *l) {
    while (l != NULL) {
        printf("%s\n", (char*) l->value);
        l = l->next;
    }
}

void print_int(linked_list *l) {
    while (l != NULL) {
        printf("%i\n", *((int*) l->value));
        l = l->next;
    }
}

void delete(linked_list **l) {
    if ((*l)->prev == NULL) {
        *l = (*l)->next;
        (*l)->prev = (*l)->next;
    } else if ((*l)->next == NULL) {
        *l = (*l)->prev;
        (*l)->next = (*l)->prev;
    } else {
        (*l)->next->prev = (*l)->prev;
        (*l)->prev->next = (*l)->next;
        *l = (*l)->prev;
    }
}

void forward(linked_list **l, int n) {
    while (n > 0 && *l != NULL) {
        *l = (*l)->next;
        n--;
    }
}

void backward(linked_list **l, int n) {
    while (n > 0 && *l != NULL) {
        *l = (*l)->prev;
        n--;
    }
}
