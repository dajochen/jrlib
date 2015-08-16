/*
 * tLayer.cpp
 *
 *  Created on: 11.01.2009
 *      Author: Jochen
 */

#include "model/tLayer.h"
// Points
#include "element/point/tFunctionPoint.h"

// Curves
#include "element/curve/tPolygonCurve.h"
#include "element/curve/tOffsetCurve.h"
#include "element/curve/tOffsetCurve2.h"
#include "element/curve/tDistortedSpline.h"
#include "element/curve/tTransformedDotListCurve.h"

#include "element/curve/tFunctionCurve.h"

// Surfaces
#include "element/surface/tPropSurface.h"
#include "element/surface/tPropHubSurface.h"
#include "element/surface/tWageningenBSeries.h"
#include "element/surface/tKaSeries.h"
#include "element/surface/tDuct19A.h"

#include "element/misc/tPolygon.h"
#include "element/misc/tQuad.h"
#include "element/misc/tTriangle.h"
#include "element/misc/tTrianglePatch.h"

//planes
#include "element/plane/tThreePointPlane.h"

//misc
#include "element/misc/draping/tDrapedPatch.h"


tLayer::tLayer(void *theowner, tVariableNameSpace *vars, QString allowedType)
: tGroup(theowner, allowedType)
{
	owningModel = theowner;
	variables = vars;
}
//-----------------------------------------------------------------------------

tLayer::~tLayer()
{
	clear();
}
//-----------------------------------------------------------------------------

iElement* tLayer::intrface(void){
  setElementLocked
  if (iface == NULL){
    iface = new iLayer(this);
  }
  return iface;
}
//-----------------------------------------------------------------------------
/**
 * Adds an element at the end of the list. If an element is added it must be
 * attached to one layer only. Hence is will be removed from the other layers.
 */
tElement* tLayer::append(tElement* el)
{
  setElementLocked
  tElement *eOut;
  eOut = tGroup::append(el);
  if (eOut){
    eOut->addOwner(owningModel);
    removeFromOtherLayers(eOut);
  }
  return eOut;
}
//-----------------------------------------------------------------------------
/**
 * Adds an element at the beginning of the list. If an element is added it must be
 * attached to one layer only. Hence is will be removed from the other layers.
 */
tElement* tLayer::prepend(tElement* el)
{
  setElementLocked
  tElement *eOut;
  eOut = tGroup::prepend(el);
  if (eOut){
    eOut->addOwner(owningModel);
    removeFromOtherLayers(eOut);
  }
  return eOut;
}
/*
void tLayer::setElements(const tList<tElement *> &l)
{
    clear();
    for (int i=0;i<l.count(); i++) {
        append(l.at(i));
    }
}*/
//-----------------------------------------------------------------------------

/**
 * Removes an element from any other layer.
 */
void tLayer::removeFromOtherLayers(tElement* el)
{
  setElementLocked
  tList<tElement*> dependents = el->dependents();

  for (int i=0;i<dependents.count();i++){
    tLayer* other = dynamic_cast<tLayer*>(dependents.at(i));
    if (other && other != this){
      other->removeElement(el, false);
    }
  }
}
//-----------------------------------------------------------------------------

void tLayer::removeElement(int i)
{
  setElementLocked
  if (i>=0 && i<nElements()){
    tElement *el = element(i);
    el->releaseOwner(owningModel);
    tGroup::removeElement(i);
  }
}
//-----------------------------------------------------------------------------

void tLayer::clear(void)
{
	setElementLocked
	while(nElements()){
		removeElement(last(), false);
	}
}
//-----------------------------------------------------------------------------
/**
 * Removes an element from this layer and all sublayers
 */
void tLayer::removeElement(tElement *el, bool recursive)
{
  setElementLocked

  if (removeAllElements(el)){
    //el->releaseOwner(owningModel); //this is allready done in removeAllElements()
  } else {
    for (int i=0; recursive && i<nElements(); i++){
      tLayer* l = dynamic_cast<tLayer*>(element(i));
      if (l){
        l->removeElement(el, recursive);
      }
    }
  }
}
//-----------------------------------------------------------------------------
/**
 * Looks for an element called <name> which is of the type <type>
 */
