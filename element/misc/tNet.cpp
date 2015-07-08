#include "element/misc/tNet.h"

#include "element/point/tPoint.h"
#include "element/point/tAbsMagnet.h"
#include "element/point/tAbsBead.h"
#include "classes/tSolve.h"

#include "classes/utils.h"

tNet::tNet(void *theowner): tElement(theowner)
{
  iterations = -1;
  clear();
  invalidate(this);
}
//-----------------------------------------------------------------------------

tNet::~tNet()
{
  clear();
}
//-----------------------------------------------------------------------------

tNetNode* tNet::getNetNode(tElement *netPoint)
{
  tNetNode *link;
  int i;
  link = NULL;
  for (i=0;i<linkList.count();i++){
    if (linkList.at(i)->netPoint == netPoint){
      link = linkList.at(i);
      i = linkList.count();
    }
  }
  return link;
}
//-----------------------------------------------------------------------------

int tNet::calcDepth(void){
  // Bestimmt die größte Entfernung (Anzahl der zusammengehängten Federn) eines
  //Knotens bis zu einem eingespannten Knoten
  tList<int> depth,d0;
  int iKnot,iStart,iEnd;
  bool found;
  int i;
  for (i=0;i<nKnot.count();i++){
    depth.append(-1);
  }

  found = true;
  while (found){
    found = false;
    for (i=0;i<spring.count();i++){
      if (bKnot.contains(spring.at(i)->start)){
        iKnot = nKnot.firstIndexOf(spring.at(i)->end);
        if (iKnot >= 0 && depth.at(iKnot) != 1){
          depth.setAt(iKnot, 1);
          found = true;
        }
      } else if (bKnot.contains(spring.at(i)->end)){
        iKnot = nKnot.firstIndexOf(spring.at(i)->start);
        if (iKnot >= 0 && depth.at(iKnot) != 1){
          depth.setAt(iKnot, 1);
          found = true;
        }
      } else {
        iStart = nKnot.firstIndexOf(spring.at(i)->start);
        iEnd = nKnot.firstIndexOf(spring.at(i)->end);
        if (iStart >= 0 && iEnd >= 0){
          if (depth.at(iStart) == -1 && depth.at(iEnd) > 0){
            depth.setAt(iStart, depth.at(iEnd)+1);
            found = true;
          } else if (depth.at(iEnd) == -1 && depth.at(iStart) > 0){
            depth.setAt(iEnd, depth.at(iStart)+1);
            found = true;
          } else if (depth.at(iStart)>0 && depth.at(iEnd)>0){
            if (depth.at(iStart) > depth.at(iEnd)+1){
              depth.setAt(iStart, depth.at(iEnd)+1);
              found = true;
            } else if (depth.at(iEnd) > depth.at(iStart)+1){
              depth.setAt(iEnd, depth.at(iStart)+1);
              found = true;
            }
          }
        }
      }
    }
  }
  iEnd = 0;
  for (i=0;i<nKnot.count();i++){
    iEnd = max(depth.at(i),iEnd);
  }
  return iEnd;
}
//-----------------------------------------------------------------------------

tDot* tNet::getRefPoint(tElement *netPoint)
{
  setElementLocked
  tNetNode *link;

  link = getNetNode(netPoint);
  if (link){
    return link->refPoint;
  } else {
    return NULL;
  }
}

//-----------------------------------------------------------------------------
tVector tNet::getVector(tElement *netPoint)
{
  setElementLocked
  tNetNode *link;
  update();
  link = getNetNode(netPoint);
  if (link){
    return link->knot->vector();
  } else {
    return tVector(0,0,0);
  }
}
//-----------------------------------------------------------------------------

void tNet::setRefPoint(tElement* netPoint, tElement *refPoint)
{
  setElementLocked
  tNetNode *link;
  tDot *refDot;

  if (netPoint){
    // nach bestehenden Verknüpfungen zum netPoint suchen.
    link = getNetNode(netPoint);
    refDot = dynamic_cast<tPoint*>(refPoint);
    if (!refDot) refDot = dynamic_cast<tAbsBead*>(refPoint);
    if (!refDot) refDot = dynamic_cast<tAbsMagnet*>(refPoint);
    // Es wurde festgestellt, ob refPoint ein AbsBead, AbsMagnet, oder Point ist)

    if (refDot){
      if (!link){
        // wenn noch kein Node vorhanden ist, wird ein neuer erstellt.
        link = new tNetNode;
        linkList.append(link);
        nKnot.append(link);
        link->netPoint = netPoint;
        link->knot = NULL;
        link->refPoint = NULL;
      } else {
        link->refPoint->removeDependent(this);
        link->knot->releaseOwner(this);
      }

      link->refPoint = refDot;
//      refPoint->addDependent(this);
      if (dynamic_cast<tPoint*>(refPoint)){
        tPoint *p;
        p = dynamic_cast<tPoint*>(refPoint);
        link->knot = new tPoint(this,p->vector());
      } else if (dynamic_cast<tAbsBead*>(refPoint)){
        tAbsBead *b;
        b = dynamic_cast<tAbsBead*>(refPoint);
        link->knot = new tAbsBead(this,b->reference(),b->position());
      } else if (dynamic_cast<tAbsMagnet*>(refPoint)){
        tAbsMagnet *m;
        m = dynamic_cast<tAbsMagnet*>(refPoint);
        link->knot = new tAbsMagnet(this,m->reference(),m->uPosition(),m->vPosition());
      }
    } else if (link){
      linkList.removeFirst(link);
      bKnot.removeFirst(link);
      nKnot.removeFirst(link);
      link->refPoint->removeDependent(this);
      link->knot->releaseOwner(this);
      delete link;
    }
  }
  invalidate(this);
}
//-----------------------------------------------------------------------------

