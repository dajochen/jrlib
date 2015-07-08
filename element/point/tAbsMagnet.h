#ifndef TABSMAGNET_H_
#define TABSMAGNET_H_

#include "element/point/tDot.h"
#include "element/surface/tSurface.h"

#include "iAbsMagnet.h"

class tAbsMagnet : public tDot
{
	private:

	protected:
    tSurface *surface;
    tReal u,v;

	public:

		//tAbsMagnet(void *theOwner);
		tAbsMagnet(void *theOwner,tElement *surf=NULL, tReal U=0.5, tReal V=0.5);
		virtual ~tAbsMagnet();

//	  virtual tList<tElement*> usedElements(void);

		iElement* intrface(void);
		virtual void refresh(void);

		virtual tReal uPosition(void){return u;};
		virtual tReal vPosition(void){return v;};
		void setPosition(tReal U, tReal V);
    void setUPosition(tReal U){setPosition(U, v);};
    void setVPosition(tReal V){setPosition(u, V);};
		tSurface* reference(void){return surface;};
		void setReference(tElement *newSurface);
};
/*I!
uPosition Real read:uPosition write:setUPosition
vPosition Real read:vPosition write:setVPosition
referenceSurface Surface read:reference write:setReference
*/


#endif /*TABSMAGNET_H_*/
