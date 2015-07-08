

#include "classes/tSolve.h"
#include <stdlib.h>
#include <math.h>
#define max(a, b)  (((a) > (b)) ? (a) : (b))


//---------------------------------------------------------------------------
tJSolve::tJSolve(const int n, const int nn)
 : tSolve(n, nn)
{

  MATRIX = (double**)calloc(N,sizeof(double*));
  for (int i=0;i<N;i++)
    MATRIX[i] = (double*)calloc(N,sizeof(double));

  RHS = (double*)calloc(N*nRHS,sizeof(double));
  x = (double*)calloc(N*nRHS,sizeof(double));

  nStoredSolutions = 0;
  storedSolution = NULL;
}

//---------------------------------------------------------------------------
tJSolve::~tJSolve()
{
  int n;
  for (n=0;n<N;n++)
    free(MATRIX[n]);
  free(MATRIX);
  free(RHS);
  free(x);
  MATRIX = NULL;
  RHS = NULL;
  x = NULL;

  for (n=0;n<nStoredSolutions;n++){
  	free(storedSolution[n]);
  }
  free (storedSolution);
}
//---------------------------------------------------------------------------

double tJSolve::getRHS(const int row, const int column)
{
  return RHS[column*N+row];
}
//---------------------------------------------------------------------------

void tJSolve::setRHS(const int row, const double value, const int column)
{
  RHS[column*N+row] = value;
}
//---------------------------------------------------------------------------

double tJSolve::getX(const int row, const int column)
{
  return x[column*N+row];
}
//---------------------------------------------------------------------------

void tJSolve::setX(const int row, const double value,const int column)
{
  x[column*N+row] = value;
}
//---------------------------------------------------------------------------

double tJSolve::solve(void)
{
// L�sungsverfahren nach Gausselimination
  int i,I,j;
  double f;
  double **a;
  I=0;

  // erstellen einer Kopie von MATRIX, die beim Loesen modifiziert wird.
  // Speicher:
  a = (double**)malloc(N*sizeof(double*));
  for (i=0;i<N;i++)
    a[i] = (double*)malloc(N*sizeof(double));
  // kopieren von Matrix in die Zwischenablage "a"
  for (i=0;i<N;i++){
    for (j=0;j<N;j++){
      a[i][j] = MATRIX[i][j];
    }
    for (j=0;j<nRHS;j++){
      x[j*N+i] = RHS[j*N+i];
    }
  }

  f = 0.;
  for(i=0;i<N;i++){
    f = 1./a[i][i];
    if (a[i][i]==0){
      // ist ein Element auf der Hauptdiagonalen = 0, werden zwei Zeilen vertauscht.
      int ii;
      f = 0.;
      ii = i;
      // eine passende Zeile suchen
      for (I=i+1;I<N;I++){
        if (fabs(a[I][i])>fabs(f)){
          f = fabs(a[I][i]);
          ii = I;
        }
      }
      if (f!=0){
        // Zeilen entsprechend vertauschen
        for (j=i;j<N;j++){
          f = a[i][j];
          a[i][j] = a[ii][j];
          a[ii][j] = f;
        }
        for (j=0;j<nRHS;j++){
          f = x[j*N+i];
          x[j*N+i] = x[j*N+ii];
          x[j*N+ii] = f;
        }
        f = 1./a[i][i];
      } else {
        // es konnte keine Zeile != 0 gefunden werden.
        f = 0.;
        return 0;
        //Rang der Matrix ist zu klein.
      }
    }
    for (j=i;j<N;j++){
      a[i][j] *=f;   //Werte der aktuellen Zeile normieren.
    }
    for (j=0;j<nRHS;j++){
      x[j*N+i] *= f;  //Rechten Seite normieren.
    }

    for(I=0;I<N;I++){
      if (I!=i && a[I][i]!=0){
        f = a[I][i];  //Eliminieren des jeweils i-ten Elements in jeder Spalte.
        for (j=i;j<N;j++){
          a[I][j] -= f*a[i][j];
        }
        for (j=0;j<nRHS;j++){
          x[j*N+I] -= f*x[j*N+i];
        }
      }
    }
  }


  //saveToFile("c:\\test.txt", a, x);

  //Speicher freigeben
  for (i=0;i<N;i++)
    free(a[i]);
  free (a);

  return f;

}
//-----------------------------------------------------------------------------

