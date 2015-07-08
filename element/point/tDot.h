#ifndef TDOT_H_
#define TDOT_H_

#include "element/tElement.h"
#include "classes/tVector.h"

#include "iDot.h"

class tDot : public tElement
{
protected:
	tVector X;
	
public:
	tDot(void *theowner);
 	virtual ~tDot();

	virtual void refresh(void)=0;
  tReal x(void);
  tReal y(void);
  tReal z(void);
	tVector vector(void);
	
  virtual tVector xMin(void);
  virtual tVector xMax(void);
	
  operator tVector() {update();return X;}
	  	
};
/*I!
location Vector read:vector
dependents ElementList read:dependents
 */

#endif /*TDOT_H_*/
