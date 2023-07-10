#include "s21_matrix_oop.h"

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (EqMatrix(other)) return *this;
  S21Matrix buffer(other.rows_, other.cols_);

  if (buffer.rows_ && buffer.cols_) {
    for (int i = 0; i < buffer.rows_; i++)
      for (int j = 0; j < buffer.cols_; j++)
        buffer.matrix_[i][j] = other.matrix_[i][j];
  } else {
    buffer.matrix_ = nullptr;
  }

  *this = std::move(buffer);

  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) noexcept {
  if (EqMatrix(other)) return *this;

  for (int i = 0; i < rows_; i++) delete[] matrix_[i];
  delete[] matrix_;
  matrix_ = nullptr;
  rows_ = 0;
  cols_ = 0;

  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  std::swap(matrix_, other.matrix_);

  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix buffer(*this);
  buffer.SumMatrix(other);

  return buffer;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix buffer(*this);
  buffer.SubMatrix(other);

  return buffer;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix buffer(*this);

  buffer.MulMatrix(other);

  return buffer;
}

S21Matrix operator*(S21Matrix& matrix, double number) {
  S21Matrix filler = matrix;

  filler.MulNumber(number);

  return filler;
}

S21Matrix operator*(double number, S21Matrix& matrix) {
  S21Matrix filler = matrix;

  filler.MulNumber(number);

  return filler;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);

  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);

  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);

  return *this;
}

S21Matrix& S21Matrix::operator*=(double number) {
  MulNumber(number);

  return *this;
}

bool S21Matrix::operator==(const S21Matrix& other) { return EqMatrix(other); }

double& S21Matrix::operator()(int i, int j) const {
  if ((i < 0) || (j < 0) || (i >= rows_) || (j >= cols_))
    throw std::out_of_range("element beyond reach");
  if (!matrix_) throw std::exception();
  return matrix_[i][j];
}