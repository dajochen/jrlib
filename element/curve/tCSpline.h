  #ifndef TCSPLINE_H_
#define TCSPLINE_H_

#include "element/curve/tCurve.h"
#include "classes/tList.h"
#include "element/point/tDot.h"
#include "element/tGroup.h"

#include "iCSpline.h"

enum tCSplineType{jrCSVortexBased,jrCSLengthBased};

class tCSpline : public tCurve
{
private:
  tList<tDot*> vertex;
  tList<tReal> dt; //,dl;
  tVector *A,*B,*C,*D;  // jeder Spline: ai*(t-ti)^3+bi*(t-ti)^2+ci*(t-ti)+di
  tCSplineType theCSplineType;
  int fDegree;

  void initialize();
  //	  tVector vectorAtSection(int section, tReal fraction);
  bool getSectionFromT(float t, int *section, tReal *fraction);

public:
  tCSpline(void *theOwner);
  tCSpline(void *theOwner, tList<tElement*> *l);
  virtual ~tCSpline();

  iElement* intrface(void);
  virtual void refresh(void);

  tCSplineType CSplineType(void);
  void setCSplineType(int  t);

  int degree(void);
  void setDegree(int deg);

  bool addVortex(tDot *P);
  bool insertVortex(int i, tElement *P);
  void insertList(int index, tList<tElement*> *l);
  void addVertices(tGroup *Group);
  void addVertices(tList<tElement*> *List);
  tList<tElement*> vertices(void);
  void setVertices(tList<tElement*> List);
  void clear(void);


  virtual tVector vectorAtAccurate(tReal t);
  virtual tVector gradientAt(tReal t);
  virtual tVector curvatureAt(tReal t);

  int nVertices(){return vertex.count();};
  tDot* getVortex(int index);
  tReal tAtVortex(int index);

};
/*I!
nVertices Int read:nVertices
smoothingType Int read:CSplineType write:setCSplineType
vertices DotList read:vertices write:setVertices
*/

#endif /*TCSPLINE_H_*/
