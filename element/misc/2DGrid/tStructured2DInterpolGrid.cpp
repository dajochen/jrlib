#include "element/misc/2DGrid/tStructured2DInterpolGrid.h"

#include "element/point/tAbsBead.h"
#include "element/point/tAbsMagnet.h"

tStructured2DInterpolGrid::tStructured2DInterpolGrid(void *theowner): tStructured2DGrid(theowner)
{
  int i;
  for (i=0;i<4;i++){
    BorderNet[i] = new tNet(this);
    BorderNet[i]->setNetIterations(3);
    corner[i] = NULL;
    edge[i] = NULL;
    neighbourGrid[i] = NULL;
    neighbourEdge[i] = -1;
  }
  base = NULL;
  Inner = new tNet(this);
  Inner->setNetIterations(3);

  edgeDistrib.setFunc("pos:=0.");
  edgeDistrib.setFunc("edge0:=1.");
  edgeDistrib.setFunc("edge1:=1.");
  edgeDistrib.setFunc("edge2:=1.");
  edgeDistrib.setFunc("edge3:=1.");
  NI = 10;
  NJ = 10;

  fMeshIterations = 250;
  invalidate(this);

}
//-----------------------------------------------------------------------------

tStructured2DInterpolGrid::~tStructured2DInterpolGrid()
{
  int i;

  clearGrid();
  for(i=0;i<4;i++){
    BorderNet[i]->releaseOwner(this);
  }
  Inner->releaseOwner(this);

  for (i=0;i<4;i++){
    if (corner[i]){ corner[i]->removeDependent(this); }
    if (edge[i]){ edge[i]->removeDependent(this); }
    if (neighbourGrid[i]){ neighbourGrid[i]->removeDependent(this); }
  }
  if (base){
    base->removeDependent(this);
  }
}
//-----------------------------------------------------------------------------
/*tDot* tStructured2DInterpolGrid::edgePointAt(int edge,int index){

  setElementLocked
  bool reverse;
  int myNi, myNj;

  update();
  myNi = ni();
  myNj = nj();

  if (grid.count() == myNi*myNj){
    if (edge > 3){
      reverse = true;
    } else {
      reverse = false;
    }
    edge = edge % 4;
    if (edge == 0 || edge == 2){
      if (index >= myNi || index < 0){
        return NULL;
      } else {
        if (reverse){
          index = myNi-1-index;
        }
        if (edge == 0){
          return grid.at(0*myNi+index);
        } else {
          return grid.at((myNj-1)*myNi+index);
        }
      }
    } else if (edge == 1 || edge == 3){
      if (index >= myNj || index < 0){
        return NULL;
      } else {
        if (reverse){
          index = myNj-1-index;
        }
        if (edge == 1){
          return grid.at(index*myNi+myNi-1);
        } else {
          return grid.at(index*myNi);
        }
      }
    } else {
      return NULL;
    }
  } else {
    return NULL;
  }
}*/
//-----------------------------------------------------------------------------

tDot* tStructured2DInterpolGrid::cornerAt(int index)
{
  setElementLocked
  int myNi, myNj;

  update();
  myNi = ni();
  myNj = nj();

  index = index %4;

  if (index == 0){
    return grid.at(0);
  } else if (index == 1){
    return grid.at(myNi-1);
  } else if (index == 2){
    return grid.at((myNj-1)*myNi+myNi-1);
  } else if (index == 3){
    return grid.at((myNj-1)*myNi);
  } else {
    return NULL;
  }
}
//-----------------------------------------------------------------------------

tDot* tStructured2DInterpolGrid::gridAt(int i, int j)
{
  setElementLocked
  int myNi = ni();
  update();
  if (i >= 0 && j>=0 && i<myNi && j<nj()){
    return grid.at(j*myNi+i);
  } else {
    return NULL;
  }
}
//-----------------------------------------------------------------------------


