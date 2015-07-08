#include "element/misc/2DGrid/tStructured2DGrid.h"

tStructured2DGrid::tStructured2DGrid(void *theowner): tStructuredAbstractGrid(theowner)
{
  fOrientation = true;
}

tStructured2DGrid::~tStructured2DGrid()
{
}

tDot* tStructured2DGrid::edgePointAt(int edge,int index)
{
  setElementLocked;
  bool reverse;
  int i,j,NI,NJ;

  if (edge>=0){
    reverse = false;
  } else {
    reverse = true;
  }

  NI = ni();
  NJ = nj();
  edge = fabs(edge);
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

}
