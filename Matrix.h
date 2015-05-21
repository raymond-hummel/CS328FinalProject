/*
  Filename:   Matrix.h
  Author:     Raymond Hummel
  Date:       4/24/2014
  Purpose:    Contains the declaration of the Matrix implementation base
*/


/*
Derived classes should override the following functions
Constructors
copyAssign
matrixSubscripting
transpose
setSize
copy
*/


#ifndef MATRIX_H
#define MATRIX_H

#include "MatrixBase.h"


template<class T>
class Matrix: public virtual MatrixBase<T>
{
  public:
    /*  Description: Default Constructor, creates empty Matrix
        Preconditions: None
        Postconditions: numRows, numCols, head all equal 0
    */
    Matrix():numRows(0), numCols(0), head(NULL) {}
    
    
    /*  Description: Pre-Sized Constructor, creates Matrix of size n by n
        Preconditions: n must be a positive, non-zero integer
                       T must have a defined default constructor
        Postconditions: head points to an array of Vectors of size n,
                        numRows = n, numCols = n, throws a SizeError 
                        exception if n < 0
    */
    Matrix(int n);
    
    
    /*  Description: Pre-Sized Constructor, creates Matrix of size rows by cols
        Preconditions: rows, cols must be positive, non-zero integers
                       T must have a defined default constructor
        Postconditions: head points to an array of Vectors of size rows,
                        numRows = rows, numCols = cols, throws a SizeError 
                        exception if rows or cols < 0
    */
    Matrix(int rows, int cols);
    
    
    /*  Description: Copy Constructor, makes a deep copy of the parameter
        Preconditions: T must have a defined copy assignment operator
        Postconditions: calling object is a deep copy of original
    */
    Matrix(const Matrix<T>& original);
    
    
    /*  Description: Base Constructor, makes a deep copy of the parameter
        Preconditions: T must have a defined copy assignment operator
        Postconditions: calling object is a deep copy of original
    */
    //Matrix(const MatrixBase<T>& original);
    
    
    /*  Description: Destructor, frees dynamic memory
        Preconditions: None
        Postconditions: all dynamic memory associated with the calling 
                        object is freed
    */
    ~Matrix() { delete [] head; }
    
    
    /*  Description: Copy Assignment Operator, supports operator chaining 
                     and self-assignment
        Preconditions: T must have a defined copy assignment operator
        Postconditions: calling object is a deep copy of rhs
                        throws a SizeError if rhs.numCols or numRows < 0
                        returns a reference to the calling object
    */
    Matrix<T>& operator=(const Matrix<T>& rhs);
    
    
    /*  Description: MatrixBase Assignment Operator, supports operator chaining 
                     and self-assignment
        Preconditions: T must have a defined copy assignment operator
        Postconditions: calling object is a deep copy of rhs
                        throws a SizeError if rhs.numCols or numRows < 0
                        returns a reference to the calling object
    */
    MatrixBase<T>& operator=(const MatrixBase<T>& rhs);
    
    
    /*  Description: Matrix Subscripting Operator, provides access to 
                     elements of the matrix
        Preconditions: i is a positive integer between 0 and numRows-1
                       calling object is not const
        Postconditions: returns a reference to the ith vector of the Matrix
                        throws a RangeError if i < 0 or i >= numRows
    */
    virtual T& operator()(int row, int col);
    
    
    /*  Description: const Matrix Subscripting Operator, provides read-only 
                     access to elements of the matrix
        Preconditions: i is a positive integer between 0 and numRows-1
        Postconditions: returns a const reference to the ith vector of the Matrix
                        throws a RangeError if i < 0 or i >= numRows
    */
    virtual const T& operator()(int row, int col) const;
    
    
    /*  Description: Matrix Addition, adds matrices
        Preconditions: T must have a defined addition operator
                       T must have a defined copy assignment operator
        Postconditions: returns matrix that is element-wise 
                        sum of calling object and rhs,
                        throws a SizeError if rhs has a different number 
                        of rows or columns
    */
    virtual MatrixBase<T>& operator+=(const MatrixBase<T>& rhs);
    
    
    /*  Description: Matrix Subtraction, subtracts matrices
        Preconditions: T must have a defined subtraction operator
                       T must have a defined copy assignment operator
        Postconditions: returns matrix that is element-wise 
                        difference of calling object and rhs,
                        throws a SizeError if rhs has a different number 
                        of rows or columns
    */
    virtual MatrixBase<T>& operator-=(const MatrixBase<T>& rhs);
    
    
    /*  Description: Scalar Multiplication, multiplies all elements of the
                     matrix by the parameter value
        Preconditions: T must have a defined multiplication operator
                       T must have a defined copy assignment operator
        Postconditions: returns matrix with every element containing the
                        calling object's element multiplied by rhs
    */
    virtual MatrixBase<T>& operator*=(const T& rhs);
    
    
    /*  Description: Matrix Multiplication, performs matrix multiplication and
                     returns the result
        Preconditions: T must have a defined multiplication operator
                       T must have a defined addition operator
                       T must have a defined copy assignment operator
        Postconditions: returns matrix multiplication product with 
                        size = numRows x rhs.numCols
                        throws SizeError if numCol != rhs.numRows
    */
    virtual MatrixBase<T>& operator*=(const MatrixBase<T>& rhs);
    
    
    /*  Description: Vector Multiplication, multiplies the matrix by a vector
                     and returns the resulting vector
        Preconditions: T must have a defined multiplication operator
                       T must have a defined addition operator
                       T must have a defined copy assignment operator
        Postconditions: returns vector multiplication product with 
                        size = numRows x 1
                        throws SizeError if numCol != rhs.numRows
    */
    virtual Vector<T> operator*(const Vector<T>& rhs) const;
    
    
    /*  Description: Getter for the columns of calling object
        Preconditions: None
        Postconditions: returns the column referenced by colIndex
    */
    virtual Vector<T> getColumn(int colIndex) const;
    
    
    /*  Description: Add Column, expands each row of the matrix to include
                     one additional column
        Preconditions: None
        Postconditions: numCols increases by 1, the added column contains 
                        the elements of newCol, throws SizeError if 
                        newCol.size != numRows
    */
    void addColumn(const Vector<T>& newCol);
    
    
    /*  Description: Getter for the rows of calling object
        Preconditions: None
        Postconditions: returns the row referenced by rowIndex
    */
    virtual Vector<T> getRow(int rowIndex) const;
    
    
    /*  Description: Getter for numRows
        Preconditions: None
        Postconditions: returns the number of rows in the matrix
    */
    virtual int getNumRows() const { return numRows; }
    
    
    /*  Description: Getter for numCols
        Preconditions: None
        Postconditions: returns the number of columns in the matrix
    */
    virtual int getNumCols() const { return numCols; }
    
    
    /*  Description: Determines if matrix is diagonally dominant
        Preconditions: None
        Postconditions: returns true if Aii > |Aij| for j!=i, else false
    */
    virtual bool isDiagonallyDominant() const;
    
    
    /*  Description: Transpose
        Preconditions: None
        Postconditions: returns the transpose of the calling object
    */
    Matrix<T> transpose() const;
    
    
    /*  Description: Row Swap, swaps the positions of two rows
        Preconditions: None
        Postconditions: vector originally found at rowIndex1 is now found
                        at rowIndex2 and vice versa
    */
    void swapRows(int rowIndex1, int rowIndex2);
    
    
    /*  Description: Setter for size
        Preconditions: rows and cols must be positive non-zero integers
                       T must have a defined default constructor
        Postconditions: numRows = rows, numCols = cols, value of all elements
                        is set by the default constructor for T
    */
    void setSize(int rows, int cols);
    
  private:
    int numRows, numCols;
    Vector<T>* head;
    
    
    /*  Description: copy function, creates deep copy of elements in a
        Preconditions: T must have a defined copy assignment operator
        Postconditions: calling object is a deep copy of a
    */
    void copy(const MatrixBase<T>& a);
    
};

#include "Matrix.hpp"
#endif