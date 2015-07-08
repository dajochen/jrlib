#ifndef TSUBSURFACE_H_
#define TSUBSURFACE_H_

#include "element/surface/tSurface.h"
#include "element/curve/snake/tSnake.h" 

#include "iSubSurface.h"

class tSubSurface : public tSurface
{
private:
  tSnake *s1, *s2;

public:
	tSubSurface(void *theOwner,tElement *S1 = NULL, tElement *S2=NULL);
	virtual ~tSubSurface();
  
  virtual void refresh(void);
  void clear(void);
  void setBoundingSnakes(tElement *el1, tElement *el2);
  
  virtual iElement* intrface(void);
  virtual tVector vectorAtAccurate(tReal u, tReal v);
  
  virtual tSurface* reference();

  tList<tElement*> boundingSnakes(void);
  void setBoundingSnakes(tList<tElement*> l);
  
};

/*I!
optional reference Surface read:reference
boundingSnakes SnakeList read:boundingSnakes write:setBoundingSnakes
*/

#endif /*TSUBSURFACE_H_*/
