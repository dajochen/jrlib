#ifndef TXPLANE_H_
#define TXPLANE_H_

#include "tBasicPlane.h"
#include "iXPlane.h"

class tXPlane : public tBasicPlane
{
protected:
public:
  tXPlane(void* theOwner);
  virtual ~tXPlane();

  virtual void refresh(void) {}
  virtual iElement *intrface(void);

  double x(void) {return fcenter.x;}
  void setX (double ax) {fcenter.x = ax; invalidate(this);}

};
/*I!
x Real write:setX read:x
*/
#endif /*TXPLANE_H_*/
