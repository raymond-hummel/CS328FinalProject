/*
  Filename:   Matrix.hpp
  Author:     Raymond Hummel
  Date:       4/24/2014
  Purpose:    Contains the implementation of the Matrix class
*/


template<class T>
Matrix<T>::Matrix(int n):numRows(0), numCols(0), head(NULL)
{
  setSize(n,n);
}


template<class T>
Matrix<T>::Matrix(int rows, int cols):numRows(0), numCols(0), head(NULL)
{
  setSize(rows,cols);
}


template<class T>
Matrix<T>::Matrix(const Matrix<T>& original):numRows(0), numCols(0), head(NULL)
{
  copy(original);
}

/*
template<class T>
Matrix<T>::Matrix(const MatrixBase<T>& original):numRows(0), numCols(0), head(NULL)
{
  copy(original);
}
*/

template<class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs)
{
  if(head != rhs.head)
  {
    copy(rhs);
  }
  return *this;
}


template<class T>
MatrixBase<T>& Matrix<T>::operator=(const MatrixBase<T>& rhs)
{
  if(&rhs != this)
  {
    const int row = rhs.getNumRows();
    const int col = rhs.getNumCols();
    if(row != getNumRows()) throw SizeError(row,"operator= row");
    if(col != getNumCols()) throw SizeError(col,"operator= col");
    for(int i=0; i < row; i++)
    {
      for(int j=0; j < col; j++)
      {
        this->operator()(i,j) = rhs(i,j);
      }
    }
  }
  return *this;
}


template<class T>
T& Matrix<T>::operator()(int row, int col)
{
  if(row < 0 || row >= getNumRows()) throw RangeError(row,"operator(): row");
  if(col < 0 || col >= getNumCols()) throw RangeError(col,"operator(): col");
  return head[row][col];
}


template<class T>
const T& Matrix<T>::operator()(int row, int col) const
{
  if(row < 0 || row >= getNumRows()) throw RangeError(row,"operator(): const row");
  if(col < 0 || col >= getNumCols()) throw RangeError(col,"operator(): const col");
  return head[row][col];
}



template<class T>
MatrixBase<T>& Matrix<T>::operator+=(const MatrixBase<T>& rhs)
{
  int rows = getNumRows();
  int cols = getNumCols();
  if( rows != rhs.getNumRows() ) throw SizeError(rows, "operator+= row");
  if( cols != rhs.getNumCols() ) throw SizeError(cols, "operator+= col");
  for(int i=0; i < rows; i++)
  {
    for(int j=0; j < cols; j++)
    {
      operator()(i,j) = operator()(i,j) + rhs(i,j);
    }
  }
  return *this;
}


template<class T>
MatrixBase<T>& Matrix<T>::operator-=(const MatrixBase<T>& rhs)
{
  int rows = getNumRows();
  int cols = getNumCols();
  if( rows != rhs.getNumRows() ) throw SizeError(rows, "operator-= row");
  if( cols != rhs.getNumCols() ) throw SizeError(cols, "operator-= col");
  for(int i=0; i < rows; i++)
  {
    for(int j=0; j < cols; j++)
    {
      operator()(i,j) = operator()(i,j) - rhs(i,j);
    }
  }
  return *this;
}


template<class T>
MatrixBase<T>& Matrix<T>::operator*=(const T& rhs)
{
  for(int i=0; i < getNumRows(); i++)
  {
    for(int j=0; j < getNumCols(); j++)
    {
      operator()(i,j) = operator()(i,j) * rhs;
    }
  }
  return *this;
}


template<class T>
MatrixBase<T>& Matrix<T>::operator*=(const MatrixBase<T>& rhs)
{
  if( getNumCols() != rhs.getNumRows() ) throw SizeError(getNumCols(), "operator*= matrix");
  MatrixBase<T>* retVal = new Matrix<T>(getNumRows(), rhs.getNumCols());
  for(int i=0; i < getNumRows(); i++)
  {
    for(int j=0; j < rhs.getNumCols(); j++)
    {
      retVal->operator()(i,j) = getRow(i) * rhs.getColumn(j);
    }
  }
  *this = *retVal;
  delete retVal;
  return *this;
}


template<class T>
Vector<T> Matrix<T>::operator*(const Vector<T>& rhs) const
{
  if( getNumRows() != rhs.getSize() ) throw SizeError(rhs.getSize(), "operator*= vector");
  Vector<T> retVal(getNumRows());
  for(int i=0; i < getNumRows(); i++)
  {
    retVal[i] = getRow(i) * rhs;
  }
  return retVal;
}


template<class T>
Vector<T> Matrix<T>::getColumn(int colIndex) const
{
  if(colIndex < 0 || colIndex >= getNumCols()) { throw RangeError(colIndex,"getColumn"); }
  Vector<T> retVal( getNumRows() );
  for(int i=0; i < getNumRows(); i++)
  {
    retVal[i] = operator()(i,colIndex);
  }
  return retVal;
}


template<class T>
void Matrix<T>::addColumn(const Vector<T>& newCol)
{
  if(newCol.getSize() != numRows) throw SizeError(newCol.getSize());
  Vector<T> temp(numCols + 1);
  for(int i=0; i < numRows; i++)
  {
    for(int j=0; j < numCols; j++)
    {
      temp[j] = head[i][j];
    }
    temp[numCols] = newCol[i];
    head[i].setSize(numCols + 1);
    head[i] = temp;
  }
  numCols++;
}


template<class T>
Vector<T> Matrix<T>::getRow(int rowIndex) const
{
  if(rowIndex < 0 || rowIndex >= getNumCols()) { throw RangeError(rowIndex,"getRow"); }
  Vector<T> retVal( getNumCols() );
  for(int i=0; i < getNumCols(); i++)
  {
    retVal[i] = operator()(rowIndex,i);
  }
  return retVal;
}


template<class T>
bool Matrix<T>::isDiagonallyDominant() const
{
  for(int i=0; i < getNumCols(); i++)
  {
    T sum = 0;
    for(int j=0; j < getNumRows(); j++)
    {
      if(j != i)
      {
        sum += abs( operator()(i,j) );
      }
    }
    if( sum > abs( operator()(i,i) ) ) return false;
  }
  return true;
}


template<class T>
Matrix<T> Matrix<T>::transpose() const
{
  Matrix<T> retVal(getNumCols(), getNumRows());
  for(int i=0; i < getNumRows(); i++)
  {
    retVal.head[i] = getColumn(i);
  }
  return retVal;
}


template<class T>
void Matrix<T>::swapRows(int rowIndex1, int rowIndex2)
{
  Vector<T> temp(head[rowIndex1]);
  head[rowIndex1] = head[rowIndex2];
  head[rowIndex2] = temp;
}


template<class T>
void Matrix<T>::setSize(int rows, int cols)
{
  if(numRows != rows || numCols != cols)
  {
    if(rows < 0) throw SizeError(rows, "setSize: row");
    if(cols < 0) throw SizeError(cols, "setSize: col");
    delete [] head;
    numRows = rows;
    numCols = cols;
    head = new Vector<T>[numRows];
    for(int i=0; i<numRows; i++)
    {
      head[i].setSize(numCols);
    }
  }
}


template<class T>
void Matrix<T>::copy(const MatrixBase<T>& a)
{
  setSize(a.getNumRows(), a.getNumCols());
  for(int i=0; i < a.getNumRows(); i++)
  {
    for(int j=0; j < a.getNumCols(); j++)
    {
      head[i][j] = a(i,j);
    }
  }
}
