void tNet::clear(void)
{
  setElementLocked
  int i;
  tNetNode *link;


  for (i=0;i<bKnot.count();i++){
    bKnot.at(i)->refPoint->removeDependent(this);
  }
  bKnot.clear();
  nKnot.clear();
  for (i=0;i<linkList.count();i++){
    link = linkList.at(i);
    link->knot->releaseOwner(this);
  }
  linkList.clear();

  for (i=0;i<spring.count();i++){
    spring.at(i)->spring->releaseOwner(this);
    delete spring.at(i);
  }

  spring.clear();
  knotDepth = 0;
}
//-----------------------------------------------------------------------------

void tNet::setBorderKnot(tElement *netPoint)
{
  setElementLocked
  tNetNode *link;
  link = getNetNode(netPoint);
  if (link && !bKnot.contains(link)){
    link->refPoint->addDependent(this);
    bKnot.append(link);
    nKnot.removeFirst(link);
  }
}
//-----------------------------------------------------------------------------

void tNet::addSpring(tElement *a, tElement *b, tReal c, tReal l0)
{
  setElementLocked
  tLine *l;
  tSpring *mySpring;
  tRGB color;
  tNetNode *A, *B;

  A = getNetNode(a);
  B = getNetNode(b);
  if (A && B){
    if (iface){
      iface->color();
    } else {
      color.setColor(20,120,130);
    }

    l = new tLine(this,A->knot,B->knot);
    if (iface){
      l->intrface()->setColor(color);
    }
    mySpring = new tSpring;
    spring.append(mySpring);

    mySpring->spring = l;
    mySpring->start = A;
    mySpring->end = B;
    mySpring->l0 = l0;
    mySpring->stiffness = c;

    if (spring.count()==1){
       maxStiffness = mySpring->stiffness;
    } else {
      maxStiffness = max(mySpring->stiffness,maxStiffness);
    }
    knotDepth = calcDepth();
    invalidate(this);
  }

}
//-----------------------------------------------------------------------------

int tNet::nSprings(void)
{
  setElementLocked
  update();
  return spring.count();
}

//-----------------------------------------------------------------------------

tLine* tNet::springLine(int index)
{
  setElementLocked
  update();
  if (index >= 0 && index < spring.count()){
    return spring.at(index)->spring;
  } else {
    return NULL;
  }
}
//-----------------------------------------------------------------------------

