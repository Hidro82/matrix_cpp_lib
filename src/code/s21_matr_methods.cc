#include "s21_matrix_oop.h"

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  if (SizeCompare(other)) {
    if (rows_ && cols_) {
      for (int i = 0; i < rows_; i++)
        for (int j = 0; j < cols_; j++)
          if (std::fabs(matrix_[i][j] - other.matrix_[i][j]) > EPS)
            return false;
    }
  } else
    return false;
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (!SizeCompare(other))
    throw std::invalid_argument("matrixes not compatible");

  if (rows_ && cols_) {
    for (int i = 0; i < rows_; i++)
      for (int j = 0; j < cols_; j++) matrix_[i][j] += other.matrix_[i][j];
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (!SizeCompare(other))
    throw std::invalid_argument("matrixes not compatible");

  if (rows_ && cols_) {
    for (int i = 0; i < rows_; i++)
      for (int j = 0; j < cols_; j++) matrix_[i][j] -= other.matrix_[i][j];
  }
}

void S21Matrix::MulNumber(const double num) {
  if (rows_ && cols_) {
    for (int i = 0; i < rows_; i++)
      for (int j = 0; j < cols_; j++) matrix_[i][j] *= num;
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (!MulSizeCompare(other))
    throw std::invalid_argument("matrixes not compatible");
  if (rows_ && cols_) {
    S21Matrix result(rows_, other.cols_);
    double buffer = 0.0;

    for (int i = 0; i < rows_; i++)
      for (int j = 0; j < other.cols_; j++) {
        buffer = 0.0;
        for (int k = 0; k < other.rows_; k++)
          buffer += (matrix_[i][k] * other.matrix_[k][j]);
        result.matrix_[i][j] = buffer;
      }

    *this = result;
  }
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix trans(cols_, rows_);
  if (rows_ && cols_) {  // This is made to check for zero matrix
    for (int i = 0; i < cols_; i++)
      for (int j = 0; j < rows_; j++) trans.matrix_[i][j] = matrix_[j][i];
  }
  return trans;
}

S21Matrix S21Matrix::CalcComplements() {
  if (!SquareCheck()) throw std::invalid_argument("not square matrix");
  if (!rows_ || !cols_) throw std::invalid_argument("zero matrix");
  int coor_1 = 0;
  int coor_2 = 0;
  double det = 0;
  S21Matrix comp(rows_);

  if (rows_ == 1) {
    comp = *this;
  } else if (rows_ && cols_) {
    S21Matrix minor(rows_ - 1);
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        for (int l = 1; l < rows_; l++) {
          for (int k = 1; k < cols_; k++) {
            coor_1 = i + l;
            coor_2 = j + k;
            if (coor_2 >= rows_) coor_2 -= rows_;
            if (coor_1 >= cols_) coor_1 -= cols_;
            minor.matrix_[l - 1][k - 1] = matrix_[coor_1][coor_2];
          }
        }
        det = minor.Determinant();
        if (((rows_ % 2) == 0) && ((i + j) % 2) != 0) {
          comp.matrix_[i][j] = -det;
        } else {
          comp.matrix_[i][j] = det;
        }
      }
    }
  }
  return comp;
}

double S21Matrix::Determinant() {
  /* I know perfectly, that this algorithm is slow,
  but hey! My work is to make a correct algorithm, not
  the best working one */
  if (SquareCheck() == false) throw std::invalid_argument("not square matrix");
  if (!rows_ || !cols_) throw std::invalid_argument("zero matrix");

  double det = 0;

  if (rows_ == 1) {
    det = matrix_[0][0];
  } else if (rows_ == 2) {
    det = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else if (rows_ == 3) {
    det = matrix_[0][0] * matrix_[1][1] * matrix_[2][2] +
          matrix_[0][1] * matrix_[1][2] * matrix_[2][0] +
          matrix_[0][2] * matrix_[1][0] * matrix_[2][1] -
          matrix_[0][2] * matrix_[1][1] * matrix_[2][0] -
          matrix_[0][1] * matrix_[1][0] * matrix_[2][2] -
          matrix_[0][0] * matrix_[1][2] * matrix_[2][1];
  } else {
    S21Matrix comp = CalcComplements();
    for (int i = 0; i < rows_; i++) {
      det += matrix_[0][i] * comp.matrix_[0][i];
    }
  }
  return det;
}

S21Matrix S21Matrix::InverseMatrix() {
  if ((!SquareCheck()) || (std::fabs(Determinant()) < EPS))
    throw std::invalid_argument("not correct matrix");
  if (!rows_ || !cols_) throw std::invalid_argument("zero matrix");

  double det = Determinant();
  S21Matrix minors = CalcComplements();
  S21Matrix trans_minors = minors.Transpose();

  trans_minors.MulNumber(1 / det);
  return trans_minors;
}
