/*
 * t2DStructuredSurfaceGrid.cpp
 *
 *  Created on: 02.12.2009
 *      Author: Jochen
 */

#include "element/misc/2DGrid/tStructured2DSurfaceGrid.h"

tStructured2DSurfaceGrid::tStructured2DSurfaceGrid(void *theowner) : tStructured2DGrid(theowner) {
  int i;
  for (i=0;i<4;i++){
    fcorner[i] = NULL;
    fedge[i] = NULL;
    fneighbour[i] = NULL;
    neighbourEdge[i] = -1;
  }
  fbase = NULL;
  currentNi = NI = 0;
  currentNj = NJ =0;
  ns = new tVariableNameSpace(this);
  u0Var = dynamic_cast<tRealVariable*>(ns->addRealVariable("u0=0."));
  v0Var = dynamic_cast<tRealVariable*>(ns->addRealVariable("v0=0."));
  uVar = dynamic_cast<tRealVariable*>(ns->addRealVariable("u=u0"));
  vVar = dynamic_cast<tRealVariable*>(ns->addRealVariable("v=v0"));
}
//-----------------------------------------------------------------------------

tStructured2DSurfaceGrid::~tStructured2DSurfaceGrid()
{
  clearGrid();
  ns->releaseOwner(this);
}
//-----------------------------------------------------------------------------

iElement* tStructured2DSurfaceGrid::intrface(void)
{
  if (iface == NULL){
    iface = new iStructured2DSurfaceGrid(this);
  }
  return iface;
}
//-----------------------------------------------------------------------------

int tStructured2DSurfaceGrid::ni(void)
{
  setElementLocked;
  update();
  return currentNi;
}
//-----------------------------------------------------------------------------

int tStructured2DSurfaceGrid::nj(void)
{
  setElementLocked;
  update();
  return currentNj;
}
//-----------------------------------------------------------------------------

void tStructured2DSurfaceGrid::refresh(void)
{
  int i,j;
  tReal u, v;
  tDot *d;

  // tabula rasa...
  if (fneighbour[0]){
    // Mal bei den Nachbarn schauen...
    if (neighbourEdge[0]%4 == 0 || neighbourEdge[0]%4 == 2){
      currentNi = fneighbour[0]->ni();
    } else {
      currentNi = fneighbour[0]->nj();
    }
  } else if (fneighbour[2]){
    if (neighbourEdge[2]%4 == 0 || neighbourEdge[2]%4 == 2){
      currentNi = fneighbour[2]->ni();
    } else {
      currentNi = fneighbour[2]->nj();
    }
  } else {
    currentNi = NI;
  }
//  ni();
  if (fneighbour[1]){
    // Mal bei den Nachbarn schauen...
    if (neighbourEdge[1]%4 == 0 || neighbourEdge[1]%4 == 2){
      currentNj = fneighbour[1]->ni();
    } else {
      currentNj = fneighbour[1]->nj();
    }
  } else if (fneighbour[3]){
    if (neighbourEdge[3]%4 == 0 || neighbourEdge[3]%4 == 2){
      currentNj = fneighbour[3]->ni();
    } else {
      currentNj = fneighbour[3]->nj();
    }
  } else {
    currentNj = NJ;
  }
//  nj();
  clearGridDots();

  if (fbase){
    for (i=0;i<currentNi;i++){
      for (j=0;j<currentNj;j++){
        u0Var->setValue((tReal)i/(tReal)(currentNi-1));
        v0Var->setValue((tReal)j/(tReal)(currentNj-1));
        u = uVar->value();
        v = vVar->value();
        d = new tAbsMagnet(NULL,fbase,u,v);
        setGridAt(i,j,d);
      }
    }
  }

  for (i=0;i<currentNi;i++){
    if (fedge[0]){
      u0Var->setValue((tReal)i/(tReal)(currentNi-1));
      v0Var->setValue(0.);
      u = uVar->value();
      d = new tAbsBead(NULL,fedge[0],u);
      setGridAt(i,0,d);
    }
    if (fedge[2]){
      u0Var->setValue((tReal)i/(tReal)(currentNi-1));
      v0Var->setValue(1.);
      u = uVar->value();
      d = new tAbsBead(NULL,fedge[2],u);
      setGridAt(i,currentNj-1,d);
    }
  }

  for (j=0;j<currentNj;j++){
    if (fedge[1]){
      u0Var->setValue(0);
      v0Var->setValue((tReal)j/(tReal)(currentNj-1));
      v = vVar->value();
      d = new tAbsBead(NULL,fedge[1],v);
      setGridAt(0,j,d);
    }
    if (fedge[3]){
      u0Var->setValue(1);
      v0Var->setValue((tReal)j/(tReal)(currentNj-1));
      v = vVar->value();
      d = new tAbsBead(NULL,fedge[3],v);
      setGridAt(currentNi-1,j,d);
    }
  }
  setGridAt(0,0,fcorner[0]);
  setGridAt(currentNi-1,0,fcorner[1]);
  setGridAt(currentNi-1,currentNj-1,fcorner[2]);
  setGridAt(0,currentNj-1,fcorner[3]);

  if (fneighbour[0]){
    for (i=0;i<currentNi;i++){
      setGridAt(i,0,fneighbour[0]->edgePointAt(neighbourEdge[0],i));
    }
  }
  if (fneighbour[1]){
    for (j=0;j<currentNj;j++){
      setGridAt(0,j,fneighbour[1]->edgePointAt(neighbourEdge[1],j));
    }
  }
  if (fneighbour[2]){
    for (i=0;i<currentNi;i++){
      setGridAt(i,currentNj-1,fneighbour[2]->edgePointAt(neighbourEdge[2],i));
    }
  }
  if (fneighbour[3]){
    for (j=0;j<currentNj;j++){
      setGridAt(currentNi-1,j,fneighbour[3]->edgePointAt(neighbourEdge[3],j));
    }
  }

}
//-----------------------------------------------------------------------------

