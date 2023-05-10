#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "matrix.h"
#include "y.tab.h"

void aux_print_tree( tree_t *t, int spaces );

tree_t *make_tree (int v, matrix_t *m,tree_t *l, tree_t *r) {
    tree_t *p = (tree_t *) malloc(sizeof(tree_t));
    assert(p != NULL);
    p->value = v;
    p->matrix = m;
    p->left = l;
    p->left = r;
    return p;
}

/* pre-order tree traversal */
void print_tree( tree_t *t )
{
	aux_print_tree( t, 0 ); //for spacing purposes
}

void aux_print_tree( tree_t *t, int spaces )
{
	if ( t == NULL ) return;

	/* indenting for visual effects */
	for (int i=0; i<spaces; i++)
		fprintf( stderr, " " );

	switch( t->type ) {
	case '+':
		fprintf( stderr, "[ADDOP:%c]\n", t->type );
		aux_print_tree( t->left, spaces+4 );
		aux_print_tree( t->right, spaces+4 );
		break;
	case '*':
		fprintf( stderr, "[MULOP:%c]\n", t->type );
		aux_print_tree( t->left, spaces+4 );
		aux_print_tree( t->right, spaces+4 );
		break;
	case '/':
		fprintf( stderr, "[MULOP:%c]\n", t->type );
		aux_print_tree( t->left, spaces+4 );
		aux_print_tree( t->right, spaces+4 );
		break;
	case '-':
		fprintf( stderr, "[ADDOP:%c]\n", t->type );
		aux_print_tree( t->left, spaces+4 );
		aux_print_tree( t->right, spaces+4 );
		break;
	case NUM:
		fprintf( stderr, "[NUM]\n" );
		break;
	case MATRIX:
		matrix_print(t->matrix);
		break;
	default:
		fprintf( stderr, "Error: print_tree, unknown type\n" );
		exit(1);
	}
}