const tList<tElement*> tLayer::elementsByName(const QRegularExpression &re, const QString &type)
{
    setElementLocked
    int i;
    tList<tElement*> found;

  for (i=nElements()-1;i>=0;i--){
    tElement *e = element(i);
    iElement *iface = e->intrface();

    if (re.match(iface->name()).hasMatch()){
        if (type.isEmpty() || iface->isOfType(type)){
                found.append(e);
        }
    }
    tLayer* l = dynamic_cast<tLayer*>(e);
    if (l){
      found.append( l->elementsByName(re, type) );
    }
  }

  return found;
}
//-----------------------------------------------------------------------------

/**
 * Looks for an element called <name> which is of the type <type>
 */
tElement* tLayer::elementByName(const QString &name, const QString &type)
{
	setElementLocked
	int i;
	tElement *e;
	iElement *iface;

  for (i=nElements()-1;i>=0;i--){
  	e = element(i);
  	iface = e->intrface();

  	if (iface->name() == name){
  		if (type.isEmpty() || iface->isOfType(type)){
				return e;
  		}
  	}
  	tLayer* l = dynamic_cast<tLayer*>(e);
  	if (l){
  	  e = l->elementByName(name, type);
  	  if (e){
  	    return e;
  	  }
  	}
  }

  return NULL;
}
//-----------------------------------------------------------------------------

/**
 * Creates a new element of the type set in <type>.
 */
