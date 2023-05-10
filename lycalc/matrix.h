#ifndef MATRIX_H
#define MATRIX_H

typedef struct matrix_s {
    int name;
    int col;
    int row;
    int matrix[9][9];
} matrix_t;

matrix_t *make_matrix(int name);
void free_matrix(matrix_t *);

void matrix_print( matrix_t *);

void matrix_insert( matrix_t *, int row, int col, int value);

#endif