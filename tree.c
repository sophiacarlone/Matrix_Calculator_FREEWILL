#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "const.h"
#include "tree.h"

#define max(a, b) (((a) > (b)) ? (a) : (b))

FILE *fptr;

void aux_print_tree( tree_t *, int );
void gencode( tree_t *t, int *registers, int start, int r);
void swap_top(int *arr);

/* basic constructor */
tree_t *make_tree( int type, tree_t *l, tree_t *r, int a )
{
	tree_t *p = (tree_t *)malloc( sizeof(tree_t) );
	assert( p != NULL );
	p->type = type;
	p->left = l;
	p->right = r;
	p->attribute = a;
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
	case NUM:
		fprintf( stderr, "[NUM]\n" );
		break;
	default:
		fprintf( stderr, "Error: print_tree, unknown type\n" );
		exit(1);
	}
}

/* evaluate the tree */
int eval_tree( tree_t *t )
{
	if ( t == NULL ){
		return -1;
		fprintf(stderr, "Panic in eval_tree\n");
		exit(1);
	} 

        switch( t->type ) {
        case '+':
                t->evaluation = eval_tree(t->left) + eval_tree(t->right);
		break;
        case '*':
                t->evaluation = eval_tree(t->left) * eval_tree(t->right);
		break;
        case NUM:
                t->evaluation = t->attribute; //how to get the value out of NUM?
		break;
        default:
                fprintf( stderr, "Error: eval_tree, unknown type\n" );
                exit(1);
        }
	return(t->evaluation);
}

/*rank of tree*/
int rank( tree_t *t, int d)
{
	int left, right;

	if( (t->left == NULL) && (t->right == NULL) )
		t->rank = d;	

	else{
	left = rank( t->left, 1);
	right = rank( t->right, 0);

	if(left != right)
		t->rank = max(left, right);
	else
		t->rank = 1 + left;
	}
	
	return t->rank;
}

void gencode_start( tree_t *t ){

 	fptr = fopen("assembly.txt","w");

   	if(fptr == NULL){
      		printf("Error with file");   
      		exit(1);             
   	}	

	t->rank = rank(t, 1);
	int* stack_registers = (int*) malloc(t->rank * sizeof(int));
	//int stack_registers[t->rank];
	int i;
	for( i = 0; i < t->rank; i++)
		stack_registers[i] = i;
	int start = 0;
	gencode( t, stack_registers, start, t->rank);
}

/* generation of the assmbley code */
void gencode( tree_t *t, int *registers, int start, int r){
	int popped = 0;
	int right_rank = 0;
	int left_rank = 0;

	/* case 0 */
	if( (t->left == NULL) && (t->right == NULL) && (t->rank == 1) ){
		fprintf(fptr, "MOV %d, R%d\n", t->attribute, registers[start]);
	}
	else if( (t->left != NULL) || (t->right != NULL)){
		right_rank = rank(t->right, 0);
		left_rank = rank(t->left, 1);
		
		/* case 1 */
		if ( right_rank == 0 ){
			gencode(t->left, registers, start, r);
			if(t->type == '+')
				fprintf(fptr, "ADD %d, R%d\n", t->right->attribute, registers[start]);
			else
				fprintf(fptr, "MUL %d, R%d\n", t->right->attribute, registers[start]);
		}
		/* case 2 */
		else if (( 1 <= left_rank )&&( left_rank < right_rank )
			&& ( left_rank < r )) { //r is the number of registers
			swap_top(registers);
			gencode(t->right, registers, start, r);
			popped = registers[start];
			start++;
			gencode(t->left, registers, start, r);
			if(t->type == '+')
				fprintf(fptr, "ADD R%d, R%d\n", popped, registers[start]); //can also make pop registers[start-1]
			else
				fprintf(fptr, "MUL R%d, R%d\n", popped, registers[start]);
			start--;
			swap_top(registers);
		}

		/* case 3 */
		else if (( 1 <= right_rank ) && ( right_rank <= left_rank )
			&& (right_rank < r)){
			gencode(t->left, registers, start, r);
			//pop
			popped = registers[start];
			start++;
			gencode(t->right, registers, start, r);
			if(t->type == '+')
				fprintf(fptr, "ADD R%d, R%d\n", registers[start], popped);
			else
				fprintf(fptr, "MUL R%d, R%d\n", registers[start], popped);
			//push
			start--;
		}
		else
			fprintf(stderr, "falling through");
		/* not doing case 4 yet? */
	}
}

void swap_top(int *arr){
	int temp = arr[0];
	arr[0] = arr[1];
	arr[1] = temp;
}