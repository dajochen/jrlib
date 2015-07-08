#ifndef TSUMCURVE_H_
#define TSUMCURVE_H_

#include "element/curve/tCurve.h"
#include "iSumCurve.h"

class tSumCurve : public tCurve
{
private:

  tList<tCurve*> support;
public:
	tSumCurve(void *theOwner);
	virtual ~tSumCurve();

  void clear(void);
  void addSupport(tElement *el);
  void addSupportList(tList<tElement*> *list);
  tList<tElement*> supportList(void);
  void setSupportList(tList<tElement*> l);

  int nCurves(void){return support.count();};
  virtual void refresh(void);
  virtual tVector vectorAtAccurate(tReal t);
  iElement* intrface(void);
};

/*I!
nSupportCurves Int read:nCurves
supportCurves CurveList read:supportList write:setSupportList
*/

#endif /*TSUMCURVE_H_*/
