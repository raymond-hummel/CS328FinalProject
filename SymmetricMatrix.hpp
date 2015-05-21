/*
  Filename:   SymmetricMatrix.hpp
  Author:     Raymond Hummel
  Date:       4/22/2014
  Purpose:    Contains the implementation of the SymmetricMatrix class
*/


template<class T>
SymmetricMatrix<T>::SymmetricMatrix(const int& n)
{
  if( n < 0 ) throw SizeError(n, "size constructor");
  numRows = n;
  numCols = n;
  head = new Vector<T>[numRows];
  for(int i=0; i<numCols; i++)
  {
    head[i].setSize(numCols-i);
  }
}


template<class T>
SymmetricMatrix<T>::SymmetricMatrix(const SymmetricMatrix<T>& original):Matrix<T>()
{
  numRows = original.numRows;
  numCols = original.numCols;
  head = new Vector<T>[numRows];
  for(int i=0; i < numRows; i++)
  {
    head[i].setSize(numCols-i);
  }
  copy(original);
}


template<class T>
SymmetricMatrix<T>::~SymmetricMatrix()
{
  delete [] head;
}


template<class T>
T& SymmetricMatrix<T>::operator()(int row, int col)
{
  if(row < 0 || row >= numRows) throw RangeError(row, "operator() row");
  if(col < 0 || col >= numCols) throw RangeError(col, "operator() col");
  if(row > col) // swap row and col if on wrong side of matrix
  {
    int temp = row;
    row = col;
    col = temp;
  }
  return head[row][col-row];
}


template<class T>
const T& SymmetricMatrix<T>::operator()(int row, int col) const
{
  if(row < 0 || row >= numRows) throw RangeError(row, "const operator() row");
  if(col < 0 || col >= numCols) throw RangeError(col, "const operator() con");
  if(row > col) // swap row and col if on wrong side of matrix
  {
    int temp = row;
    row = col;
    col = temp;
  }
  return head[row][col-row];
}


template<class T>
SymmetricMatrix<T>& SymmetricMatrix<T>::operator=(const SymmetricMatrix<T>& rhs)
{
  if( head != rhs.head )
  {
    setSize(rhs.getNumRows(), rhs.getNumCols());
    copy(rhs);
  }
  return *this;
}


template<class T>
MatrixBase<T>& SymmetricMatrix<T>::operator+=(const MatrixBase<T>& rhs)
{
  if( numRows != rhs.getNumRows() ) throw SizeError(numRows, "operator += row");
  if( numCols != rhs.getNumCols() ) throw SizeError(numCols, "operator += col");
  if( !isSymmetric(rhs) ) throw "Matrix must be symmetric";
  for(int i=0; i < numRows; i++)
  {
    for(int j=0; j <= i; j++)
    {
      operator()(i,j) += rhs(i,j);
    }
  }
  return *this;
}


template<class T>
MatrixBase<T>& SymmetricMatrix<T>::operator-=(const MatrixBase<T>& rhs)
{
  if( numRows != rhs.getNumRows() ) throw SizeError(numRows, "operator -= row");
  if( numCols != rhs.getNumCols() ) throw SizeError(numCols, "operator -= col");
  if( !isSymmetric(rhs) ) throw "Matrix must be symmetric";
  for(int i=0; i < numRows; i++)
  {
    for(int j=0; j <= i; j++)
    {
      operator()(i,j) -= rhs(i,j);
    }
  }
  return *this;
}


template<class T>
MatrixBase<T>& SymmetricMatrix<T>::operator*=(const T& rhs)
{
  for(int i=0; i < numRows; i++)
  {
    head[i] = head[i] * rhs;
  }
  return *this;
}


template<class T>
MatrixBase<T>& SymmetricMatrix<T>::operator*=(const MatrixBase<T>& rhs)
{
  if( numCols != rhs.getNumRows() ) throw SizeError(numCols, "operator *= matrix");
  if( !isSymmetric(rhs) ) throw "Matrix must be symmetric";
  SymmetricMatrix<T> temp(numRows);
  for(int i=0; i < numRows; i++)
  {
    for(int j=0; j < rhs.getNumCols(); j++)
    {
      temp(i,j) = getRow(i) * rhs.getColumn(j);//TODO: check that this all makes sense
    }
  }
  *this = temp;
  return *this;
}


template<class T>
Vector<T> SymmetricMatrix<T>::operator*(const Vector<T>& rhs) const
{
  if( numCols != rhs.getSize() ) throw SizeError(numCols, "operator * vector");
  Vector<T> retVal(numRows);
  for(int i=0; i < numRows; i++)
  {
    retVal[i] = head[i] * rhs;
  }
  return retVal;
}


template<class T>
Vector<T> SymmetricMatrix<T>::getColumn(int colIndex) const
{
  if(colIndex < 0 || colIndex >= numCols) throw RangeError(colIndex, "getColumn");
  Vector<T> column(numRows);
  for(int i=0; i < numRows; i++)
  {
    column[i] = operator()(i,colIndex);
  }
  return column;
}


template<class T>
Vector<T> SymmetricMatrix<T>::getRow(int rowIndex) const
{
  if(rowIndex < 0 || rowIndex >= numRows) throw RangeError(rowIndex, "getRow");
  Vector<T> row(numCols);
  for(int i=0; i < numCols; i++)
  {
    row[i] = operator()(rowIndex, i);
  }
  return row;
}


template<class T>
int SymmetricMatrix<T>::getNumRows() const
{
  return numRows;
}


template<class T>
int SymmetricMatrix<T>::getNumCols() const
{
  return numCols;
}


template<class T> 
void SymmetricMatrix<T>::setSize(int rows, int cols)
{
  if(numRows != rows || numCols != cols)
  {
    if(rows < 0) throw SizeError(rows, "setSize row");
    if(cols < 0) throw SizeError(cols, "setSize col");
    if(rows != cols) throw SizeError(cols, "setSize square");
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
bool isSymmetric(const MatrixBase<T>& matrix)
{
  if(matrix.getNumRows() != matrix.getNumCols()) return false;
  
  for(int i=0; i < matrix.getNumRows(); i++)
  {
    for(int j=0; j <= i; j++)
    {
      if(matrix(i,j) != matrix(j,i)) return false;
    }
  }
  return true;
}


template<class T>
void SymmetricMatrix<T>::copy(const SymmetricMatrix<T>& a)
{
  for(int i=0; i < numRows; i++)
  {
    head[i] = a.head[i]; // copy assign throws SizeError
  }
}