double tJSolve::solveSimple(void)
{
// L�sungsverfahren nach Gausselimination
  int i,j,k, l;
  double P, P2;
  double **a, *b;

  // erstellen einer Kopie von MATRIX, die beim Loesen modifiziert wird.
  // Speicher:
  a = (double**)malloc(N*sizeof(double*));
  b = (double*)malloc((nRHS*N)*sizeof(double));
  for (i=0;i<N;i++){
    a[i] = (double*)malloc(N*sizeof(double));
  }
  // kopieren von Matrix in die Zwischenablage "a"
  for (i=0;i<N;i++){
    for (j=0;j<N;j++){
      a[i][j] = MATRIX[i][j];
    }
    for (j=0;j<nRHS;j++){
      b[j*N+i] = RHS[j*N+i];
    }
  }
  saveToFile("c:\\test_start.txt", a, b);

  //! INITIALIZE THE G VECTOR TO ALL ZEROES
  for (i=0;i<N;i++){
   x[i]=0;
  }

  //! CONVERT COEFFICIENT MATRIX TO
  //! UPPER TRIANGULAR FORM
  for (i=0;i<N;i++){
    if(fabs(a[i][i]) < 0.0000001){
//      5  IF(ABS(A(I,I)).LT.0.0000001) GOTO 9
//      int palim;
      saveToFile("c:\\test_failure.txt", a, b);
//      palim= -1;
    }

    P = a[i][i]; // P=A(I,I)
    for (j=i;j<N;j++){//DO J=I,N
      a[i][j] = a[i][j] / P; //A(I,J)=A(I,J)/P
    } // END DO
    for (k=0;k<nRHS;k++){
      b[k*N+i] = b[k*N+i] / P;
    }

    for (k=i+1;k<N;k++){ //DO K=I+1,N-1
      P2 = a[k][i]; //P2=A(K,I)
      for (l=i;l<N;l++){ //DO L=I,N
        a[k][l] = a[k][l]-P2*a[i][l];// A(K,L)=A(K,L)-P2*A(I,L)
      }//END DO
      for (l=0;l<nRHS;l++){
        b[l*N+k] = b[l*N+k] - P2 *b[l*N+i];
      }
    }//    END DO
  }
  saveToFile("c:\\test.txt", a, b);

  //! BACK SUBSTITUTE TRIANGULARIZED MATRIX T0 GET
  //! VALUES OF SOLUTION VECTOR

  for (i=N-1;i>=0;i--){//DO I=N-1,1,-1
    x[i] = b[i];//G(I)=A(I,N)
    for (j=0;j<N;j++){ //DO J=1,N-1
      //a[i][i] = 0.;//A(I,I)=0
      if (j!=i){
        x[i] = x[i] - a[i][j]*x[j]; //G(I)=G(I)-A(I,J)*G(J)
      }
    } //END DO
  } //END DO



  saveToFile("c:\\test.txt", a, b);

  //Speicher freigeben
  for (i=0;i<N;i++)
    free(a[i]);
  free (a);

  return 0.;

}
//-----------------------------------------------------------------------------

int tJSolve::solveGS(const double eps, const int maxIterations)
{
// Gauss Seidel Verfahren
  int i,j,k,iteration;

  double err,s,xx,relax;
  double **a, *b, *x0;

  if (eps <= 0.)
    return -1;

  relax = 1.3;

  // Speicher fuer eine Kopie von MATRIX und RHS anlegen
  a = (double**)malloc(N*sizeof(double*));
  b = (double*)malloc(N*nRHS*sizeof(double));
  x0 = (double*)malloc(N*nRHS*sizeof(double));

  for (i=0;i<N;i++)
    a[i] = (double*)malloc(N*sizeof(double));

  for (i=0;i<N;i++){
    //Kopie von MATRIX und RHS erzeugen
    if (MATRIX[i][i] != 0.){
      xx = MATRIX[i][i];
      for (j=0;j<N;j++){
        a[i][j] = MATRIX[i][j]/xx;
      }
      for (j=0;j<nRHS;j++){
        b[j*N+i] = RHS[j*N+i]/xx;
      }
    } else {
      //Ein Element auf der Hauptdiagonalen ist null
      for (k=0; MATRIX[k][i]== 0. && k<N;k++);
      //Eine Zeile wird subtrahiert, so dass die Hauptdiagonale nicht mehr null ist.
      if (k<N){
        xx = MATRIX[k][i];
        for (j=0;j<N;j++){
          a[i][j] = (MATRIX[i][j] + MATRIX[k][j])/xx;
        }
        for (j=0;j<nRHS;j++){
          b[j*N+i] = (RHS[j*N+i] + RHS[j*N+k])/xx;
        }
      } else {
        return -1;
      }
    }
  }

  iteration = 0;
  do {
    err = 0.;
    for (k=0;k<nRHS*N;k+=N){
      for (i=0;i<N;i++){
        s = 0.;
        for (j=0;   j<i; j++) s += a[i][j]*x[k+j];
        for (j=i+1; j<N; j++) s += a[i][j]*x[k+j];
        x0[k+i] = x[k+i];
        x[k+i] = b[k+i]-s;
        err = max(fabs(x[k+i]-x0[k+i]),double(err));
      }
    }
    iteration++;
    if (err > eps){
      for (k=0;k<nRHS*N;k+=N){
        for (i=0;i<N;i++){
          x[k+i] = (x[k+i]-x0[k+i])*relax + x0[k+i];
          if (x[k+i]*x0[k+i] < 0){
            x[k+i] = (x[k+i]+x0[k+i])*0.5;
          }
        }
      }
    }
  } while (err > eps && isfinite(err) && (iteration<maxIterations || maxIterations<=0));

  for (i=0;i<N;i++)
    free(a[i]);
  free(a);
  free(b);
  free(x0);

  if (!isfinite(err)){
  	return -1;
  } else {
  	return iteration;
  }

}
//-----------------------------------------------------------------------------

