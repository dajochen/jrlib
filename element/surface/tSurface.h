#ifndef TSURFACE_H_
#define TSURFACE_H_

#include "classes/tVector.h"
#include "classes/jrTypes.h"
#include "element/tElement.h"

#include "iSurface.h"

class tSurface : public tElement
{
	private:
    bool validCache;
  protected:

    bool isAccurate,
         fOrientation;
    int fuRes, fvRes, fuDiv, fvDiv;
    tVector *fuvCache;

    void reallocCache(void);
    void updateCache(void);

    virtual tVector vectorAtAccurate(tReal u, tReal v)=0;

	public:
		tSurface(void *theOwner);
		virtual ~tSurface();

		virtual iElement* intrface(void)=0;
	  virtual tVector xMin(void);
	  virtual tVector xMax(void);

    virtual void invalidate(tElement *sender);
    virtual tVector vectorAt(tReal u, tReal v);
	  virtual tVector normalVectorAt(tReal u, tReal v);

    virtual void setUDiv(int UDIV);
    virtual void setURes(int URES);
    virtual void setVDiv(int VDIV);
    virtual void setVRes(int VRES);
    int uDiv(void){setElementLocked; return fuDiv;}
    int uRes(void){setElementLocked; return fuRes;}
    int vDiv(void){setElementLocked; return fvDiv;}
    int vRes(void){setElementLocked; return fvRes;}

    tVector* uvCache(void){updateCache(); return fuvCache;}

    bool accurate(void){setElementLocked; return isAccurate;}
    void setAccurate(bool a){setElementLocked; isAccurate = a; invalidate(this);}
    bool orientation(void){setElementLocked; return fOrientation;}
    void setOrientation(bool o){setElementLocked fOrientation = o; invalidate(this);}
};
/*I!
uDiv Int read:uDiv write:setUDiv
vDiv Int read:vDiv write:setVDiv
uRes Int read:uRes write:setURes
vRes Int read:vRes write:setVRes
orientation Bool read:orientation write:setOrientation
accurate Bool read:accurate write:setAccurate
*/

#endif /*TSURFACE_H_*/
