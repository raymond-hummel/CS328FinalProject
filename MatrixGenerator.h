/*
  Filename:   MatrixGenerator.h
  Author:     Raymond Hummel
  Date:       5/8/2014
  Purpose:    Contains the declaration of the MatrixGenerator class
*/

#ifndef MATRIXGENERATOR_H
#define MATRIXGENERATOR_H

#include <exception>
#include "SymmetricMatrix.h"

class MatrixGenerator
{
  public:
    /*  Description: Constructor, initializes member variables
        Preconditions: N must be a positive, non-zero integer
        Postconditions: theMatrix is the correct matrix for a Direchlet 
                        problem with N mesh divisions
    */
    MatrixGenerator(int N){ buildMatrix(N); }
    
    /*  Description: Getter
        Preconditions: None
        Postconditions: returns theMatrix
    */
    SymmetricMatrix<double> getMatrix(){ return theMatrix; }
    
    /*  Description: Setter
        Preconditions: N must be a positive, non-zero integer
        Postconditions: theMatrix is the correct matrix for a Direchlet 
                        problem with N mesh divisions
    */
    void set(int N){ buildMatrix(N); }
    
    
  private:
    SymmetricMatrix<double> theMatrix;
    
    /*  Description: Container for common behavior between constructor and setter
        Preconditions: N must be a positive, non-zero integer
        Postconditions: theMatrix is the correct matrix for a Direchlet 
                        problem with N mesh divisions
    */
    void buildMatrix(int N)
    {
      int size = (N-1)*(N-1);
      double h = 1.0/N;
      theMatrix.setSize(size,size);
      double x = 0;
      double y = 0;
      bool up, right;
      
      for(int row=0; row < size; row++)
      {
        x += h;
        if(0 == row%(N-1)) 
        {
          x = h;
          y += h;
        }
        up = (row != size-1);
        //down = (row != 0);
        right = (N-2 != row%(N-1));
        //left = (col != 0);
        
        for(int col=row; col < size; col++) //exploits SymmetricMatrix
        {
          //up
          if(col == (row+(N-1)) && up) theMatrix(row,col) = -h;
          //down
          //else if(col == (row-(N-1)) && down) theMatrix(row,col) = -h;
          //right
          else if(col == (row+1) && right) theMatrix(row,col) = -h;
          //left
          //else if(col == (row-1) && left) theMatrix(row,col) = -h;
          //itself
          else if(row == col) theMatrix(row,row) = 1;
          //every other entry
          else theMatrix(row,col) = 0;
        }
      }
    }
    
};

#endif