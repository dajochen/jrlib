#ifndef TLINE_H_
#define TLINE_H_

#include "element/curve/tCurve.h"
#include "element/point/tDot.h"

#include "iLine.h"

class tLine : public tCurve
{
	private:
		tDot *c1,*c2;

	public:
		tLine(void *theOwner,tElement *C1=NULL, tElement *C2=NULL);
		virtual ~tLine();

//	  virtual tList<tElement*> usedElements(void);

		iElement* intrface(void);
		virtual void refresh(void);

        tDot* start(void){return c1;}
        tDot* end(void){return c2;}
    void setStart(tElement *el);
    void setEnd(tElement *el);
		void setVortex(int i, tElement *el);
		void setVertices(tElement *C1, tElement *C2);

	  virtual tVector vectorAtAccurate(tReal t);
	  virtual tVector gradientAt(tReal t);
	  virtual tVector curvatureAt(tReal t);
//	  virtual tReal getSFromT(tReal t);
//		virtual tReal getTFromS(tReal s);

		virtual tReal length(void);
	  virtual tVector xMin(void);
	  virtual tVector xMax(void);
};

/*I!
start Dot write:setStart read:start
end Dot write:setEnd read:end
*/

#endif /*TLine_H_*/
