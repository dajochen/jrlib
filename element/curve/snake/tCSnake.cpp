#include "element/curve/snake/tCSnake.h"

tCSnake::tCSnake(void *theOwner, tList<tElement*> *List): tSnake(theOwner)
{
  c = new tCSpline(this);
  c->setCSplineType(jrCSLengthBased);
  s = NULL;
  if (List){
    addVertices(List);
  }
}
//-----------------------------------------------------------------------------

tCSnake::~tCSnake()
{
  removeAllVertices();
  c->releaseOwner(this);
}
//-----------------------------------------------------------------------------
/*tList<tElement*>& tCSnake::usedElements(void)
{
	tList<tElement*> L;
  int i;
  for (i=0;i<vertex.count();i++){
    L.append(vertex.at(i));
  }
	return L;
}*/
//-----------------------------------------------------------------------------

tSurface* tCSnake::reference(void){
  setElementLocked
  return s;
}
//-----------------------------------------------------------------------------

iElement* tCSnake::intrface(void){
  setElementLocked
	if (iface == NULL){
		iface = new iCSnake(this);
	}
	return iface;
}
//-----------------------------------------------------------------------------

void tCSnake::removeAllVertices(void){
  setElementLocked
  int i;
  for (i=0;i<vertex.count();i++){
    vertex.at(i)->removeDependent(this);
  }
  vertex.clear();
  s = NULL;
  invalidate(this);
}
//-----------------------------------------------------------------------------

void tCSnake::setVertices(tList<tElement*> List)
{
  removeAllVertices();
  addVertices(&List);
}
//-----------------------------------------------------------------------------

tList<tElement*> tCSnake::vertices(void)
{
  tList<tElement*> l;
  int i;
  for (i=0;i<vertex.count();i++){
    l.append(vertex.at(i));
  }
  return l;
}
//-----------------------------------------------------------------------------

void tCSnake::addVertices(tList<tElement*> *List){
  setElementLocked
  int i;
  tAbsMagnet *m;

//  vertex.clear();
//  s = NULL;
  i = 0;
  while (s==NULL && i< List->count()){
    m = dynamic_cast<tAbsMagnet*>(List->at(i));
    if (m){
      s = m->reference();
    }
    i++;
  }
  for (i=0;i<List->count();i++){
    m = dynamic_cast<tAbsMagnet*>(List->at(i));
    if (m && s && s == m->reference()){
      vertex.append(m);
      m->addDependent(this);
    }
  }
  invalidate(this);
}
//-----------------------------------------------------------------------------

tVector tCSnake::vectorAtAccurate(tReal t)
{
  setElementLocked
	tVector x;

	update();
  x = c->vectorAt(t);
  if (s){
    return s->vectorAt(x.x,x.y);
  } else {
    x.setZero();
    return  x;
  }
}
//-----------------------------------------------------------------------------

void tCSnake::uvPosition(tReal t, tReal *u, tReal *v){
  setElementLocked

  tVector x;
  update();

  x = c->vectorAt(t);
  *u = x.x;
  *v = x.y;
}

//-----------------------------------------------------------------------------

void tCSnake::refresh(void)
{
  tReal u,v;
  int i;
  c->clear();
  tList<tElement*> pl;

  for (i=0;i<vertex.count();i++){
    u=vertex.at(i)->uPosition();
    v=vertex.at(i)->vPosition();
    pl.append(new tPoint(NULL,u,v,0.));
  }
  c->addVertices(&pl);

}
//-----------------------------------------------------------------------------
