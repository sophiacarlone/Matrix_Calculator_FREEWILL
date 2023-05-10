%{
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "matrix.h"
#include "list.h"

int matrix_name_holder = 0;
int row = 0;
int col = 0;
list_t *matrix_ptr;
%}

%union {    /* token attributes */
    int ival;   /* NUM */
    int opval;  /* ADDOP, MULOP */
    int *pval[][];
}

%token <ival> NUM
%token <pval> MATRIX

%left <opval> ADDOP
%left <opval> MULOP

%type <ival> expr


%%

boo: expr { fprintf( stderr, "\nValue = %d\n", $1); }
    ;

expr: expr ADDOP expr
        {
            if( $2 == '+' ) $$ = $1 + $3;
            else $$ = $1 - $3;
        }
    | expr MULOP expr
        {
            if( $2 == '*' ) $$ = $1 * $3;
            else $$ = $1 / $3;
        }
    | '(' expr ')'      { $$ = $2; }
    | NUM               { $$ = $1; }
    | '[' 
        {
            matrix_t *m = make_matrix(matrix_name_holder);
            if(matrix_name_holder == 0) matrix_ptr = make_list(matrix_name_holder++);
            matrix_ptr = list_insert(matrix_ptr,matrix_name_holder,m);
        } 
        rows ']'      
        {
            set_row(list_search(matrix_ptr,matrix_name_holder),row);
            row = 0;
            set_col(list_search(matrix_ptr,matrix_name_holder),col);
            col = 0;
            matrix_name_holder++;
        }
    ;

rows: row {row++;col=0;} ';' rows
    | row {row++;}
    ;

row: NUM {matrix_insert(list_search(matrix_ptr,matrix_name_holder),row,col++,$1);} ',' row
    | NUM {matrix_insert(list_search(matrix_ptr,matrix_name_holder),row,col++,$1);}
    ;

%%

main()
{

    yyparse();
}