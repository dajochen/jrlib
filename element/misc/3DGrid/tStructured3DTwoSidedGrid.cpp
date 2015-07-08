#include "element/misc/3DGrid/tStructured3DTwoSidedGrid.h"

#include "element/point/tPoint.h"

#include "classes/utils.h"

//------------------------------------------------------------------------------------------------

tStructured3DTwoSidedGrid::tStructured3DTwoSidedGrid(void *theowner): tStructured3DGrid(theowner)
{
  fMergeNodeTolerance = 1.0e-4;
  for (int n=0; n<2;n++){
    faces_[n] = NULL;
  }

}
//------------------------------------------------------------------------------------------------

tStructured3DTwoSidedGrid::~tStructured3DTwoSidedGrid()
{
  for (int n=0; n<2;n++){
    if (faces_[n]){
      faces_[n]->removeDependent(this);
      faces_[n] = NULL;
    }
  }
}
//------------------------------------------------------------------------------------------------

iElement* tStructured3DTwoSidedGrid::intrface(void)
{
  if (iface == NULL){
    iface = new iStructured3DTwoSidedGrid(this);
  }
  return iface;
}
//------------------------------------------------------------------------------------------------

void tStructured3DTwoSidedGrid::refresh(void)
{
//  int i,j,k;
  tReal ii,jj,kk;

//  ni_= max(niSoll_,2);
//  nj_= max(njSoll_,2);
//  nk_= max(nkSoll_,2);

  clearDots();

  // Face 1 und Face 2:
  if (faces_[0] && faces_[1]){
    for (int f=0; f<2; f++){
      int i;
      if (f==0){
        i = 0;
      } else {
        i = ni_-1;
      }
      for (int j=0; j<nj_; j++){
        jj = (double)j/(double)(nj_-1);
        for (int k=0; k<nk_; k++){
          kk = (double)k/(double)(nk_-1);

          tVector p = faces_[f]->vectorAt(jj,kk);
          int index = ijk(0,j,k);
          if (f==1 && dots.at(index) && (dots.at(index)->vector()-p).length()<fMergeNodeTolerance){
            tDot* d = dots.at(index);
            d->addOwner(this);
            dots.setAt(ijk(i,j,k), d);
          } else {
            setDot(i,j,k,p);
          }

        }
      }
    }

    for (int i=1; i<ni_-1; i++){
      ii = (double)i/(double)(ni_-1);
      for (int j=0; j<nj_; j++){
        jj = (double)j/(double)(nj_-1);
        for (int k=0; k<nk_; k++){
          kk = (double)k/(double)(nk_-1);
          tDot *d0 = dots.at(ijk(0,j,k)),
               *d1 = dots.at(ijk(ni_-1,j,k));
          if (d0==d1){
            d0->addOwner(this);
            dots.setAt(ijk(i,j,k), d0);
          } else {
            tVector p = d0->vector()*(1.-ii) + d1->vector()*(ii);
            setDot(i,j,k,p);
          }

        }
      }
    }

  } else {
    // Liste leeren und neue NULL-Liste erstellen.
    clearDots();
  }


}
//------------------------------------------------------------------------------------------------

tList<tElement*> tStructured3DTwoSidedGrid::faces(void)
{
  tList<tElement*> list;
  for (int i=0;i<2;i++){
    list.append(faces_[i]);
  }
  return list;
}
//------------------------------------------------------------------------------------------------

void tStructured3DTwoSidedGrid::setFace(int f, tElement* el)
{
  f = f % 2;
  tSurface *s = dynamic_cast<tSurface*>(el);
  if (faces_[f]){
    faces_[f]->removeDependent(this);
  }
  if (s && s->addDependent(this)){
    faces_[f] = s;
  } else {
    faces_[f] = NULL;
  }
  invalidate(this);

}
//------------------------------------------------------------------------------------------------

void tStructured3DTwoSidedGrid::setFaces(tList<tElement*> list)
{
  while (list.count()<2){
    list.append(NULL);
  }
  for (int i=0;i<list.count();i++){
    setFace(i,list.at(i));
  }
}
//------------------------------------------------------------------------------------------------
