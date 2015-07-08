#ifndef TYPlane_H_
#define TYPlane_H_

#include "tBasicPlane.h"
#include "iYPlane.h"
class tYPlane : public tBasicPlane
{
protected:
public:
    tYPlane(void* theOwner);
    virtual ~tYPlane();

    virtual iElement* intrface(void);
    virtual void refresh(void){}

    double y(void) {return fcenter.y;}
    void setY (double ay) {fcenter.x = ay; invalidate(this);}

};

/*I!
y Real write:setY read:y
*/

#endif /*TYPlane_H_*/