tElement* tLayer::addElement(const QString &type, const QString &name)
{
  setElementLocked;

  tElement *el = NULL;

  el = NULL;

  // user-variables
  if (type == iRealVariable::theType()){
    el = variables->addRealVariable("");
  } else if (type == iVectorVariable::theType()){
    el = variables->addVectorVariable("");
  } else if (type == iListVariable::theType()){
    el = variables->addListVariable("");
  } else// {
    // Dots, points, etc.
    if (type == iPoint::theType()){
      el = new tPoint(NULL);
    } else if (type == iRelPoint::theType()){
      el = new tRelPoint(NULL);
    } else if (type == iMidPoint::theType()){
      el = new tMidPoint(NULL);
    } else if (type == iProjectedPoint::theType()){
      el = new tProjectedPoint(NULL);
    } else if (type == iOffsetPoint::theType()){
      el = new tOffsetPoint(NULL);
    } else if (type == iRotatedPoint::theType()){
      el = new tRotatedPoint(NULL);
    } else if (type == iFunctionPoint::theType()){
      el = new tFunctionPoint(NULL, variables);
    } else if (type == iAbsBead::theType()){
      el = new tAbsBead(NULL);
    } else if (type == iAbsMagnet::theType()){
      el = new tAbsMagnet(NULL);
    } else if (type == iStickyMagnet::theType()){
      el = new tStickyMagnet(NULL);
    // curves
    } else if (type == iCSpline::theType()){
      el = new tCSpline(NULL);
    } else if (type == iBSpline::theType()){
      el = new tBSpline(NULL);
    } else if (type == iHermiteSpline::theType()){
      el = new tHermiteSpline(NULL);
    } else if (type == iDxfSpline::theType()){
      el = new tDxfSpline(NULL);
    } else if (type == iLine::theType()){
      el = new tLine(NULL);
    } else if (type == iPolygonCurve::theType()){
      el = new tPolygonCurve(NULL);
    } else if (type == iSubCurve::theType()){
      el = new tSubCurve(NULL);
    } else if (type == iRotatedCurve::theType()){
      el = new tRotatedCurve(NULL);
    } else if (type == iPolyCurve::theType()){
      el = new tPolyCurve(NULL);
    } else if (type == iMidCurve::theType()){
      el = new tMidCurve(NULL);
    } else if (type == iSumCurve::theType()){
      el = new tSumCurve(NULL);
    } else if (type == iOffsetCurve::theType()){
      el = new tOffsetCurve(NULL);
    } else if (type == iOffsetCurve2::theType()){
      el = new tOffsetCurve2(NULL);
    } else if (type == iDistortedSpline::theType()){
      el = new tDistortedSpline(NULL);
    } else if (type == iTransformedDotListCurve::theType()){
      el = new tTransformedDotListCurve(NULL);
    } else if (type == iFunctionCurve::theType()){
      el = new tFunctionCurve(NULL,variables);
    // snakes
    } else if (type == iLineSnake::theType()){
      el = new tLineSnake(NULL);
    } else if (type == iCSnake::theType()){
      el = new tCSnake(NULL);
    // sufaces
    } else if (type == iRuledSurface::theType()){
      el = new tRuledSurface(NULL);
    } else if (type == iCLoft::theType()){
      el = new tCLoft(NULL);
    } else if (type == iRotatedSurface::theType()){
      el = new tRotatedSurface(NULL);
    } else if (type == iRevolvedSurface::theType()){
      el = new tRevolvedSurface(NULL);
    } else if (type == iSubSurface::theType()){
      el = new tSubSurface(NULL);
    } else if (type == iFunctionSurface::theType()){
      el = new tFunctionSurface(NULL);
    // special propeller surfaces
    } else if (type == iPropSurface::theType()){
      el = new tPropSurface(NULL);
    } else if (type == iWageningenBSeries::theType()){
      el = new tWageningenBSeries(NULL);
    } else if (type == iKaSeries::theType()){
      el = new tKaSeries(NULL);
    } else if (type == iDuct19A::theType()){
      el = new tDuct19A(NULL);
    } else if (type == iPropHubSurface::theType()){
      el = new tPropHubSurface(NULL);
    // planes
    } else if (type == iXPlane::theType()){
      el = new tXPlane(NULL);
    } else if (type == iYPlane::theType()){
      el = new tYPlane(NULL);
    } else if (type == iZPlane::theType()){
      el = new tZPlane(NULL);
    } else if (type == iPlane::theType()){
        el = new tPlane(NULL);
    } else if (type == iThreePointPlane::theType()){
      el = new tThreePointPlane(NULL);
    // miscellaneuos
    } else if (type == iPolygon::theType()){
      el = new tPolygon(NULL);
    } else if (type == iTriangle::theType()){
      el = new tTriangle(NULL);
    } else if (type == iTrianglePatch::theType()){
      el = new tTrianglePatch(NULL);
    } else if (type == iQuad::theType()){
      el = new tQuad(NULL);
    } else if (type == iDrapedPatch::theType()){
      el = new tDrapedPatch(NULL);
    // 2D-Grids
    } else if (type == iStructured2DSurfaceGrid::theType()){
      el = new tStructured2DSurfaceGrid(NULL);
    } else if (type == iStructured2DInterpolGrid::theType()){
      el = new tStructured2DInterpolGrid(NULL);
    } else if (type == iStructured2DSubGrid::theType()){
      el = new tStructured2DSubGrid(NULL);
    // 2D-Grids
    } else if (type == iStructured3DBlockMeshGrid::theType()){
      el = new tStructured3DBlockMeshGrid(NULL);
    } else if (type == iStructured3DTwoSidedGrid::theType()){
      el = new tStructured3DTwoSidedGrid(NULL);
    // Organisatorisches
    } else if (type == iGroup::theType()){
      el = new tGroup(NULL);
    } else if (type == iLayer::theType()){
      el = new tLayer(owningModel, variables);
    }

    tElement *allowed = append(el);

    if (allowed){
      if (!name.isEmpty()){
        el->intrface()->setName(name);
      }
      invalidate(this);
    } else if (el) {
      el->releaseOwner(NULL);
      el = NULL;
    }
  //}
  return el;
}
//-----------------------------------------------------------------------------

