#ifndef TBASICPLANE_H_
#define TBASICPLANE_H_

#include "element/tElement.h"
#include "iBasicPlane.h"

class tBasicPlane : public tElement
{
protected:
    tVector fcenter, fnormal, fHorizontalDir;
public:
    tBasicPlane(void* theOwner);
    virtual ~tBasicPlane();

    virtual void refresh(){}
    virtual tVector xMin(void) { update(); return fcenter; }
    virtual tVector xMax(void) { update(); return fcenter; }

    virtual tVector normal(void){ update(); return fnormal; }
    virtual tVector center(void){ update(); return fcenter; }
    virtual tVector horizontalDir(void) { update(); return fHorizontalDir;}

    virtual tReal distance(const tVector& x);
    virtual bool isValidPlane(void);
    virtual tVector projectToPlane(const tVector& x);
    virtual tVector projectToPlaneCoords(const tVector& x);

};

/*I!
center Vector read:center
normal Vector read:normal
horizontalDir   Vector read:horizontalDir
*/


#endif /*TBASICPLANE_H_*/