void tStructured2DSurfaceGrid::setGridAt(int i, int j, tDot *d)
{
  if (i<currentNi && j<currentNj && d){
    if (grid.at(j*currentNi+i)){
      grid.at(j*currentNi+i)->removeDependent(this);
    }
    grid.setAt(j*currentNi+i,d);
    d->addDependent(this);
  }
}
//-----------------------------------------------------------------------------

tDot* tStructured2DSurfaceGrid::gridAt(int i, int j)
{
  update();
  if (i>=0 && i<currentNi && j>=0 && j<currentNj){
    return grid.at(j*currentNi+i);
  } else {
    return NULL;
  }
}
//-----------------------------------------------------------------------------

void tStructured2DSurfaceGrid::clearGrid(void)
{
  int i;
  for (i=0;i<4;i++){
    if (fcorner[i]){
      fcorner[i]->removeDependent(this);
    }
    if (fedge[i]){
      fedge[i]->removeDependent(this);
    }
    if (fneighbour[i]){
      fneighbour[i]->removeDependent(this);
    }
    fcorner[i] = NULL;
    fedge[i] = NULL;
    fneighbour[i] = NULL;
    neighbourEdge[i]= -1;
  }
  if (fbase){
    fbase->removeDependent(this);
  }
  fbase = NULL;
  NI = 0;
  NJ=0;

}
//-----------------------------------------------------------------------------

void tStructured2DSurfaceGrid::clearGridDots(void)
{
  int i,j;
  tDot *d;
  for (i=0;i<grid.count();i++){
    d = grid.at(i);
    if (d){
      d->removeDependent(this);
    }
  }
  grid.clear();
  for (i=0;i<currentNi;i++){
    for (j=0;j<currentNj;j++){
      grid.append(NULL);
    }
  }
}
//-----------------------------------------------------------------------------

/*tDot* tStructured2DSurfaceGrid::edgePointAt(int edge,int index)
{
  update();
  edge = edge%4;
  if (edge==0 && index >=0 && index<currentNi){
    return gridAt(index,0);
  } else if (edge==1 && index >=0 && index<currentNj){
    return gridAt(currentNi-1,index);
  } else if (edge==2 && index >=0 && index<currentNi){
    return gridAt(index,currentNj-1);
  } else if (edge==3 && index >=0 && index<currentNj){
    return gridAt(0,index);
  } else {
    return NULL;
  }
}*/
//-----------------------------------------------------------------------------

tDot* tStructured2DSurfaceGrid::cornerAt(int index)
{
  update();
  index = index%4;
  if (index == 0){
    return grid.at(0);
  } else if (index == 1){
    return gridAt(currentNi-1,0);
  } else if (index == 2){
    return gridAt(currentNi-1,currentNj-1);
  } else if (index == 3){
    return gridAt(0,currentNj-1);
  } else {
    return NULL;
  }
}
//-----------------------------------------------------------------------------

