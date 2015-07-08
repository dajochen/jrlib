#include "element/misc/2DGrid/tStructured2DSubGrid.h"

#include "classes/utils.h"

tStructured2DSubGrid::tStructured2DSubGrid(void *theowner): tStructured2DGrid(theowner)
{
  fparentGrid = NULL;
  fparent3DGrid = NULL;
  OffsetI = 0;
  OffsetJ = 0;
  NI = -1;
  NJ = -1;
  NIskip = 0;
  NJskip = 0;

  grid3D_Dir = 0;
  grid3D_DirOffset = 0;
}
//-----------------------------------------------------------------------------

tStructured2DSubGrid::~tStructured2DSubGrid()
{
  if (fparentGrid){
    fparentGrid->removeDependent(this);
  }
}
//-----------------------------------------------------------------------------

void tStructured2DSubGrid::setOffsetI(int ii)
{
  setElementLocked
  OffsetI = ii;
  invalidate(this);
}
//-----------------------------------------------------------------------------

void tStructured2DSubGrid::setOffsetJ(int jj)
{
  setElementLocked
  OffsetJ = jj;
  invalidate(this);
}
//-----------------------------------------------------------------------------

int tStructured2DSubGrid::offsetI(void)
{
  setElementLocked
  update();
  return OffsetI;
}
//-----------------------------------------------------------------------------

int tStructured2DSubGrid::offsetJ(void)
{
  setElementLocked
  update();
  return OffsetJ;
}
//-----------------------------------------------------------------------------

void tStructured2DSubGrid::setNi(int ii)
{
  setElementLocked
  NI = ii;
  invalidate(this);
}
//-----------------------------------------------------------------------------

void tStructured2DSubGrid::setNj(int jj)
{
  setElementLocked
  NJ = jj;
  invalidate(this);
}
//-----------------------------------------------------------------------------

int tStructured2DSubGrid::ni(void)
{
  setElementLocked

  update();
  return NI;
}
//-----------------------------------------------------------------------------

int tStructured2DSubGrid::nj(void)
{
  setElementLocked
  update();
  return NJ;
}
//-----------------------------------------------------------------------------

void tStructured2DSubGrid::setNiSkip(int ii)
{
  setElementLocked
  NIskip = ii;
  invalidate(this);
}
//-----------------------------------------------------------------------------

void tStructured2DSubGrid::setNjSkip(int jj)
{
  setElementLocked
  NJskip = jj;
  invalidate(this);
}
//-----------------------------------------------------------------------------

int tStructured2DSubGrid::niSkip(void)
{
  update();
  return NIskip;
}
//-----------------------------------------------------------------------------

int tStructured2DSubGrid::njSkip(void)
{
  update();
  return NJskip;
}
//-----------------------------------------------------------------------------

/*tDot* tStructured2DSubGrid::edgePointAt(int edge,int index)
{
  int i,j;
  bool reverse;

  setElementLocked
  update();

  if (edge > 3){
    reverse = true;
  } else {
    reverse = false;
  }
  edge = edge%4;

  if (!reverse){
    if (edge==0){
      i=index;                   j=0;
    } else if (edge == 1){
      i=NI-1;                    j=index;
    } else if (edge == 2){
      i=index;                   j=NJ-1;
    } else {
      i=0 ;                      j=index;
    }
  } else {
    if (edge==0){
      i=NI-1-index;              j=0;
    } else if (edge == 1){
      i=NI-1;                    j=NJ-1-index;
    } else if (edge == 2){
      i=NI-1-index;              j=NJ-1;
    } else {
      i=0;                       j=NJ-1-index;
    }
  }
  return gridAt(i,j);
}*/
//-----------------------------------------------------------------------------

