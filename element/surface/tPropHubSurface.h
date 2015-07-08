/*
 * tPropHubSurface.h
 *
 *  Created on: 22.07.2010
 *      Author: Jochen
 */

#ifndef TPROPHUBSURFACE_H_
#define TPROPHUBSURFACE_H_

#include "element/surface/tSurface.h"
#include "element/surface/tPropSurface.h"
#include "iPropHubSurface.h"

class tPropHubSurface : public tSurface {
public:
protected:
  tPropSurface* prop;
  tCurve *fhubContour;

  tReal radiusAt(tReal x);
  tReal fleadingPartition, ftrailingPartition, // Laenger der Nabe vor der Eintrittskante / hinter der Austrittskante
        fleadingAlpha, ftrailingAlpha;   //Drehwinkel, auf den die Nabe auslaeuft
  tReal xTE, xLE,
        alphaMaxTE, alphaMaxLE;

  tReal getValueAtCurve(tCurve *c, tReal xx);

public:
  tPropHubSurface(void *theOwner);
  virtual ~tPropHubSurface();

  virtual void refresh(void);
  virtual iElement* intrface(void);
  virtual tVector vectorAtAccurate(tReal u, tReal v);

  void clear(void);

  void setPropellerSurface(tElement* p);
  tPropSurface* propellerSurface(void);
  void setHubContour(tElement *h);
  tCurve* hubContour(void);

  void setLeadingPartition(tReal frac);
  tReal leadingPartition(void);
  void setTrailingPartition(tReal frac);
  tReal trailingPartition(void);

  void setLeadingAlpha(tReal a);
  tReal leadingAlpha(void);
  void setTrailingAlpha(tReal a);
  tReal trailingAlpha(void);

};

/*I!
propellerSurface PropSurface read:propellerSurface write:setPropellerSurface
hubContour Curve read:hubContour write:setHubContour
leadingPartition Real read:leadingPartition write:setLeadingPartition
trailingPartition Real read:trailingPartition write:setTrailingPartition
leadingAlpha Real read:leadingAlpha write:setLeadingAlpha
trailingAlpha Real read:trailingAlpha write:setTrailingAlpha
*/

#endif /* TPROPHUBSURFACE_H_ */