void tStructured2DSurfaceGrid::setEdges(tList<tElement*> list)
{
  int i;
  tCurve *c;

  for (i=0;i<4;i++){
    if (i<list.count()){
      c = dynamic_cast<tCurve*>(list.at(i));
    } else {
      c = NULL;
    }
    if (fedge[i]) fedge[i]->removeDependent(this);
    if (c && c->addDependent(this)){
      fedge[i] = c;
    } else {
      fedge[i] = NULL;
    }
  }
  invalidate(this);
}
//-----------------------------------------------------------------------------

void tStructured2DSurfaceGrid::setCorners(tList<tElement*> list)
{
  int i;
  tDot *d;

  for (i=0;i<4;i++){
    if (i<list.count()){
      d = dynamic_cast<tDot*>(list.at(i));
    } else {
      d = NULL;
    }
    if (fcorner[i]) fcorner[i]->removeDependent(this);
    if (d && d->addDependent(this)){
      fcorner[i] = d;
    } else {
      fcorner[i] = NULL;
    }
  }
  invalidate(this);
}
//-----------------------------------------------------------------------------

void tStructured2DSurfaceGrid::setNeighbours(tList<tElement*> list)
{
  int i;
  tStructured2DGrid *n;

  for (i=0;i<4;i++){
    if (i<list.count()){
      n = dynamic_cast<tStructured2DGrid*>(list.at(i));
    } else {
      n = NULL;
    }
    if (fneighbour[i]) fneighbour[i]->removeDependent(this);
    if (n && n->addDependent(this)){
      fneighbour[i] = n;
    } else {
      fneighbour[i] = NULL;
    }
  }
  invalidate(this);
}
//-----------------------------------------------------------------------------

void tStructured2DSurfaceGrid::setNeighbourEdges(tList<int> list)
{
  for (int i=0;i<4;i++){
    if (i<list.count()){
      neighbourEdge[i] = list.at(i);
    } else {
      neighbourEdge[i] = -1;
    }
  }
  invalidate(this);
}
//-----------------------------------------------------------------------------

void tStructured2DSurfaceGrid::tStructured2DSurfaceGrid::setBase(tElement *el)
{
  tSurface *b;

  b = dynamic_cast<tSurface*>(el);
  if (fbase) fbase->removeDependent(this);
  fbase= b;
  if (b && b->addDependent(this)){
    fbase= b;
  } else {
    fbase = NULL;
  }
  invalidate(this);
}
//-----------------------------------------------------------------------------

tList<tElement*> tStructured2DSurfaceGrid::edges(void)
{
  setElementLocked
  update();
  int i;
  tList<tElement*> l;
  for (i=0;i<4;i++){
    l.append(fedge[i]);
  }
  return l;
}
//-----------------------------------------------------------------------------

tList<tElement*> tStructured2DSurfaceGrid::corners(void)
{
  setElementLocked
  update();
  int i;
  tList<tElement*> l;
  for (i=0;i<4;i++){
    l.append(fcorner[i]);
  }
  return l;
}
//-----------------------------------------------------------------------------

tList<tElement*> tStructured2DSurfaceGrid::neighbours(void)
{
  setElementLocked
  update();
  int i;
  tList<tElement*> l;
  for (i=0;i<4;i++){
    l.append(fneighbour[i]);
  }
  return l;
}
//-----------------------------------------------------------------------------

tList<int> tStructured2DSurfaceGrid::neighbourEdges(void)
{
  setElementLocked
  update();
  int i;
  tList<int> l;
  for (i=0;i<4;i++){
    l.append(neighbourEdge[i]);
  }
  return l;
}

//-----------------------------------------------------------------------------

tSurface* tStructured2DSurfaceGrid::base(void)
{
  update();
  return fbase;
}
//-----------------------------------------------------------------------------

QString tStructured2DSurfaceGrid::uRefinement(void)
{
  update();
  return uVar->RHS();
}
//-----------------------------------------------------------------------------

QString tStructured2DSurfaceGrid::vRefinement(void)
{
  update();
  return vVar->RHS();
}
//-----------------------------------------------------------------------------

void tStructured2DSurfaceGrid::setURefinement(QString func)
{
  uVar->setRHS(func);
  invalidate(this);
}
//-----------------------------------------------------------------------------

void tStructured2DSurfaceGrid::setVRefinement(QString func)
{
  vVar->setRHS(func);
  invalidate(this);
}
//-----------------------------------------------------------------------------

