#include "tThreePointPlane.h"

tThreePointPlane::tThreePointPlane(void* theOwner)
    : tBasicPlane(theOwner)
{
    fcenterPoint=NULL;
    fP1=NULL;
    fP2=NULL;
}

tThreePointPlane::~tThreePointPlane()
{
    setCenter(NULL);
    setP1(NULL);
    setP2(NULL);
}

void tThreePointPlane::refresh()
{
    if (fP1 && fP2 && fcenterPoint) {
        fcenter = fcenterPoint->vector();
        fHorizontalDir = (fP1->vector()-fcenterPoint->vector()).normalize();

        fnormal = (fHorizontalDir % (fP2->vector()-fcenter) ).normalize();

        if (fnormal.length_squared() == 0 || fHorizontalDir.length_squared()==0) {
            fcenter.setZero();
            fnormal.setZero();
            fHorizontalDir.setZero();
        }
    } else {
        fcenter.setZero();
        fnormal.setZero();
        fHorizontalDir.setZero();
    }
}

iElement *tThreePointPlane::intrface()
{
    if (!iface){
        iface = new iThreePointPlane(this);
    }
    return iface;
}

void tThreePointPlane::setCenter(tElement *center)
{
    if (fcenterPoint != center) {
        if (fcenterPoint) {
            fcenterPoint->removeDependent(this);
        }
        fcenterPoint = dynamic_cast<tDot*>(center);
        if (fcenterPoint && !fcenterPoint->addDependent(this)) {
            fcenterPoint = NULL;
        }
    }
    invalidate(this);
}

void tThreePointPlane::setP1(tElement *p)
{
    if (fP1 != p) {
        if (fP1) {
            fP1->removeDependent(this);
        }
        fP1 = dynamic_cast<tDot*>(p);
        if (fP1 && !fP1->addDependent(this)) {
            fP1= NULL;
        }
    }
    invalidate(this);
}

void tThreePointPlane::setP2(tElement *p)
{
    if (fP2 != p) {
        if (fP2) {
            fP2->removeDependent(this);
        }
        fP2 = dynamic_cast<tDot*>(p);
        if (fP2 && !fP2->addDependent(this)) {
            fP2= NULL;
        }
    }
    invalidate(this);
}

tDot *tThreePointPlane::centerPoint()
{
    return fcenterPoint;
}

tDot *tThreePointPlane::p1()
{
    return fP1;
}

tDot *tThreePointPlane::p2()
{
    return fP2;
}
