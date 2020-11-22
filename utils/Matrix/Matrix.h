#ifndef __QS_MATRIX_H
#define __QS_MATRIX_H

#include <vector>

template <typename T> class Matrix {
    private:
        std::vector<std::vector<T> > mat;
        unsigned rows;
        unsigned cols;

    public:
        Matrix(unsigned _rows, unsigned _cols, const T& _initial);
        Matrix(const Matrix<T>& rhs);
        virtual ~Matrix();

        // Operator overloading, for "standard" mathematical matrix operations                                                                                                                                                          
        Matrix<T>& operator=(const Matrix<T>& rhs);

        // Matrix mathematical operations                                                                                                                                                                                               
        Matrix<T> operator+(const Matrix<T>& rhs);
        Matrix<T>& operator+=(const Matrix<T>& rhs);
        Matrix<T> operator-(const Matrix<T>& rhs);
        Matrix<T>& operator-=(const Matrix<T>& rhs);
        Matrix<T> operator*(const Matrix<T>& rhs);
        Matrix<T>& operator*=(const Matrix<T>& rhs);
        Matrix<T> transpose();

        // Matrix/scalar operations                                                                                                                                                                                                     
        Matrix<T> operator+(const T& rhs);
        Matrix<T> operator-(const T& rhs);
        Matrix<T> operator*(const T& rhs);
        Matrix<T> operator/(const T& rhs);

        // Matrix/vector operations                                                                                                                                                                                                     
        std::vector<T> operator*(const std::vector<T>& rhs);
        std::vector<T> diagonalVector();

        // Access the individual elements                                                                                                                                                                                               
        T& operator()(const unsigned& row, const unsigned& col);
        const T& operator()(const unsigned& row, const unsigned& col) const;

        // Access the row and column sizes                                                                                                                                                                                              
        unsigned getRows() const;
        unsigned getColumns() const;

        void print();

};

#endif