void tStructured2DInterpolGrid::setIterations(int iter)
{
  setElementLocked
  int i;
  for (i=0;i<4;i++){
    BorderNet[i]->setNetIterations(iter);
  }
  invalidate(this);
};

//-----------------------------------------------------------------------------

void tStructured2DInterpolGrid::setCorner(int i, tElement *el)
{
  setElementLocked
  tDot *d;
  i = i%4;
  if (corner[i]){
    corner[i]->removeDependent(this);
  }
  d = dynamic_cast<tDot*>(el);
  if (d && d->addDependent(this)){
    corner[i]= d;
  } else {
    corner[i]= NULL;
  }
  invalidate(this);
}
//-----------------------------------------------------------------------------

void tStructured2DInterpolGrid::setEdge(int i, tElement *el)
{
  setElementLocked
  tDot* d = dynamic_cast<tDot*>(el);
  i = i%4;
  if (edge[i]){
    edge[i]->removeDependent(this);
  }
  if (d &&  d->addDependent(this)){
    edge[i] = d;
  } else {
    edge[i] = NULL;
  }
  invalidate(this);
}
//-----------------------------------------------------------------------------

void tStructured2DInterpolGrid::setNeighbour(int myEdge, tElement *el, int edge)
{
  setElementLocked
  tStructured2DGrid *grid=dynamic_cast<tStructured2DGrid*>(el);
  myEdge = myEdge%4;
  if (neighbourGrid[myEdge]){
    neighbourGrid[myEdge]->removeDependent(this);
  }
  if (grid && grid->addDependent(this)){
    neighbourGrid[myEdge]= grid;
  } else {
    neighbourGrid[myEdge]= NULL;
  }
  neighbourEdge[myEdge] = edge;

  invalidate(this);
}
//-----------------------------------------------------------------------------

void tStructured2DInterpolGrid::setBase(tElement *el)
{
  setElementLocked
  if (base){
    base->removeDependent(this);
  }
  base = dynamic_cast<tDot*>(el);
  if (base && !base->addDependent(this)){
    base = NULL;
  }
  invalidate(this);
}
//-----------------------------------------------------------------------------

int tStructured2DInterpolGrid::ni(void)
{
  setElementLocked
  int myNi;
  update();
  if (neighbourGrid[0]){
    // Mal bei den Nachbarn schauen...
    if (neighbourEdge[0]%4 == 0 || neighbourEdge[0]%4 == 2){
      myNi = neighbourGrid[0]->ni();
    } else {
      myNi = neighbourGrid[0]->nj();
    }
  } else if (neighbourGrid[2]){
    if (neighbourEdge[2]%4 == 0 || neighbourEdge[2]%4 == 2){
      myNi = neighbourGrid[2]->ni();
    } else {
      myNi = neighbourGrid[2]->nj();
    }
  } else {
    myNi = NI;
  }
  return myNi;
}
//-----------------------------------------------------------------------------

int tStructured2DInterpolGrid::nj(void)
{
  setElementLocked
  int myNj;
  update();
  if (neighbourGrid[1]){
    // Mal bei den Nachbarn schauen...
    if (neighbourEdge[1]%4 == 0 || neighbourEdge[1]%4 == 2){
      myNj = neighbourGrid[1]->ni();
    } else {
      myNj = neighbourGrid[1]->nj();
    }
  } else if (neighbourGrid[3]){
    if (neighbourEdge[3]%4 == 0 || neighbourEdge[3]%4 == 2){
      myNj = neighbourGrid[3]->ni();
    } else {
      myNj = neighbourGrid[3]->nj();
    }
  } else {
    myNj = NJ;
  }
  return myNj;
}
//-----------------------------------------------------------------------------

void tStructured2DInterpolGrid::setNi(int Ni)
{
  setElementLocked
  if (Ni > 1) {
    NI = Ni;
  }
  invalidate(this);
}
//-----------------------------------------------------------------------------

void tStructured2DInterpolGrid::setNj(int Nj)
{
  setElementLocked
  if (Nj > 1) {
    NJ = Nj;
  }
  invalidate(this);
}
//-----------------------------------------------------------------------------

