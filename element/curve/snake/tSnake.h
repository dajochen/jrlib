#ifndef TSNAKE_H_
#define TSNAKE_H_

#include "element/curve/tCurve.h"
#include "element/surface/tSurface.h"

#include "iSnake.h"

class tSnake: public tCurve
{
private:

public:
	tSnake(void *theOwner);
  virtual ~tSnake();
  
  virtual tSurface* reference()=0;
  virtual void uvPosition(tReal t, tReal *u, tReal *v)=0;
};

/*I!
reference Surface read:reference
*/

#endif /*TSNAKE_H_*/
