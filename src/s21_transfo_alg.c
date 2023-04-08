#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int code = OK;
  if (!s21_is_mem(A)) {
    code = ERROR;
  } else {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  return code;
}

int s21_determinant(matrix_t *A, double *result) {
  int code = OK;
  if (s21_is_mem(A) && result) {
    if (A->rows == A->columns) {
      *result = s21_recursion_det(*A);
    } else {
      code = CALCULATION_ERROR;
    }
  } else {
    code = ERROR;
  }
  return code;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int code = OK;
  if (!s21_is_mem(A)) {
    code = ERROR;
  } else if (A->rows != A->columns) {
    code = CALCULATION_ERROR;
  } else {
    if (s21_create_matrix(A->rows, A->columns, result) == OK) {
      matrix_t minor_mtrx = {0};
      int row = A->rows;
      if (A->rows == 1) {
        result->matrix[0][0] = A->matrix[0][0];
        row--;
      }
      for (int i = 0; i < row; i++) {
        for (int j = 0; j < result->columns; j++) {
          s21_new_minor(*A, i, j, &minor_mtrx);
          double det = 0.0;
          s21_determinant(&minor_mtrx, &det);
          result->matrix[i][j] = pow(-1, i + j) * det;
          s21_remove_matrix(&minor_mtrx);
        }
      }
    } else {
      code = ERROR;
    }
  }
  return code;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int code = OK;
  if (!s21_is_mem(A)) {
    code = ERROR;
  } else if (A->rows != A->columns) {
    code = CALCULATION_ERROR;
  } else {
    double det = 0;
    s21_determinant(A, &det);
    if (det == 0.0) {
      code = CALCULATION_ERROR;
    } else {
      s21_calc_complements(A, result);
      matrix_t tmp = {0};

      s21_transpose(result, &tmp);
      s21_remove_matrix(result);

      s21_mult_number(&tmp, tmp.rows == 1 ? pow(det, -2) : 1.0 / det, result);

      s21_remove_matrix(&tmp);
    }
  }
  return code;
}