void tStructured2DInterpolGrid::setMeshIterations(int iter)
{
  setElementLocked
  if (iter > 0) {
    fMeshIterations = iter;
  }
  invalidate(this);
}
//-----------------------------------------------------------------------------

int tStructured2DInterpolGrid::meshIterations(void)
{
	return fMeshIterations;
}
//-----------------------------------------------------------------------------

void tStructured2DInterpolGrid::setDistribOnEdge(int i, QString func)
{
  setElementLocked
  i = i%4;
  edgeDistrib.setFunc("edge"+QString::number(i)+"="+func);
  invalidate(this);
}
//-----------------------------------------------------------------------------

tReal tStructured2DInterpolGrid::distribOnEdge(int edge, tReal pos)
{
  setElementLocked
  bool reverse;
  tReal value;

  update();
  if (edge > 3){
    reverse = true;
  } else {
    reverse = false;
  }
  edge = edge % 4;
  if (reverse){
    pos = 1.-pos;
  }
  edgeDistrib.setFunc("pos:="+QString::number(pos));
  value = edgeDistrib.calc("edge"+QString::number(edge));
  return value;
}

//-----------------------------------------------------------------------------

void tStructured2DInterpolGrid::clearGrid(void)
{
  setElementLocked
  int i;
  tDot *d;

  // Die n2 und sonstigen Dots aus initGrid
  for (i=0;i<grid.count();i++){
    d = grid.at(i);
    if (d && d!=corner[0] && d!=corner[1] && d!=corner[2] && d!=corner[3]){
      d->releaseOwner(this);
    }
  }
  grid.clear();
  // Die n1-netPoints aus addProjectionSpring()
  for (i=0;i<gridWaste.count();i++){
    d = gridWaste.at(i);
    d->releaseOwner(this);
  }
  gridWaste.clear();

  Inner->clear();
  for (i=0;i<4;i++){
    BorderNet[i]->clear();
  }


}
//-----------------------------------------------------------------------------

tDot* tStructured2DInterpolGrid::addProjectionSpring(int i, int j, tNet *net, tDot *dot, tList<tPoint*> *gridBase)
{
  tPoint *d;
  tNetPoint *n1,*n2;
  d = new tPoint(this, dot->vector());
  gridBase->setAt(j*ni()+i, d);
  n1 = new tNetPoint(this, net, d);
  gridWaste.append(n1);
  net->setBorderKnot(n1);
  n2 = new tNetPoint(this, net, dot);
  net->addSpring(n1,n2);
  return n2;
}
//-----------------------------------------------------------------------------

