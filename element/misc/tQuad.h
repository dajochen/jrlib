#ifndef TQUAD_H_
#define TQUAD_H_

#include "element/tElement.h"
#include "element/point/tDot.h"
#include "iQuad.h"

class tQuad : public tElement
{
private:
  tDot* fC[4];
  tVector fnormalVector, fcenter;
  tReal farea, fsize, fdiameter, ftwistiness;
  tVector minVector(tVector x1, tVector x2);
  tVector maxVector(tVector x1, tVector x2);

public:
	tQuad(void *theowner);
	virtual ~tQuad();
  virtual void refresh(void);
  virtual iElement* intrface(void);
  virtual tVector xMin(void);
  virtual tVector xMax(void);

  void setCorner(int index, tElement *c);
  void defineQuad(tElement *C1,tElement *C2, tElement *C3,tElement *C4);

  virtual tList<tElement*> corners(void);
  virtual void setCorners(const tList<tElement*>& c);

  tDot* c(int index);
  tDot* c1(void) {/*setElementLocked update(); */return fC[1];}
  tDot* c2(void) {/*setElementLocked update(); */return fC[2];}
  tDot* c3(void) {/*setElementLocked update(); */return fC[3];}
  tDot* c4(void) {/*setElementLocked update(); */return fC[0];}
  tVector normalVector(void){update(); return fnormalVector;}
  tVector center(void){update(); return fcenter;}
  tReal area(void){update(); return farea;}
  tReal size(void){update(); return fsize;}
  tReal diameter(void){update(); return fdiameter;}
  tReal twistiness(void){ update(); return ftwistiness;}
};

/*I!
center Vector read:center
normalVector Vector read:normalVector
area Real read:area
size Real read:size
diameter Real read:diameter
corners DotList read:corners write:setCorners
*/

#endif /*TQUAD_H_*/
