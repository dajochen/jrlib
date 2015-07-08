#ifndef TMIDCURVE_H_
#define TMIDCURVE_H_

#include "element/curve/tCurve.h"
#include "iMidCurve.h"
 
class tMidCurve : public tCurve
{
private:

  tList<tCurve*> support;
public:
	tMidCurve(void *theOwner);
	virtual ~tMidCurve();
  
  void clear(void);
  void addElement(tElement *el);
  void addList(tList<tElement*> *list);
  
  void removeAllCurves(void);
  void setCurves(tList<tElement*> list);
  tList<tElement*> curves(void);
  int nCurves(void){return support.count();};

  virtual void refresh(void);
  virtual tVector vectorAtAccurate(tReal t);
  iElement* intrface(void);
};

/*I!
nSupportingCurves Int read:nCurves
supportingCurves CurveList read:curves write:setCurves
*/

#endif /*TMIDCURVE_H_*/
