#include "tRefinedQuad.h"

tRefinedQuad::tRefinedQuad(void* theowner)
    : tQuad(theowner)
{
}
//-----------------------------------------------------------------------------

tRefinedQuad::~tRefinedQuad()
{
  for (int i=0; i<4;i++){
    for (int j=0; j<refinement[i].count(); j++){
      refinement[i].at(j)->removeDependent(this);
    }
    refinement[i].clear();
  }
}
//-----------------------------------------------------------------------------

iElement* tRefinedQuad::intrface(void)
{
  if (iface == NULL){
    iface = new iRefinedQuad(this);
  }
  return iface;
}
//-----------------------------------------------------------------------------

void tRefinedQuad::refresh(void)
{
  //nothing special to do.
}

//-----------------------------------------------------------------------------

void tRefinedQuad::setDot(int edge, int pos, tDot* d)
{
  edge = edge%4;
  if (pos>=refinement[edge].count()){
    refinement[edge].append(d);
    d->addDependent(this);
  }  else {
    if (d!=refinement[edge].at(pos)) {
      refinement[edge].at(pos)->removeDependent(this);
      refinement[edge].setAt(pos, d);
      d->addDependent(this);
    }
  }
}
//-----------------------------------------------------------------------------

void tRefinedQuad::setDotList(int edge, const tList<tElement*>& l)
{
  tList<tDot*> dotList;
  for (int i=0; i<l.count(); i++){
    tDot* d = dynamic_cast<tDot*>(l.at(i));
    if (d){
      dotList.append(d);
    }
  }
  for (int i=0;i<dotList.count(); i++){
    dotList.at(i)->addDependent(this);
  }
  for (int i=0;i<refinement[edge].count(); i++){
    refinement[edge].at(i)->removeDependent(this);
  }
  refinement[edge].clear();
  for (int i=0;i<dotList.count(); i++){
    refinement[edge].append(dotList.at(i));
  }
}
//-----------------------------------------------------------------------------

tList<tElement*> tRefinedQuad::dotList(int edge)
{
  tList<tElement*> l;
  for (int i=0; i< refinement[edge].count(); i++){
      l.append(refinement[edge].at(i));
  }
  return l;
}
