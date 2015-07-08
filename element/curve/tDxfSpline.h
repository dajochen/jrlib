#ifndef TDXFSPLINE_H
#define TDXFSPLINE_H

#include "tAbstractSpline.h"
#include "tHermiteSpline.h"
#include "iDxfSpline.h"

class tDxfSpline : public tAbstractSpline
{
public:
    tDxfSpline(void *theOwner);
    virtual ~tDxfSpline();

    iElement* intrface(void);
    virtual void refresh(void);

    bool isClosed;
    int degree;

    virtual tVector vectorAtAccurate(tReal t);
private:

    tList<tVector> controlPoints;
    tHermiteSpline* hs;



    double* GetMatrix(int iCount, double *dt);
    void UpdateControlPoints();
    void updateXX();

    static void knot(int num, int order, int knotVector[]);
    static void rbspline(int npts, int k, int p1,
                         double b[], double h[], double p[]);

    static void knotu(int num, int order, int knotVector[]);
    static void rbsplinu(int npts, int k, int p1,
                         double b[], double h[], double p[]);

    static void rbasis(int c, double t, int npts, int x[], double h[], double r[]);
};
/*I!
*/

#endif // TDXFSPLINE_H