tDot* tStructured2DSubGrid::gridAt(int i, int j)
{
  setElementLocked
  update();
  if (fparentGrid){
    return fparentGrid->gridAt(OffsetI+i*(NIskip+1), OffsetJ+j*(NJskip+1));
  } else if (fparent3DGrid){
    int ijk[3];
    ijk[grid3D_Dir%3] = grid3D_DirOffset;
    ijk[(grid3D_Dir+1)%3] = OffsetI+i*(NIskip+1);
    ijk[(grid3D_Dir+2)%3] = OffsetJ+j*(NJskip+1);
    return fparent3DGrid->gridAt(ijk[0], ijk[1], ijk[2]);
  } else {
    return NULL;
  }
}
//-----------------------------------------------------------------------------
tDot* tStructured2DSubGrid::cornerAt(int index)
{
  setElementLocked
  update();

  index = index%4;
  if (index==0){
    return gridAt(0,0);
  } else if (index==1){
    return gridAt(NI-1,0);
  } else if (index==2){
    return gridAt(NJ-1,NJ-1);
  } else if (index==3){
    return gridAt(0,NJ-1);
  } else {
    return NULL;
  }
}
//-----------------------------------------------------------------------------

//tReal tStructured2DSubGrid::distribOnEdge(int edge, tReal pos)
//{
//  setElementLocked
//  if (fparentGrid){
//    return fparentGrid->distribOnEdge(edge, pos);
//  } else {
//    return 1.;
//  }
//}
////-----------------------------------------------------------------------------

void tStructured2DSubGrid::setParentGrid(tElement *el)
{
  setElementLocked
  if (fparentGrid){
    fparentGrid->removeDependent(this);
  }
  if (fparent3DGrid){
    fparent3DGrid->removeDependent(this);
  }
  fparentGrid = dynamic_cast<tStructured2DGrid*>(el);
  fparent3DGrid = dynamic_cast<tStructured3DGrid*>(el);
  if (fparentGrid && !fparentGrid->addDependent(this)){
    fparentGrid = NULL;
  }
  if (fparent3DGrid && !fparent3DGrid->addDependent(this)){
    fparent3DGrid = NULL;
  }
  invalidate(this);
}
//-----------------------------------------------------------------------------

tElement* tStructured2DSubGrid::parentGrid(void)
{
  setElementLocked
  if (fparentGrid){
    return  fparentGrid;
  }
  if (fparent3DGrid){
    return  fparent3DGrid;
  }
  return NULL;
}
//-----------------------------------------------------------------------------

void tStructured2DSubGrid::refresh(void)
{
  int parentNi, parentNj;

  if (fparentGrid){
    parentNi = fparentGrid->ni();
    parentNj = fparentGrid->nj();
    NIskip = min (NIskip,parentNi-2);
    NJskip = min (NJskip,parentNj-2);
    NIskip = max (NIskip, 0);
    NJskip = max (NJskip, 0);

    OffsetI = min(OffsetI,parentNi-2-NIskip);
    OffsetJ = min(OffsetJ,parentNj-2-NJskip);
    OffsetI = max(OffsetI, 0);
    OffsetJ = max(OffsetJ, 0);

    NI = min(NI, ((parentNi-1-OffsetI)/(NIskip+1))+1 );
    NJ = min(NJ, ((parentNj-1-OffsetJ)/(NJskip+1))+1 );
    NI = max(NI,2);//sollte eigentlich unnoetig sein...
    NJ = max(NJ,2);//sollte eigentlich unnoetig sein...
  } else if (fparent3DGrid){
    parentNi = fparent3DGrid->nIJK(grid3D_Dir+1);
    parentNj = fparent3DGrid->nIJK(grid3D_Dir+2);

    NIskip = min (NIskip,parentNi-2);
    NJskip = min (NJskip,parentNj-2);
    NIskip = max (NIskip, 0);
    NJskip = max (NJskip, 0);

    OffsetI = min(OffsetI,parentNi-2-NIskip);
    OffsetJ = min(OffsetJ,parentNj-2-NJskip);
    OffsetI = max(OffsetI, 0);
    OffsetJ = max(OffsetJ, 0);

    NI = min(NI, ((parentNi-1-OffsetI)/(NIskip+1))+1 );
    NJ = min(NJ, ((parentNj-1-OffsetJ)/(NJskip+1))+1 );
    NI = max(NI,2);//sollte eigentlich unnoetig sein...
    NJ = max(NJ,2);//sollte eigentlich unnoetig sein...
  }

}
//-----------------------------------------------------------------------------

iElement* tStructured2DSubGrid::intrface(void)
{
  if (iface == NULL){
    iface = new iStructured2DSubGrid(this);
  }
  return iface;
}
//-----------------------------------------------------------------------------
