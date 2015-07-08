#include "element/curve/tPolyCurve.h"

#include "element/tGroup.h"
#include "classes/utils.h"

tPolyCurve::tPolyCurve(void *theOwner): tCurve(theOwner)
{
	thePolyCurveType = jrPCLengthBased;
  fgapTolerance = 0.;
  closePolyCurve = false;
  freversedCurve.append(0);
  freversedCurve.append(1);
  freversedCurve.append(0);
  freversedCurve.append(1);
}
//-----------------------------------------------------------------------------

tPolyCurve::~tPolyCurve()
{
	removeAllCurves();
}
//-----------------------------------------------------------------------------

iElement* tPolyCurve::intrface(void){
	if (iface == NULL){
		iface = new iPolyCurve(this);
	}
	return (iface);
}
//-----------------------------------------------------------------------------

void tPolyCurve::deleteConnections(void)
{
  setElementLocked
  for (int i=0; i< curve.count(); i++){
    curve.at(i)->removeDependent(this);
  }
  curve.clear();

}
//-----------------------------------------------------------------------------

void tPolyCurve::createConnections(void)
{
  setElementLocked
  deleteConnections();
  for (int i=0;i<supportCurve.count();i++){
    tCurve *current, *next;
    bool currentReversed = false, nextReversed = false;
    current = supportCurve.at(i);
    if (freversedCurve.count()>i && freversedCurve.at(i)){
      currentReversed = true;
    }


    if (i<supportCurve.count()-1){
      next = supportCurve.at(i+1);
      if (freversedCurve.count()>i+1 && freversedCurve.at(i+1)){
        nextReversed = true;
      }
    } else {
      if (closePolyCurve){
        next = supportCurve.at(0);
      } else {
        next = NULL;
      }
    }

    if (current){
      curve.append(current);
      current->addDependent(this);
      if (next){
        tAbsBead *currentEnd = new tAbsBead(NULL, current, 1.),
                 *nextStart = new tAbsBead(NULL, next, 0.);

        if (current && currentReversed){
          currentEnd->setPosition(0);
        }
        if (next && nextReversed){
          nextStart->setPosition(1);
        }

        if ( fgapTolerance > 0 &&
             (currentEnd->vector()-nextStart->vector()).length() > fgapTolerance ){
          curve.append(new tLine(NULL, currentEnd, nextStart));
        } else {
          currentEnd->setReference(NULL);
          nextStart->setReference(NULL);
        }
      }
    }
  }
}
//-----------------------------------------------------------------------------

void tPolyCurve::addElement(tElement* el)
{
  setElementLocked
  tCurve *c = dynamic_cast<tCurve*>(el);
  tGroup *g = dynamic_cast<tGroup*>(el);
  if (c) {
  	supportCurve.append(c);
  	c->addDependent(this);
  	invalidate(this);
  } else if (g) {
    int i;
    for (i=0;i<g->nElements();i++){
      addElement(g->element(i));
    }
  }

}
//-----------------------------------------------------------------------------

void tPolyCurve::removeAllCurves()
{
  setElementLocked
	int i;
	deleteConnections();
	for (i=0;i<supportCurve.count();i++){
		supportCurve.at(i)->removeDependent(this);
	}
	supportCurve.clear();
	invalidate(this);
}
//-----------------------------------------------------------------------------

void tPolyCurve::setCurves(tList<tElement*> list)
{
  setElementLocked;
  removeAllCurves();
  addList(&list);
}
//-----------------------------------------------------------------------------

void tPolyCurve::addList(tList<tElement*> *list)
{
  setElementLocked
  int i;
  if (list){
    for (i=0;i<list->count();i++){
      addElement(list->at(i));
    }
  }
}
//-----------------------------------------------------------------------------

tList<tElement*> tPolyCurve::curves(void){
  setElementLocked;
  tList<tElement*> l;
  int i,n;
  n = supportCurve.count();
  for (i=0;i<n;i++){
    l.append(supportCurve.at(i));
  }
  return l;
}
//-----------------------------------------------------------------------------

tVector tPolyCurve::vectorAtAccurate(tReal t)
{
  setElementLocked
	update();

  if (curve.count() > 0 && dt.count()==curve.count()){
    tReal lastT = 0.;
    int i=0;
    while ( i<curve.count()-1 && t > dt.at(i)){
      lastT = dt.at(i);
      i++;
    }
    double tt = (t-lastT)/(dt.at(i)-lastT);

    int id = supportCurve.firstIndexOf(curve.at(i));
    if (id>=0 && freversedCurve.count()>id && freversedCurve.at(id) != 0){
      tt = 1.-tt;
    }
  	return curve.at(i)->vectorAt(tt);
  } else {
    return tVector(0.,0.,0.);
  }
}
//-----------------------------------------------------------------------------

tPolyCurveType tPolyCurve::polyCurveType(void)
{
  setElementLocked
	return thePolyCurveType;
}
//-----------------------------------------------------------------------------

void tPolyCurve::setPolyCurveType(tPolyCurveType plt)
{
  setElementLocked
	thePolyCurveType = plt;
	invalidate(this);
}
//-----------------------------------------------------------------------------

void tPolyCurve::setPolyCurveType(int type){
  type = type % 2;
  if (type==jrPCCurveBased){
    setPolyCurveType(jrPCCurveBased);
  } else {//(type == jrPCLengthBased) {
    setPolyCurveType(jrPCLengthBased);
  }
}
//-----------------------------------------------------------------------------

void tPolyCurve::refresh(void)
{

  createConnections();

  dt.clear();

  if (thePolyCurveType == jrPCLengthBased){
    tReal L = 0.;
    for (int i=0; i<curve.count(); i++){
      L += curve.at(i)->length();
      dt.append(L);
    }
    for (int i=0; i<curve.count(); i++){
      dt.setAt(i, dt.at(i)/L);
    }

  } else if (thePolyCurveType == jrPCCurveBased){
    for (int i=1; i<=curve.count(); i++){
			dt.append( tReal(i)/tReal(curve.count()) );
		}
	}
}
//-----------------------------------------------------------------------------
