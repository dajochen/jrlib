#ifndef TPOLYGONCURVE_H
#define TPOLYGONCURVE_H


#include "tAbstractSpline.h"
#include "iPolygonCurve.h"

class tPolygonCurve : public tAbstractSpline
{
public:
    tPolygonCurve(void* theOwner, int maxVerts=-1);
    virtual ~tPolygonCurve(){}

    virtual void refresh(void){}
    iElement* intrface(void);

    void setIsLoop(bool isLoop);
    bool isLoop(void);

    virtual tVector vectorAtAccurate(tReal t);

private:
    bool isLoop_;
};

/*I!
isLoop Bool read:isLoop write:setIsLoop
*/

#endif // TPOLYGONCURVE_H
