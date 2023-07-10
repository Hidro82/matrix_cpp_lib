#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <cmath>
#include <iostream>

const double EPS = 1e-7;

class S21Matrix {
 public:
  S21Matrix();
  S21Matrix(int size);
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;

  ~S21Matrix();

  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other) noexcept;

  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  friend S21Matrix operator*(S21Matrix& matrix, double number);
  friend S21Matrix operator*(double number, S21Matrix& matrix);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(double number);
  bool operator==(const S21Matrix& other);
  double& operator()(int i, int j) const;

  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  bool SizeCompare(const S21Matrix& other);
  bool MulSizeCompare(const S21Matrix& other);
  bool SquareCheck();
  void Printer();
  void NumCreate();
  void NumFill(double num);
  void SetNum(int i, int j, double num);
  void SetRows(int new_rows);
  void SetCols(int new_cols);
  void SetSize(int new_rows, int new_cols);
  double GetNum(int i, int j);
  int GetRows();
  int GetCols();

 private:
  int rows_, cols_;
  double** matrix_;
  void MemCreate();  // MemCreate is needed to be private because of memory work
};

/* This link is made to make possible the multiplication of number and
matrix in both orders. The methology is written in materials */

S21Matrix operator*(S21Matrix& matrix, double number);
S21Matrix operator*(double number, S21Matrix& matrix);

#endif  // SRC_S21_MATRIX_OOP_H_
