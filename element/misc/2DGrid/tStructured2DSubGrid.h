#ifndef T2DSTRUCTUREDSUBGRID_H_
#define T2DSTRUCTUREDSUBGRID_H_

#include "element/misc/2DGrid/tStructured2DGrid.h"
#include "element/misc/3DGrid/tStructured3DGrid.h"

#include "iStructured2DSubGrid.h"

class tStructured2DSubGrid : public tStructured2DGrid
{
private:
  tStructured2DGrid *fparentGrid;
  tStructured3DGrid *fparent3DGrid;
  int NI, NJ,                 // Number of grid nodes in I and J direction
      OffsetI, OffsetJ,       // offset for I and J
      NIskip, NJskip,         // 0: copies each node of the parent grid, 1: skips every second node, 2: skips two nodes and so on
                              // Only effective, if fparent3DGrid is used:
      grid3D_Dir,              // indicates in which plane (i,j,k) the SubGrid will be created.
      grid3D_DirOffset;        // indicates at which Offset the Grid will start in the 3D Grid
public:
  tStructured2DSubGrid(void *theowner);
	virtual ~tStructured2DSubGrid();

  void setOffsetI(int ii);
  void setOffsetJ(int jj);
  int offsetI(void);
  int offsetJ(void);

  void setNi(int ii);
  void setNj(int jj);
  virtual int ni(void);
  virtual int nj(void);

  void setNiSkip(int ii);
  void setNjSkip(int jj);
  virtual int niSkip(void);
  virtual int njSkip(void);

  void setParentGrid(tElement *el);
  tElement* parentGrid(void);

  //  if parent grid is 3DGrid
  void setDirOn3DGrid(int ijk) {grid3D_Dir = ijk; invalidate(this);};
  int dirOn3DGrid(void) {return grid3D_Dir;};
  void setDirOffsetOn3DGrid(int offset) {grid3D_DirOffset = offset; invalidate(this);};
  int dirOffsetOn3DGrid(void) {return grid3D_DirOffset;};

  virtual tDot* gridAt(int i, int j);
  virtual tDot* cornerAt(int index);
//  virtual tReal distribOnEdge(int edge, tReal pos);


  virtual iElement* intrface(void);
  virtual void refresh(void);
};
/*I!
parentGrid StructuredAbstractGrid read:parentGrid write:setParentGrid
ni Int read:ni write:setNi
nj Int read:nj write:setNj
iOffset Int read:offsetI write:setOffsetI
jOffset Int read:offsetJ write:setOffsetJ
niSkip Int read:niSkip write:setNiSkip
njSkip Int read:njSkip write:setNjSkip
dirOffsetOn3DGrid Int read:dirOffsetOn3DGrid write:setDirOffsetOn3DGrid
dirOn3DGrid Int read:dirOn3DGrid write:setDirOn3DGrid
*/

#endif /*T2DSTRUCTUREDSUBGRID_H_*/
