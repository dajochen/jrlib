/*
 * t2DStructuredSurfaceGrid.h
 *
 *  Created on: 02.12.2009
 *      Author: Jochen
 */

#ifndef T2DSTRUCTUREDSURFACEGRID_H_
#define T2DSTRUCTUREDSURFACEGRID_H_

#include "element/point/tDot.h"
#include "element/curve/tCurve.h"
#include "element/surface/tSurface.h"
#include "element/point/tAbsMagnet.h"
#include "element/point/tAbsBead.h"
#include "element/variable/tVariableNameSpace.h"
#include "element/variable/tRealVariable.h"
#include "element/misc/2DGrid/tStructured2DGrid.h"

#include "iStructured2DSurfaceGrid.h"

class tStructured2DSurfaceGrid : public tStructured2DGrid {

private:
  tDot *fcorner[4];
  tCurve *fedge[4];
  tSurface *fbase;

  int neighbourEdge[4];
  tStructured2DGrid *fneighbour[4]; // Gibt die Kante im Netz an, die benachbart ist (0, 1, 2, 3).
                                       // Soll die Kante eine entgegen gerichtete Orientierung haben,
                                       // wird die Kantennummer um 4 erhöht (4, 5, 6, 7)
  int NI, NJ, currentNi, currentNj;
  tList<tDot*> grid;

  tVariableNameSpace *ns;
  tRealVariable *uVar, *vVar, *u0Var, *v0Var;

  void setGridAt(int i, int j, tDot *d);
  void clearGridDots(void);
  void clearGrid(void);

public:
  tStructured2DSurfaceGrid(void *theowner);
  virtual ~tStructured2DSurfaceGrid();

  virtual iElement* intrface(void);
  virtual void refresh(void);

  virtual int ni(void);//{return NI;};
  virtual int nj(void);//{return NJ;};
  void setNi(int i){NI=i; invalidate(this);};
  void setNj(int j){NJ=j; invalidate(this);};

//  virtual tDot* edgePointAt(int edge,int index);
  virtual tDot* gridAt(int i, int j);
  virtual tDot* cornerAt(int index);
//  virtual tReal distribOnEdge(int edge, tReal pos){edge=1; pos =1; return 1.;};

  void setEdges(tList<tElement*> list);
  void setCorners(tList<tElement*> list);
  void setNeighbours(tList<tElement*> list);
  void setNeighbourEdges(tList<int> list);
  void setBase(tElement *el);
  QString uRefinement(void);
  QString vRefinement(void);
  void setURefinement(QString func);
  void setVRefinement(QString func);

  tList<tElement*> edges(void);
  tList<tElement*> corners(void);
  tList<tElement*> neighbours(void);
  tList<int> neighbourEdges(void);
  tSurface* base(void);
};
/*I!
ni Int read:ni write:setNi
nj Int read:nj write:setNj
base Surface read:base write:setBase
uRefinement String read:uRefinement write:setURefinement
vRefinement String read:vRefinement write:setVRefinement
edges CurveList read:edges write:setEdges
corners DotList read:corners write:setCorners
neighbours Structured2DGridList read:neighbours write:setNeighbours
neighbourEdges IntList read:neighbourEdges write:setNeighbourEdges
*/

#endif /* T2DSTRUCTUREDSURFACEGRID_H_ */