tElement* tLayer::addDeepCopy(tElement *copy, tList<tCopyPasteOption> options)
{
  setElementLocked
  tElement* paste = NULL;
  if (copy){

    if (options.contains(cpoDotsToRelPoints) && dynamic_cast<tDot*>(copy)){
      tRelPoint *rp = dynamic_cast<tRelPoint*>(addElement(iRelPoint::theType()));
      rp->setReference(copy);
      rp->setOffset(tVector(0,0,0));
      paste = rp;
    } else {
      paste = addElement(copy->intrface()->type());
    }

    if (paste){
      //int nProps = copy->intrface()->nProperties();

      for ( int propIndex=0; propIndex<(int)(copy->intrface()->nProperties()); propIndex++ ){

        int iVal;
        tReal rVal;
        bool bVal;
        tVector vVal;
        tRGB rgbVal;
        QString strVal;
        tElement* elVal;

        tList<int> iListVal;
        tList<tReal> rListVal;
        tList<bool> bListVal;
        tList<tVector> vListVal;
        tList<tRGB> rgbListVal;
        tList<QString> strListVal;
        tList<tElement*> elListVal;

        void *value;

        QString propType = copy->intrface()->getPropertyType(propIndex),
                propName = copy->intrface()->getPropertyName(propIndex);
            char dbg[500];
            strcpy(dbg, qPrintable(propType));

        if (propType=="Int"){
          value = &iVal;
        } else if (propType=="Real"){
          value = &rVal;
        } else if (propType=="Bool"){
          value = &bVal;
        } else if (propType=="Vector"){
          value = &vVal;
        } else if (propType=="RGB"){
          value = &rgbVal;
        } else if (propType=="String"){
          value = &strVal;
        } else if (propType.endsWith("List")){
          if (propType=="IntList") {
            value = &iListVal;
          } else if (propType=="RealList") {
            value = &rListVal;
          } else if (propType=="BoolList") {
            value = &bListVal;
          } else if (propType=="VectorList") {
            value = &vListVal;
          } else if (propType=="RGBList") {
            value = &rgbListVal;
          } else if (propType=="StringList") {
            value = &strListVal;
          } else {
            value = &elListVal;
          }
        } else {
          value = &elVal;
        }

        copy->intrface()->getPropertyValue(propName,propType,value);

        if (value == &elListVal) {
          for (int i=0;i<elListVal.count(); i++){
            tElement *oldListItem = elListVal.at(i),
                     *newListItem = addDeepCopy(oldListItem, options);
            elListVal.setAt(i,newListItem);
          }
        }

        if (value==&elVal){
            //ToDo: tElemente muessen hier umgeaendert werden, da die interface-Klasse einmal &el und einmal el erwartet.
            //      Etwas unschoen. Bei Gelegenheit mal den interface generator und alle abhaengigen bearbeiten...
          value = addDeepCopy(elVal, options);
        }

        paste->intrface()->setPropertyValue(propName,propType,value);

      }

    }
  }
  return paste;
}
//-----------------------------------------------------------------------------

tPoint* tLayer::addPoint(tVector x)
{
	setElementLocked
	tPoint *p;
    p = new(tPoint)(NULL,x);
	if (append(p) == NULL){
      p->releaseOwner(NULL);
	  p = NULL;
	} else {
	  invalidate(this);
	}
	return p;
}
//-----------------------------------------------------------------------------

tRelPoint* tLayer::addRelPoint(tElement *el, tVector x)
{
	setElementLocked
  tRelPoint *p;
  p = new(tRelPoint)(NULL,el,x);
  if (append(p) == NULL){
    p->releaseOwner(NULL);
    p->setReference(NULL);
    p = NULL;
  } else {
    invalidate(this);
  }
  return p;
}
//-----------------------------------------------------------------------------

tMidPoint* tLayer::addMidPoint(tElement *el)
{
	setElementLocked
  tMidPoint *p;
  p = new(tMidPoint)(NULL,el);
  if (append(p) == NULL){
    p->releaseOwner(NULL);
    p->removeAll();
    p = NULL;
  } else {
    invalidate(this);
  }
  return p;
}
//----------------------------------------------------------------------------

