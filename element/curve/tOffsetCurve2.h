#ifndef TOFFSETCURVE2_H
#define TOFFSETCURVE2_H

#include "element/curve/tCurve.h"
#include "element/curve/tDotListCurve.h"
#include "element/curve/tAbstractSpline.h"

#include "iOffsetCurve2.h"

class tOffsetCurve2 : public tCurve
{

private:
    tDotListCurve *reference;
    tAbstractSpline *offsetCurve;
    double offset_;

public:
    tOffsetCurve2(void *theOwner);
    virtual ~tOffsetCurve2();

    iElement* intrface(void);
    virtual void refresh(void);

    virtual tVector vectorAtAccurate(tReal t);

    void setReferenceCurve(tElement* el);
    tDotListCurve* referenceCurve(void);

    void setOffset(double value);
    double offset(void) {return offset_;}

};

/*I!
referenceCurve Curve read:referenceCurve write:setReferenceCurve
offset Real read:offset write:setOffset
*/

#endif // TOFFSETCURVE2_H
