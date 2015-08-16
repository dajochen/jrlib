/*
 * tLayer.h
 *
 *  Created on: 11.01.2009
 *      Author: Jochen
 */

#ifndef TLAYER_H_
#define TLAYER_H_

#include "element/tGroup.h"
#include "element/variable/tRealVariable.h"
#include "element/variable/tVectorVariable.h"
#include "element/variable/tListVariable.h"
#include "element/variable/tVariableNameSpace.h"
#include "classes/tVector.h"
#include "element/point/tPoint.h"
#include "element/point/tRelPoint.h"
#include "element/point/tMidPoint.h"
#include "element/point/tProjectedPoint.h"
#include "element/point/tOffsetPoint.h"
#include "element/point/tRotatedPoint.h"

#include "element/point/tAbsBead.h"
#include "element/point/tAbsMagnet.h"
#include "element/point/tStickyMagnet.h"

#include "element/curve/tLine.h"
#include "element/curve/tCSpline.h"
#include "element/curve/tHermiteSpline.h"
#include "element/curve/tDxfSpline.h"
#include "element/curve/tBSpline.h"
#include "element/curve/tSubCurve.h"
#include "element/curve/tPolyCurve.h"
#include "element/curve/tRotatedCurve.h"
#include "element/curve/tMidCurve.h"
#include "element/curve/tSumCurve.h"

#include "element/curve/snake/tLineSnake.h"
#include "element/curve/snake/tCSnake.h"

#include "element/surface/tRuledSurface.h"
#include "element/surface/tCLoft.h"
#include "element/surface/tRotatedSurface.h"
#include "element/surface/tRevolvedSurface.h"
#include "element/surface/tFunctionSurface.h"

#include "element/surface/tSubSurface.h"


#include "element/plane/tXPlane.h"
#include "element/plane/tYPlane.h"
#include "element/plane/tZPlane.h"

#include "element/misc/tQuad.h"
#include "element/misc/tNet.h"
#include "element/misc/2DGrid/tStructured2DInterpolGrid.h"
#include "element/misc/2DGrid/tStructured2DSurfaceGrid.h"
#include "element/misc/2DGrid/tStructured2DSubGrid.h"

#include "element/misc/3DGrid/tStructured3DGrid.h"
#include "element/misc/3DGrid/tStructured3DBlockMeshGrid.h"
#include "element/misc/3DGrid/tStructured3DTwoSidedGrid.h"

#include "views/tCopyPasteOptionsDlg.h"

#include "model/iLayer.h"


class tLayer: public tGroup {
protected:
  void* owningModel;
  tVariableNameSpace *variables;
  void removeFromOtherLayers(tElement *el);
  virtual void removeElement(int i);


public:
  tLayer(void *theowner=NULL, tVariableNameSpace *vars=NULL, QString allowedType="");
  virtual ~tLayer();

  virtual iElement* intrface(void);

  virtual void clear(void);
  virtual void removeElement(tElement *el, bool recursive=true);

  tElement* elementByName(const QString& name, const QString &type = "");
  const tList<tElement*> elementsByName(const QRegularExpression &re, const QString &type ="");

  virtual tElement* addElement(const QString &type, const QString& name="");
  virtual tElement* addElement(tElement *el){return append(el);}
  virtual tElement* addDeepCopy(tElement *el, tList<tCopyPasteOption> options=tList<tCopyPasteOption>());
  virtual tElement* append(tElement* el);
  virtual tElement* prepend(tElement* el);
  //virtual void setElements(const tList<tElement*> &l);

  // not needed. Just add an element to a Layer and it will be removed from the other layers automatically
  //virtual void changeElementLayer(tElement *el, tLayer *newLayer);

  virtual tVariableNameSpace* vars(void) {return variables;}

  virtual tVariable *variable(QString varName);
  virtual tReal getRealVarValue(QString varName, tReal defaultValue = 0.);
  virtual tVector getVectorVarValue(QString varName, tVector defaultValue = tVector(0., 0., 0.));

  // Funktionen zum Hinzufuegen von Elementen
  tVariable* addVariable(QString func);
  tRealVariable* addRealVariable(QString func);
  tVectorVariable* addVectorVariable(QString func);
  tListVariable* addListVariable(QString func);

  tPoint* addPoint(tVector x = tVector(0, 0, 0));
  tRelPoint* addRelPoint(tElement *el = NULL, tVector x = tVector(0, 0, 0));
  tMidPoint* addMidPoint(tElement *el = NULL);
  tProjectedPoint* addProjectedPoint(void);
  tAbsBead* addAbsBead(tElement *curve = NULL, tReal t = 0.5);
  tAbsMagnet* addAbsMagnet(tElement *surf = NULL, tReal u = 0.5, tReal v = 0.5);
  tStickyMagnet* addStickyMagnet(void);
  tOffsetPoint* addOffsetPoint(tElement *surf = NULL, tReal u = 0.5, tReal v = 0.5, tReal dist = 0.);
  tRotatedPoint* addRotatedPoint(tElement *el = NULL, tElement *axis = NULL, tReal angle = 0.);

  tLine* addLine(tElement *C1 = NULL, tElement *C2 = NULL);
  tCSpline* addCSpline(tList<tElement*> *List = NULL);
  tBSpline* addBSpline(tList<tElement*> *List = NULL);
  tHermiteSpline* addHermiteSpline(tList<tElement*> *List = NULL, tReal c = 0., tReal b = 0., tReal t = 0.);

  tSubCurve* addSubCurve(tElement *b1, tElement *b2);
  tPolyCurve* addPolyCurve(tList<tElement*> *List = NULL);
  tRotatedCurve* addRotatedCurve(tElement *curve = NULL, tElement *axis = NULL, tReal angle = 0.);
  tMidCurve* addMidCurve(tList<tElement*> *List = NULL);
  tSumCurve* addSumCurve(tList<tElement*> *List = NULL);

  tLineSnake* addLineSnake(tElement *m1, tElement *m2);
  tCSnake* addCSnake(tList<tElement*> *List = NULL);

  tRuledSurface* addRuled(tCurve *c1, tCurve *c2);
  tCLoft* addCLoft(tList<tElement*> *List = NULL);
  tRotatedSurface* addRotatedSurface(tSurface *surf, tLine *axis, tReal angle);
  tRevolvedSurface* addRevolvedSurface(tElement *curve, tElement *axis, tReal start, tReal end);
  tFunctionSurface* addFunctionSurface(void);

  tSubSurface* addSubSurface(tElement *s1, tElement *s2);

  tSurface* addPropSurface(QString fileName);
  tXPlane* addXPlane(double x);
  tYPlane* addYPlane(double y);
  tZPlane* addZPlane(double z);

  tGroup* addGroup(void);
  tLayer* addLayer(QString name="unknown");

  tQuad* addQuad(tElement *c1, tElement *c2, tElement *c3, tElement *c4);

  tStructured2DInterpolGrid* add2DStructuredInterpolGrid(void);
  tStructured2DSurfaceGrid* add2DStructuredSurfaceGrid(void);
  tStructured2DSubGrid* add2DStructuredSubGrid(void);
};

/*I!
 */
#endif /* TLAYER_H_ */