tAbsBead* tLayer::addAbsBead(tElement *curve, tReal t)
{
	setElementLocked
	tAbsBead *b;
    b = new(tAbsBead)(NULL,curve,t);
  if (append(b) == NULL){
    b->releaseOwner(NULL);
    b->setReference(NULL);
    b = NULL;
  } else {
    invalidate(this);
  }
	return b;
}
//----------------------------------------------------------------------------

tAbsMagnet* tLayer::addAbsMagnet(tElement *surf, tReal u, tReal v)
{
  setElementLocked
  tAbsMagnet *m;
  m = new tAbsMagnet(NULL,surf,u,v);
  if (append(m) == NULL){
    m->releaseOwner(NULL);
    m->setReference(NULL);
    m = NULL;
  } else {
    invalidate(this);
  }
  return m;
}
//----------------------------------------------------------------------------

tStickyMagnet* tLayer::addStickyMagnet(void)
{
  setElementLocked
  tStickyMagnet *m;
  m = new tStickyMagnet(NULL);
  if (append(m) == NULL){
    m->releaseOwner(NULL);
    m = NULL;
  } else {
    invalidate(this);
  }
  return m;
}
//----------------------------------------------------------------------------

tProjectedPoint* tLayer::addProjectedPoint(void)
{
  setElementLocked
  tProjectedPoint *pp;
  pp = new tProjectedPoint(NULL);
  if (append(pp) == NULL){
    pp->releaseOwner(NULL);
    pp = NULL;
  } else {
    invalidate(this);
  }  return pp;
}
//----------------------------------------------------------------------------

tOffsetPoint* tLayer::addOffsetPoint(tElement *surf, tReal u, tReal v, tReal  dist)
{
	setElementLocked
	tOffsetPoint *op;
    op = new tOffsetPoint(NULL,surf,u,v,dist);
  if (append(op) == NULL){
    op->releaseOwner(NULL);
    op->setReference(NULL);
    op = NULL;
  } else {
    invalidate(this);
  }	return op;
}
//-----------------------------------------------------------------------------

tRotatedPoint* tLayer::addRotatedPoint(tElement* x, tElement* axis, tReal angle)
{
	setElementLocked
	tRotatedPoint* p;
	tDot *refDot;
	tLine *Axis;

	refDot = dynamic_cast<tDot*>(x);
	Axis = dynamic_cast<tLine*>(axis);
    p = new tRotatedPoint(NULL,refDot,Axis,angle);
  if (append(p) == NULL){
    p->releaseOwner(NULL);
    p->setAxis(NULL);
    p->setReference(NULL);
    p = NULL;
  } else {
    invalidate(this);
  }	return p;
}

//-----------------------------------------------------------------------------

tLine* tLayer::addLine(tElement *C1, tElement *C2){
	setElementLocked
  tLine *l;
  l = new(tLine)(NULL,C1,C2);
  if (append(l) == NULL){
    l->releaseOwner(NULL);
    l->setVertices(NULL, NULL);
    l = NULL;
  } else {
    invalidate(this);
  }
  return l;
}
//-----------------------------------------------------------------------------

tCSpline* tLayer::addCSpline(tList<tElement*> *List)
{
	setElementLocked
  tCSpline *c;

  c = new(tCSpline)(NULL,List);
  if (append(c) == NULL){
    c->releaseOwner(NULL);
    c->clear();
    c = NULL;
  } else {
    invalidate(this);
  }
  return c;
}
//-----------------------------------------------------------------------------

tBSpline* tLayer::addBSpline(tList<tElement*> *List)
{
	setElementLocked
  tBSpline *b;
  b = new(tBSpline)(NULL);
  if (append(b) == NULL){
    b->releaseOwner(NULL);
    b = NULL;
  } else {
    b->addVertices(List);
    invalidate(this);
  }
  return b;
}
//-----------------------------------------------------------------------------

