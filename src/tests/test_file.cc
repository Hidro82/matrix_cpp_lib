#include <gtest/gtest.h>

#include "../code/s21_matrix_oop.h"

TEST(MatrixTest, Constr) {
  S21Matrix test1;
  S21Matrix test2(3);
  S21Matrix test3(3, 3);

  EXPECT_EQ(true, test1.EqMatrix(test2));
  EXPECT_EQ(true, test2.EqMatrix(test3));
}

TEST(MatrixTest, BasicMath) {
  S21Matrix test1(3);
  S21Matrix test2(3);
  S21Matrix test3(3);
  S21Matrix test4(3);

  test1.NumCreate();
  test2.NumCreate();
  test3.SetNum(0, 0, 2);
  test3.SetNum(0, 1, 4);
  test3.SetNum(0, 2, 6);
  test3.SetNum(1, 0, 8);
  test3.SetNum(1, 1, 10);
  test3.SetNum(1, 2, 12);
  test3.SetNum(2, 0, 14);
  test3.SetNum(2, 1, 16);
  test3.SetNum(2, 2, 18);

  S21Matrix test5 = test1 + test2;
  S21Matrix test6 = test1 - test2;
  test2 += test1;
  test2 -= test1;
  double test_num = test1(0, 0);

  EXPECT_EQ(true, test_num == 1.0);
  EXPECT_EQ(true, test3.EqMatrix(test5));
  EXPECT_EQ(true, test4.EqMatrix(test6));
  EXPECT_EQ(true, test2.EqMatrix(test1));
}

TEST(MatrixTest, Multiplex1) {
  S21Matrix test1(3);
  S21Matrix test2(3);
  S21Matrix test3(3);

  test1.NumCreate();
  test2.NumCreate();
  test3.SetNum(0, 0, 30);
  test3.SetNum(0, 1, 36);
  test3.SetNum(0, 2, 42);
  test3.SetNum(1, 0, 66);
  test3.SetNum(1, 1, 81);
  test3.SetNum(1, 2, 96);
  test3.SetNum(2, 0, 102);
  test3.SetNum(2, 1, 126);
  test3.SetNum(2, 2, 150);

  S21Matrix test4 = test1 * test2;
  test1 *= test2;

  EXPECT_EQ(true, test3.EqMatrix(test4));
  EXPECT_EQ(true, test3.EqMatrix(test1));
}

TEST(MatrixTest, Multiplex2) {
  S21Matrix test1(2, 3);
  S21Matrix test2(3, 2);
  S21Matrix test3(2);

  test1.NumFill(2);
  test2.NumFill(2);
  test3.NumFill(12);

  S21Matrix test4 = test1 * test2;

  EXPECT_EQ(true, test3.EqMatrix(test4));
}

TEST(MatrixTest, Multiplex3) {
  S21Matrix test1(3, 2);
  S21Matrix test2(2, 3);
  S21Matrix test3(3);

  test1.NumFill(2);
  test2.NumFill(2);
  test3.NumFill(8);

  S21Matrix test4 = test1 * test2;

  EXPECT_EQ(true, test3.EqMatrix(test4));
}

TEST(MatrixTest, MultNum) {
  S21Matrix test1(3);
  S21Matrix test2(3);

  test1.NumCreate();
  test2.SetNum(0, 0, 2);
  test2.SetNum(0, 1, 4);
  test2.SetNum(0, 2, 6);
  test2.SetNum(1, 0, 8);
  test2.SetNum(1, 1, 10);
  test2.SetNum(1, 2, 12);
  test2.SetNum(2, 0, 14);
  test2.SetNum(2, 1, 16);
  test2.SetNum(2, 2, 18);

  S21Matrix test3 = 2 * test1;
  S21Matrix test4 = test1 * 2;
  test1 *= 2;

  EXPECT_EQ(true, test2.EqMatrix(test3));
  EXPECT_EQ(true, test2.EqMatrix(test4));
  EXPECT_EQ(true, test2.EqMatrix(test1));
}

