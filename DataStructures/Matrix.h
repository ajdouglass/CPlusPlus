#ifndef MATRIX_H
#define MATRIX_H

#include <stdexcept>
#include <ostream>

template <class T>
class Matrix {
public:
  Matrix();
  Matrix(int rowSize, int colSize);
  ~Matrix();
  Matrix(const Matrix<T>& mat);
  Matrix<T>& operator=(const Matrix<T>& mat); 

  T* operator[](int row) const;
  T* operator[](int row);
  int rows() const;
  int columns() const;
  T& at(int row, int col) const;
  T& at(int row, int col);

  bool contains(T item) const;
  void resize(int rowSize, int colSize);
  void clear();
private:
  int numRows, numCols;
  T** elems;

  void deleteMatrix();
};

template <class T>
Matrix<T>::Matrix() {
  numRows = 0;
  numCols = 0;
  elems = NULL;
}

template <class T>
Matrix<T>::Matrix(int rowSize, int colSize) {
  if(rowSize < 0 || colSize < 0) {
    throw std::range_error("Arguments must be positive");
  }
  numRows = rowSize;
  numCols = colSize;
  elems = new T*[numRows];
  for(int i = 0; i < numRows; i++) {
    elems[i] = new T[numCols];
  }
  for(int row = 0; row < numRows; row++) {
    for(int col = 0; col < numCols; col++) {
      elems[row][col] = T(); 
    }
  }
}

template <class T>
Matrix<T>::~Matrix() {
  deleteMatrix();
}

template <class T>
Matrix<T>::Matrix(const Matrix<T>& mat) {
  numRows = mat.numRows;
  numCols = mat.numCols; 
  elems = new T*[numRows];
  for(int i = 0; i < numRows; i++) {
    elems[i] = new T[numCols];
  }
  for(int row = 0; row < numRows; row++) {
    for(int col = 0; col < numCols; col++) {
      elems[row][col] = mat.elems[row][col];
    }
  }
}

template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& mat) {
  if(this == &mat) {
    return *this;
  }
  if(numRows == mat.numRows && numCols == mat.numCols) {
    for(int row = 0; row < numRows; row++) {
      for(int col = 0; col < numCols; col++) {
        elems[row][col] = mat.elems[row][col];
      }
    }
    return *this;
  }
  deleteMatrix(); 
  numRows = mat.numRows;
  numCols = mat.numCols; 
  elems = new T*[numRows];
  for(int i = 0; i < numRows; i++) {
    elems[i] = new T[numRows];
  }
  for(int row = 0; row < numRows; row++) {
    for(int col = 0; col < numCols; col++) {
      elems[row][col] = mat.elems[row][col];
    }
  }
  return *this;
}

template <class T>
T* Matrix<T>::operator[](int row) const {
  return elems[row];
}

template <class T>
T* Matrix<T>::operator[](int row) {
  return elems[row];
}

template <class T>
int Matrix<T>::rows() const {
  return numRows;
}

template <class T>
int Matrix<T>::columns() const {
  return numCols;
}

template <class T>
T& Matrix<T>::at(int row, int col) const {
  if(row < 0 || row >= numRows) {
    throw std::range_error("Row index out of range");
  }
  if(col < 0 || col >= numCols) {
    throw std::range_error("Col index out of range");
  }
  return elems[row][col];
}

template <class T>
T& Matrix<T>::at(int row, int col) {
  if(row < 0 || row >= numRows) {
    throw std::range_error("Row index out of range");
  }
  if(col < 0 || col >= numCols) {
    throw std::range_error("Column index out of range");
  }
  return elems[row][col];
}

template <class T>
bool Matrix<T>::contains(T item) const {
  for(int row = 0; row < numRows; row++) {
    for(int col = 0; col < numCols; col++) {
      if(elems[row][col] == item) {
        return true;
      }
    }
  }
  return false;
}

template <class T>
void Matrix<T>::resize(int rowSize, int colSize) {
  if(rowSize < 0 || colSize < 0) {
    throw std::range_error("Arguments must be positive");
  }
  T** newMat = new T*[rowSize];
  for(int i = 0; i < rowSize; i++) {
    newMat[i] = new T[colSize];
  }
  for(int row = 0; row < rowSize; row++) {
    for(int col = 0; col < colSize; col++) {
      if(row >= numRows || col >= numCols)  {
        newMat[row][col] = T();
      }
      else {
        newMat[row][col] = elems[row][col];
      }
    }
  }
  deleteMatrix();
  elems = newMat;
  numRows = rowSize;
  numCols = colSize;
}

template <class T>
void Matrix<T>::clear() {
  for(int row = 0; row < numRows; row++) {
    for(int col = 0; col < numCols; col++) {
      elems[row][col] = T();
    }
  }
}

template <class T>
bool operator==(const Matrix<T>& m1, const Matrix<T>& m2) {
  if((m1.rows() != m2.rows()) || (m1.columns() != m2.columns())) {
    return false;
  }
  for(int row = 0; row < m1.rows(); row++) {
    for(int col = 0; col < m2.columns(); col++) {
      if(m1[row][col] != m2[row][col]) {
        return false;
      }
    }
  }
  return true;
}

template <class T>
void Matrix<T>::deleteMatrix() {
  for(int i = 0; i < numRows; i++) {
    delete[] elems[i];
  }
  delete[] elems;
}

template <class T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& mat) {
  out << '[';
  for(int row = 0; row < mat.rows(); row++) {
    out << '[';
    for(int col = 0; col < mat.columns(); col++) {
      out << mat[row][col];
      if(col != mat.columns()-1) {
        out << ", "; 
      }
    }
    if(row == mat.rows()-1) {
      out << "]]";
    }
    else {
      out << "]\n ";
    }
  }
  return out << ']';
}

#endif
