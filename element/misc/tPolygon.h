#ifndef TPOLYFACE_H
#define TPOLYFACE_H

#include "tAbstractPolygon.h"
#include "iPolygon.h"

class tPolygon : public tAbstractPolygon
{

protected:

public:
    tPolygon(void* theOwner): tAbstractPolygon(theOwner,-1) {}
    virtual ~tPolygon(){}

    iElement *intrface(void);

/*I!
*/
};

#endif // TPOLYFACE_H
