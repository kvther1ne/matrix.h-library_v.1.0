#include "s21_matrix_oop.h"

#include <cmath>
#include <iostream>
using namespace std;

//-------------------------ИНИЦИАЛИЗАЦИЯ----------------------------

S21Matrix::S21Matrix(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  this->AllocateMemory();
}

S21Matrix::S21Matrix() : S21Matrix(5, 5){};

S21Matrix::S21Matrix(const S21Matrix& other) { *this = other; }

S21Matrix::S21Matrix(S21Matrix&& other) : matrix_{other.matrix_} {
  rows_ = exchange(other.rows_, 0);
  cols_ = exchange(other.cols_, 0);
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() { FreeMatrix(); }

//---------------------------АКСЕССОРЫ------------------------------

int S21Matrix::GetRows() const { return rows_; }
int S21Matrix::GetCols() const { return cols_; }

void S21Matrix::SetRows(int rows_new) {
  S21Matrix temp_matrix(std::move(*this));
  rows_ = rows_new;
  cols_ = temp_matrix.cols_;
  this->AllocateMemory();
  this->CopyMatrix(temp_matrix);
}

void S21Matrix::SetCols(int cols_new) {
  S21Matrix temp_matrix(std::move(*this));
  rows_ = temp_matrix.rows_;
  cols_ = cols_new;
  this->AllocateMemory();
  this->CopyMatrix(temp_matrix);
}

//------------------------------МЕТОДЫ------------------------------

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  bool result = true;
  if ((cols_ == other.cols_) && (rows_ == other.rows_)) {
    for (int r = 0; r < rows_; r++) {
      for (int c = 0; c < cols_; c++) {
        if (fabs(matrix_[r][c] - other.matrix_[r][c]) > S21_EPS) {
          result = false;
        }
      }
    }
  } else {
    result = false;
  }
  return result;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::length_error(
        "Incorrect input, matrices should have the same size");
  }
  for (int r = 0; r < rows_; r++) {
    for (int c = 0; c < cols_; c++) {
      matrix_[r][c] += other.matrix_[r][c];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::length_error(
        "Incorrect input, matrices should have the same size");
  }
  for (int r = 0; r < rows_; r++) {
    for (int c = 0; c < cols_; c++) {
      matrix_[r][c] -= other.matrix_[r][c];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int r = 0; r < rows_; r++) {
    for (int c = 0; c < cols_; c++) {
      matrix_[r][c] *= num;
    }
  }
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::length_error("Incorrect input, matrix is not square");
  }
  double result = 0.0;
  if (cols_ == 1) {
    result = matrix_[0][0];
  } else if (cols_ == 2) {
    result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else if (cols_ > 2) {
    int degree = 1;
    S21Matrix new_matrix(rows_ - 1, cols_ - 1);
    for (int c = 0; c < cols_; c++) {
      this->MinorMatrix(0, c, new_matrix);
      result += degree * (matrix_[0][c] * new_matrix.Determinant());
      degree *= -1;
    }
  }
  return result;
}

void S21Matrix::MinorMatrix(int r, int c, const S21Matrix& other) const {
  int i_rm = 0, j_rm = 0;
  for (int row = 0; row < rows_; row++) {
    if (row != r) {
      for (int col = 0; col < cols_; col++) {
        if (col != c) {
          other.matrix_[i_rm][j_rm] = matrix_[row][col];
          j_rm++;
        }
      }
      i_rm++;
      j_rm = 0;
    }
  }
}

void S21Matrix::CofactorMatrix() {
  for (int r = 0; r < rows_; r++) {
    for (int c = 0; c < cols_; c++) {
      matrix_[r][c] *= pow(-1, (r + c));
    }
  }
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) {
    throw std::length_error("Incorrect input, matrix is not square");
  }
  S21Matrix result(rows_, cols_);
  if (cols_ == 1) {
    result.matrix_[0][0] = 1;
  } else {
    S21Matrix temp_matrix(rows_ - 1, cols_ - 1);
    for (int r = 0; r < rows_; r++) {
      for (int c = 0; c < cols_; c++) {
        this->MinorMatrix(r, c, temp_matrix);
        result.matrix_[r][c] = temp_matrix.Determinant();
      }
    }
    result.CofactorMatrix();
  }
  return result;
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(rows_, cols_);
  for (int r = 0; r < rows_; r++) {
    for (int c = 0; c < cols_; c++) {
      result.matrix_[c][r] = matrix_[r][c];
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() const {
  double det = this->Determinant();
  S21Matrix result(rows_, cols_);
  if (det == 0) {
    throw std::out_of_range("Determinant is equal to zero");
  }
  if (rows_ == 1) {
    result.matrix_[0][0] = 1 / matrix_[0][0];
  } else {
    S21Matrix temp_matrix_cof(rows_, cols_),
        temp_matrix_cof_trans(rows_, cols_);
    temp_matrix_cof = this->CalcComplements();
    result = temp_matrix_cof.Transpose() * (1 / det);
  }
  return result;
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  S21Matrix result(rows_, other.cols_);
  if (cols_ != other.rows_) {
    throw std::length_error("Incorrect input, matrix is not square");
  }
  for (int r = 0; r < result.rows_; r++) {
    for (int c = 0; c < result.cols_; c++) {
      result.matrix_[c][r] = 0.0;
      for (int k = 0; k < cols_; k++) {
        result.matrix_[r][c] += matrix_[r][k] * other.matrix_[k][c];
      }
    }
  }
  *this = result;
}

void S21Matrix::PrintMatrix() const {
  for (int r = 0; r < 1; r++) {
    for (int c = 0; c < 1; c++) {
      std::cout << matrix_[r][c] << std::endl;
    }
  }
}

void S21Matrix::FreeMatrix() {
  if (matrix_ != nullptr) {
    for (int r = 0; r < rows_; r++) {
      delete[] matrix_[r];
    }
    delete[] matrix_;
  }
  matrix_ = nullptr;
}

void S21Matrix::CopyMatrix(const S21Matrix& other) {
  int rows = 0;
  int columns = 0;
  rows = min(other.rows_, rows_);
  columns = min(other.cols_, cols_);
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < columns; c++) {
      matrix_[r][c] = other.matrix_[r][c];
    }
  }
}

void S21Matrix::AllocateMemory() {
  if (rows_ <= 0 || cols_ <= 0) {
    throw std::out_of_range("Incorrect matrix size");
  }
  matrix_ = new double*[rows_];
  for (int r = 0; r < rows_; r++) {
    matrix_[r] = new double[cols_]();
  }
}

//----------------------------ПЕРЕГРУЗ----------------------------

double& S21Matrix::operator()(int row, int col) const {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix_[row][col];
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix res(*this);
  res.SumMatrix(other);
  return res;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix res(*this);
  res.SubMatrix(other);
  return res;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  this->SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix res(*this);
  res.MulMatrix(other);
  return res;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  this->MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double num) {
  this->MulNumber(num);
  return *this;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this == &other) {
    return *this;
  }
  this->FreeMatrix();
  rows_ = other.rows_;
  cols_ = other.cols_;
  this->AllocateMemory();
  this->CopyMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) {
  if (this == &other) {
    return *this;
  }
  this->FreeMatrix();
  rows_ = exchange(other.rows_, 0);
  cols_ = exchange(other.cols_, 0);
  matrix_ = exchange(other.matrix_, nullptr);
  return *this;
}

bool S21Matrix::operator==(const S21Matrix& other) const {
  return this->EqMatrix(other);
}

S21Matrix operator*(const double num, S21Matrix other) {
  other *= num;
  return other;
}

S21Matrix operator*(S21Matrix other, const double num) {
  other *= num;
  return other;
}