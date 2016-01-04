#ifndef MATRIX_H
#define MATRIX_H

#include <stdexcept>
#include <ostream>

template <class T>
class Matrix {
public:
    Matrix(int r, int c);
    ~Matrix();
    Matrix(const Matrix<T>& mat);
    Matrix<T>& operator=(const Matrix<T>& mat); 

    T* operator[](int r) const
        { return matrix[r]; }
    T* operator[](int r)
        { return matrix[r]; }
    int rows() const
        { return ROWS; }
    int columns() const 
        { return COLS; }
    T& at(int r, int c) const;
    T& at(int r, int c);

    bool contains(T item) const;
    void resize(int r, int c);
    void clear();
private:
    int ROWS, COLS;
    T** matrix;

    void deleteMatrix();
};

template <class T>
void Matrix<T>::deleteMatrix() {
    for(int i = 0; i < ROWS; i++)
        delete[] matrix[i];
    delete[] matrix;
}

template <class T>
Matrix<T>::Matrix(int r, int c) 
    :ROWS(r), COLS(c) 
{
    if(ROWS < 0 || COLS < 0)
        throw std::range_error("Arguments must be positive");
    matrix = new T*[ROWS];
    for(int i = 0; i < ROWS; i++)
        matrix[i] = new T[COLS];
    for(int r = 0; r < ROWS; r++) {
        for(int c = 0; c < COLS; c++) {
            matrix[r][c] = T();
        }
    }
}

template <class T>
Matrix<T>::~Matrix() {
    deleteMatrix();
}

template <class T>
Matrix<T>::Matrix(const Matrix<T>& mat) 
    :ROWS(mat.ROWS), COLS(mat.COLS), matrix(new T*[ROWS])
{
    for(int i = 0; i < ROWS; i++)
        matrix[i] = new T[COLS];
    for(int r = 0; r < ROWS; r++) {
        for(int c = 0; c < COLS; c++) {
            matrix[r][c] = mat.matrix[r][c];
        }
    }
}

template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& mat) {
    if(this == &mat)
        return *this;
    if(ROWS == mat.ROWS && COLS == mat.COLS) {
        for(int r = 0; r < ROWS; r++) {
            for(int c = 0; c < COLS; c++) {
                 matrix[r][c] = mat.matrix[r][c];
            }
        }
        return *this;
    }
    deleteMatrix();
    ROWS = mat.ROWS;
    COLS = mat.COLS;
    matrix = new T*[ROWS];
    for(int i = 0; i < ROWS; i++)
        matrix[i] = new T[ROWS];
    for(int r = 0; r < ROWS; r++) {
        for(int c = 0; c < COLS; c++) {
            matrix[r][c] = mat.matrix[r][c];
        }
    }
    return *this;
}

template <class T>
T& Matrix<T>::at(int r, int c) const {
    if(r < 0 || r >= ROWS)
        throw std::range_error("Rows out of range");
    if(c < 0 || c >= COLS) 
        throw std::range_error("Columns out of range");
    return matrix[r][c];
}

template <class T>
T& Matrix<T>::at(int r, int c) {
    if(r < 0 || r >= ROWS)
        throw std::range_error("Rows out of range");
    if(c < 0 || c >= COLS)
        throw std::range_error("Columns out of range");
    return matrix[r][c];
}

template <class T>
bool Matrix<T>::contains(T item) const {
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            if(matrix[i][j] == item) 
                return true;
        }
    }
    return false;
}

template <class T>
void Matrix<T>::resize(int r, int c) {
    if(r < 0 || c < 0)
        throw std::range_error("Arguments must be positive");
    if(r < ROWS || c < COLS)
        throw std::invalid_argument("Can't resize to smaller dimensions");
    T** p = new T*[r];
    for(int i = 0; i < r; i++)
        p[i] = new T[c];
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
             if(i >= ROWS || j >= COLS)  p[i][j] = T();
             else  p[i][j] = matrix[i][j];
        }
    }
    deleteMatrix();
    matrix = p;
    ROWS = r;
    COLS = c;
}

template <class T>
void Matrix<T>::clear() {
	for(int r = 0; r < ROWS; r++) {
		for(int c = 0; c < COLS; c++) {
			matrix[r][c] = T();
		}
	}
}

template <class T>
bool operator==(const Matrix<T>& m1, const Matrix<T>& m2) {
    if((m1.rows() != m2.rows()) || (m1.columns() != m2.columns()))
        return false;
    for(int r = 0; r < m1.rows(); r++) {
        for(int c = 0; c < m2.columns(); c++) {
            if(m1[r][c] != m2[r][c])
                return false;
        }
    }
    return true;
}

template <class T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& mat) {
    out << '[';
    for(int i = 0; i < mat.rows(); i++) {
        out << '[';
        for(int j = 0; j < mat.columns(); j++) {
             out << mat[i][j];
             if(j != mat.columns()-1) 
                 out << ", "; 
        }
        if(i == mat.rows()-1)  out << "]]";
        else  out << "]\n ";
    }
    return out << ']';
}

#endif
