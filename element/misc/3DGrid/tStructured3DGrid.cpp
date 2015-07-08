#include "element/misc/3DGrid/tStructured3DGrid.h"

#include "element/point/tPoint.h"

#include "classes/utils.h"

//------------------------------------------------------------------------------------------------

tStructured3DGrid::tStructured3DGrid(void *theowner): tStructuredAbstractGrid(theowner)
{
  ni_ = 0;
  nj_ = 0;
  nk_ = 0;
}
//------------------------------------------------------------------------------------------------

tStructured3DGrid::~tStructured3DGrid()
{
}
//------------------------------------------------------------------------------------------------

iElement* tStructured3DGrid::intrface(void)
{
  if (iface == NULL){
    iface = new iStructured3DGrid(this);
  }
  return iface;
}
//------------------------------------------------------------------------------------------------

int tStructured3DGrid::ni(void)
{
  update();
  return ni_;
};
//------------------------------------------------------------------------------------------------

int tStructured3DGrid::nj(void)
{
  update();
  return nj_;
};
//------------------------------------------------------------------------------------------------

int tStructured3DGrid::nk(void)
{
  update();
  return nk_;
};
//------------------------------------------------------------------------------------------------

void tStructured3DGrid::setDot(int i, int j, int k, tVector value)
{
  int index = ijk(i,j,k);
  if (dots.at(index)){
    dots.at(index)->releaseOwner(this);
  }
  dots.setAt(index, new tPoint(this, value));
}
//------------------------------------------------------------------------------------------------

void tStructured3DGrid::clearDots(void)
{
  int i,j,k;
  // Liste leeren und neue NULL-Liste erstellen.
  for (int i=0;i<dots.count();i++){
    tDot* d = dots.at(i);
    if (d){
      dots.at(i)->releaseOwner(this);
    }
  }
  dots.clear();
  for(k=0;k<nk_;k++){
    for(j=0;j<nj_;j++){
      for(i=0;i<ni_;i++){
        dots.append(NULL);
      }
    }
  }
}
//------------------------------------------------------------------------------------------------

tDot* tStructured3DGrid::gridAt(int i, int j, int k)
{
  update();
  i = min(i, ni_-1); i = max(i,0);
  j = min(j, nj_-1); j = max(j,0);
  k = min(k, nk_-1); k = max(k,0);

  return dots.at(ijk(i,j,k));
//  return dots.at(k*ni_*nj_ + j*ni_ + i);
}
//------------------------------------------------------------------------------------------------
void tStructured3DGrid::setFaceNames(tList<QString> names){
  faceNames_ = names;
  while (faceNames_.count() < 6){
    faceNames_.append("");
  }
}
//------------------------------------------------------------------------------------------------

tList<QString> tStructured3DGrid::faceNames(void){
  tList<QString> names = faceNames_;
  while (names.count() < 6){
    names.append("");
  }
  return names;
};
//------------------------------------------------------------------------------------------------
