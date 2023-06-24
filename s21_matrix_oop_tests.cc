#include "gtest/gtest.h"
#include "s21_matrix_oop.h"

//------------------------------EQUAl------------------------------

TEST(EqTest, eq_test_1) {
  S21Matrix A(2, 3), B(2, 3);
  A(0, 0) = 0.25;
  A(0, 1) = 1.25;
  A(0, 2) = 2.25;
  A(1, 0) = 3.25;
  A(1, 1) = 4.25;
  A(1, 2) = 5.25;

  B(0, 0) = 0.25;
  B(0, 1) = 1.25;
  B(0, 2) = 2.25;
  B(1, 0) = 3.25;
  B(1, 1) = 4.25;
  B(1, 2) = 5.25;

  ASSERT_TRUE(A.EqMatrix(B) == true);
}

TEST(EqTest, eq_test_2) {
  S21Matrix A(1, 1), B(1, 1);
  A(0, 0) = 5;
  B(0, 0) = 8.8;

  ASSERT_TRUE(A.EqMatrix(B) == false);
}

TEST(EqTest, eq_test_diff_size) {
  S21Matrix A(2, 3), B(3, 3);
  A(0, 0) = 0.25;
  A(0, 1) = 1.25;
  A(0, 2) = 2.25;
  A(1, 0) = 3.25;
  A(1, 1) = 4.25;
  A(1, 2) = 5.25;

  B(0, 0) = 0.25;
  B(0, 1) = 1.25;
  B(0, 2) = 2.25;
  B(1, 0) = 3.25;
  B(1, 1) = 4.25;
  B(1, 2) = 5.25;
  B(2, 0) = 6.25;
  B(2, 1) = 7.25;
  B(2, 2) = 8.25;

  ASSERT_TRUE(A.EqMatrix(B) == false);
}

//------------------------------SUM------------------------------

TEST(SumTest, sum_test_1) {
  S21Matrix A(1, 1), B(1, 1), R(1, 1), R2(1, 1);
  A(0, 0) = 1.25;
  B(0, 0) = 2.25;
  R(0, 0) = 3.5;

  ASSERT_TRUE(A + B == R);
}

TEST(SumTest, sum_test_2) {
  S21Matrix A(3, 3), B(3, 3), R(3, 3);
  A(0, 0) = 0.25;
  A(0, 1) = 1.25;
  A(0, 2) = 2.25;
  A(1, 0) = 3.25;
  A(1, 1) = 4.25;
  A(1, 2) = 5.25;
  A(2, 0) = 6.25;
  A(2, 1) = 7.25;
  A(2, 2) = 8.25;

  B(0, 0) = 9.65;
  B(0, 1) = 8.65;
  B(0, 2) = 7.65;
  B(1, 0) = 6.65;
  B(1, 1) = 5.65;
  B(1, 2) = 4.65;
  B(2, 0) = 3.65;
  B(2, 1) = 2.65;
  B(2, 2) = 1.65;

  R(0, 0) = 9.9;
  R(0, 1) = 9.9;
  R(0, 2) = 9.9;
  R(1, 0) = 9.9;
  R(1, 1) = 9.9;
  R(1, 2) = 9.9;
  R(2, 0) = 9.9;
  R(2, 1) = 9.9;
  R(2, 2) = 9.9;
  A.SumMatrix(B);

  ASSERT_TRUE(A == R);
}

TEST(SumMatrix, sum_test_incorrect_matrix) {
  S21Matrix A(1, 1), B(2, 1);
  A(0, 0) = 1.25;
  B(0, 0) = 2.25;

  ASSERT_THROW(A.SumMatrix(B), std::exception);
}

//------------------------------SUB------------------------------
TEST(SubMatrix, sub_test_1) {
  S21Matrix A(1, 1), B(1, 1), R(1, 1), R2(1, 1);
  A(0, 0) = 1.25;
  B(0, 0) = 2.25;
  R(0, 0) = -1;

  R2 = A - B;
  ASSERT_TRUE(R2 == R);
}

