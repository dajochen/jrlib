#ifndef TLINESNAKE_H_
#define TLINESNAKE_H_

#include "element/curve/snake/tSnake.h"
#include "element/point/tAbsMagnet.h"

#include "iLineSnake.h"
class tLineSnake : public tSnake
{
	private:
		tAbsMagnet *m1,*m2;

	public:
		tLineSnake(void *theOwner);
		tLineSnake(void *theOwner,tElement *M1, tElement *M2);
		virtual ~tLineSnake();

		iElement* intrface(void);
		virtual void refresh(void);

		tAbsMagnet* start(void){setElementLocked return m1;};
		tAbsMagnet* end(void){setElementLocked return m2;};
    void setStart(tElement *c){setMagnet(0,c);};
    void setEnd(tElement *c){setMagnet(1,c);};
    void setMagnet(int i, tElement *c);
		void setMagnets(tElement *C1, tElement *C2);
	  virtual tVector vectorAtAccurate(tReal t);
    virtual void uvPosition(tReal t, tReal *u, tReal *v);

    virtual tSurface* reference(void);
};

/*I!
start AbsMagnet read:start write:setStart
end AbsMagnet read:end write:setEnd
*/
#endif /*TLINESNAKE_H_*/
