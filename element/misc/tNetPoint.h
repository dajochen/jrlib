#ifndef TNETPOINT_H_
#define TNETPOINT_H_

#include "element/point/tDot.h"
#include "element/misc/tNet.h"

#include "iNetPoint.h" 

class tNetPoint : public tDot
{
private:
  tNet *fnet;
  
public:
	tNetPoint(void *theowner, tNet *net, tDot *refPoint);
	virtual ~tNetPoint();
  virtual void refresh(void);
  
  tNet* net(void);
  void setNet(tElement* net);
  
  tDot* refPoint(void);
  void setRefPoint(tElement* refPoint);
  
  virtual iElement* intrface(void);
};

/*I!
 */

#endif /*TNETPOINT_H_*/
