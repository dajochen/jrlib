#ifndef TPLANE_H_
#define TPLANE_H_

#include "element/point/tDot.h"
#include "tBasicPlane.h"
#include "iPlane.h"

class tPlane : public tBasicPlane
{
public:
  tPlane(void* theOwner);
  virtual ~tPlane();

  virtual void refresh(void);
  virtual iElement *intrface(void);

  virtual void setCenter(tElement *center);
  virtual void setOnNormal(tElement *onNormal);
  virtual void setOnHorizontal(tElement *onHorizontal);
  virtual void setMode (int mode);

  virtual tDot* centerPoint(void);
  virtual tDot* onNormal(void);
  virtual tDot* onHorizontal(void);
  virtual int mode(void);

protected:
    tDot *fcenterPoint, *fPointOnNormal, *fPointOnHorizontal;
    int fmode; //mode%2 -> 0: normal vector is accurate
               //       -> 1: horizontal dir is accurate

};
/*I!
centerPoint Dot read:centerPoint write:setCenter
onNormal Dot read:onNormal write:setOnNormal
onHorizontal Dot read:onHorizontal write:setOnHorizontal
mode Int write:setMode read:mode
*/

#endif /*TPLANE_H_*/
