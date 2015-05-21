/*
  Filename:   Norm.h
  Author:     Raymond Hummel
  Date:       4/24/2014
  Purpose:    Contains the definition and implementation of the Norm class/function
*/

#ifndef NORM_H
#define NORM_H

#include <cmath>
#include <cstdlib>

#include "Vector.h"

template <class T>
class Norm
{
  public:
    T operator()(const Vector<T>& vect)
    {
      T norm = 0;
      int size = vect.getSize();
      
      for(int i = 0; i < size; i++)
      {
        norm += abs(vect[i]);
      }
      
      return norm;
    }
};

#endif