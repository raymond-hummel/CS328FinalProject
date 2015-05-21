/*
  Filename:   Vector.h
  Author:     Raymond Hummel
  Date:       4/8/2014
  Purpose:    Contains the declaration of a vector class derived from the
              Simple Array class of Scientific and Engineering C++,
              by Barton and Nackman
*/


#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cstdlib>
#include <cmath>


using namespace std;

// Forward Declarations
template<class T>
class Vector;
template<class T>
ostream& operator<<( ostream& output, const Vector<T>& vector);
template<class T>
istream& operator>>( istream& input, Vector<T>& vector);
template<class T>
ifstream& operator>>( ifstream& input, Vector<T>& vector);


template<class T>
class Vector
{
  public:
    /*  Description: Pre-Sized Constructor, creates Vector of size n
        Preconditions: n must be a positive, non-zero integer
                       T must have a defined default constructor
        Postconditions: head points to an vector of size n, size = n
                        throws a SizeError exception if n < 0
    */
    Vector(int n);
    
    
    /*  Description: Default Constructor, creates Vector of size 0
        Preconditions: None
        Postconditions: size = 0, head is a pointer to 0
    */
    Vector();
    
    
    /*  Description: Copy Constructor, makes a deep copy of the parameter
        Preconditions: T must have a defined copy assignment operator
        Postconditions: calling object is a deep copy of original
    */
    Vector(const Vector<T>& original);
    
    
    /*  Description: Destructor, frees dynamic memory
        Preconditions: None
        Postconditions: all dynamic memory associated with the calling 
                        object is freed
    */
    ~Vector();
    
    
    /*  Description: Vector Subscripting Operator, provides access to 
                     elements of the vector
        Preconditions: i is a positive integer between 0 and size-1
                       calling object is not const
        Postconditions: returns a reference to the ith member of the Vector
                        throws a RangeError if i < 0 or i >= size
    */
    T& operator[](int i);
    
    
    /*  Description: const Vector Subscripting Operator, provides access to 
                     elements of the vector
        Preconditions: i is a positive integer between 0 and size-1
        Postconditions: returns a const reference to the ith member of the Vector
                        throws a RangeError if i < 0 or i >= size
    */
    const T& operator[](int i) const;
    
    
    /*  Description: Copy Assignment Operator, supports operator chaining 
                     and self-assignment
        Preconditions: T must have a defined copy assignment operator
        Postconditions: calling object is a deep copy of rhs
                        throws a SizeError if rhs.size < 0
                        returns a reference to the calling object
    */
    Vector<T>& operator=(const Vector<T>& rhs);
    
    
    /*  Description: Scalar Assignment Operator, initializes all elements 
                     of the Vector to a parameter value
        Preconditions: T must have a defined copy assignment operator
        Postconditions: every element of the calling object is equal to rhs
                        returns a reference to the calling object
    */
    Vector<T>& operator=(const T& rhs);
    
    
    /*  Description: Scalar Multiplication Operator, multiplies all elements 
                     of the Vector by the parameter value
        Preconditions: T must have a defined multiplication operator
                       T must have a defined copy assignment operator
        Postconditions: returns vector with every element containing 
                        calling object's element multiplied by rhs
    */
    Vector<T> operator*(const T& rhs) const;
    
    
    /*  Description: Scalar Multiplication and Assignment Operator, multiplies
                     all elements of the Vector by the parameter value
        Preconditions: T must have a defined multiplication operator
                       T must have a defined copy assignment operator
        Postconditions: every element of the calling object is multiplied by the rhs
                        returns a reference to the calling object
    */
    Vector<T>& operator*=(const T& rhs);
    
    
    /*  Description: Dot Product, multiplies all elements 
                     of the Vector by the parameter value
        Preconditions: T must have a defined multiplication operator
                       T must have a defined copy assignment operator
                       T must be able to convert ints
        Postconditions: returns the sum of an elementwise multiplication
    */
    T operator*(const Vector<T>& rhs) const;
    
    
    /*  Description: Vector Addition Operator, adds all elements
                     of the two vectors
        Preconditions: T must have a defined addition operator
                       T must have a defined copy assignment operator
        Postconditions: throws SizeError if vectors are not same size
                        returns vector with element-wise addition of rhs
                        and the calling object
    */
    Vector<T> operator+(const Vector<T>& rhs) const;
    
    
    /*  Description: Vector Addition and Assignment Operator, adds all elements
                     of parameter vector to the calling vector
        Preconditions: T must have a defined addition operator
                       T must have a defined copy assignment operator
        Postconditions: throws SizeError if vectors are not same size
                        callingObject[i] += rhs[i]
                        returns a reference to the calling object
    */
    Vector<T>& operator+=(const Vector<T>& rhs);
    
    
    /*  Description: Vector Subtraction Operator, subtracts all elements
                     of the two vectors
        Preconditions: T must have a defined subtraction operator
                       T must have a defined copy assignment operator
        Postconditions: throws SizeError if vectors are not same size
                        returns vector with element-wise difference of rhs
                        and the calling object
    */
    Vector<T> operator-(const Vector<T>& rhs) const;
    
    
    /*  Description: Vector Sum, adds all elements of the vector together
        Preconditions: T must have a defined addition operator
                       T must have a defined copy assignment operator
                       T must be able to convert ints
        Postconditions: returns the sum of the vector's elements
    */
    T sum() const;
    
    
    /*  Description: Getter for size
        Preconditions: None
        Postconditions: returns the size of the vector by value
    */
    int getSize() const;
    
    
    /*  Description: Setter for size
        Preconditions: n must be a positive non-zero integer
                       T must have a defined default constructor
        Postconditions: calling object is of size n, value of all elements
                        is set by the default constructor for T
    */
    void setSize(int n);
    
    
    /*  Description: Extraction operator
        Preconditions: None
        Postconditions: elements of vector are streamed to output, 
                        separated by newlines
    */
    friend ostream& operator<< <>( ostream& output, const Vector<T>& vector);
    
    
    /*  Description: Insertion operator
        Preconditions: None
        Postconditions: elements of input stream are added to the vector, 
                        starting at vector[0], until the vector is full
    */
    friend istream& operator>> <>( istream& input, Vector<T>& vector);
    
    
    /*  Description: File Extraction operator
        Preconditions: None
        Postconditions: elements of file are added to the vector, 
                        starting at vector[0], until the vector is full,
                        or the end of the file is reached
    */
    friend ifstream& operator>> <>( ifstream& input, Vector<T>& vector);
    
    
  private:
    // number of elements
    int size;
    // pointer to dynamically allocated array
    T* head;
    
    /*  Description: copy function, creates deep copy of elements in a
        Preconditions: T must have a defined copy assignment operator
        Postconditions: calling object is a deep copy of a
    */
    void copy(const Vector<T>& a);
};


#include "Vector.hpp"
#endif