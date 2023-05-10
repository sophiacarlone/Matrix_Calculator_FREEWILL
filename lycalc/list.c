#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "list.h"

// typedef struct list_s {
//     char *name;
//     struct list_s *next;
// } list_t;

/* constructor/destructor */
list_t *make_list( int str ) {
    list_t *p = (list_t *)malloc( sizeof(list_t));
    assert(p != NULL);
    p->name = str;  /* safer */
    p->next = NULL;
    p->matrix = NULL;
    return p;
}

void free_list( list_t *p) {
    free_matrix(p->matrix);
    if(p->next != NULL){
        free_list(p->next);
    }
    free( p );
}

// void list_print( list_t *top){
//     list_t *q = top;
//     while ( q != NULL) {
//         printf("[%s] -> ",q->name);
//         q = q->next;
//     }
//     printf("[]\n");
// }

/* insert to top of linked list 
 * returns new top of linked list
 */
list_t *list_insert( list_t *top, int name, matrix_t *m ) {
    list_t *p = make_list(name); // new node to store name

    p->matrix = m;
    if ( top != NULL) { // linked list is empty
        p->next = top;
    }
    return top = p;
}

/* search linked list for str
 * returns pointer to node (where str is) or NULL (otherwise)
 */
matrix_t *list_search( list_t *top, int str ) {
    list_t *q = top;
    while ( q != NULL) {
        if ( q->name == str )
            return q->matrix;
        q = q->next;
    }
    return NULL;
}