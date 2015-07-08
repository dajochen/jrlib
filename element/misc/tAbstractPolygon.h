#ifndef TABSTRACTPOLYGON_H
#define TABSTRACTPOLYGON_H

#include "element/tPaintableElement.h"
#include "element/curve/tPolygonCurve.h"

#include "iAbstractPolygon.h"

class tAbstractPolygon : public tPaintableElement
{
protected:
    tVector normal_;
    tVector center_;
    double area_;
    tPolygonCurve *poly;

public:
    tAbstractPolygon(void* theOwner, int maxVerts);
    virtual ~tAbstractPolygon();

    iElement* intrface(void);
    virtual void refresh(void);

    virtual tVector normal(void) {update(); return normal_;}
    virtual tVector center(void) {update(); return center_;}
    virtual double area(void) {update(); return area_;}

    virtual int nVertices(void)         { update(); return poly->nVertices(); invalidate(this);}
    virtual tList<tElement*> vertices() { update(); return poly->vertices();  invalidate(this);}
    virtual tDot* vertex(int i)         { update(); return poly->vertex(i);   invalidate(this);}

    void addVertex(tElement *el) {poly->addVertex(el);}
    void addVertices(tList<tElement*> *List) {poly->addVertices(List); invalidate(this);}
    void setVertices(tList<tElement*> list)  {poly->setVertices(list); invalidate(this);}
    void setVertices(tList<tDot*> list)      {poly->setVertices(list); invalidate(this);}

    void removeAllVertices(void)             {poly->removeAllVertices(); invalidate(this);}

    virtual void paintGL(const tVector& EyePoint, const tVector& ObjectPoint, const tRGB& rgb, const tVector &defaultN, const bool &isSelected);

/*I!
normal Vector read:normal
area Real read:area
nVertices Int read:nVertices
vertices DotList read:vertices write:setVertices
*/
};

#endif // TABSTRACTPOLYGON_H
