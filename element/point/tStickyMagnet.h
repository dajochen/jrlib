/*
 * tStickyMagnet.h
 *
 *  Created on: 19 Feb 2012
 *      Author: jochen
 */

#ifndef TSTICKYMAGNET_H_
#define TSTICKYMAGNET_H_

#include "tMagnet.h"
#include "element/tGroup.h"
#include "classes/simplex.h"

#include "iStickyMagnet.h"

class OF_StickyMagnet : public jrObjectiveFunction
{
private:
  tSurface *f_;
  tVector refPoint_;
public:
  OF_StickyMagnet(tSurface *f, tVector refPoint);
  virtual double evaluate (double uv[2]) const ;
};

class tStickyMagnet : public tMagnet
{
private:
  tDot* refDot;
  tGroup* refFaces;
  tVector refDotLocation;
  tSurface* selectedFace;
  double u,v;

//  virtual void clearFaces(void);

public:
  tStickyMagnet(void *theOwner);
  virtual  ~tStickyMagnet();

  iElement* intrface(void);
  virtual void refresh(void);

  virtual tReal uPosition(void){update(); return u;};
  virtual tReal vPosition(void){update(); return v;};

  virtual tSurface* reference(void){update(); return selectedFace;};

  tDot* referenceDot(void){update(); return refDot;};
  void setReferenceDot(tElement *d);

  tGroup* stickyFaces(void) {update(); return refFaces;};
  void setStickyFaces(tElement* faces);

//  virtual void addStickyFace(tElement* faces);

};
/*I!
referenceDot Dot read:referenceDot write:setReferenceDot
stickySurfaces Group read:stickyFaces write:setStickyFaces
*/

#endif /* TSTICKYMAGNET_H_ */
