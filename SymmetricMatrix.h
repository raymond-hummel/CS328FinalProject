/*
  Filename:   SymmetricMatrix.h
  Author:     Raymond Hummel
  Date:       4/22/2014
  Purpose:    Contains the declaration of the SymmetricMatrix class
*/

#ifndef SYMMETRICMATRIX_H
#define SYMMETRICMATRIX_H


#include "MatrixBase.h"
#include "Matrix.h"


// Forward Declarations
template<class T>
bool isSymmetric(const MatrixBase<T>& matrix);


template<class T>
class SymmetricMatrix:public virtual MatrixBase<T>, private Matrix<T>
{
  public:
    /*  Description: Default Constructor, creates empty SymmetricMatrix
        Preconditions: None
        Postconditions: numRows, numCols, head all equal 0
    */
    SymmetricMatrix():numRows(0), numCols(0), head(0) {}
    
    
    /*  Description: Pre-Sized Constructor, creates SymmetricMatrix of size n by n
        Preconditions: n must be a positive, non-zero integer
                       T must have a defined default constructor
        Postconditions: head points to an array of Vectors of size n,
                        numRows = n, numCols = n, throws a SizeError 
                        exception if n < 0
    */
    SymmetricMatrix(const int& n);
    
    
    /*  Description: Copy Constructor, makes a deep copy of the parameter
        Preconditions: T must have a defined copy assignment operator
        Postconditions: calling object is a deep copy of original
    */
    SymmetricMatrix(const SymmetricMatrix<T>& original);
    
    
    /*  Description: Destructor, frees dynamic memory
        Preconditions: None
        Postconditions: all dynamic memory associated with the calling 
                        object is freed
    */
    virtual ~SymmetricMatrix();
    
    
    /*  Description: MatrixBase Subscripting Operator, provides access to 
                     elements of the matrix
        Preconditions: row, col are positive integers between 
                       0 and numRows or numCols respectively
                       calling object is not const
        Postconditions: returns a reference to the element of the MatrixBase 
                        specified by row, col
                        throws a RangeError if row,col < 0 or row >= numRows 
                        or col >= numCols
    */
    virtual T& operator()(int row, int col);
    
    
    /*  Description: const MatrixBase Subscripting Operator, provides read-only 
                     access to elements of the matrix
        Preconditions: row, col are positive integers between 
                       0 and numRows or numCols respectively
        Postconditions: returns a const reference to the element of the MatrixBase
                        specified by row, col
                        throws a RangeError if row,col < 0 or row >= numRows 
                        or col >= numCols
    */
    virtual const T& operator()(int row, int col) const;
    
    
    /*  Description: Copy Assignment Operator, supports operator chaining 
                     and self-assignment
        Preconditions: T must have a defined copy assignment operator
        Postconditions: calling object is a deep copy of rhs
                        throws a SizeError if rhs.numCols or numRows < 0
                        returns a reference to the calling object
    */
    SymmetricMatrix<T>& operator=(const SymmetricMatrix<T>& rhs);
    
    
    /*  Description: SymmetricMatrix Addition, adds matrices
        Preconditions: T must have a defined addition operator
                       T must have a defined copy assignment operator
        Postconditions: returns matrix that is element-wise 
                        sum of calling object and rhs,
                        throws a SizeError if rhs has a different number 
                        of rows or columns
    */
    virtual MatrixBase<T>& operator+=(const MatrixBase<T>& rhs);
    
    
    /*  Description: SymmetricMatrix Subtraction, subtracts matrices
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
    
    
    /*  Description: SymmetricMatrix Multiplication, performs matrix multiplication and
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
    
    
    /*  Description: Getter for the rows of calling object
        Preconditions: None
        Postconditions: returns the row referenced by rowIndex
    */
    virtual Vector<T> getRow(int rowIndex) const;
    
    
    /*  Description: Transpose
        Preconditions: None
        Postconditions: returns the transpose of the calling object
    */
    SymmetricMatrix<T> transpose() const { return *this; }
    
    
    /*  Description: Getter for numRows
        Preconditions: None
        Postconditions: returns the number of rows in the matrix
    */
    virtual int getNumRows() const;
    
    
    /*  Description: Getter for numCols
        Preconditions: None
        Postconditions: returns the number of columns in the matrix
    */
    virtual int getNumCols() const;
    
    
    /*  Description: Determines if matrix is diagonally dominant
        Preconditions: None
        Postconditions: returns true if Aii > |Aij| for j!=i, else false
    */
    virtual bool isDiagonallyDominant() const { return Matrix<T>::isDiagonallyDominant(); }
    
    
    /*  Description: Setter for size
        Preconditions: row, col must be positive non-zero integers
                       T must have a defined default constructor
        Postconditions: numRows = row, numCols = col, value of all elements
                        is set by the default constructor for T
                        throws SizeError if row != col
    */
    void setSize(int rows, int cols);
    
    
    /*  Description: Determine if given matrix is symmetric
        Preconditions: None
        Postconditions: returns true iff matrix is symmetric, else false
    */
    friend bool isSymmetric<> (const MatrixBase<T>& matrix);
    
    
    
    
  private:
    int numRows, numCols;
    Vector<T>* head;
    
    /*  Description: copy function, creates deep copy of elements in a
        Preconditions: T must have a defined copy assignment operator
        Postconditions: calling object is a deep copy of a
    */
    void copy(const SymmetricMatrix<T>& a);
    
};


#include "SymmetricMatrix.hpp"
#endif