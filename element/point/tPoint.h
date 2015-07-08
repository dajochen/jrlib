#ifndef TPOINT_H_
#define TPOINT_H_

#include "element/point/tDot.h"
#include "element/tElement.h"

#include "iPoint.h"

class tPoint : public tDot
{	
public:
	tPoint(void *theOwner, tVector X=tVector(0.,0.,0.));
	tPoint(void *theOwner, tReal x, tReal y, tReal z);
	virtual ~tPoint();
	
	void setX(tReal X);
	void setY(tReal Y);
	void setZ(tReal Z);
	void setVector(tVector X);
	
	void refresh(void);
	
	virtual iElement* intrface(void);
};

/*I!
location Vector write:setVector read:vector
optional x Real write:setX read:x
optional y Real write:setY read:y
optional z Real write:setZ read:z
*/

#endif /*TPOINT_H_*/
