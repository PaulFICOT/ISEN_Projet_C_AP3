#include <stdio.h>
#include <stdlib.h>
#include "../includes/linked_list.h"

linked_list* linked_list_create(void* n) {
    linked_list *l = malloc(sizeof(linked_list));
    l->value = n;
    l->next = NULL;
    return l;
}

short is_null(linked_list* l) {
    return l == NULL || (l->value == NULL && l->next == NULL);
}

short has_next(linked_list* l) {
    return !is_null(l) && l->next != NULL;
}

void push(linked_list *l, void* n) {
    while(has_next(l)) {
        forward(&l, 1);
    }
    linked_list *tmp = linked_list_create(n);
    l->next = tmp;
}

int count_occurrences(linked_list *l, void* n) {
    int counter = 0;
    while (!is_null(l)) {
        if (l->value == n) {
            counter++;
        }
        forward(&l, 1);
    }
    return counter;
}

void fusion(linked_list *lA, linked_list *lB) {
    forward(&lA, length(lA));
    lA->next = lB;
}

int length(linked_list *l) {
    int counter = 0;
    while (!is_null(l)) {
        counter++;
        forward(&l, 1);
    }
    return counter;
}

void swap_next(linked_list *l) {
    if (!has_next(l)) {
        return;
    }
    void* tmp = l->value;
    l->value = l->next->value;
    l->next->value = tmp;
}

void print_float(linked_list *l) {
    while (!is_null(l)) {
        printf("%f\n", *((float*) l->value));
        forward(&l, 1);
    }
}

void print_string(linked_list *l) {
    while (!is_null(l)) {
        printf("%s\n", (char*) l->value);
        forward(&l, 1);
    }
}

void print_int(linked_list *l) {
    while (!is_null(l)) {
        printf("%i\n", *((int*) l->value));
        forward(&l, 1);
    }
}

void delete(linked_list **l, void* e) {
    /* case l is null */
    if (is_null(*l)) {
        printf("null case\n");
        return;
    }

    /* case e is the first elem of l */
    if ((*l)->value == e) {
        printf("first case\n");
        /* case e is the only elem of l */
        if (!has_next(*l)) {
            *l = NULL;
            return;
        }

        *l = (*l)->next;
        return;
    }

    linked_list* iterator = (*l);
    while (has_next(iterator) && iterator->next->value != e) {
        forward(&iterator, 1);
    }

    /* case e isn't in l */
    if (!has_next(iterator)) {
        printf("nope case\n");
        return;
    }

    linked_list* tmp = iterator->next;

    /* case e is the last elem of l */
    if (!has_next(iterator->next)) {
        printf("last case\n");
        iterator->next = NULL;
        free(tmp);
        return;
    }

    printf("normal case\n");
    iterator->next = iterator->next->next;
    free(tmp);
}

void forward(linked_list **l, int n) {
    while (n > 0 && !is_null(*l)) {
        *l = (*l)->next;
        n--;
    }
}
