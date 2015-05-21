/*
  Filename:   Vector.hpp
  Author:     Raymond Hummel
  Date:       4/8/2014
  Purpose:    Contains the implementation of the Vector class
*/

#include <iostream>

#include "Error.h"

using namespace std;

template<class T>
Vector<T>::Vector(int n)
{
  if(n < 0) throw SizeError(n, "Vector(int n)");
  size = n;
  head = new T[n];
}


template<class T>
Vector<T>::Vector()
{
  size = 0;
  head = 0;
}


template<class T>
Vector<T>::Vector(const Vector<T>& original)
{
  size = original.size;
  head = new T[size];
  copy(original);
}


template<class T>
Vector<T>::~Vector()
{
  delete [] head;
}


template<class T>
T& Vector<T>::operator[](int i)
{
  if(i < 0 || i >= size) throw RangeError(i, "operator[]");
  return head[i];
}


template<class T>
const T& Vector<T>::operator[](int i) const
{
  if(i < 0 || i >= size) throw RangeError(i, "const operator[]");
  return head[i];
}


template<class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& rhs)
{
  if(head != rhs.head)
  {
    setSize(rhs.size);
    copy(rhs);
  }
  return *this;
}


template<class T>
Vector<T>& Vector<T>::operator=(const T& rhs)
{
  T* p = head + size;
  while(p > head) *--p = rhs;
  return *this;
}


template<class T>
Vector<T> Vector<T>::operator*(const T& rhs) const
{
  Vector<T> retVal(*this);
  retVal *= rhs;
  return retVal;
}


template<class T>
Vector<T>& Vector<T>::operator*=(const T& rhs)
{
  for(int i=0; i < size; i++)
  {
    head[i] = head[i] * rhs;
  }
  return *this;
}


template<class T>
T Vector<T>::operator*(const Vector<T>& rhs) const
{
  if(size != rhs.size) throw SizeError(rhs.size, "operator*(Vector)");
  T retVal = 0;
  for(int i=0; i < size; i++)
  {
    retVal += head[i] * rhs[i];
  }
  return retVal;
}


template<class T>
Vector<T> Vector<T>::operator+(const Vector<T>& rhs) const
{
  if(size != rhs.size) throw SizeError(rhs.size, "operator+");
  Vector<T> retVal(*this);
  retVal += rhs;
  return retVal;
}


template<class T>
Vector<T>& Vector<T>::operator+=(const Vector<T>& rhs)
{
  if(size != rhs.size) throw SizeError(rhs.size, "operator+=");
  for(int i=0; i < size; i++)
  {
    head[i] = head[i] + rhs[i];
  }
  return *this;
}


template<class T>
Vector<T> Vector<T>::operator-(const Vector<T>& rhs) const
{
  if(size != rhs.size) throw SizeError(rhs.size, "operator-");
  Vector<T> retVal(size);
  for(int i=0; i < size; i++)
  {
    retVal[i] = head[i] - rhs[i];
  }
  return retVal;
}


template<class T>
T Vector<T>::sum() const
{
  T retVal = 0;
  for(int i=0; i < size; i++)
  {
    retVal = retVal + head[i];
  }
  return retVal;
}


template<class T>
int Vector<T>::getSize() const
{
  return size;
}


template<class T>
void Vector<T>::setSize(int n)
{
  if(n != size)
  {
    if(n < 0) throw SizeError(n, "setSize");
    delete [] head;
    size = n;
    head = new T[n];
    for(int i=0; i < 0; i++)
    {
      head[i] = 0;
    }
  }
}


// Copies the elements of a into *this
template<class T>
void Vector<T>::copy(const Vector<T>& a)
{
  T* p = head + size;
  T* q = a.head + a.size;
  while(p > head) *--p = *--q;
}



template<class T>
ostream& operator<<( ostream& output, const Vector<T>& vector)
{
  output.precision(3);
  for(int i=0; i<vector.size; i++)
  {
    output.width(8);
    if(abs(vector[i]) < 0.0000001) 
    {
      output << 0 << "";
    }
    else
    {
      output << vector[i] << "";
    }
  }
  output << endl;
  output.precision(6);
  return output;
}


template<class T>
istream& operator>>( istream& input, Vector<T>& vector)
{
  for(int i=0; i<vector.size; i++)
  {
    input >> vector[i];
  }
  return input;
}


template<class T>
ifstream& operator>>( ifstream& input, Vector<T>& vector)
{
  T temp;
  for(int i=0; i<vector.size; i++)
  {
    input >> temp;
    if(input.eof()) break;
    vector[i] = temp;
  }
  return input;
}


