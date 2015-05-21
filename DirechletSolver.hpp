/*
  Filename:   DirechletSolver.hpp
  Author:     Raymond Hummel
  Date:       5/8/2014
  Purpose:    Contains the declaration of the DirechletSolver class
*/


template<class T>
void DirechletSolver<T>::setN(int newN)
{
  N = newN;
  int numMeshPoints = (N-1)*(N-1);
  MatrixGenerator gen(N);
  A = gen.getMatrix();
  x.setSize(numMeshPoints);
  b.setSize(numMeshPoints);
  buildVector();
}


template<class T>
Vector<double> DirechletSolver<T>::operator()()
{
  //SteepestDescent<double> solver1;
  //GaussianElimination<double> solver2;
  GaussSeidel<double> solver3;
  
  //cout << "steepest descent: " << endl << solver1(A,b) << endl;
  //cout << "gauss-seidel: " << endl << solver3(A,b) << endl;
  x = solver3(A,b);
  
  return x/* * (1.0/N)*/;
}


template<class T>
void DirechletSolver<T>::buildVector()
{
  double h = 1.0/N;
  double x = 0;
  double y = 0;
  bool up, down, right, left;
  
  for(int row=0; row < b.getSize(); row++)
  {
    x += h;
    if(0 == row%(N-1)) 
    {
      x = h;
      y += h;
    }
    up = (y == 1-h);
    down = (y == h);
    right = (x == 1-h);
    left = (x == h);
    
    b[row] = 0;
    if(up) b[row] += U(x,y+h);
    if(down) b[row] += U(x,y-h);
    if(right) b[row] += U(x+h,y);
    if(left) b[row] += U(x-h,y);
  }
  b = b * h;
}