TEST(SubMatrix, sub_test_2) {
  S21Matrix A(3, 3), B(3, 3), R(3, 3);
  A(0, 0) = 0.25;
  A(0, 1) = 1.25;
  A(0, 2) = 2.25;
  A(1, 0) = 3.25;
  A(1, 1) = 4.25;
  A(1, 2) = 5.25;
  A(2, 0) = 6.25;
  A(2, 1) = 7.25;
  A(2, 2) = 8.25;

  B(0, 0) = 9.25;
  B(0, 1) = 8.25;
  B(0, 2) = 7.25;
  B(1, 0) = 6.25;
  B(1, 1) = 5.25;
  B(1, 2) = 4.25;
  B(2, 0) = 3.25;
  B(2, 1) = 2.25;
  B(2, 2) = 1.25;

  R(0, 0) = -9.0;
  R(0, 1) = -7.0;
  R(0, 2) = -5.0;
  R(1, 0) = -3.0;
  R(1, 1) = -1.0;
  R(1, 2) = 1.0;
  R(2, 0) = 3.0;
  R(2, 1) = 5.0;
  R(2, 2) = 7.0;
  A.SubMatrix(B);

  ASSERT_TRUE(A == R);
}

TEST(SubMatrix, sub_test_incorrect_matrix) {
  S21Matrix A(1, 1), B(2, 1);
  A(0, 0) = 1.25;
  B(0, 0) = 2.25;

  ASSERT_THROW(A.SubMatrix(B), std::exception);
}

//----------------------------MULT NUM----------------------------
TEST(MultNum, mult_num_test_1) {
  S21Matrix A(1, 1), B(1, 1), R(1, 1);
  A(0, 0) = 1.25;
  B(0, 0) = -5;
  R = A * (-4);

  ASSERT_TRUE(R == B);
}

TEST(MultNum, mult_num_test_2) {
  S21Matrix A(3, 3), B(3, 3);
  A(0, 0) = 0.25;
  A(0, 1) = 1.25;
  A(0, 2) = 2.25;
  A(1, 0) = 3.25;
  A(1, 1) = 4.25;
  A(1, 2) = 5.25;
  A(2, 0) = 6.25;
  A(2, 1) = 7.25;
  A(2, 2) = 8.25;

  B(0, 0) = 1;
  B(0, 1) = 5;
  B(0, 2) = 9;
  B(1, 0) = 13;
  B(1, 1) = 17;
  B(1, 2) = 21;
  B(2, 0) = 25;
  B(2, 1) = 29;
  B(2, 2) = 33;

  A.MulNumber(4);

  ASSERT_TRUE(A == B);
}

//-----------------------------DETERMINANT-----------------------------
TEST(Det, determinant_test_1) {
  S21Matrix A(1, 1);
  double B, R = 1.25;
  A(0, 0) = 1.25;
  B = A.Determinant();
  ASSERT_TRUE(B == R);
}

TEST(Det, determinant_test_2) {
  S21Matrix A(3, 3);
  double B, R = -69;
  A(0, 0) = 0.25;
  A(0, 1) = 1.25;
  A(0, 2) = 2.25;
  A(1, 0) = 3.25;
  A(1, 1) = 10;
  A(1, 2) = 5.25;
  A(2, 0) = 6.25;
  A(2, 1) = 7.25;
  A(2, 2) = 8.25;

  B = A.Determinant();
  ASSERT_TRUE(B == R);
}

TEST(Det, determinant_test_not_square) {
  S21Matrix A(4, 5);

  A(0, 0) = 1.25;
  ASSERT_THROW(A.Determinant();, std::exception);
}

