#ifndef TTRIANGLE_H
#define TTRIANGLE_H

#include "tAbstractPolygon.h"
#include "iTriangle.h"
class tTriangle  : public tAbstractPolygon
{

protected:

public:
    tTriangle(void* theOwner): tAbstractPolygon(theOwner,3) {}
    virtual ~tTriangle(){}

    iElement *intrface(void);

/*I!
*/
};



#endif // TTRIANGLE_H
