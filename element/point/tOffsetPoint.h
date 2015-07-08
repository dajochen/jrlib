#ifndef TOFFSETPOINT_H_
#define TOFFSETPOINT_H_

#include "element/point/tDot.h"
#include "element/surface/tSurface.h"

#include "iOffsetPoint.h"

class tOffsetPoint : public tDot
{
	private:
		tReal uu,vv,distance;
		tSurface *surface;
	public:
		tOffsetPoint(void *theOwner,tElement *S=NULL, tReal U=0.5, tReal V=0.5, tReal D=0.);
		virtual ~tOffsetPoint();
		iElement* intrface(void);
		virtual void refresh(void);

		tReal u(void);
		tReal v(void);
    tReal offset(void);
		tSurface* reference(void);
		void setU(tReal u);
		void setV(tReal v);
		void setOffset(tReal d);
		void setReference(tElement *el);

//	  virtual tList<tElement*> usedElements(void);

};
/*I!
offset Real read:offset write:setOffset
reference Surface read:reference write:setReference
u Real read:u write:setU
v Real read:v write:setV
*/

#endif /*TOFFSETPOINT_H_*/
