#ifndef TREFINEDQUAD_H
#define TREFINEDQUAD_H

#include "classes/tList.h"
#include "element/point/tDot.h"
#include "element/misc/tQuad.h"
#include "iRefinedQuad.h"

/**
 * @brief The tRefinedQuad class
 * A tQuad with refined edges.
 *
 *  c1-----refinement[1]-----c2
 *  |                         |
 *  |                         |
 * refinement[0]            refinement[2]
 *  |                         |
 *  |                         |
 *c0/c4-----refinement[3]-----c3
 *
 */
class tRefinedQuad : public tQuad
{
protected:
    tList<tDot*> refinement[4];
public:
  tRefinedQuad(void *theowner);
  virtual ~tRefinedQuad();

  virtual iElement* intrface(void);
  virtual void refresh(void);

  virtual void setDot(int edge, int pos, tDot* d);
  virtual void setDotList(int edge, const tList<tElement*>& l);
  virtual void setDotList0(const tList<tElement*>& l) {setDotList(0,l);}
  virtual void setDotList1(const tList<tElement*>& l) {setDotList(1,l);}
  virtual void setDotList2(const tList<tElement*>& l) {setDotList(2,l);}
  virtual void setDotList3(const tList<tElement*>& l) {setDotList(3,l);}

  virtual tList<tElement*> dotList(int edge);
  virtual tList<tElement*> dotList0() {return dotList(0);}
  virtual tList<tElement*> dotList1() {return dotList(1);}
  virtual tList<tElement*> dotList2() {return dotList(2);}
  virtual tList<tElement*> dotList3() {return dotList(3);}

// Can be adapted if necessary:
//  tVector normalVector(void){update(); return fnormalVector;};
//  tVector center(void){update(); return fcenter;};
//  tReal area(void){update(); return farea;};
//  tReal size(void){update(); return fsize;};
//  tReal diameter(void){update(); return fdiameter;};
//  tReal twistiness(void){ update(); return ftwistiness;};
};

/*I!
refinement0 DotList read:dotList0 write:setDotList0
refinement1 DotList read:dotList1 write:setDotList1
refinement2 DotList read:dotList2 write:setDotList2
refinement3 DotList read:dotList3 write:setDotList3
*/
#endif // TREFINEDQUAD_H