bool tJSolve::saveToFile(const char *fileName,double** a,double* b){
  int i,j;
  FILE *file;

  file = fopen(fileName,"wt");

  if (!a){
    a = MATRIX;
  }
  if (!b){
    b = RHS;
  }

  if (file){
    for (i=0;i<N;i++){
      for (j=0;j<N;j++){
        fprintf(file,"%f\t",a[i][j]);
      }
      if (nRHS>1){
        fprintf(file,"\n");
      }
      for (j=0;j<nRHS;j++){
        fprintf(file,"x[%i]:\t%f\t",j,x[j*N+i]);
        fprintf(file,"RHS[%i]:\t%f\t",j,b[j*N+i]);
        fprintf(file,"\n");
      }
    }
    fclose(file);
    return true;
  } else {
    return false;
  }
}
//-----------------------------------------------------------------------------
bool tJSolve::saveToFileFloat(const char *fileName,float** a,float* b){
  int i,j;
  FILE *file;

  file = fopen(fileName,"wt");

//  if (!a){
//    a = MATRIX;
//  }
//  if (!b){
//    b = RHS;
//  }

  if (file){
    for (i=0;i<N;i++){
      for (j=0;j<N;j++){
        fprintf(file,"%f\t",a[i][j]);
      }
      if (nRHS>1){
        fprintf(file,"\n");
      }
      for (j=0;j<nRHS;j++){
        fprintf(file,"x[%i]:\t%f\t",j,x[j*N+i]);
        fprintf(file,"RHS[%i]:\t%f\t",j,b[j*N+i]);
        fprintf(file,"\n");
      }
    }
    fclose(file);
    return true;
  } else {
    return false;
  }
}
//-----------------------------------------------------------------------------

int tJSolve::storeSolution(const int index)
{
	int i, idx;
	if (index<0 || index >=nStoredSolutions){
		storedSolution = (double**)realloc(storedSolution, (nStoredSolutions+1)*sizeof(double*));
		storedSolution[nStoredSolutions] = (double*)malloc(N*nRHS*sizeof(double));
		idx = nStoredSolutions;
		nStoredSolutions ++;
	}
	for (i=0;i<N*nRHS;i++){
		storedSolution[idx][i]= x[i];
	}
	return (idx++);
}
//-----------------------------------------------------------------------------

