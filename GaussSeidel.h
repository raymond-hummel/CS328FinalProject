/*
  Filename:   GaussSeidel.h
  Author:     Raymond Hummel
  Date:       5/10/2014
  Purpose:    Contains the declaration of the GaussSeidel class
*/

#ifndef GAUSSSEIDEL_H
#define GAUSSSEIDEL_H

#include "MatrixBase.h"
#include "Matrix.h"
#include "Norm.h"

template<class T>
class GaussSeidel
{
  public:
    /*  Description: Function Evaluation Operator, returns solution of Ax=b
        Preconditions: A has no element Aii == 0
        Postconditions: returns Vector representing the approximate solution 
                        of of Ax=b for x
    */
    Vector<T> operator()(const MatrixBase<T>& A, const Vector<T>& b)
    {
      int n = A.getNumCols();
      Vector<T> x(n);
      Vector<T> prevX(n);
      Norm<T> norm;
      int count = 0;
      T sum;
      
      x = 0;
      prevX = 1;
      
      while(norm(x - prevX) > 0.0000001)
      {
        prevX = x;
        for(int i=0; i < n; i++)
        {
          sum = 0;
          for(int j=0; j <= i-1; j++)
          {
            sum -= A(i,j)*x[j];
          }
          for(int j=i+1; j < n; j++)
          {
            sum -= A(i,j)*prevX[j];
          }
          sum += b[i];
          x[i] = (1/A(i,i))*sum;
        }
        count++;
      }
      return x;
    }
    
};

#endif