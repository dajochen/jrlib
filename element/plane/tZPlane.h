#ifndef TZPlane_H_
#define TZPlane_H_

#include "tBasicPlane.h"
#include "iZPlane.h"

class tZPlane : public tBasicPlane
{
protected:
public:
    tZPlane(void* theOwner);
    virtual ~tZPlane();

    virtual void refresh(void) {}
    virtual iElement* intrface(void);

    double z(void) {return fcenter.z;}
    void setZ (double az) {fcenter.z = az; invalidate(this);}
};

/*I!
z Real write:setZ read:z
*/

#endif /*TZPlane_H_*/
