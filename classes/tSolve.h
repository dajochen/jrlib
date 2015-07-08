//---------------------------------------------------------------------------

#ifndef SolveH
#define SolveH
//  Die Klasse berechnet die Lösung für x in einem Gleichungsystem der Form:
//
//       Matrix        *  x  = RHS
//   |  1 2 3 . . . n |
//   | 1    .         |  |1|   |1|
//   | 2    .         |  |2|   |2|
//   | 3    .         |  |3|   |3|
//   | .    .         |* |.| = |.|
//   | .    .         |  |.|   |.|
//   | .    .         |  |.|   |.|
//   | n. A[n][3] . n |  |n|   |n|
//
#include <stdio.h>


class tSolve{
protected:

public:
  const int N,   // Groesse des Gleichungssystems
  nRHS;// Anzahl der rechten Seiten, fuer die das LGS geloest werden soll.

  tSolve(const int n, const int nrhs) : N(n),
      nRHS((((nrhs) > (1)) ? (nrhs) : (1))) {};
  virtual ~tSolve(){};


  virtual void setMATRIX(const int row, const int column, const double value) = 0;
  virtual void setRHS(const int row, const double value, const int iRHS) = 0;
  virtual void setX(const int row, const double value, const int iRHS) = 0;

  virtual double getMATRIX(const int row, const int column) = 0;
  virtual double getRHS(const int row, const int iRHS=0) = 0;
  virtual double getX(const int row, const int iRHS=0) = 0;


  virtual int storeSolution(const int index) = 0;
  virtual bool reloadSolution(const int index) = 0;


};

class tJSolve : public tSolve{
private:
  int nStoredSolutions;

public:
  double **MATRIX,*x,*RHS,**storedSolution;

  tJSolve(const int n, const int nn=1);
  virtual ~tJSolve();
  double solve(void);
  int solveGS(const double eps, const int maxIterations=-1);
  double solveSimple(void);


  bool saveToFile(const char *fileName,double** a=NULL,double* b=NULL);
  bool saveToFileFloat(const char *fileName,float** a=NULL,float* b=NULL);
  int storeSolution(int index);
  bool reloadSolution(int index);

  virtual void setMATRIX(const int row, const int column, const double value) {MATRIX[row][column] = value;}
  void setRHS(const int row, const double value, const int iRHS=0);
  void setX(const int row, const double value, const int iRHS=0);

  virtual double getMATRIX(const int row, const int column) {return MATRIX[row][column];}
  double getRHS(const int row, const int iRHS=0);
  double getX(const int row, const int iRHS=0);

};


#ifdef BUILD_WITH_GSL

#include "classes/tList.h"
#include <map>

#ifdef linux
  #include <gsl/gsl_linalg.h>
#endif

class tGSLSolve : public tSolve {
private:
  tList<gsl_vector*> RHS, x;
  std::map<int, tList<gsl_vector*>* > storedSolution;

  gsl_matrix *MATRIX;

public:
  tGSLSolve(const int n, const int nrhs=1);
  virtual ~tGSLSolve();


  void solve(void);
  int solveLU(void);
  void solveHouseholder(void);
  int solveGaussSeidel(const double eps, const int maxIterations=-1);

  virtual void setMATRIX(const int row, const int column, const double value);
  virtual void setRHS(const int row, const double value, const int iRHS=0);
  virtual void setX(const int row, const double value, const int iRHS=0);

  virtual double getMATRIX(const int row, const int column);
  virtual double getRHS(const int row, const int iRHS=0);
  virtual double getX(const int row, const int iRHS=0);

  virtual int storeSolution(const int index);
  virtual bool reloadSolution(const int index);

  virtual bool saveToFile(const char *fileName);


};
#endif // BUILD_WITH_GSL

#endif // SolveH
