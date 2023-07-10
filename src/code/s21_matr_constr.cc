#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() {
  rows_ = 3;
  cols_ = 3;

  MemCreate();
}

S21Matrix::S21Matrix(int size) {
  if (size < 0) throw std::exception();

  rows_ = size;
  cols_ = size;

  MemCreate();
}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows < 0 || cols < 0) throw std::exception();

  rows_ = rows;
  cols_ = cols;

  MemCreate();
}

S21Matrix::S21Matrix(const S21Matrix& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;

  if (rows_ && cols_) {
    MemCreate();

    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  } else {
    matrix_ = nullptr;
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(0), cols_(0), matrix_(nullptr) {
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  std::swap(matrix_, other.matrix_);
}

S21Matrix::~S21Matrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) delete[] matrix_[i];
    delete[] matrix_;
    matrix_ = nullptr;
  }

  rows_ = 0;
  cols_ = 0;
}
