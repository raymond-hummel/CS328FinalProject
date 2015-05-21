/*
  Filename:   MatrixBase.h
  Author:     Raymond Hummel
  Date:       4/24/2014
  Purpose:    Contains the declaration of the MatrixBase interface
*/

#ifndef MATRIXBASE_H
#define MATRIXBASE_H

#include <iostream>
#include <cstdlib>
#include <cmath>

#include "Vector.h"
#include "Error.h"

using namespace std;


// Forward Declarations
template<class T>
class MatrixBase;

template<class T>
ostream& operator<<( ostream& output, const MatrixBase<T>& matrix);

template<class T>
istream& operator>>( istream& input, MatrixBase<T>& matrix);

template<class T>
ifstream& operator>>( ifstream& input, MatrixBase<T>& matrix);


template<class T>
class MatrixBase
{
  public:
    /*  Description: Destructor, frees dynamic memory
        Preconditions: None
        Postconditions: all dynamic memory associated with the calling 
                        object is freed
    */
    virtual ~MatrixBase() {}
    
    
    /*  Description: Matrix Subscripting Operator, provides access to 
                     elements of the matrix
        Preconditions: i is a positive integer between 0 and numRows-1
                       calling object is not const
        Postconditions: returns a reference to the ith vector of the Matrix
                        throws a RangeError if i < 0 or i >= numRows
    */
    virtual T& operator()(int row, int col) = 0;
    
    
    /*  Description: const Matrix Subscripting Operator, provides read-only 
                     access to elements of the matrix
        Preconditions: i is a positive integer between 0 and numRows-1
        Postconditions: returns a const reference to the ith vector of the Matrix
                        throws a RangeError if i < 0 or i >= numRows
    */
    virtual const T& operator()(int row, int col) const = 0;
    
    
    /*  Description: Matrix Addition, adds matrices
        Preconditions: T must have a defined addition operator
                       T must have a defined copy assignment operator
        Postconditions: returns matrix that is element-wise 
                        sum of calling object and rhs,
                        throws a SizeError if rhs has a different number 
                        of rows or columns
    */
    virtual MatrixBase<T>& operator+=(const MatrixBase<T>& rhs) = 0;
    
    
    /*  Description: Matrix Subtraction, subtracts matrices
        Preconditions: T must have a defined subtraction operator
                       T must have a defined copy assignment operator
        Postconditions: returns matrix that is element-wise 
                        difference of calling object and rhs,
                        throws a SizeError if rhs has a different number 
                        of rows or columns
    */
    virtual MatrixBase<T>& operator-=(const MatrixBase<T>& rhs) = 0;
    
    
    /*  Description: Scalar Multiplication, multiplies all elements of the
                     matrix by the parameter value
        Preconditions: T must have a defined multiplication operator
                       T must have a defined copy assignment operator
        Postconditions: returns matrix with every element containing the
                        calling object's element multiplied by rhs
    */
    virtual MatrixBase<T>& operator*=(const T& rhs) = 0;
    
    
    /*  Description: Matrix Multiplication, performs matrix multiplication and
                     returns the result
        Preconditions: T must have a defined multiplication operator
                       T must have a defined addition operator
                       T must have a defined copy assignment operator
        Postconditions: returns matrix multiplication product with 
                        size = numRows x rhs.numCols
                        throws SizeError if numCol != rhs.numRows
    */
    virtual MatrixBase<T>& operator*=(const MatrixBase<T>& rhs) = 0;
    
    
    /*  Description: Vector Multiplication, multiplies the matrix by a vector
                     and returns the resulting vector
        Preconditions: T must have a defined multiplication operator
                       T must have a defined addition operator
                       T must have a defined copy assignment operator
        Postconditions: returns vector multiplication product with 
                        size = numRows x 1
                        throws SizeError if numCol != rhs.numRows
    */
    virtual Vector<T> operator*(const Vector<T>& rhs) const = 0;
    
    
    /*  Description: Getter for the columns of calling object
        Preconditions: None
        Postconditions: returns the column referenced by colIndex
    */
    virtual Vector<T> getColumn(int colIndex) const = 0;
    
    
    /*  Description: Getter for the rows of calling object
        Preconditions: None
        Postconditions: returns the row referenced by rowIndex
    */
    virtual Vector<T> getRow(int rowIndex) const = 0;
    
    
    /*  Description: Getter for numRows
        Preconditions: None
        Postconditions: returns the number of rows in the matrix
    */
    virtual int getNumRows() const = 0;
    
    
    /*  Description: Getter for numCols
        Preconditions: None
        Postconditions: returns the number of columns in the matrix
    */
    virtual int getNumCols() const = 0;
    
    
    /*  Description: Determines if matrix is diagonally dominant
        Preconditions: None
        Postconditions: returns true if Aii > |Aij| for j!=i, else false
    */
    virtual bool isDiagonallyDominant() const = 0;
    
    
    /*  Description: Extraction operator
        Preconditions: None
        Postconditions: elements of matrix are streamed to output, 
                        rows separated by newlines
    */
    friend ostream& operator<< <>( ostream& output, const MatrixBase<T>& matrix);
    
    
    /*  Description: Insertion operator
        Preconditions: None
        Postconditions: elements of input stream are added to the matrix, 
                        starting at matrix[0][0], until the vector is full
    */
    friend istream& operator>> <>( istream& input, MatrixBase<T>& matrix);
    
    
    /*  Description: File Insertion operator
        Preconditions: None
        Postconditions: elements of file are added to the matrix, 
                        starting at matrix[0][0], until the matrix is full
                        or the end of the file is reached
    */
    friend ifstream& operator>> <>( ifstream& input, MatrixBase<T>& matrix);
    
};


template<class T>
ostream& operator<<( ostream& output, const MatrixBase<T>& matrix)
{
  output.precision(3);
  for(int i=0; i < matrix.getNumRows(); i++)
  {
    for(int j=0; j < matrix.getNumCols(); j++)
    {
      output.width(8);
      output << matrix(i,j);
    }
    output << endl;
  }
  output.precision(6);
  return output;
}


template<class T>
istream& operator>>( istream& input, MatrixBase<T>& matrix)
{
  for(int i=0; i < matrix.getNumRows(); i++)
  {
    for(int j=0; j < matrix.getNumCols(); j++)
    {
      input >> matrix(i,j);
    }
  }
  return input;
}


template<class T>
ifstream& operator>>( ifstream& input, MatrixBase<T>& matrix)
{
  T temp;
  for(int i=0; i < matrix.getNumRows(); i++)
  {
    for(int j=0; j < matrix.getNumCols(); j++)
    {
      input >> temp;
      if( input.eof() ) return input;
      matrix(i,j) = temp;
    }
  }
  return input;
}


#endif