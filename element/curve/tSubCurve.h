#ifndef TSUBCURVE_H_
#define TSUBCURVE_H_

#include "element/curve/tCurve.h"
#include "element/point/tAbsBead.h"

#include "iSubCurve.h"

class tSubCurve : public tCurve
{
	private:
		tAbsBead *c1,*c2;

	public:
		tSubCurve(void *theOwner);
		tSubCurve(void *theOwner,tAbsBead *C1, tAbsBead *C2);
		virtual ~tSubCurve();

		iElement* intrface(void);
		virtual void refresh(void);

    tAbsBead* start(void){return c1;};
    tAbsBead* end(void){return c2;};

    void setStart(tElement *el){setVertex(0,el);};
    void setEnd(tElement *el){setVertex(1,el);};
		void setVertex(int i, tElement *El);
		void setVertices(tElement *C1, tElement *C2);
	  virtual tVector vectorAtAccurate(tReal t);
	  virtual tVector gradientAt(tReal t);
	 // virtual tVector curvatureAt(tReal t);
};

/*I!
start AbsBead read:start write:setStart
end AbsBead read:end write:setEnd
*/
#endif /*TSubCurve_H_*/
