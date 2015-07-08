#ifndef TMAGNET_H_
#define TMAGNET_H_

#include "element/point/tDot.h"
#include "element/surface/tSurface.h"

#include "iMagnet.h"

class tMagnet : public tDot
{
	private:

	protected:

	public:

		tMagnet(void *theOwner);
		virtual ~tMagnet();

		iElement* intrface(void);

		virtual tReal uPosition(void)=0;
		virtual tReal vPosition(void)=0;
		virtual tSurface* reference(void)=0;

};
/*I!
uPosition Real read:uPosition
vPosition Real read:vPosition
referenceSurface Surface read:reference
*/


#endif /*tMagnet_H_*/
