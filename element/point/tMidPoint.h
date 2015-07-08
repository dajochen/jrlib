#ifndef TMIDPOINT_H_
#define TMIDPOINT_H_

#include "element/tGroup.h"

#include "element/point/tDot.h"
#include "iMidPoint.h"

class tMidPoint: public tDot 
{
  tList<tElement*> dot;
  tVector sumGroup(tGroup *g);
  int countGroupDots(tGroup *g);
  
public:
	tMidPoint(void *theOwner, tElement *element=NULL);
	virtual ~tMidPoint();
  
  virtual tList<tElement*> dots(void);
  void setDots(tList<tElement*> dList);

  void addDot(tElement* d);
  void removeDot(tElement* d);
  void removeAll(void);
  tList<tElement*> dotList(void);
    
  virtual void refresh(void);
  iElement* intrface(void);

};
/*I!
supportDots DotList read:dots write:setDots
*/


#endif /*TMIDPOINT_H_*/
