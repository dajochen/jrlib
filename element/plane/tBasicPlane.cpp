#include "tBasicPlane.h"

tBasicPlane::tBasicPlane(void* theOwner) : tElement(theOwner)
{
//    fCenter = tVector(0,0,0);
//    fnormal = tVector(0,0,0);
}
//-----------------------------------------------------------------------------

tBasicPlane::~tBasicPlane()
{
}

tReal tBasicPlane::distance(const tVector& x)
{
    update();
    if (isValidPlane()) {
        return fnormal*(x-fcenter)*(1./fnormal.length());
    } else {
        return 0.;
    }
}

bool tBasicPlane::isValidPlane()
{
    update();
    if  ( fnormal.length_squared()>0 && fHorizontalDir.length_squared() > 0 ) {
        return true;
    } else {
        return false;
    }
}

tVector tBasicPlane::projectToPlane(const tVector& x)
{
    update();
    double dist = distance(x);
    tVector X = x - fnormal*dist;
    return X;
}

tVector tBasicPlane::projectToPlaneCoords(const tVector& x)
{
    update();
    tVector toX = (x-fcenter);
    tVector up = (fnormal % fHorizontalDir).normalize();
    tVector local = tVector (toX * fHorizontalDir, toX * up, 0.);

    return local;
}
//-----------------------------------------------------------------------------
