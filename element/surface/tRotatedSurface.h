#ifndef TROTATEDSURFACE_H_
#define TROTATEDSURFACE_H_

#include "classes/tVector.h"
#include "element/surface/tSurface.h"
#include "element/curve/tLine.h"

#include "iRotatedSurface.h"

class tRotatedSurface : public tSurface
{
	private:
		tSurface *frefSurface;
		tLine *faxis;
		tReal fangle;
	public:
		tRotatedSurface(void *theOwner);
		tRotatedSurface(void *theOwner, tSurface *surf, tLine *axis, tReal phi);
		virtual ~tRotatedSurface();

//	  virtual tList<tElement*> usedElements(void);

		virtual iElement* intrface(void);

	  virtual tVector vectorAtAccurate(tReal u, tReal v);
	  virtual tVector normalVectorAt(tReal u, tReal v);
	  virtual void refresh(void);

	  void setAxis(tElement *el);
	  void setRefSurface(tElement *el);
    void setAngle(tReal alpha);

    tLine* axis(void){return faxis;}
    tSurface* refSurface(void){return frefSurface;}
    tReal angle(void){return fangle;}
};

/*I!
axis Line read:axis write:setAxis
referenceSurface Surface read:refSurface write:setRefSurface
angle Real read:angle write:setAngle
*/

#endif /*TROTATEDSURFACE_H_*/
