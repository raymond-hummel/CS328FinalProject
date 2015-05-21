/*
  Filename:   Error.h
  Author:     Raymond Hummel
  Date:       2/27/2014
  Purpose:    Contains the definition and implementation of two error classes 
              derived from classes described in Scientific and Engineering 
              C++, by Barton and Nackman
*/


#ifndef ERROR_H
#define ERROR_H

#include <string>


class RangeError
{
  public:
    RangeError(int i, string name="not set"):subscript(i), funcName(name) {}
    int badSubscript(){ return subscript; }
    string calledFrom(){ return funcName; }
  private:
    int subscript;
    string funcName;
};


class SizeError
{
  public:
    SizeError(int n, string name="not set"):size(n), funcName(name) {}
    int badSize(){ return size; }
    string calledFrom(){ return funcName; }
  private:
    int size;
    string funcName;
};


#endif