void tNet::refresh(void)
{
  int i,j,k,nForces,maxNForces,iter;
  tVector force,uDir,vDir,wDir,dx;
  tReal dt,u,v,c,l,l0;//,maxStiffness;
  tJSolve *LGS;

  tDot *knot;
  tList<tVector> nKnotForce;

  tAbsMagnet *m;
  tAbsBead *b;
  tPoint *p;
  tSurface *s;
  tCurve *curve;
  tNetNode *link;

  for (i=0;i<bKnot.count();i++){
    link = bKnot.at(i);
    if (dynamic_cast<tPoint*>(link->refPoint)){
      tPoint *p;
      p = dynamic_cast<tPoint*>(link->refPoint);
      ((tPoint*)link->knot)->setVector(p->vector());
    } else if (dynamic_cast<tAbsBead*>(link->refPoint)){
      tAbsBead *b;
      b = dynamic_cast<tAbsBead*>(link->refPoint);
      ((tAbsBead*)link->knot)->setReference(b->reference());
      ((tAbsBead*)link->knot)->setPosition(b->position());
    } else if (dynamic_cast<tAbsMagnet*>(link->refPoint)){
      tAbsMagnet *m;
      m = dynamic_cast<tAbsMagnet*>(link->refPoint);
      ((tAbsMagnet*)link->knot)->setReference(m->reference());
      ((tAbsMagnet*)link->knot)->setPosition(m->uPosition(),m->vPosition());
    }
  }

  if (spring.count() > 0){
    if (iterations <= 0){
      iter = knotDepth*90;
    } else {
      iter = iterations;
    }

    LGS = new tJSolve(3);
    dt = 0.007;

    for (i=0;i<iter;i++){
      nKnotForce.clear();
      l = -1.;
      maxNForces = 0;

      for (j=0;j<nKnot.count();j++){
        knot = nKnot.at(j)->knot;
        force.setZero();
        nForces = 0;
        for (k=0;k<spring.count();k++){
          if (spring.at(k)->spring->start() == knot || spring.at(k)->spring->end() == knot){
            if (spring.at(k)->spring->start() == knot){
              dx = (tVector)*spring.at(k)->spring->end()-(tVector)*knot;
            } else {
              dx = (tVector)*spring.at(k)->spring->start()-(tVector)*knot;
            }
            l = dx.length();
            if (l > 0){
              c = spring.at(k)->stiffness/**spring.at(k)->stiffnessFactor)*//maxStiffness;
              l0 = spring.at(k)->l0;

              force = force + dx *(1./l *(l-l0)*c);// (1./l): um einen Einheitsvektor für dx zu Bilden.
              nForces ++;
            } else {
              force.setZero();
              nForces ++;
            }
          }
        }

        if (nForces > 0){
          force = force * (0.5);
        }
        maxNForces = max(nForces,maxNForces);
        nKnotForce.append(force);
      }
      for (j=0;j<nKnot.count();j++){
        knot = nKnot.at(j)->knot;
        force = nKnotForce.at(j)*(1./maxNForces);;

        p = dynamic_cast<tPoint*>(knot);
        m = dynamic_cast<tAbsMagnet*>(knot);
        b = dynamic_cast<tAbsBead*>(knot);
        if (m){
          u = m->uPosition();
          v = m->vPosition();
          s = m->reference();
          uDir = (s->vectorAt(u+dt,v)-s->vectorAt(u-dt,v))*0.5;// Zentraldifferenz zur Bestimmung der Ableitung der Oberflaeche
          vDir = (s->vectorAt(u,v+dt)-s->vectorAt(u,v-dt))*0.5;
          wDir = uDir % vDir;

          LGS->MATRIX[0][0] = uDir.x; LGS->MATRIX[0][1] = vDir.x; LGS->MATRIX[0][2] = wDir.x; LGS->RHS[0] = force.x;
          LGS->MATRIX[1][0] = uDir.y; LGS->MATRIX[1][1] = vDir.y; LGS->MATRIX[1][2] = wDir.y; LGS->RHS[1] = force.y;
          LGS->MATRIX[2][0] = uDir.z; LGS->MATRIX[2][1] = vDir.z; LGS->MATRIX[2][2] = wDir.z; LGS->RHS[2] = force.z;
          LGS->solve();

          u = u +  LGS->x[0]*dt*0.7;
          v = v + LGS->x[1]*dt*0.7;
          v = max(v,0.);
          v = min(v,1.);
          u = max(u,0.);
          u = min(u,1.);
          m->setUPosition(u);
          m->setVPosition(v);
        } else if (b){
          u = b->position();
          curve = b->reference();

          uDir = (curve->vectorAt(u+dt)-curve->vectorAt(u-dt))*0.5;// Zentraldifferenz zur Bestimmung der Ableitung der Oberflaeche
          vDir.setZero();
          vDir.x = dt;
          wDir = uDir % vDir;
          if (wDir.length_squared() == 0){
            vDir.y = dt;
            wDir = uDir % vDir;
          }
          vDir = wDir%uDir;


          LGS->MATRIX[0][0] = uDir.x; LGS->MATRIX[0][1] = vDir.x; LGS->MATRIX[0][2] = wDir.x; LGS->RHS[0] = force.x;
          LGS->MATRIX[1][0] = uDir.y; LGS->MATRIX[1][1] = vDir.y; LGS->MATRIX[1][2] = wDir.y; LGS->RHS[1] = force.y;
          LGS->MATRIX[2][0] = uDir.z; LGS->MATRIX[2][1] = vDir.z; LGS->MATRIX[2][2] = wDir.z; LGS->RHS[2] = force.z;
          LGS->solve();

          u = u +  LGS->x[0]*dt;
          u = max(u,0.);
          u = min(u,1.);
          b->setPosition(u);

        } else if (p){
          p->setVector(p->vector()+force);
        }
      }
    }
    delete LGS;
  }
}
//-----------------------------------------------------------------------------
void tNet::setColor(tRGB color)
{
  setElementLocked
  int i;
  for (i=0;i<spring.count();i++){
    spring.at(i)->spring->intrface()->setColor(color);
  }
  intrface()->setColor(color);
}

//-----------------------------------------------------------------------------

iElement* tNet::intrface(void)
{
  if (iface == NULL){
    iface = new iNet(this);
  }
  return iface;
}
//-----------------------------------------------------------------------------