//----------------------------COMPLEMENTS---------------------------
TEST(CalcComplements, complement_test_1) {
  S21Matrix A(3, 3), B(3, 3), R(3, 3);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 0;
  A(1, 1) = 4;
  A(1, 2) = 2;
  A(2, 0) = 5;
  A(2, 1) = 2;
  A(2, 2) = 1;

  B(0, 0) = 0;
  B(0, 1) = 10;
  B(0, 2) = -20;
  B(1, 0) = 4;
  B(1, 1) = -14;
  B(1, 2) = 8;
  B(2, 0) = -8;
  B(2, 1) = -2;
  B(2, 2) = 4;

  R = A.CalcComplements();

  ASSERT_TRUE(R == B);
}

TEST(CalcComplements, complement_test_1_1) {
  S21Matrix A(1, 1), B(1, 1), R(1, 1);
  A(0, 0) = 1.25;
  B(0, 0) = 1;
  R = A.CalcComplements();
  ASSERT_TRUE(R == B);
}

TEST(CalcComplements, complement_test_2) {
  S21Matrix A(3, 3), B(3, 3), R(3, 3);
  A(0, 0) = 5;
  A(0, 1) = -1;
  A(0, 2) = 1;
  A(1, 0) = 2;
  A(1, 1) = 3;
  A(1, 2) = 4;
  A(2, 0) = 1;
  A(2, 1) = 0;
  A(2, 2) = 3;

  B(0, 0) = 9;
  B(0, 1) = -2;
  B(0, 2) = -3;
  B(1, 0) = 3;
  B(1, 1) = 14;
  B(1, 2) = -1;
  B(2, 0) = -7;
  B(2, 1) = -18;
  B(2, 2) = 17;

  R = A.CalcComplements();

  ASSERT_TRUE(R == B);
}

TEST(CalcComplements, complement_test_not_square) {
  S21Matrix A(2, 3);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 0;
  A(1, 1) = 4;
  A(1, 2) = 2;

  ASSERT_THROW(A.CalcComplements(), std::exception);
}

//----------------------------TRANSPOSE---------------------------

TEST(Transpose, transpose_test_1) {
  S21Matrix A(1, 1), B(1, 1), R(1, 1);
  A(0, 0) = 1.25;
  B(0, 0) = 1.25;
  R = A.Transpose();
  ASSERT_TRUE(R == B);
}

//----------------------------INVERSE---------------------------
TEST(Inverse, inverse_test_1) {
  S21Matrix A(3, 3), B(3, 3), R(3, 3);
  A(0, 0) = 2;
  A(0, 1) = 5;
  A(0, 2) = 7;
  A(1, 0) = 6;
  A(1, 1) = 3;
  A(1, 2) = 4;
  A(2, 0) = 5;
  A(2, 1) = -2;
  A(2, 2) = -3;

  B(0, 0) = 1;
  B(0, 1) = -1;
  B(0, 2) = 1;
  B(1, 0) = -38;
  B(1, 1) = 41;
  B(1, 2) = -34;
  B(2, 0) = 27;
  B(2, 1) = -29;
  B(2, 2) = 24;

  R = A.InverseMatrix();

  ASSERT_TRUE(R == B);
}

TEST(Inverse, inverse_test_not_square) {
  S21Matrix A(1, 1), R(1, 1), B(1, 1);
  A(0, 0) = 1;
  B(0, 0) = 1;
  R = A.InverseMatrix();

  ASSERT_TRUE(R == B);
}

//----------------------------MULT MATRIX---------------------------
TEST(MultMatrix, mult_matrix_different_matrix) {
  S21Matrix A(1, 1), B(2, 2);
  A(0, 0) = 1;
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 3;
  B(1, 1) = 4;
  ASSERT_THROW(A.MulMatrix(B), std::exception);
}

TEST(MultMatrix, mult_matrix_test_1) {
  S21Matrix A(1, 1), B(1, 1), R(1, 1), R2(1, 1);
  A(0, 0) = -1;
  B(0, 0) = 2;
  R(0, 0) = -2;
  R2 = A * B;

  ASSERT_TRUE(R2 == R);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}