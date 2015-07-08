#ifndef TFIBER_H
#define TFIBER_H

#include "element/curve/tPolygonCurve.h"
#include "element/misc/tTrianglePatch.h"

class tFiber
{
public:
    tFiber();
    virtual ~tFiber();
    virtual tPolygonCurve* fiber(void) {return fiber_;}
    virtual tDot *fiberNode(int id);
protected:
    tPolygonCurve *fiber_;
    void appendNode(tDot *d);
    void prependNode(tDot *d);
private:
    int startNodeID;
};

#endif // TFIBER_H
