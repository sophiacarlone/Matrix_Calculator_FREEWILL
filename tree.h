#ifndef TREE_H
#define TREE_H

#define max(a, b) (((a) > (b)) ? (a) : (b))


typedef struct tree_s {
	int type;	/* token types: ADDOP, MULOP, NUM */
	int attribute;	/* token attribute, if matrix, row = /10, col = %10 */
	struct tree_s *left;
	struct tree_s *right;
	int evaluation;
	int rank; 
} tree_t;

tree_t *make_tree( int v, tree_t *l, tree_t *r, int a );
void print_tree( tree_t *t );
int eval_tree( tree_t *t );
int rank( tree_t *t, int d );
void gencode_start( tree_t *t );

#endif