#ifndef TBSPLINE_H_
#define TBSPLINE_H_

#include "element/curve/tCurve.h"
#include "element/tGroup.h"
#include "classes/tList.h"
#include "element/point/tDot.h"
#include "element/curve/tCurve.h"

#include "iBSpline.h"

class tBSpline : public tCurve
{
private:
    tList<tDot*> vertex;
    tDot* getPoint(int i);

 public:
    tBSpline(void *theOwner);
    virtual ~tBSpline();

    iElement* intrface(void);
    virtual void refresh(void);

    bool addVortex(tDot *P);
    void addVertices(tGroup *Group);
    void addVertices(tList<tElement*> *List);
    tList<tElement*> vertices(void);
    virtual tVector vectorAtAccurate(tReal t);

    int nVertices(void){return vertex.count();}
    void setVertices(tList<tElement*> list);
    void removeAllVertices(void);
};

/*-----------------------------------------------------------------------------
 * Das Interface
 * --------------------------------------------------------------------------*/
/*I!
nVertices Int read:nVertices
vertices DotList read:vertices write:setVertices
*/

#endif /*TBSPLINE_H_*/