bool tJSolve::reloadSolution(const int index)
{
	int i;
	if (index < nStoredSolutions){
		for (i=0;i<N*nRHS;i++){
			x[i]=storedSolution[index][i];
		}
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#ifdef BUILD_WITH_GSL

tGSLSolve::tGSLSolve(const int n, const int nrhs)
: tSolve(n, nrhs)
{
  for (int i=0;i<nrhs; i++){
    RHS.append( gsl_vector_calloc(N) );
    x.append( gsl_vector_calloc(N) );
  }

  MATRIX = gsl_matrix_calloc(N,N);

}
//-----------------------------------------------------------------------------

tGSLSolve::~tGSLSolve()
{
  for (int i=0;i<RHS.count();i++){
    gsl_vector_free(RHS.at(i));
    gsl_vector_free(x.at(i));
  }
  gsl_matrix_free(MATRIX);

  for (std::map< int, tList<gsl_vector*>* >::iterator soluIter = storedSolution.begin();
       soluIter != storedSolution.end();
       soluIter ++){
    for (int i=0; i<soluIter->second->count(); i++){
      gsl_vector_free(soluIter->second->at(i));
    }
  }


}
//-----------------------------------------------------------------------------

void tGSLSolve::solve(void)
{
  solveHouseholder();
}
//-----------------------------------------------------------------------------

int tGSLSolve::solveLU(void)
{
  int s;
  gsl_permutation * p = gsl_permutation_alloc (N);
  gsl_linalg_LU_decomp(MATRIX, p, &s);
  for (int i=0;i<RHS.count() && i<x.count(); i++){
    gsl_linalg_LU_solve (MATRIX, p, RHS.at(i), x.at(i));
  }
  return s;
}
//-----------------------------------------------------------------------------

void tGSLSolve::solveHouseholder(void)
{
  gsl_matrix* tmp =  gsl_matrix_calloc(N,N);
  gsl_matrix_memcpy(tmp, MATRIX);
  for (int i=0;i<RHS.count() && i<x.count(); i++){
    gsl_linalg_HH_solve (tmp, RHS.at(i), x.at(i));
  }
}
//-----------------------------------------------------------------------------

int tGSLSolve::solveGaussSeidel(const double eps,const  int maxIterations)
{
  tJSolve lgs(N);
  for (int i=0;i<N;i++){
    for (int j=0;j<N; j++){
      lgs.setMATRIX(i,j,getMATRIX(i,j));
    }
    for (int k=0;k<nRHS;k++){
      lgs.setRHS(i, getRHS(i,k), k);
      lgs.setX(i, getX(i,k), k);
    }
  }


  int iterations =  lgs.solveGS(eps, maxIterations);

  // x zurueckkopieren
  for (int i=0;i<N;i++){
    for (int k=0;k<nRHS;k++){
      setX(i, lgs.getX(i,k), k);
    }
  }

  return iterations;
}

//-----------------------------------------------------------------------------

void tGSLSolve::setMATRIX(const int row, const int column, const double value)
{
  gsl_matrix_set(MATRIX,row,column,value);
}
//-----------------------------------------------------------------------------

void tGSLSolve::setRHS(const int row, const double value, const int iRHS)
{
  if (iRHS < nRHS && row < N){
    gsl_vector_set(RHS.at(iRHS), row, value);
  }
}
//-----------------------------------------------------------------------------

void tGSLSolve::setX(const int row, const double value, const int iRHS)
{
  if (iRHS < nRHS && row < N){
    gsl_vector_set(x.at(iRHS), row, value);
  }
}
//-----------------------------------------------------------------------------

double tGSLSolve::getMATRIX(const int row, const int column)
{
  return (gsl_matrix_get(MATRIX, row, column));
}
//-----------------------------------------------------------------------------

double tGSLSolve::getRHS(const int row, const int iRHS)
{
  if (iRHS < nRHS && row < N){
    return (gsl_vector_get(RHS.at(iRHS),row));
  } else {
    return 0.;
  }
}
//-----------------------------------------------------------------------------

double tGSLSolve::getX(const int row, const int iRHS)
{
  if (iRHS < nRHS && row < N){
    return (gsl_vector_get(x.at(iRHS),row));
  } else {
    return 0.;
  }
}
//-----------------------------------------------------------------------------

int tGSLSolve::storeSolution(const int index)
{

  if (storedSolution.find(index) == storedSolution.end()){
    storedSolution[index] = new tList<gsl_vector*>;
  }
  tList<gsl_vector*>* list = storedSolution[index];

  list->clear();
  for (int i=0; i<nRHS; i++){
    gsl_vector* vec = gsl_vector_alloc(N);
    gsl_vector_memcpy(vec, x.at(i));
    list->append(vec);
  }

  return (index);
}
//-----------------------------------------------------------------------------

bool tGSLSolve::reloadSolution(const int index)
{
  if (storedSolution.find(index) != storedSolution.end()){
    for (int i=0; i<nRHS; i++){
      gsl_vector_memcpy(x.at(i), storedSolution[index]->at(i));
    }
    return true;
  } else {
    return false;
  }

}
//-----------------------------------------------------------------------------

bool tGSLSolve::saveToFile(const char *fileName)
{
  int i,j;
  FILE *file;

  file = fopen(fileName,"wt");

  if (file){
    for (i=0;i<N;i++){
      for (j=0;j<N;j++){
        fprintf(file,"%f\t",getMATRIX(i,j));
      }
      if (nRHS>1){
        fprintf(file,"\n");
      }
      for (j=0;j<nRHS;j++){
        fprintf(file,"x[%i]:\t%f\t",j,getX(i,j));
        fprintf(file,"RHS[%i]:\t%f\t",j,getRHS(i,j));
        fprintf(file,"\n");
      }
    }
    fclose(file);
    return true;
  } else {
    return false;
  }
}

#endif

