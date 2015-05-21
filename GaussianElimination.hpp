/*
  Filename:   GaussianElimination.hpp
  Author:     Raymond Hummel
  Date:       4/8/2014
  Purpose:    Contains implementation of the Gaussian Elimination class
*/


template<class T>
Vector<T> GaussianElimination<T>::operator()(MatrixBase<T>& A, const Vector<T>& b)
{
  Vector<T> x( b.getSize() );
  
  Matrix<T> newA(A.getNumRows(),A.getNumCols());
  newA = A;
  newA.addColumn(b);
  
  // Forward Elimination
  for(int i=1; i < newA.getNumRows(); i++)
  {
    reduceDown(newA, i);
  }
  // Backward Elimination
  for(int i=newA.getNumRows()-2; i >= 0; i--)
  {
    reduceUp(newA, i);
  }
  // Solve for x
  for(int i=0; i < x.getSize(); i++)
  {
    x[i] = newA(i,newA.getNumCols()-1) / newA(i,i);
  }
  
  return x;
}


template<class T>
void GaussianElimination<T>::reduceDown(Matrix<T>& A, int start)
{
  double coeff;
  float tolerance = 0.01;
  T pivot = A(start-1,start-1);
  if( pivot < tolerance && pivot > -tolerance ) swap(A, start-1, start-1);
  for(int i=start; i < A.getNumRows(); i++)
  {
    coeff = -(A(i,start-1) / A(start-1,start-1));
    for(int j=0; j < A.getNumCols(); j++)
    {
      A(i,j) += A(start-1,j) * coeff;
    }
  }
}


template<class T>
void GaussianElimination<T>::reduceUp(Matrix<T>& A, int start)
{
  double coeff;
  for(int i=start; i >= 0; i--)
  {
    coeff = -(A(i,start+1) / A(start+1,start+1));
    for(int j=0; j < A.getNumCols(); j++)
    {
      A(i,j) += A(start+1,j) * coeff;
    }
  }
}


template<class T>
void GaussianElimination<T>::swap(Matrix<T>& A, int row, int col)
{
  Vector<T> column;
  column = A.getColumn(col);
  T max = 0;
  int maxIndex;
  for(int i=row; i < A.getNumRows(); i++)
  {
    if( abs(column[i]) > max )
    {
      max = column[i];
      maxIndex = i;
    }
  }
  A.swapRows(row, maxIndex);
}