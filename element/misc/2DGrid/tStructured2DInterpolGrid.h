#ifndef T2DSTRUCTUREDINTERPOLGRID_H_
#define T2DSTRUCTUREDINTERPOLGRID_H_

#include "classes/tFunction.h"

#include "element/misc/2DGrid/tStructured2DGrid.h"
#include "element/point/tPoint.h"
#include "element/misc/tNetPoint.h"
#include "element/misc/tNet.h"

#include "iStructured2DInterpolGrid.h"

class tStructured2DInterpolGrid : public tStructured2DGrid
{
private:
  tNet *BorderNet[4],*Inner;

  tDot *corner[4];
  tDot *edge[4];
  tDot *base;
  int neighbourEdge[4];
  tStructured2DGrid *neighbourGrid[4]; // Gibt die Kante im Netz an, die benachbart ist (0, 1, 2, 3).
                                       // Soll die Kante eine entgegen gerichtete Orientierung haben,
                                       // wird die Kantennummer um 4 erhöht (4, 5, 6, 7)
  tFunction edgeDistrib;

  int NI, NJ;
  tList<tDot*> grid;
  tList<tNetPoint*> gridWaste;

  int fMeshIterations;

  void clearGrid(void);
  bool initGrid(tList<tPoint*> *gridBase);
  tDot* addProjectionSpring(int i, int j, tNet *net, tDot *dot, tList<tPoint*> *gridBase);

public:
  tStructured2DInterpolGrid(void *theowner);
	virtual ~tStructured2DInterpolGrid();

  void refresh(void);
  iElement* intrface(void);

  tElement* neighbour(int index){setElementLocked update(); return neighbourGrid[index%4];}

  void setCorner(int i, tElement *el);
  void setEdge(int i, tElement *el);
  void setBase(tElement *el);
  void setNeighbour(int myEdge, tElement *el, int edge);
  virtual void setDistribOnEdge(int i, QString func);
  virtual void setIterations(int iter);

  void setNi(int Ni);
  void setNj(int Nj);
  virtual int ni(void);
  virtual int nj(void);

  void setMeshIterations(int iter);
  int meshIterations(void);

//  virtual tDot* edgePointAt(int edge,int index);
  virtual tDot* gridAt(int i, int j);
  virtual tDot* cornerAt(int index);
  virtual tReal distribOnEdge(int edge, tReal pos);
};

// Achtung Interface modifiziert!!!!!
/*I!
ni Int read:ni write:setNi
nj Int read:nj write:setNj
meshIterations Int read:meshIterations write:setMeshIterations
*/

#endif /*T2DSTRUCTUREDINTERPOLGRID_H_*/


