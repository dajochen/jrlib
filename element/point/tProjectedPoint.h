#ifndef TPROJECTEDPOINT_H_
#define TPROJECTEDPOINT_H_

#include "element/point/tDot.h"
#include "element/plane/tPlane.h"
#include "iProjectedPoint.h"

class tProjectedPoint : public tDot
{
	private:
		tDot *fdot;
    tPlane *fplane;
		tVector forigin;
	public:
		tProjectedPoint(void *theOwner);
		virtual ~tProjectedPoint();
		iElement* intrface(void);
		virtual void refresh(void);

		tVector origin(void);
		void setOrigin(tVector v);
    tPlane* plane(void);
    void setPlane(tElement *el);
    tDot* refDot(void);
    void setRefDot(tElement *el);
};
/*I!
origin Vector read:origin write:setOrigin
refDot Dot read:refDot write:setRefDot
plane Plane read:plane write:setPlane
*/

#endif /*TPROJECTEDPOINT_H_*/
