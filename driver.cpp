/*
  Filename:   driver.cpp
  Author:     Raymond Hummel
  Date:       4/22/2014
  Purpose:    Runs tests for assignment 5
*/


#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "Matrix.h"
#include "SteepestDescent.h"
#include "GaussSeidel.h"
#include "DirechletSolver.h"
#include "BoundaryFunction.h"
#include "MatrixGenerator.h"

using namespace std;

void runTests();

double ourFunction(double x, double y);
double otherFunction(double x, double y);

typedef double(*funcPtr)(double,double);

int main(int argc, char *argv[])
{
  int N = 0;
  bool test = false;
  
  if(argc != 2)
  {
    // if incorrect number of parameters, explain usage
    cout << "Please specify a mesh size. Example:" << endl;
    cout << "\tdriver 4" << endl;
    cin >> N;
  }
  else N = atoi(argv[1]);
  
  DirechletSolver<double> solver(N,ourFunction);
  Vector<double> vec = solver();
  cout << "direchlet approximation= " << endl;
  //cout << vec << endl;
  
  cout.precision(3);
  for(int i=vec.getSize()-1; i>=0; i--)
  { 
    cout.width(8);
    cout << vec[i] << "  \t";
    if( (i)%(N-1) == 0 ) cout << endl;
  }
  
  if(test) runTests();
  
  return 1;
}


void runTests()
{
  // open file
  ifstream infile("testData.dat");
  while(!infile.is_open())
  {
    cout << "Test data not found" << endl;
    return;
  }
  
  unsigned int numElements;
  infile >> numElements;
  Matrix<double> myMatrix(numElements);
  Vector<double> myVector(numElements);
  infile >> myMatrix;
  infile >> myVector;
  infile.close();
  
  cout << "A=" << endl;
  cout << myMatrix << endl;
  
  cout << "b=" << endl;
  cout << myVector << endl;
  
  SteepestDescent<double> solver;
  GaussSeidel<double> solver2;
  
  Vector<double> x;
  try{
  x = solver(myMatrix,myVector);
  }catch(char const* e) { cout << e << endl; }
  cout << "x=" << endl;
  cout << x << endl;
  
  x = solver2(myMatrix,myVector);
  cout << "x=" << endl;
  cout << x << endl;
  
  
  
  //start tests for Direchlet
  cout << ourFunction(0.25,0) << endl;
  BoundaryFunction<double, funcPtr> func(ourFunction);
  cout << func(0.5,0) << endl;
  
  int N = 6;
  DirechletSolver<double> solver3(N,otherFunction);
  Vector<double> vec = solver3();
  cout << "direchlet approximation= " << endl;
  cout << vec << endl;
  
  for(int i=vec.getSize()-1; i>=0; i--)
  { 
    cout << vec[i] << "  \t";
    if( (i)%(N-1) == 0 ) cout << endl;
  }
  
}

double ourFunction(double x, double y)
{
  if(y != 0) return 0;
  return 1 - (4*(x - 0.5)*(x - 0.5));
}

double otherFunction(double x, double y)
{
  return x+y;
}

/*
try{

}
catch(char const* m)
{
  cout << m << endl;
}


*/





























