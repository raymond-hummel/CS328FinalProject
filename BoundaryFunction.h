/*
  Filename:   BoundaryFunction.h
  Author:     Raymond Hummel
  Date:       5/8/2014
  Purpose:    Contains the declaration of the BoundaryFunction class
*/

#ifndef BOUNDARYFUNCTION_H
#define BOUNDARYFUNCTION_H

template<typename T, typename T_func>
class BoundaryFunction
{
  public:
    /*  Description: Constructor, initializes member variables
        Preconditions: None
        Postconditions: A contains the proper matrix for a Direchlet problem 
                        with numPoints sized mesh, U = function, 
                        x and b are size numPoints-1
    */
    BoundaryFunction(T_func theFunc):myFunc(theFunc){}
    
    /*  Description: Function Evaluation Operator
        Preconditions: None
        Postconditions: returns the value of the function at (x,y)
    */
    T operator()(T x, T y){ return myFunc(x,y); }
    
    /*  Description: Setter
        Preconditions: None
        Postconditions: myFunc = newFunc
    */
    void setFunction(T_func newFunc){ myFunc = newFunc; }
    
  private:
    T_func myFunc;
    
};

#endif