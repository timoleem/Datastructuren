#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Made by  
// Timo Leemans
// Student number : 10785612
// 20 / 02 / 2019

// Extra functions necessary for a solid working insertion sort

#include "list.h"

// Necessary structs and variables for list
struct list {

    struct node* head;
    struct node *tail;
};

// Necessary structs and variables for node
struct node {

    struct node* next;
    struct node *previous;
    int val;
};

/* Creates a new linked list and returns a pointer to it.
 * Returns NULL on failure. */
struct list* list_init(void) {

    struct list *l = malloc(sizeof(struct list));
    if (l == NULL) {
        return NULL;
    }
    l->head = NULL;
    l->tail = NULL;
    return l;
}

/* Creates a new node that contains the number num and returns a pointer to it.
 * Returns NULL on failure. */
struct node* list_new_node(int num) {

    struct node *n = malloc(sizeof(struct node));
    if (n == NULL) {
        return NULL;
    }
    n->val = num;
    n->next = NULL; 
    n->previous = NULL;
    return n;
}

/* Returns the first node of the list L or NULL if list is empty. */
struct node* list_head(struct list* l) {
    
    if (!l) {
        return NULL;
    }
    return l->head;
}

/* Returns a pointer to the node after node N or NULL if N is the last node in
 * the list. */
struct node* list_next(struct node* n) {

    if (!n || !n->next) {
        return NULL;
    }
    return n->next;    
}

/* Inserts node N at the front of list L.
 * Returns 0 if N was succesfully inserted, 1 otherwise. */
int list_add_front(struct list* l, struct node* n) {

    if (!l || !n) {
        return 1;
    }
    struct node *last = list_head(l);
    l->head = n;
    n->next = last;
    return 0;
}

/* Returns the last node of the list L or NULL if list is empty. */
struct node* list_tail(struct list* l) {

    if(!l) {
        return NULL;
    }
    struct node *last = list_head(l); 
    while (last->next) 
    { 
        last = list_next(last); 
    } 
    return last;
}

/* Returns a pointer to the node before node N in the list L, or returns NULL
 * if N is the first node in the list or if N is not in the list at all. */
struct node* list_prev(struct list* l, struct node* n) {

    if (!l || !n || list_head(l) == n) {
        return NULL;
    }
    struct node *last = list_head(l);
    while (last->next != n) {
        if (last == NULL) {
            return NULL;
        }
        last = list_next(last);
    }
    return last;    
}

/* Appends node N at the back of list L.
 * Returns 0 if N was succesfully appended, 1 otherwise. */
int list_add_back(struct list* l, struct node* n) {

    if (!l || !n) {
        return 1;
    }
    if (!list_head(l)) {
        // if the list has no elements
        l->head = n;
        return 0;
    }
    struct node *last = list_tail(l); 
    last->next = n;
    return 0;
}

/* Returns the value stored in the list node N, or 0 if N is the NULL
 * pointer. */
int list_node_value(struct node* n) {

    if (n) {
        return n->val;
    }
    return 0;
}

/* Unlink node N from list L. After unlinking, the list L contains no pointers
 * to the node N and N contains no pointers to nodes in L.
 * Returns 0 if N was succesfully unlinked from list L, or 1 otherwise */
int list_unlink_node(struct list* l, struct node* n) {

    if (!l || !n) {
        return 1;
    }
    if (n == list_head(l)) {
        struct node *following = list_next(n);
        l->head = following;
        n->next = NULL;        
        return 0;
    }
    struct node *following = list_next(n);
    struct node *previous = list_prev(l, n);

    previous->next = following;
    n->next = NULL;
    return 0;
}

/* Frees node N. */
void list_free_node(struct node* n) {

    free(n);
}

/* Cleans up entire list L data structure.
 * Returns 0 if succesful, 1 otherwise. */
int list_cleanup(struct list* l) {

    if (!list_head(l)) {
        free(l);
        return 0;
    }
    struct node *last = list_head(l); 
    while (last != NULL) { 
        struct node *temp = last;
        last = list_next(last);
        list_unlink_node(l, temp);        
        list_free_node(temp);    
    }      
    free(l);
    return 0;
}

/* Returns 1 if node N is present in list L, 0 otherwise. */
int list_node_present(struct list* l, struct node* n) {

    struct node *last = list_head(l); 
    while (last != NULL) {
        if (list_node_value(last) == list_node_value(n)) {
            return 1;
        }
        last = list_next(last);
    }
    return 0;
}

/* Inserts node N after node M in list L.
 * Fails if node M is not in the list L or if node N is already in list L.
 * Returns 0 if N was succesfully inserted, or 1 otherwise. */
int list_insert_after(struct list* l, struct node* n, struct node* m) {

    if (!l || !n || !m) {
        return 1;
    }
    struct node *next_m = list_next(m);
    n->next = next_m;
    m->next = n;
    return 0;
}

/* Inserts node N before node M in list L.
 * Fails if node M is not in the list L or if node N is already in list L.
 * Returns 0 if N was succesfully inserted, or 1 otherwise. */
int list_insert_before(struct list* l, struct node* n, struct node* m) {

    if (!l || !n || !m) {
        return 1;
    }
    struct node *prev_m = list_prev(l, m);
    prev_m->next = n;
    n->next = m;
    return 0;
}

/* Returns the length of list L, or 0 if L is the NULL pointer */
int list_length(struct list* l) {

    // check if L is the NULL pointer
    if (!l) {
        return 0;
    }
    struct node *last = l->head; 
    int count = 0;
    while (last != NULL) 
    { 
        last = last->next; 
        count++;
    }
    return count;
}

/* Returns a pointer to the i^th node of list L or NULL if there is no i^th
 * element in list L. */
struct node* list_get_ith(struct list* l, int i) {

    if (!l) {
        return NULL;
    }
    struct node *last = l->head; 
    int count = 0;
    while (count != i) { 
        last = last->next; 
        if (!last) {
            return NULL;
        }
        count++;
    }
    return last;
}

/* Cuts list L into 2 lists, with node N being the last node in the first half
 * and all nodes after nodes N are added to the second half, preserving the
 * same order they were in in the original list.
 * Modifies list L to only contain the first half and creates a new list for
 * the second half. Returns a pointer to the second half if succesfully cut
 * and NULL otherwise. */
struct list* list_cut_after(struct list* l, struct node* n) {

    if (!l || !n || !list_node_present(l, n)) {
        return NULL;
    }
    struct list *second = list_init();
    while (n != NULL) { 
        n = n->next;
        struct node *new = list_new_node(list_node_value(n));
        list_add_back(second, new);
        list_unlink_node(l, n);
    } 
    return second; 
}