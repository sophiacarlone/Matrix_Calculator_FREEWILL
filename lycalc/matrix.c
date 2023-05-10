#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "matrix.h"

matrix_t *make_matrix(int name){
    matrix_t *m = (matrix_t *)malloc(sizeof(matrix_t));
    assert(m != NULL);
    m->name = name;
    m->row = 9;
    m->col = 9;
    int i,j;
    for (i = 0; i < 9; i++){
        for (j = 0; j < 9; j++)
            m->matrix[i][j] = -1;
    }
    return m;
}

void free_matrix(matrix_t *m){
    free(m->matrix);
    free(m);
}

void set_row(matrix_t *m, int rows){
    m->row = rows;
}

void set_col(matrix_t *m, int cols){
    m->col = cols;
}

void matrix_print( matrix_t *m){
    int i,j;
    for (i = 0; i < m->row; i++){
        fprintf(stderr,"[");
        for (j = 0; j < m->col; j++){
            fprintf(stderr,"%d,",m->matrix[i][j]);
        }
        fprintf(stderr,"]\n");
    }
}

void matrix_insert( matrix_t *m, int row, int col, int value){
    assert(row < m->row && col < m->col);
    m->matrix[row][col] = value;
}