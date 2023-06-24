#ifndef S21MATRIX_H_
#define S21MATRIX_H_

#define S21_EPS 1e-8

#include <utility>

class S21Matrix {
 public:
  S21Matrix(int rows, int cols);
  S21Matrix();
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();

  int GetRows() const;
  int GetCols() const;

  void SetRows(int rows_new);
  void SetCols(int cols_new);

  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);
  bool operator==(const S21Matrix& other) const;
  double& operator()(int row, int col) const;

  friend S21Matrix operator*(const double num, S21Matrix other);
  friend S21Matrix operator*(S21Matrix other, const double num);

 private:
  int rows_, cols_;
  double** matrix_ = nullptr;

  void CopyMatrix(const S21Matrix& other);
  void MinorMatrix(int r, int c, const S21Matrix& other) const;
  void CofactorMatrix();
  void PrintMatrix() const;
  void FreeMatrix();
  void AllocateMemory();
};

#endif  // S21MATRIX_H_