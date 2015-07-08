#ifndef TABSBEAD_H_
#define TABSBEAD_H_

#include "element/point/tDot.h"
#include "element/curve/tCurve.h"

#include "iAbsBead.h"

class tAbsBead : public tDot
{
private:
	tCurve *curve;
	tReal pos;
public:
	tAbsBead(void *theOwner,tElement *CURVE=NULL, tReal POS=0.5);
	virtual ~tAbsBead();
	iElement* intrface(void);
	virtual void refresh(void);

	tReal position(void);
	void setPosition(tReal POS);
	tCurve* reference(void);
	void setReference(tElement *el);
};
/*I!
position Real read:position write:setPosition
referenceCurve Curve read:reference write:setReference
*/

#endif /*TABSBEAD_H_*/
