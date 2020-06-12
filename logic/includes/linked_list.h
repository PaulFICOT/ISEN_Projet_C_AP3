#ifndef LINKED_LIST
#define LINKED_LIST

typedef struct linked_list_ linked_list;

struct linked_list_
{
    void* value;
    linked_list *next;
};

/**
 * linked_list constructor.
 * 
 * @param n the value of the linked list
 * @return a new linked_list instance
 */
linked_list* linked_list_create(void* n);

/**
 * Checks if the linked list is null
 * 
 * @param l the linked list
 */
short is_null(linked_list* l);

/**
 * Checks if the element has a successor (including the tail)
 * 
 * @param l the element to check
 * 
 * @return true if the element has a successor
 */
short has_next(linked_list* l);

/**
 * Appends an element at the end of the linked_list
 * 
 * @param l the list
 * @param n the value of the new element
 */
void push(linked_list *l, void* n);

/**
 * Counts the number of occurences of an element in a linked_list
 * 
 * @param l the linked_list
 * @param n the element to search
 * 
 * @return the number of occurences
 */
int count_occurrences(linked_list *l, void* n);

/**
 * Append a linked list to another linked list
 * 
 * @param lA the linked list which will receive the other list
 * @param lB the linked list whicj will be merged in the other
 */
void fusion(linked_list *lA, linked_list *lB);

/**
 * Count the number of elements in a linked list (exluding head and tail)
 * 
 * @param l the linked_list
 * 
 * @return the number of elements
 */
int length(linked_list *l);

/**
 * Swaps the element of a linked list with the next one
 * 
 * @param l the element to be swapped
 */
void swap_next(linked_list *l);

/**
 * print all the values of a linked lit of floats
 * 
 * @param l the linked list
 */
void print_float(linked_list *l);

/**
 * print all the values of a linked lit of strings
 * 
 * @param l the linked list
 */
void print_string(linked_list *l);

/**
 * print all the values of a linked lit of integers
 * 
 * @param l the linked list
 */
void print_int(linked_list *l);

/**
 * Deletes an element of a linked list
 * 
 * @param l a pointer to a linked_list's pointer
 */
void delete(linked_list **l, void* e);

/**
 * Move the pointer to the next element of the list
 * 
 * @param l a pointer to a linked_list's pointer
 */
void forward(linked_list **l, int n);

#endif
