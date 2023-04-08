#include "s21_matrix.h"
/*checks whether memory has been allocated for each of the arrays in the
  matrix return 1 - OK, 0 - ERROR*/
int s21_is_mem(matrix_t *A) {
  return A && A->matrix != NULL && (A->columns > 0 && A->rows > 0);
}

int s21_is_size(matrix_t *A, matrix_t *B) {
  int size = ERROR;
  if ((A->rows == B->rows) && (A->columns == B->columns)) {
    size = OK;
  }
  return size;
}

int s21_add_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result, char sign) {
  int code = 0;
  if (!s21_is_mem(A) || !s21_is_mem(B)) {
    code = ERROR;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    code = CALCULATION_ERROR;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (sign == '+') {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
        if (sign == '-') {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    }
  }
  return code;
}
// Removes row and column from matrix A and writes to result
void s21_new_minor(matrix_t A, int row, int column, matrix_t *result) {
  int true_i = 0;
  int true_j = 0;
  if (!s21_create_matrix(A.rows - 1, A.columns - 1, result)) {
    for (int i = 0; i < A.rows; i++) {
      true_j = 0;
      if (i == row) {
        continue;
      }
      for (int j = 0; j < A.columns; j++) {
        if (j == column) {
          continue;
        }
        result->matrix[true_i][true_j] = A.matrix[i][j];
        true_j++;
      }
      true_i++;
    }
  }
}

double s21_recursion_det(matrix_t A) {
  matrix_t tmp = {0};
  double res = 0;
  if (A.rows == 1) {
    res = A.matrix[0][0];
  } else if (A.rows == 2) {
    res = (A.matrix[0][0] * A.matrix[1][1]) - (A.matrix[0][1] * A.matrix[1][0]);
  } else if (A.rows >= 3) {
    int sign = 1;
    for (int i = 0; i < A.rows; i++) {
      s21_new_minor(A, i, 0, &tmp);
      res += sign * A.matrix[i][0] * s21_recursion_det(tmp);
      sign *= -1;
      s21_remove_matrix(&tmp);
    }
  }
  return res;
}
