/*
 * tKaSeries.h
 *
 *  Created on: 14.07.2010
 *      Author: Jochen
 */

#ifndef TKASERIES_H_
#define TKASERIES_H_

#include "element/surface/tPropSurface.h"
#include "iKaSeries.h"

class tLayer;

class tKaSeries : public tPropSurface {
protected:
  tReal fPD, fAEA0;

  virtual tReal pitchAt(tReal rR);
  virtual tReal chordAt(tReal rR);
  virtual tReal rakeAt(tReal rR);
  virtual tReal skewAt(tReal rR);
  virtual tReal maxThicknessAt(tReal rR);

public:
  tKaSeries(void *theOwner, tLayer *hostingLayer = NULL);
  virtual ~tKaSeries();

  virtual void refresh(void);
  virtual iElement* intrface(void);

  void setPD(tReal pd){fPD = pd; invalidate(this);};
  tReal PD(void){return fPD;};

  void setAEA0(tReal aeao){fAEA0=aeao; invalidate(this);}
  tReal AEA0(void){return fAEA0;};


/*I!
PD Real read:PD write:setPD
AEA0 Real read:AEA0 write:setAEA0
optional pitch
optional chord
optional rake
optional skew
optional maxThickness
optional thickness
optional camber
*/

};

#endif /* TKASERIES_H_ */
