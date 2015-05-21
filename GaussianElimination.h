/*
  Filename:   GaussianElimination.h
  Author:     Raymond Hummel
  Date:       4/8/2014
  Purpose:    Contains declaration and implementation of the Gaussian 
              Elimination class
*/


#ifndef GAUSSIANELIMINATION_H
#define GAUSSIANELIMINATION_H

#include <cstdlib>
#include <cmath>

#include "MatrixBase.h"
#include "Matrix.h"
#include "Vector.h"


template<class T>
class GaussianElimination
{
  public:
    /*  Description: Function Evaluation Operator, performs Gaussian 
                     Elimination to solve the equation Ax=b
        Preconditions: A must be a square matrix
                       T must have a properly defined division operator
                       T must be convertible to a float
                       T must have an overload for the abs() function
        Postconditions: x contains the solution the equation Ax=b
                        throws a SizeError if A.numRows != b.size
    */
    Vector<T> operator()(MatrixBase<T>& A, const Vector<T>& b);
    
    
  private:
    /*  Description: Reduce Down, reduces all elements in A below the
                     start position to zero
        Preconditions: 1 <= start < numRows in A
        Postconditions: the column referenced by start - 1 is all zeros 
                        from row start to numRows-1
    */
    void reduceDown(Matrix<T>& A, int start);
    
    
    /*  Description: Reduce Up, reduces all elements in A above the
                     start position to zero
        Preconditions: 0 < start <= numRows-2 in A
        Postconditions: the column referenced by start + 1 is all zeros
                        from row start to row 0
    */
    void reduceUp(Matrix<T>& A, int start);
    
    
    /*  Description: Swap, swaps the current row with the row that has the 
                     largest absolute valued element in the column
        Preconditions: T must overload the abs() function
        Postconditions: A[row][col] contains the largest element of A[>=row][col]
    */
    void swap(Matrix<T>& A, int row, int col);
    
    
};

#include "GaussianElimination.hpp"

#endif