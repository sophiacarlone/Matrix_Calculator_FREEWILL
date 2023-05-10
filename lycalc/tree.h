#ifndef TREE_H
#define TREE_H
#include "matrix.h"

typedef struct tree_s {
    int type;	/* token types: ADDOP, MULOP, NUM */
	int attribute;
    int value;
    matrix_t *matrix;
    struct tree_s *left;
    struct tree_s *right;
} tree_t;

tree_t *make_tree (int value, matrix_t *m,tree_t *l, tree_t *r);
void print_tree (tree_t *t);

#endif