bool tStructured2DInterpolGrid::initGrid(tList<tPoint*> *gridBase)
{
  int i,j;
  int myNi,myNj;
  tVector center;
  tDot *dot;
  tAbsMagnet *magnetBase;
  bool error;

  myNi = ni();
  myNj = nj();

  error = false;

  clearGrid();

  magnetBase = dynamic_cast<tAbsMagnet*>(base);

  for (i=0;i<myNi*myNj;i++){
    grid.append(NULL);
  }


  // Die Kanten:
  for (i=0;i<myNi;i++){
    // Kante 0:
    j = 0;
    if (neighbourGrid[0]){
      dot = neighbourGrid[0]->edgePointAt(neighbourEdge[0],i);
      dot->addDependent(this);
    } else if (i==0){
      dot = corner[0];
    } else if (i==myNi-1){
      dot = corner[1];
    } else {
      if (edge[0]){
        if (dynamic_cast<tAbsBead*>(edge[0]) || dynamic_cast<tAbsMagnet*>(edge[0]) ){
          dot = addProjectionSpring(i,j, BorderNet[0], edge[0], gridBase);
        } else {
          dot = new tPoint(this,edge[0]->vector());
        }
      } else if (magnetBase){
        dot = addProjectionSpring(i,j,BorderNet[0], magnetBase, gridBase);
      } else {
        dot = NULL;
      }
    }
    grid.setAt(j*myNi+i, dot);
    // Kante 2:
    j = myNj-1;
    if (neighbourGrid[2]){
      dot = neighbourGrid[2]->edgePointAt(neighbourEdge[2],i);
      dot->addDependent(this);
    } else if (i==0){
      dot = corner[3];
    } else if (i==myNi-1){
      dot = corner[2];
    } else {
      if (edge[2]){
        if (dynamic_cast<tAbsBead*>(edge[2]) || dynamic_cast<tAbsMagnet*>(edge[2]) ){
          dot = addProjectionSpring(i,j, BorderNet[2], edge[2], gridBase);
        } else {
          dot = new tPoint(this,edge[2]->vector());
        }
      } else if (magnetBase){
        dot = addProjectionSpring(i,j,BorderNet[2], magnetBase, gridBase);
      } else {
        dot = NULL;
      }
    }
    grid.setAt(j*myNi+i, dot);
  }


  for (j=0;j<myNj;j++){
    // Kante 3:
    i = 0;
    if (neighbourGrid[3]){
      dot = neighbourGrid[3]->edgePointAt(neighbourEdge[3],j);
      dot->addDependent(this);
    } else if (j==0 || j==myNj-1){
      dot = NULL; // Die Ecken wurden schon zuvor definiert
    } else {
      if (edge[3]){
        if (dynamic_cast<tAbsBead*>(edge[3]) || dynamic_cast<tAbsMagnet*>(edge[3]) ){
          dot = addProjectionSpring(i,j, BorderNet[3], edge[3], gridBase);
        } else {
          dot = new tPoint(this,edge[3]->vector());
        }
      } else if (magnetBase){
        dot = addProjectionSpring(i,j,BorderNet[3], magnetBase, gridBase);
      } else {
        dot = NULL;
      }
    }
    if (dot){
      grid.setAt(j*myNi+i, dot);
    }
    // Kante 1:
    i = myNi-1;
    if (neighbourGrid[1]){
      dot = neighbourGrid[1]->edgePointAt(neighbourEdge[1],j);
      dot->addDependent(this);
    } else if (j==0 || j==myNj-1){
      dot = NULL; // Die Ecken wurden schon zuvor definiert
    } else {
      if (edge[1]){
        if (dynamic_cast<tAbsBead*>(edge[1]) || dynamic_cast<tAbsMagnet*>(edge[1]) ){
          dot = addProjectionSpring(i,j, BorderNet[1], edge[1], gridBase);
        } else {
          dot = new tPoint(this,edge[1]->vector());
        }
      } else if (magnetBase){
        dot = addProjectionSpring(i,j,BorderNet[1], magnetBase, gridBase);
      } else {
        dot = NULL;
      }
    }
    if (dot){
      grid.setAt(j*myNi+i, dot);
    }
  }


  if (grid.at(0) && grid.at(0+myNi-1) && grid.at((myNj-1)*myNi+(myNi-1)) && grid.at((myNj-1)*myNi+0)){
    center = ( grid.at(0                    )->vector()
              +grid.at(0            + myNi-1 )->vector()
              +grid.at((myNj-1)*myNi+(myNi-1))->vector()
              +grid.at((myNj-1)*myNi+ 0)->vector())*0.25;
  } else {
    center.setZero();
    error = true;
  }
  if (base){
    center = base->vector();
  }

  // Die Mitte des Feldes
  for (i=0;i<myNi;i++){
    for (j=0;j<myNj;j++){
      if (grid.at(j*myNi+i) == NULL){
        if (magnetBase){
          dot = addProjectionSpring(i,j,Inner, magnetBase, gridBase);
        } else {
          dot = new tPoint(this, center);
        }
        grid.setAt(j*myNi+i, dot);
      }
    }
  }
  return !error;
}


//-----------------------------------------------------------------------------

