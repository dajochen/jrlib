#ifndef TCSNAKE_H_
#define TCSNAKE_H_

#include "element/curve/snake/tSnake.h"
#include "element/point/tAbsMagnet.h"
#include "element/curve/tCSpline.h"
#include "element/point/tPoint.h"

#include "iCSnake.h"

class tCSnake : public tSnake
{
	private:
		tList<tAbsMagnet*> vertex;
    tSurface *s;
    tCSpline *c;

	public:
    tCSnake(void *theOwner,tList<tElement*> *List = NULL);

		virtual ~tCSnake();

//	  virtual tList<tElement*> usedElements(void);

		iElement* intrface(void);
		virtual void refresh(void);

    void removeAllVertices(void);
    void addVertices(tList<tElement*> *List);
    void setVertices(tList<tElement*> List);
    tList<tElement*> vertices(void);

    tSurface* reference(void);
	  virtual tVector vectorAtAccurate(tReal t);
    void uvPosition(tReal t, tReal *u, tReal *v);

};

/*I!
vertices DotList read:vertices write:setVertices
*/


#endif /*TCSNAKE_H_*/
