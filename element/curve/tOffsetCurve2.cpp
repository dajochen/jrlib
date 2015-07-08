#include "tOffsetCurve2.h"

#include "tHermiteSpline.h"
#include "tPoint.h"

tOffsetCurve2::tOffsetCurve2(void *theOwner)
    : tCurve(theOwner)
{
    reference = NULL;
    tHermiteSpline *hs = new tHermiteSpline(this);
    hs->setBias(1.);
    hs->setTension(1.);
    hs->setContinuity(1.);
    hs->setTResolution(60);

    offsetCurve  = hs;

    offset_ = 0.;
}

tOffsetCurve2::~tOffsetCurve2()
{
    setReferenceCurve(NULL);
    offsetCurve->releaseOwner(this);
}

iElement *tOffsetCurve2::intrface()
{
    if (iface == NULL){
        iface = new iOffsetCurve2(this);
    }
    return iface;
}

void tOffsetCurve2::refresh()
{

    tList<tVector> basePts, oPoints;
    bool isLoop = false;

    for (int i=0; i<reference->nVertices()-1; i++){
        oPoints.append(reference->vertex(i)->vector());
    }
    if ((reference->vertex(0)->vector()-reference->vertex(reference->nVertices()-1)->vector()).length_squared() > 0){
        oPoints.append(tPoint(NULL, reference->vertex(reference->nVertices()-1)->vector()));
        isLoop = false;
    } else {
        isLoop = true;
    }

    tVector nRef = tVector(0,0,0);


    double toDo = offset_;

    while (toDo > 0){
        basePts = oPoints;
        oPoints.clear();

        int nBasePts = basePts.count();

        // calc max offset value (without collapsing edges)
        double offsetMax = toDo;

        for (int i=0; i<nBasePts-1; i++){
            tVector x0,x1,x2,x3,
                    a,b,c;
            int i1 = (i+1+nBasePts) % nBasePts,
                    i2 = (i+2+nBasePts) % nBasePts,
                    i3 = (i+3+nBasePts) % nBasePts;
            x0 = basePts.at(i);
            x1 = basePts.at(i1);
            x2 = basePts.at(i2);
            x3 = basePts.at(i3);

            a = x1-x0;
            b = x2-x1;
            c = x3-x2;

            bool skipCheck;

            tVector n = (a*(-1.) % b).normalize();
            if (n*nRef < 0.){
                skipCheck = true;
            }
            nRef = n;
            n = (b*(-1.) % c).normalize();
            if (n*nRef < 0.){
                skipCheck = true;
            }
            nRef = n;


            if (skipCheck == false) {
                double A = a.length(),
                        B = b.length(),
                        C = c.length();

                double alpha = acos(b*(a*(-1.)) /(A*B)),
                        beta  = acos(c*(b*(-1.)) /(C*B));

                double oMax = B / (1./tan(alpha/2.) + 1./tan(beta/2.));

                if (oMax < offsetMax) {
                    offsetMax = oMax;
                }
            }
        }


        toDo -= offsetMax;

        //create offset
        nRef = tVector(0,0,0);
        for (int i=0; i<nBasePts; i++){

            tVector x,x0,x1,
                    a,b,
                    f, n,
                    p;

            double dist;
            int ip = (i+1+nBasePts) % nBasePts,
                    im = (i-1+nBasePts) % nBasePts;
            x = basePts.at(i);
            x0 = basePts.at(im);
            x1 = basePts.at(ip);

            a = (x0-x).normalize();
            b = (x1-x).normalize();

            f = a+b;

            n = (a % b).normalize();
            if (n*nRef < 0.){
                n = n* (-1.);
            }
            nRef = n;
            n = n%a;// ( % a).normalize();

            dist = f*n;
            double scale = offsetMax / dist;
            dist = f*scale * n;

            //double ll;
            //ll = f.length();
            //ll = n.length();
            //ll = (f*scale).length();



            if (dist !=0) {
                p = x + f * scale;
            } else {
                p = x;
            }
            oPoints.append(p);
        }

        for (int i=0; i<nBasePts; i++) {
            if ( (oPoints.at(i)-oPoints.at((i+1)%nBasePts)).length_squared() < 1e-10 ) {
                oPoints.removeAt(i);
                i--;
                nBasePts--;
            }
        }

    }

    tList<tDot*> pts;
    for (int i=0; i<oPoints.count(); i++){
        tDot *d = NULL;
        d = new tPoint(NULL,oPoints.at(i));

        pts.append(d);
    }
    if (isLoop && pts.count() >0 ){
        pts.append(pts.at(0));
    }

    offsetCurve->setVertices(pts);

}

tVector tOffsetCurve2::vectorAtAccurate(tReal t)
{
    setElementLocked
    update();
    if (offsetCurve){
        return offsetCurve->vectorAtAccurate(t);
    } else {
        return tVector(0.,0.,0.);
    }
}

void tOffsetCurve2::setReferenceCurve(tElement *el)
{
    setElementLocked;
    if (reference){
      reference->removeDependent(this);
    }
    reference=dynamic_cast<tDotListCurve*>(el);
    if (reference){
      reference->addDependent(this);
    }
    invalidate(this);
}

tDotListCurve *tOffsetCurve2::referenceCurve()
{
    return reference;
}

void tOffsetCurve2::setOffset(double value)
{
    if (value != offset_) {
        offset_ = value;
        invalidate(this);
    }
}
