#ifndef TRELPOINT_H_
#define TRELPOINT_H_

#include "element/point/tDot.h"
#include "iRelPoint.h"

class tRelPoint : public tDot
{
	private:
		tDot *dot;
		tVector dx;
	public:
		tRelPoint(void *theOwner,tElement *el=NULL, tVector DX=tVector(0,0,0));
		virtual ~tRelPoint();
		iElement* intrface(void);
		virtual void refresh(void);

		tVector offset(void);
		void setOffset(tVector v);
		tDot* reference(void);
		void setReference(tElement *el);
};
/*I!
offset Vector read:offset write:setOffset
reference Dot read:reference write:setReference
*/

#endif /*TRELPOINT_H_*/