TEST(MatrixTest, Trans) {
  S21Matrix test1(3);
  S21Matrix test2(3);

  test1.NumCreate();
  S21Matrix test3 = test1.Transpose();
  test2.SetNum(0, 0, 1);
  test2.SetNum(0, 1, 4);
  test2.SetNum(0, 2, 7);
  test2.SetNum(1, 0, 2);
  test2.SetNum(1, 1, 5);
  test2.SetNum(1, 2, 8);
  test2.SetNum(2, 0, 3);
  test2.SetNum(2, 1, 6);
  test2.SetNum(2, 2, 9);

  EXPECT_EQ(true, test2.EqMatrix(test3));
}

TEST(MatrixTest, Det) {
  S21Matrix test1(6);

  test1.NumCreate();
  double deter = test1.Determinant();

  EXPECT_EQ(true, std::fabs(0.0 - deter) < EPS);
}

TEST(MatrixTest, EqOper) {
  S21Matrix test1(3);
  S21Matrix test2(3);

  test1.NumCreate();
  test2 = test1;

  EXPECT_EQ(true, test2.EqMatrix(test1));
}

TEST(MatrixTest, Inverse) {
  S21Matrix test1(3);
  S21Matrix test2(3);

  test1.NumCreate();
  test1.SetNum(2, 1, 2);
  S21Matrix test3 = test1.InverseMatrix();
  test3.Printer();

  test2.SetNum(0, 0, (-11.0 / 12));
  test2.SetNum(0, 1, (1.0 / 3));
  test2.SetNum(0, 2, (1.0 / 12));
  test2.SetNum(1, 0, (-1.0 / 6));
  test2.SetNum(1, 1, (1.0 / 3));
  test2.SetNum(1, 2, (-1.0 / 6));
  test2.SetNum(2, 0, (3.0 / 4));
  test2.SetNum(2, 1, (-1.0 / 3));
  test2(2, 2) = (1.0 / 12);

  EXPECT_EQ(true, test2.EqMatrix(test3));
}

TEST(MatrixTest, Mutator) {
  S21Matrix test1(3);
  S21Matrix test2(2);
  S21Matrix test6(2);
  S21Matrix test7(3);
  S21Matrix test8(4);
  S21Matrix test9(3);

  test1.NumCreate();
  test1.SetSize(-1, -1);

  test6.NumCreate();
  test6.SetSize(1, 1);

  test7.SetSize(1, 1);

  test2.SetNum(0, 0, 1);
  test2.SetNum(0, 1, 2);
  test2.SetNum(1, 0, 4);
  test2.SetNum(1, 1, 5);
  test2.Printer();

  test9.SetNum(0, 0, 1);
  test9.SetNum(0, 1, 2);
  test9.SetNum(1, 0, 3);
  test9.SetNum(1, 1, 4);

  double test3 = test2.GetNum(0, 0);
  int test4 = test2.GetCols();
  int test5 = test2.GetRows();

  EXPECT_EQ(true, test2.EqMatrix(test1));
  EXPECT_EQ(true, std::fabs(test3 - 1.0) < EPS);
  EXPECT_EQ(true, test4 == test5);
  EXPECT_EQ(true, test9.EqMatrix(test6));
  EXPECT_EQ(true, test7.EqMatrix(test8));
}

TEST(MatrixTest, Paste) {
  S21Matrix test1(3);
  test1.NumCreate();
  S21Matrix test2 = std::move(test1);
  S21Matrix test3;
  test3 = test2;

  EXPECT_EQ(true, test3 == test2);
}

TEST(MatrixTest, CrushTest) {
  S21Matrix test1(2);
  S21Matrix test2 = std::move(test1);
  S21Matrix test3 = test1;
  S21Matrix test4(2);

  EXPECT_EQ(true, test2.EqMatrix(test4));
  EXPECT_EQ(true, test3.EqMatrix(test1));
}

TEST(MatrixTest, Exceptions) {
  EXPECT_THROW(S21Matrix test1(-3), std::exception);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}