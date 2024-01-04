
#ifndef _S21_MATRIX_OOP_H_
#define _S21_MATRIX_OOP_H_

#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>

#define EPS 1e-7

class S21Matrix {
 public:
  // Конструкторы и деструктор
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(std::initializer_list<double> itmpnit);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();

  //  Геттеры и сеттеры
  double GetRows() const;
  void SetRows(int row);
  double GetCols() const;
  void SetCols(int column);

  // Операции
  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant() const;
  S21Matrix InverseMatrix();

  // Перегрузки операторов
  double& operator()(int i, int j);
  double operator()(int i, int j) const;
  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix operator*(const double num) const;
  friend S21Matrix operator*(double num, const S21Matrix& other);
  bool operator==(const S21Matrix& other) const;
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);

  double* matrix_;

 private:
  int rows_, cols_;

  // Вспомогательные приватные методы
  void Clear();
  double SimpleDet() const;
  double Minor(int n, int m) const;
  double Complement(int n, int m) const;
};

#endif  // _S21_MATRIX_OOP_H_