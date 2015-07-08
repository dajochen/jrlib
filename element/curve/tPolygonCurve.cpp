#include "tPolygonCurve.h"

tPolygonCurve::tPolygonCurve(void *theOwner, int maxVerts)
    : tAbstractSpline(theOwner, maxVerts),
      isLoop_(true)
{
}

iElement *tPolygonCurve::intrface()
{
    if (iface == NULL){
        iface = new iPolygonCurve(this);
    }
    return iface;
}

void tPolygonCurve::setIsLoop(bool isLoop)
{
    if (isLoop != isLoop_) {
        isLoop_ = isLoop;
        invalidate(this);
    }
}

bool tPolygonCurve::isLoop()
{
    return isLoop_;
}

tVector tPolygonCurve::vectorAtAccurate(tReal t)
{
    update();
    tVector x(0,0,0);
    if (nVertices()>0){
        int segments = 0;
        if (isLoop_){
            segments = nVertices();
        } else {
            segments = nVertices()-1;
        }

        int i = (int) floor(t * double(segments));
        double frac = 1./double(segments);

        frac = (t - double(i) * frac) / frac;

        x= vertex(i)->vector() * (1.-frac)
          +vertex((i+1)%nVertices())->vector() * (frac);

    }

    return x;
}
