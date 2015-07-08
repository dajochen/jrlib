#include "tAbstractPolygon.h"

#include "GL/glu.h"

tAbstractPolygon::tAbstractPolygon(void *theOwner, int maxVerts)
    :tPaintableElement(theOwner),
      poly(NULL)
{
    poly = new tPolygonCurve(this,maxVerts);
    poly->addDependent(this);
}


tAbstractPolygon::~tAbstractPolygon()
{
    poly->releaseOwner(this);
    poly->removeDependent(this);
}

iElement *tAbstractPolygon::intrface()
{
    if (iface == NULL){
        iface = new iAbstractPolygon(this);
    }
    return iface;
}

void tAbstractPolygon::refresh()
{
    area_ = 0.;
    normal_ = tVector(0,0,0);
    center_ = tVector(0,0,0);

    int nVerts = nVertices();
    for (int i=1; i<=nVerts; i++){
        tVector x0 = vertex(i-1)->vector(),
                x1 = vertex(i%nVerts)->vector();

        center_ = center_ + x0;
        normal_ = normal_ - tVector ( (x0.y+x1.y) * (x0.z-x1.z),
                                      (x0.z+x1.z) * (x0.x-x1.x),
                                      (x0.x+x1.x) * (x0.y-x1.y) );

    }

    normal_ = normal_ * 0.5;
    area_ = normal_.length();
    normal_ = normal_ * (1./area_);

    center_ = center_ * (1./double(nVerts));

}

void tAbstractPolygon::paintGL(const tVector& EyePoint, const tVector& ObjectPoint, const tRGB& rgb, const tVector &defaultN, const bool& isSelected)
{
    tDot *d;
    tVector n;
    tVector x;
    int i;

    n = normal();
    if (n*(EyePoint-ObjectPoint)<0 && rgb.alpha == 255){
        glColor4ub (230, 190, 200, 55);
    } else {
        glColor4ub (rgb.red, rgb.green, rgb.blue, rgb.alpha);
    }

    glNormal3f(n.x,n.y,n.z);
    // Die Flaeche
    glBegin(GL_POLYGON);
    for (i=0;i<nVertices() ;i++){
        d = vertex(i);
        if (d){
            x = d->vector();
        } else {
            x.setZero();
        }
        glVertex3f( x.x, x.y, x.z);
    }
    glEnd();
    // Die Kanten
    if (rgb.alpha>250 || 1==1){
        glLineWidth(3);
        glColor4ub ((unsigned char)(rgb.red*0.8+255*0.2),
                    (unsigned char)(rgb.green*0.8+255*0.2),
                    (unsigned char)(rgb.blue*0.8+255*0.2),255
                    );
        glBegin(GL_LINE_LOOP);
        for (i=0;i<nVertices();i++){
            d = vertex(i);
            if (d){
                x = d->vector();
            } else {
                x.setZero();
            }
            glVertex3f( x.x, x.y, x.z);
        }
        glEnd();

    }
}