tHermiteSpline* tLayer::addHermiteSpline(tList<tElement*> *List, tReal b, tReal c, tReal t)
{
	setElementLocked
  tHermiteSpline *h;
  h = new tHermiteSpline(NULL);
  if (append(h) == NULL){
    h->releaseOwner(NULL);
    h = NULL;
  } else {
    h->addVertices(List);
    h->setContinuity(c);
    h->setBias(b);
    h->setTension(t);
    invalidate(this);
  }
  return h;
}
//-----------------------------------------------------------------------------

tSubCurve* tLayer::addSubCurve(tElement *b1, tElement *b2)
{
	setElementLocked
	tSubCurve *sc;
    sc = new(tSubCurve)(NULL);
  if (append(sc) == NULL){
    sc->releaseOwner(NULL);
    sc = NULL;
  } else {
    sc->setVertices(b1,b2);
    invalidate(this);
  }
	return sc;
}
//-----------------------------------------------------------------------------

tPolyCurve* tLayer::addPolyCurve(tList<tElement*> *List)
{
	setElementLocked
  tPolyCurve *pc;
  pc = new tPolyCurve(NULL);
  if (append(pc) == NULL){
    pc->releaseOwner(NULL);
    pc = NULL;
  } else {
    pc->addList(List);
    invalidate(this);
  }
  return pc;
}
//-----------------------------------------------------------------------------

tRotatedCurve* tLayer::addRotatedCurve(tElement *curve, tElement *axis, tReal angle)
{
	setElementLocked
	tRotatedCurve* c;

    c = new tRotatedCurve(NULL,curve,axis,angle);
  if (append(c) == NULL){
    c->releaseOwner(NULL);
    c->setReference(NULL);
    c->setAxis(NULL);
    c = NULL;
  } else {
    invalidate(this);
  }
	return c;
}
//-----------------------------------------------------------------------------

tMidCurve* tLayer::addMidCurve(tList<tElement*> *List)
{
  setElementLocked;
  tMidCurve *mc;
  mc = new tMidCurve(NULL);
  if (append(mc) == NULL){
    mc->releaseOwner(NULL);
    mc = NULL;
  } else {
    mc->addList(List);
    invalidate(this);
  }
  return mc;
}
//-----------------------------------------------------------------------------

tSumCurve* tLayer::addSumCurve(tList<tElement*> *List)
{
  setElementLocked;
  tSumCurve *sc;
  sc = new tSumCurve(NULL);
  if (append(sc) == NULL){
    sc->releaseOwner(NULL);
    sc = NULL;
  } else {
    sc->addSupportList(List);
    invalidate(this);
  }
  return sc;
}
//-----------------------------------------------------------------------------

tLineSnake* tLayer::addLineSnake(tElement *m1, tElement *m2)
{
	setElementLocked
	tLineSnake *s;
    s = new tLineSnake(NULL,m1,m2);
  if (append(s) == NULL){
    s->releaseOwner(NULL);
    s->setMagnets(NULL,NULL);
    s = NULL;
  } else {
    invalidate(this);
  }
	return s;
}
//-----------------------------------------------------------------------------

tCSnake* tLayer::addCSnake(tList<tElement*> *List){
	setElementLocked
  tCSnake *s;
  s = new tCSnake(NULL,List);
  if (append(s) == NULL){
    s->releaseOwner(NULL);
    s->removeAllVertices();
    s = NULL;
  } else {
    invalidate(this);
  }
  return s;
}
//-----------------------------------------------------------------------------

tRuledSurface* tLayer::addRuled(tCurve *c1, tCurve *c2)
{
	setElementLocked
  tRuledSurface *r;
  r = new tRuledSurface(NULL, c1, c2);
  if (append(r) == NULL){
    r->releaseOwner(NULL);
    r->setCurves(NULL, NULL);
    r = NULL;
  } else {
    invalidate(this);
  }
  return r;
}
//-----------------------------------------------------------------------------

tCLoft* tLayer::addCLoft(tList<tElement*> *List)
{
	setElementLocked
	tCLoft *c;
    c = new(tCLoft)(NULL);
  if (append(c) == NULL){
    c->releaseOwner(NULL);
    c = NULL;
  } else {
    c->insertList(0,List);
    invalidate(this);
  }
	return c;
}
//-----------------------------------------------------------------------------