void tStructured2DInterpolGrid::refresh(void)
{
  int i,j,k,l,
      iter = fMeshIterations;
  int myNi,myNj;

  QString func;
  tPoint *p;
  tNetPoint *np;
  tList<tPoint*> gridBase;  // Basis fuer Gitterpunkte auf einer Flaeche

  tVector center;
  tReal pos;
  tList<tReal> springStrength[4];

  tVector *h,n_i,n_j,P;
  tReal d,s_i,s_j,d1;
  int pp;

  myNi = ni();
  myNj = nj();

  for (i=0;i<myNi*myNj;i++){
    gridBase.append(NULL);
  }

  if (initGrid(&gridBase)){
    // Die Längenverhältnisse der Elemente bestimmen
    for (i=0;i<myNi-1;i++){
      pos = ((float)i+0.5)/(float)(myNi-1);
      edgeDistrib.setFunc("pos:="+QString::number(pos));
//      if (neighbourGrid[0]){
//        springStrength[0].append(neighbourGrid[0]->distribOnEdge(neighbourEdge[0],pos));
//      } else {
        springStrength[0].append(edgeDistrib.calc("edge0"));
//      }
//      if (neighbourGrid[2]){
//        springStrength[2].append(neighbourGrid[2]->distribOnEdge(neighbourEdge[2],pos));
//      } else {
        springStrength[2].append(edgeDistrib.calc("edge2"));
//      }
    }
    for (i=0;i<myNj-1;i++){
      pos = ((float)i+0.5)/(float)(myNj-1);
      edgeDistrib.setFunc("pos:="+QString::number(pos));
//      if (neighbourGrid[1]){
//        springStrength[1].append(neighbourGrid[1]->distribOnEdge(neighbourEdge[1],pos));
//      } else {
        springStrength[1].append(edgeDistrib.calc("edge1"));
//      }
//      if (neighbourGrid[3]){
//        springStrength[3].append(neighbourGrid[3]->distribOnEdge(neighbourEdge[3],pos));
//      } else {
        springStrength[3].append(edgeDistrib.calc("edge3"));
//      }
    }

    //Das Netz an den Kanten erstellen.
    // Die Kanten 0 und 2 erzeugen
    h = (tVector*)malloc((myNi-2)*sizeof(tVector));
    for (l=0;l<3;l+=2){
      if (!neighbourGrid[l]){
        if (l==0){
          j = 0;
        } else {
          j = myNj-1;
        }
        for (k=0;k<iter;k++){
          pp = 0;
          for (i=1;i<myNi-1;i++){
            s_i = (springStrength[l].at(i-1)/(springStrength[l].at(i-1)+springStrength[l].at(i)));
            h[pp] = (gridAt(i-1,j)->vector()*(1.-s_i)
                   + gridAt(i+1,j)->vector()*s_i);
            pp++;
          }
          pp = 0;
          for (i=1;i<myNi-1;i++){
            p = dynamic_cast<tPoint*>(gridAt(i,j));
            np  = dynamic_cast<tNetPoint*>(gridAt(i,j));
            if (p){
              // Punkt uebernehmen
              p->setVector(h[pp]);
            } else if (np){
              // Punkt uebernehmen und durch das tNet auf die base-Flaeche projezieren.
              gridBase.at(j*myNi+i)->setVector(h[pp]);
            }
            pp++;
          }
        }
      }
    }
    free(h);

    // Die Kanten 1 und 3 erzeugen
    h = (tVector*)malloc((myNj-2)*sizeof(tVector));
    for (l=1;l<4;l+=2){
      if (!neighbourGrid[l]){
        if (l==1){
          i = myNi-1;
        } else {
          i = 0;
        }
        for (k=0;k<iter;k++){
          pp = 0;
          for (j=1;j<myNj-1;j++){
            s_j = (springStrength[l].at(j-1)/(springStrength[l].at(j-1)+springStrength[l].at(j)));
            h[pp] = (gridAt(i,j-1)->vector()*(1.-s_j)
                   + gridAt(i,j+1)->vector()*s_j);
            pp++;
          }
          pp = 0;
          for (j=1;j<myNj-1;j++){
            p = dynamic_cast<tPoint*>(gridAt(i,j));
            np  = dynamic_cast<tNetPoint*>(gridAt(i,j));
            if (p){
              // Punkt uebernehmen
              p->setVector(h[pp]);
            } else if (np){
              // Punkt uebernehmen und durch das tNet auf die base-Flaeche projezieren.
              gridBase.at(j*myNi+i)->setVector(h[pp]);
            }
            pp++;
          }
        }
      }
    }
    free(h);



    h = (tVector*)malloc((myNi-2)*(myNj-2)*sizeof(tVector));
    for (k=0;k<iter;k++){
      // Flaeche aus den vier Randkurven interpolieren, dies geschieht durch Mittelung entsprechend der um i,j liegenden Punkte.
      pp=0;
      for (i=1;i<myNi-1;i++){
        for (j=1;j<myNj-1;j++){
          s_i = (springStrength[0].at(i-1)/(springStrength[0].at(i-1)+springStrength[0].at(i)))*(1.-((float)j/(float)(myNj-1)))
               +(springStrength[2].at(i-1)/(springStrength[2].at(i-1)+springStrength[2].at(i)))*((float)j/(float)(myNj-1));
          s_j = (springStrength[1].at(j-1)/(springStrength[1].at(j-1)+springStrength[1].at(j)))*(1.-((float)i/(float)(myNi-1)))
               +(springStrength[3].at(j-1)/(springStrength[3].at(j-1)+springStrength[3].at(j)))*(((float)i/(float)(myNi-1)));
//          s_i = (springStrength[0].at(i-1)/(springStrength[0].at(i-1)+springStrength[0].at(i)));
//          s_j = (springStrength[1].at(j-1)/(springStrength[1].at(j-1)+springStrength[1].at(j)));
          d1 = (gridAt(i+1,j)->vector()-gridAt(i-1,j)->vector()).length_squared();
          d  = (gridAt(i,j+1)->vector()-gridAt(i,j-1)->vector()).length_squared();
          if (d1 > 0 && d >0){
            d = d1/(d1+d);
            d = (1.-cos(d*M_PI))/2.;
            d = (float)k/(float)iter*d+ (1.-(double)k/(double)iter)*0.5;
            h[pp] = (gridAt(i-1,j)->vector()*(1.-s_i)+
                      gridAt(i+1,j)->vector()*s_i)*(1.-d)+
                     (gridAt(i,j-1)->vector()*(1.-s_j)+
                      gridAt(i,j+1)->vector()*s_j)*d;
          } else {
            h[pp] = (gridAt(i-1,j)->vector()*(1.-s_i)+
                      gridAt(i+1,j)->vector()*s_i+
                      gridAt(i,j-1)->vector()*(1.-s_j)+
                     gridAt(i,j+1)->vector()*s_j)*0.5;
          }
          pp++;
        }
      }
      pp = 0;
      for (i=1;i<myNi-1;i++){
        for (j=1;j<myNj-1;j++){
          p = dynamic_cast<tPoint*>(gridAt(i,j));
          np  = dynamic_cast<tNetPoint*>(gridAt(i,j));
          if (p){
            // Punkt uebernehmen
            p->setVector(h[pp]);
          } else if (np){
            // Punkt uebernehmen und durch das tNet auf die base-Flaeche projezieren.
            gridBase.at(j*myNi+i)->setVector(h[pp]);
          }
          pp++;
        }
      }
    }
    free(h);
  }

  for (i=0;i<gridBase.count();i++){
    if (gridBase.at(i)){
      gridBase.at(i)->releaseOwner(this);
    }
  }
  gridBase.clear();

}
//-----------------------------------------------------------------------------

iElement* tStructured2DInterpolGrid::intrface(void)
{
  if (iface == NULL){
    iface = new iStructured2DInterpolGrid(this);
  }
  return iface;
}
//-----------------------------------------------------------------------------
