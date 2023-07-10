#include "s21_matrix_oop.h"

void S21Matrix::MemCreate() {
  if (rows_ && cols_) {
    matrix_ = new double*[rows_];
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new double[cols_]{0.0};
      if (!(*matrix_)) throw std::out_of_range("not enough memory");
    }
  } else {
    matrix_ = nullptr;
  }
}

bool S21Matrix::SizeCompare(const S21Matrix& other) {
  if ((cols_ == other.cols_) && (rows_ == other.rows_)) return true;
  return false;
}

bool S21Matrix::MulSizeCompare(const S21Matrix& other) {
  if (cols_ == other.rows_) return true;
  return false;
}

bool S21Matrix::SquareCheck() {
  if (cols_ == rows_) return true;
  return false;
}

void S21Matrix::Printer() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) std::cout << "\t" << matrix_[i][j];
    std::cout << std::endl;
  }
}

void S21Matrix::NumCreate() {
  double bs = 1.0;

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = bs;
      bs += 1.0;
    }
  }
}

void S21Matrix::NumFill(double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = num;
    }
  }
}

void S21Matrix::SetNum(int i, int j, double num) {
  if ((i < 0) || (j < 0) || (i >= rows_) || (j >= cols_))
    throw std::exception();

  matrix_[i][j] = num;
}

void S21Matrix::SetRows(int new_rows) {
  if ((new_rows < 0) && std::abs(new_rows) > rows_)
    throw std::out_of_range("trying to shrink matrix beyond limit");
  if (new_rows != rows_) {
    S21Matrix copycat(rows_ + new_rows, cols_);
    for (int i = 0; i < copycat.rows_; i++)
      for (int j = 0; j < copycat.cols_; j++) {
        if (i < rows_)
          copycat.matrix_[i][j] = matrix_[i][j];
        else
          copycat.matrix_[i][j] = 0.0;
      }
    *this = std::move(copycat);
  }
}

void S21Matrix::SetCols(int new_cols) {
  if ((new_cols < 0) && std::abs(new_cols) > cols_)
    throw std::out_of_range("trying to shrink matrix beyond limit");
  if (new_cols != cols_) {
    S21Matrix copycat(rows_, cols_ + new_cols);
    for (int i = 0; i < copycat.rows_; i++)
      for (int j = 0; j < copycat.cols_; j++) {
        if (j < cols_)
          copycat.matrix_[i][j] = matrix_[i][j];
        else
          copycat.matrix_[i][j] = 0.0;
      }
    *this = std::move(copycat);
  }
}

void S21Matrix::SetSize(int new_rows, int new_cols) {
  SetRows(new_rows);
  SetCols(new_cols);
}

double S21Matrix::GetNum(int i, int j) {
  if ((i < 0) || (j < 0) || (i >= rows_) || (j >= cols_))
    throw std::out_of_range("element beyond reach");

  return matrix_[i][j];
}

int S21Matrix::GetRows() { return rows_; }

int S21Matrix::GetCols() { return cols_; }