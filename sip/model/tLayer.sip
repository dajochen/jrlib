//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tLayer.h (Mo. Jan. 27 00:25:00 2014)
//------------------------------------------------------------------------

class tLayer :  public tGroup  {

%TypeHeaderCode
#include "tLayer.h"
%End

public:
	tLayer(void *theowner=NULL, tVariableNameSpace *vars=NULL, QString allowedType="");
	virtual ~tLayer();

	virtual iElement* intrface();
	virtual void clear();
	virtual tElement* addElement(tElement *el);
	virtual tElement* append(tElement* el);
	virtual tElement* prepend(tElement* el);
	virtual tVariableNameSpace* vars();
	tVariable* addVariable(QString func);
	tRealVariable* addRealVariable(QString func);
	tVectorVariable* addVectorVariable(QString func);
	tListVariable* addListVariable(QString func);
	tProjectedPoint* addProjectedPoint();
	tStickyMagnet* addStickyMagnet();
	tSubCurve* addSubCurve(tElement *b1, tElement *b2);
	tLineSnake* addLineSnake(tElement *m1, tElement *m2);
	tRuledSurface* addRuled(tCurve *c1, tCurve *c2);
	tRotatedSurface* addRotatedSurface(tSurface *surf, tLine *axis, tReal angle);
	tRevolvedSurface* addRevolvedSurface(tElement *curve, tElement *axis, tReal start, tReal end);
	tFunctionSurface* addFunctionSurface();
	tSubSurface* addSubSurface(tElement *s1, tElement *s2);
	tSurface* addPropSurface(QString fileName);
	tXPlane* addXPlane(double x);
	tYPlane* addYPlane(double y);
	tZPlane* addZPlane(double z);
	tGroup* addGroup();
	tQuad* addQuad(tElement *c1, tElement *c2, tElement *c3, tElement *c4);
	tStructured2DInterpolGrid* add2DStructuredInterpolGrid();
	tStructured2DSurfaceGrid* add2DStructuredSurfaceGrid();
	tStructured2DSubGrid* add2DStructuredSubGrid();
};
