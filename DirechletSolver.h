/*
  Filename:   DirechletSolver.h
  Author:     Raymond Hummel
  Date:       5/8/2014
  Purpose:    Contains the declaration of the DirechletSolver class
*/

#ifndef DIRECHLETSOLVER_H
#define DIRECHLETSOLVER_H

#include "SymmetricMatrix.h"
#include "SteepestDescent.h"
#include "GaussianElimination.h"
#include "GaussSeidel.h"
#include "MatrixGenerator.h"
#include "BoundaryFunction.h"
#include "Vector.h"

template<class T>
class DirechletSolver
{
  public:
    typedef T(*T_func)(T,T);
    
    /*  Description: Constructor, initializes member variables
        Preconditions: numDivisions must be a positive, non-zero integer
                       T must have a defined default constructor
        Postconditions: A contains the proper matrix for a Direchlet problem 
                        with numDivisions sized mesh, U = function, 
                        x and b are size numDivisions-1
    */
    DirechletSolver(int numDivisions, T_func function):U(function){ setN(numDivisions); }
    
    
    /*  Description: Boundary function setter
        Preconditions: newU is a function pointer describing the boundary of the Direchlet problem
        Postconditions: U = newU
    */
    void setU(T_func newU){ U.setFunction(newU); }
    
    
    /*  Description: Setter for size of mesh to use in the solution
        Preconditions: newN must be a positive, non-zero integer
        Postconditions: A contains the proper matrix for a Direchlet problem 
                        with N sized mesh, x and b are size (N-1)^2, N = newN
    */
    void setN(int newN);
    
    
    /*  Description: Function Evaluation Operator, returns solution to 
                     the specified Direchlet problem
        Preconditions: None
        Postconditions: returns Vector representing the approximate solution 
                        of the Direchlet problem at the inner mesh points
    */
    Vector<double> operator()();
    
    
  private:
    BoundaryFunction<T,T_func> U;
    SymmetricMatrix<double> A;
    Vector<double> x, b;
    int N;
    
    /*  Description: helper function to build the b vector
        Preconditions: None
        Postconditions: initializes b vector with the appropriate values for
                        the current Direchlet problem
    */
    void buildVector();
};

#include "DirechletSolver.hpp"

#endif