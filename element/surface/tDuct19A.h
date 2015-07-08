/*
 * t19ADuct.h
 *
 *  Created on: 30.01.2011
 *      Author: Jochen
 */

#ifndef TDUCT19A_H_
#define TDUCT19A_H_

#include "element/surface/tSurface.h"
#include "element/surface/tKaSeries.h"
#include "element/curve/tCSpline.h"
#include "classes/tSolve.h"
#include "iDuct19A.h"

class tDuct19A : public tSurface
{
private:
  double vTE, vLE, midAngle;
  tVector tePos, lePos, midPos;

  tKaSeries *fprop;
  tCSpline *contur;
  tCSpline *midTwist, *leTwist, *teTwist;
  double xTE,xLE;
  double uTEinner, uTEouter, uLE, uLEinner, uLEouter;
  double tTEinner, tTEouter, tLE, tLEinner, tLEouter, dtduLE;

  tJSolve *innerLGS, *leLGS, *outerLGS;
  tJSolve *vlgs;

  bool fAdaptToPropellerPitch;

public:
  tDuct19A(void *theOwner);
  virtual ~tDuct19A();

  virtual void refresh(void);
  virtual iElement* intrface(void);
  virtual tVector vectorAtAccurate(tReal u, tReal v);

  void setPropeller(tElement *p);
  tKaSeries* propeller(void){return fprop;};

  bool adaptToPropellerPitch(void){return fAdaptToPropellerPitch;};
  void setAdaptToPropellerPitch(bool value){fAdaptToPropellerPitch=value; invalidate(this);};
};

/*I!
referencePropeller KaSeries read:propeller write:setPropeller
adaptToPropellerPitch Bool read:adaptToPropellerPitch write:setAdaptToPropellerPitch
*/

#endif /* TDUCT19A_H_ */