tRotatedSurface* tLayer::addRotatedSurface(tSurface *surf, tLine *axis, tReal angle)
{
	setElementLocked
  tRotatedSurface *r;
  r = new(tRotatedSurface)(NULL,surf,axis,angle);
  if (append(r) == NULL){
    r->releaseOwner(NULL);
    r->setAxis(NULL);
    r->setRefSurface(NULL);
    r = NULL;
  } else {
    invalidate(this);
  }
  return r;
}
//-----------------------------------------------------------------------------

tRevolvedSurface* tLayer::addRevolvedSurface(tElement *curve,tElement *axis,tReal phi0,tReal phi1)
{
	setElementLocked
  tRevolvedSurface *r;
  r = new(tRevolvedSurface)(NULL,curve,axis,phi0,phi1);
  if (append(r) == NULL){
    r->releaseOwner(NULL);
    r->setAxis(NULL);
    r->setRefCurve(NULL);
    r = NULL;
  } else {
    invalidate(this);
  }
  return r;
}
//-----------------------------------------------------------------------------

tFunctionSurface* tLayer::addFunctionSurface(void)
{
	setElementLocked
	tFunctionSurface *f;
    f = new(tFunctionSurface)(NULL,variables);
  if (append(f) == NULL){
    f->releaseOwner(NULL);
    f->clear(true);
    f = NULL;
  } else {
    invalidate(this);
  }
	return f;
}
//-----------------------------------------------------------------------------

tSubSurface* tLayer::addSubSurface(tElement *s1, tElement *s2)
{
	setElementLocked
  tSubSurface *s;
  s = new(tSubSurface)(NULL, s1, s2);
  if (append(s) == NULL){
    s->releaseOwner(NULL);
    s->setBoundingSnakes(NULL,NULL);
    s = NULL;
  } else {
    invalidate(this);
  }
  return s;
}
//-----------------------------------------------------------------------------

tSurface* tLayer::addPropSurface(QString fileName)
{
	setElementLocked
  tPropSurface *ps = new tPropSurface(NULL);
  if (append(ps) == NULL){
    ps->releaseOwner(NULL);
    ps = NULL;
  } else {
    ps->openPff(fileName, this);
    invalidate(this);
  }
  return ps;
}
//-----------------------------------------------------------------------------

tXPlane* tLayer::addXPlane(double x)
{
	setElementLocked
  tXPlane *p = new tXPlane(NULL);
  if (append(p) == NULL){
    p->releaseOwner(NULL);
    p = NULL;
  } else {
    p->setX(x);
    invalidate(this);
  }
  return p;
}
//-----------------------------------------------------------------------------

tYPlane* tLayer::addYPlane(double y)
{
	setElementLocked
  tYPlane *p = new tYPlane(NULL);
  if (append(p) == NULL){
    p->releaseOwner(NULL);
    p = NULL;
  } else {
    p->setY(y);
    invalidate(this);
  }
  return p;
}
//-----------------------------------------------------------------------------

tZPlane* tLayer::addZPlane(double z)
{
	setElementLocked
  tZPlane *p = new tZPlane(NULL);
  if (append(p) == NULL){
    p->releaseOwner(NULL);
    p = NULL;
  } else {
    p->setZ(z);
    invalidate(this);
  }
  return p;
}
//-----------------------------------------------------------------------------
tGroup* tLayer::addGroup(void){
	setElementLocked
	tGroup *group;

    group = new tGroup(NULL);
  if (append(group) == NULL){
    group->releaseOwner(NULL);
    group = NULL;
  } else {
    invalidate(this);
  }
  return group;
}
//-----------------------------------------------------------------------------

tLayer* tLayer::addLayer(QString name)
{
  setElementLocked
  tLayer *layer;

  layer = new tLayer(NULL, variables);
  layer->intrface()->setName(name);
  if (append(layer) == NULL){
    layer->releaseOwner(NULL);
    layer = NULL;
  } else {
    invalidate(this);
  }
  return layer;
}
//-----------------------------------------------------------------------------

