#ifndef LIST_H
#define LIST_H
#include "matrix.h"

/* linked list data structure */
typedef struct list_s {
    int name;     /* identifier name */
    matrix_t *matrix;

    /* additional information 
     * FUNC PROC: sequence of expected types (which includes #arguments)
     */
    struct list_s *next;
} list_t;

/* constructor/destructor */
list_t *make_list( int);
void free_list(list_t *);

// void list_print( list_t *);

/* search/insert */
list_t *list_insert( list_t *, int, matrix_t * );
matrix_t *list_search( list_t *, int );

#endif