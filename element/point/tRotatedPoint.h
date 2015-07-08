#ifndef TROTATEDPOINT_H_
#define TROTATEDPOINT_H_

#include "element/point/tDot.h"
#include "element/point/tPoint.h"
#include "element/curve/tLine.h"

#include "iRotatedPoint.h"

class tRotatedPoint : public tDot
{
	private:
		tDot *refDot;
		tLine *Axis;
		tReal Angle;
	public:
		tRotatedPoint(void *theOwner,tElement *REFDOT=NULL, tElement *AXIS=NULL, tReal angle=0.);
		virtual ~tRotatedPoint();
		iElement* intrface(void);
		virtual void refresh(void);

		tReal angle(void);
    tLine* axis(void);
    tDot* reference(void);
		void setAngle(tReal a);
		void setAxis(tElement *el);
		void setReference(tElement *el);

};
/*I!
angle Real read:angle write:setAngle
axis Line read:axis write:setAxis
referencePoint Dot read:reference write:setReference
*/

#endif /*TROTATEDPOINT_H_*/
