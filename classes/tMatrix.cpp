
#include "tMatrix.h"
#include "classes/tSolve.h"

#include <malloc.h>

#define dataIJ data[i*fnj+j] //j-tes Element aus i-ter Zeile.

tMatrix::tMatrix() {
  init();
}
//-----------------------------------------------------------------------------

tMatrix::tMatrix(int ni, int nj) {
  init();
  setSize(ni,nj);
}
//-----------------------------------------------------------------------------

tMatrix::~tMatrix() {
  setSize(0,0);
}

tMatrix& tMatrix::operator= (const tMatrix& rhs)
{
  int i, j;
  setSize(rhs.ni(), rhs.nj());
  for (i=0;i<fni;i++){
    for (j=0;j<fnj;j++){
      dataIJ = rhs.at(i,j);
    }
  }
  return *this;
}

//-----------------------------------------------------------------------------

int tMatrix::ni(void) const
{
  return fni;
};
//-----------------------------------------------------------------------------

int tMatrix::nj(void) const
{
  return fnj;
};
//-----------------------------------------------------------------------------

void tMatrix::init(void)
{
  data = NULL;
  fni = 0;
  fnj = 0;
}
//-----------------------------------------------------------------------------

void tMatrix::clear(void)
{
  int i,j;
  for (i=0;i<fni;i++){
    for (j=0;j<fnj;j++){
      dataIJ = 0.;
    }
  }
}
//-----------------------------------------------------------------------------

void tMatrix::setSize(const int ni, const int nj)
{
  data = (tReal*)realloc(data,sizeof(tReal)*ni*nj);
  fni = ni;
  fnj = nj;
  clear();
}
//-----------------------------------------------------------------------------

tReal tMatrix::at(int i, int j) const
{
  if (i>=0 && j>=0 && i<fni && j<fnj){
    return dataIJ;
  } else {
    return 0.;
  }
}
//-----------------------------------------------------------------------------

void tMatrix::setAt(int i, int j, tReal value)
{
  if (i>=0 && j>=0 && i<fni && j<fnj){
    dataIJ = value;
  }
}
//-----------------------------------------------------------------------------

tMatrix tMatrix::transpose(void)
{
  tMatrix tt(fnj,fni);
  int i,j;

  for (i=0;i<fni;i++){
    for (j=0;j<fnj;j++){
      tt.setAt(j,i,dataIJ);
    }
  }
  return tt;
}
//-----------------------------------------------------------------------------

void tMatrix::multiply(tReal value)
{
  int i,j;
  for (i=0;i<fni;i++){
    for (j=0;j<fnj;j++){
      dataIJ *= value;
    }
  }
}
//-----------------------------------------------------------------------------

tMatrix tMatrix::inverse(void)
{
  tMatrix ii;
  tJSolve *lgs;
  int i,j;
  ii.setSize(fni,fnj);
  if (fnj == fni){
    lgs = new tJSolve(fni,fni);
    for (i=0;i<fni;i++){
      for (j=0;j<fnj;j++){
        lgs->MATRIX[i][j] = dataIJ;
      }
    }
    for (j=0;j<fnj;j++){
      //RHS besetzen mit dem Vektor (0,0,...0,1,0,...0)
      for (i=0;i<fni;i++){
        if (j==i){
          lgs->RHS[j*fni+i] = 1.;
        } else {
          lgs->RHS[j*fni+i] = 0.;
        }
      }
    }
    //Loesen
    lgs->solve();
    for (j=0;j<fnj;j++){
      for (i=0;i<fni;i++){
        ii.setAt(i,j,lgs->x[j*fni+i]);
      }
    }
  }
  return ii;
}

//-----------------------------------------------------------------------------
