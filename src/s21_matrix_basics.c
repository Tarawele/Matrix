#include "./s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int code = OK, out = 0;
  if (result != NULL && rows > 0 && columns > 0) {
    result->columns = columns;
    result->rows = rows;
    result->matrix = calloc(rows, sizeof(double *));
    if (result->matrix != NULL) {
      for (int i = 0; i < rows && out == 0; i++) {
        result->matrix[i] = calloc(columns, sizeof(double));
        if (result->matrix[i] == NULL) {
          code = ERROR;
          for (int j = i - 1; j <= 0; j--) {
            free(result->matrix[j]);
          }
          free(result->matrix);
          out = 1;
        }
      }
    } else {
      code = ERROR;
    }
  } else {
    if (result != NULL) {
      result->rows = rows;
      result->columns = columns;
      result->matrix = NULL;
    }
    code = ERROR;
  }
  return code;
}

void s21_remove_matrix(matrix_t *A) {
  if (s21_is_mem(A) && A->matrix) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
    A->rows = 0;
    A->columns = 0;
    A->matrix = NULL;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int code = SUCCESS, out = 0;
  if (s21_is_mem(A) && s21_is_mem(B) && s21_is_size(A, B) == 0) {
    for (int i = 0; i < A->rows && out == 0; i++) {
      for (int j = 0; j < A->columns && out == 0; j++) {
        if ((fabs((A->matrix)[i][j] - (B->matrix)[i][j]) > 1e-7)) {
          code = FAILURE;
          out = 1;
        }
      }
    }
  } else {
    code = FAILURE;
  }
  return code;
}
