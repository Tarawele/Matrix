#ifndef S21_HEADER_MATRIX_H
#define S21_HEADER_MATRIX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_DOUBLE 1.79769e+308
#define MIN_DOUBLE 2.22507e-308
#define SUCCESS 1
#define FAILURE 0
#define E 1e-7
#define OK 0    // OK
#define ERROR 1 //   Error, incorrect matrix
/*  Calculation error (mismatched matrix sizes; matrix for
    which calculations cannot be performed,..*/
#define CALCULATION_ERROR 2

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;

} matrix_t;

// basics matrix
int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);

// arithmetics operations of matrix
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// transformations and algebrics of matrix
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);

// helpers
int s21_is_mem(matrix_t *A);
int s21_is_size(matrix_t *A, matrix_t *B);
int s21_add_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result, char sign);
void s21_new_minor(matrix_t A, int row, int column, matrix_t *result);
double s21_recursion_det(matrix_t A);

#endif // S21_HEADER_MATRIX_H