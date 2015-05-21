/*
  Filename:   SteepestDescent.h
  Author:     Raymond Hummel
  Date:       4/8/2014
  Purpose:    Contains the declaration of the SteepestDescent class
*/

#ifndef STEEPESTDESCENT_H
#define STEEPESTDESCENT_H

#include "MatrixBase.h"
#include "SymmetricMatrix.h"
#include "Norm.h"

template<class T>
class SteepestDescent
{
  public:
    Vector<T> operator()(const MatrixBase<T>& A, const Vector<T>& b)
    {
      if(A.getNumRows() != b.getSize()) throw "Matrix A and Vector b must be the same size.";
      if(!isSymmetric(A)) throw "Matrix A must be symmetric";
      if(!A.isDiagonallyDominant()) throw "Matrix A must be diagonally dominant";
      Norm<T> norm;
      Vector<T> x(b);
      Vector<T> d(b.getSize());
      double error = 0.0000001;
      T numerator = 0;
      T denominator = 0;
      
      d = ( (A*x) - b )* -1;
      
      int count = 0;
      
      while( norm(d) > error )
      {
        //numerator
        numerator = norm(d)*norm(d);
        
        //denominator
        denominator = d * (A*d);
        
        //new x
        x = x + (d * (numerator/denominator));
        
        //new d
        d = ( (A*x) - b )* -1;
        
        count++;
        if(count > 5000) 
        {
          cout << "SteepestDescent method did not converge after 5000 iterations" << endl;
          break;
        }
      }
      
      return x;
    }
    
};

#endif