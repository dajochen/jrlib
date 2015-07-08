#ifndef TSURFACEDRAPER_H
#define TSURFACEDRAPER_H

#include "element/tPaintableElement.h"
#include "element/point/tDot.h"
#include "element/curve/tLine.h"
#include "element/misc/tTrianglePatch.h"
#include "element/misc/draping/tInitialFiber.h"
#include "model/tLayer.h"

#include "element/misc/draping/iDrapedPatch.h"


class tDrapedPatch : public tPaintableElement
{
public:
    tDrapedPatch(void* theOwner);
    virtual ~tDrapedPatch();
    iElement* intrface(void);
    virtual void refresh(void);
    virtual void invalidate(tElement *sender) {isDrapingUptoDate = false; tElement::invalidate(sender);}

    virtual tDot* initialPoint() {update(); return initialPoint_;}
    virtual tLine* initialPointProjectionDir() {update(); return initialPointProjectionDir_;}
    virtual tLine* initialFiberDir() {update(); return initialFiberDir_;}
    virtual tTrianglePatch* patch() {update(); return patch_;}
    virtual double meshSize() {update(); return meshSize_;}

    virtual void setInitialPoint(tElement* el);
    virtual void setInitialPointProjectionDir(tElement* el);
    virtual void setInitialFiberDir(tElement* el);
    virtual void setPatch(tElement* el);
    virtual void setMeshSize(double mSize);

    virtual void runDrapingSimulation(void);

    virtual void paintGL(const tVector& EyePoint, const tVector& ObjectPoint, const tRGB& rgb, const tVector &defaultN, const bool &isSelected);

protected:

private:
    tTrianglePatch* patch_;
    tDot* initialPoint_;
    tLine *initialPointProjectionDir_,
          *initialFiberDir_;
    double meshSize_;
    bool isDrapingUptoDate;

    tInitialFiber *initialFiber;
    tLayer* helper;
    void clearDrapData(void);

};

/*I!
patch TrianglePatch read:patch write:setPatch
meshSize Real read:meshSize write:setMeshSize
initialPoint Dot read:initialPoint write:setInitialPoint
initialPointProjectionDir Line read:initialPointProjectionDir write:setInitialPointProjectionDir
initialFiberDir Line read:initialFiberDir write:setInitialFiberDir
action runDrapingSimulation
*/
#endif // TSURFACEDRAPER_H
