#ifndef TSTRUCTURED2DGRID_H_
#define TSTRUCTURED2DGRID_H_

#include "element/misc/tStructuredAbstractGrid.h"
#include "element/point/tDot.h"

#include "iStructured2DGrid.h"

class tStructured2DGrid : public tStructuredAbstractGrid
{
private:
  bool fOrientation;
public:
	tStructured2DGrid(void *theowner);
	virtual ~tStructured2DGrid();

  bool orientation(void){setElementLocked return fOrientation;};
  void setOrientation(bool orient){setElementLocked fOrientation = orient; invalidate(this);};

  virtual int ni(void) = 0;
  virtual int nj(void) = 0;

  virtual tDot* edgePointAt(int edge,int index);
  virtual tDot* gridAt(int i, int j) = 0;
  virtual tDot* cornerAt(int index) = 0;
//  virtual tReal distribOnEdge(int edge, tReal pos) = 0;

};

/*I!
orientation Bool read:orientation write:setOrientation
*/
#endif /*TSTRUCTURED2DGRID_H_*/