tQuad* tLayer::addQuad(tElement *c1,tElement *c2,tElement *c3,tElement *c4)
{
  setElementLocked
  tQuad *quad;
  quad = new tQuad(NULL);
  if (append(quad) == NULL){
    quad->releaseOwner(NULL);
    quad = NULL;
  } else {
    quad->defineQuad(c1,c2,c3,c4);
    invalidate(this);
  }
  return quad;

}
//-----------------------------------------------------------------------------

tStructured2DInterpolGrid* tLayer::add2DStructuredInterpolGrid(void){
  tStructured2DInterpolGrid *grid;

  grid = new tStructured2DInterpolGrid(NULL);
  if (append(grid) == NULL){
    grid->releaseOwner(NULL);
    grid = NULL;
  } else {
    invalidate(this);
  }
  return grid;
}
//-----------------------------------------------------------------------------

tStructured2DSurfaceGrid* tLayer::add2DStructuredSurfaceGrid(void){
  tStructured2DSurfaceGrid *grid;

  grid = new tStructured2DSurfaceGrid(NULL);
  if (append(grid) == NULL){
    grid->releaseOwner(NULL);
    grid = NULL;
  } else {
    invalidate(this);
  }
  return grid;
}
//-----------------------------------------------------------------------------

tStructured2DSubGrid* tLayer::add2DStructuredSubGrid(void){
	setElementLocked
  tStructured2DSubGrid *grid;

  grid = new tStructured2DSubGrid(NULL);
  if (append(grid) == NULL){
    grid->releaseOwner(NULL);
    grid = NULL;
  } else {
    invalidate(this);
  }
  return grid;
}
//-----------------------------------------------------------------------------

tVariable* tLayer::addVariable(QString func)
{
	setElementLocked
	tVariable *var;
	var = dynamic_cast<tVariable*>(variables->addVariable(func));
	if (append(var) == NULL){
	  variables->removeVariable(var);
	  var = NULL;
	} else {
	  invalidate(this);
	}
  return var;
}
//-----------------------------------------------------------------------------

tRealVariable* tLayer::addRealVariable(QString func)
{
	setElementLocked
	tRealVariable *var;
	var = dynamic_cast<tRealVariable*>(variables->addRealVariable(func));
  if (append(var) == NULL){
    variables->removeVariable(var);
    var = NULL;
  } else {
    invalidate(this);
  }
  return var;
}
//-----------------------------------------------------------------------------

tVectorVariable* tLayer::addVectorVariable(QString func)
{
	setElementLocked
	tVectorVariable *var;
	var = dynamic_cast<tVectorVariable*>(variables->addVectorVariable(func));
  if (append(var) == NULL){
    variables->removeVariable(var);
    var = NULL;
  } else {
    invalidate(this);
  }
  return var;
}
//-----------------------------------------------------------------------------

tListVariable* tLayer::addListVariable(QString func)
{
	setElementLocked
	tListVariable *var;
	var = dynamic_cast<tListVariable*>(variables->addListVariable(func));
  if (append(var) == NULL){
    variables->removeVariable(var);
    var = NULL;
  } else {
    invalidate(this);
  }
  return var;
}
//-----------------------------------------------------------------------------

tVariable* tLayer::variable(QString varName)
{
  return dynamic_cast<tVariable*>(variables->variable(varName));
}
//-----------------------------------------------------------------------------

tReal tLayer::getRealVarValue(QString varName, tReal defaultValue)
{
	tRealVariable *var;
	var = dynamic_cast<tRealVariable*>(variables->variable(varName));
	if (var){
		return var->value();
	} else {
		return defaultValue;
	}
}
//-----------------------------------------------------------------------------

tVector tLayer::getVectorVarValue(QString varName, tVector defaultValue)
{
	tVectorVariable *var;
	var = dynamic_cast<tVectorVariable*>(variables->variable(varName));
	if (var){
		return var->value();
	} else {
		return defaultValue;
	}
}
//-----------------------------------------------------------------------------
