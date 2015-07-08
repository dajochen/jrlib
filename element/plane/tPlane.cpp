#include "tPlane.h"

tPlane::tPlane(void* theOwner):
    tBasicPlane(theOwner)
{
    fcenterPoint = NULL;
    fPointOnNormal = NULL;
    fPointOnHorizontal = NULL;

    fmode = 0;
}
//-----------------------------------------------------------------------------

tPlane::~tPlane()
{
    setCenter(NULL);
    setOnNormal(NULL);
    setOnHorizontal(NULL);
}
//-----------------------------------------------------------------------------

void tPlane::refresh()
{
    if (fcenterPoint && fPointOnNormal && fPointOnHorizontal) {
        fcenter = fcenterPoint->vector();

        fnormal = fPointOnNormal->vector()-fcenterPoint->vector();
        fHorizontalDir = fPointOnHorizontal->vector()-fcenterPoint->vector();

        tVector right = fHorizontalDir % fnormal;
        if (fmode%2 == 0) {
            fHorizontalDir = (fnormal % right).normalize();
            fnormal = fnormal.normalize();
        } else {
            fnormal = (right % fHorizontalDir).normalize();
            fHorizontalDir = fHorizontalDir.normalize();
        }
    } else {
        fcenter.setZero();
        fnormal.setZero();
        fHorizontalDir.setZero();
    }
}
//-----------------------------------------------------------------------------

iElement *tPlane::intrface(void)
{
    if (!iface){
        iface = new iPlane(this);
    }
    return iface;
}
//-----------------------------------------------------------------------------

void tPlane::setCenter(tElement* center)
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
//-----------------------------------------------------------------------------

void tPlane::setOnNormal(tElement* onNormal)
{
    if (fPointOnNormal != onNormal) {
        if (fPointOnNormal) {
            fPointOnNormal->removeDependent(this);
        }
        fPointOnNormal = dynamic_cast<tDot*>(onNormal);
        if (fPointOnNormal && !fPointOnNormal->addDependent(this)) {
            fPointOnNormal = NULL;
        }
    }
    invalidate(this);
}
//-----------------------------------------------------------------------------

void tPlane::setOnHorizontal(tElement *onHorizontal)
{
    if (fPointOnHorizontal != onHorizontal) {
        if (fPointOnHorizontal) {
            fPointOnHorizontal->removeDependent(this);
        }
        fPointOnHorizontal = dynamic_cast<tDot*>(onHorizontal);
        if (fPointOnHorizontal && !fPointOnHorizontal->addDependent(this)) {
            fPointOnHorizontal = NULL;
        }
    }
    invalidate(this);
}
//-----------------------------------------------------------------------------

void tPlane::setMode(int mode)
{
    fmode = mode;
    invalidate(this);
}
//-----------------------------------------------------------------------------

tDot *tPlane::centerPoint(void)
{
    return fcenterPoint;
}
//-----------------------------------------------------------------------------

tDot *tPlane::onNormal(void)
{
    return fPointOnNormal;
}
//-----------------------------------------------------------------------------

tDot *tPlane::onHorizontal(void)
{
    return fPointOnHorizontal;
}
//-----------------------------------------------------------------------------

int tPlane::mode()
{
    return fmode;
}
//-----------------------------------------------------------------------------


