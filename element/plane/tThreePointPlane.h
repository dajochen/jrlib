#ifndef TTHREEPOINTPLANE_H
#define TTHREEPOINTPLANE_H

#include "element/point/tDot.h"
#include "tBasicPlane.h"
#include "iThreePointPlane.h"

class tThreePointPlane : public tBasicPlane
{
public:
    tThreePointPlane(void* theOwner);
    virtual ~tThreePointPlane();

    virtual void refresh(void);
    virtual iElement *intrface(void);

    virtual void setCenter(tElement *center);
    virtual void setP1(tElement* p);
    virtual void setP2(tElement* p);

    virtual tDot* centerPoint(void);
    virtual tDot* p1(void);
    virtual tDot* p2(void);

protected:
    tDot *fcenterPoint, *fP1, *fP2;

};
/*I!
centerPoint Dot read:centerPoint write:setCenter
p1 Dot read:p1 write:setP1
p2 Dot read:p2 write:setP2
*/

#endif // T3POINTPLANE_H
