#ifndef THERMITESPLINE_H_
#define THERMITESPLINE_H_

#include "tAbstractSpline.h"
#include "element/point/tDot.h"

#include "iHermiteSpline.h"


class tHermiteSpline : public tAbstractSpline
{	
	private: 
    tReal fc,fb,ft;

	public:
		tHermiteSpline(void *theOwner);
		virtual ~tHermiteSpline();

		iElement* intrface(void);
		virtual void refresh(void);

    virtual tVector vectorAtAccurate(tReal t);

    tReal tension(void){return ft;}
    tReal bias(void){return fb;}
    tReal continuity(void){return fc;}
    void setTension(tReal t){setElementLocked  ft = t; invalidate(this);}
    void setBias(tReal b){setElementLocked fb = b; invalidate(this);}
    void setContinuity(tReal c){setElementLocked fc = c; invalidate(this);}
};

/*I!
tension Real write:setTension read:tension
bias Real write:setBias read:bias
continuity Real write:setContinuity read:continuity
*/

#endif /*THERMITESPLINE_H_*/
