#ifndef TTRIANGLEPATCH_H
#define TTRIANGLEPATCH_H


#include "element/tPaintableElement.h"
#include "element/tGroup.h"
#include "model/tLayer.h"
#include "tTriangle.h"

#include "iTrianglePatch.h"

struct tPatchLocation {
    tTriangle *tri;
    tVector x;
};

class tTrianglePatch : public tPaintableElement
{
protected:
    tGroup *tris;
    tLayer *helper_;
public:
    tTrianglePatch(void * theOwner);
    virtual ~tTrianglePatch();

    iElement* intrface(void);
    virtual void refresh(void);

    int nTriangles(void)                  { update(); return tris->nElements();}
    virtual tList<tElement*> triangles()  { update(); return tris->elements(); }
    virtual tTriangle* triangle(int i)         { update(); return dynamic_cast<tTriangle*>(tris->element(i));  }

    void addTriangle(tElement *el)            {tris->append(el);}
    void addTriangles(const tList<tElement*> List) {tris->append(List); invalidate(this);}
    void setTriangles(const tList<tElement*> list)  {tris->setElements(list); invalidate(this);}

    void clear(void)                          {tris->clear(); invalidate(this);}

    void randomizeOrientation(void);
    void alignOrientation(void);

    void test();
    tElement *helper(){return helper_;}
    tPatchLocation projectPointToPatch(tVector p, tVector projDir, tGroup *foundTri = NULL);
    tPatchLocation walkOnPatch(tVector start, tVector &walkDir, tVector &upDir, double& distance, bool walkUprightOnPatch=true);
    tPatchLocation walkOnPatch(tPatchLocation start, tVector &walkDir, tVector &upDir, double& distance, bool walkUprightOnPatch=true);

    void paintGL(const tVector &EyePoint, const tVector &ObjectPoint, const tRGB &rgb, const tVector &defaultN, const bool &isSelected);

private:
    tList<tTriangle*> neighbours (tTriangle* tri);
    tTriangle *neighbour(tDot *d0, tDot*d1, tTriangle *notThis);
    void orientNeighbours(tTriangle *tri, tList<tTriangle*>& processedTris);

    bool walkOnTri(tTriangle *tri, tVector &start, const tVector &walkDir, const tVector &upDir, double &distance, int &edgeIndex);
    bool projectPointToTriangle(tTriangle *tri, tVector& p, const tVector& projDir);

    tVector intersectTriPlaneToAxis(tTriangle* tri, const tVector &p, const tVector &dir, bool& found);
    tVector intersectPlaneToAxis(const tVector& x, const tVector& n, const tVector &p, const tVector &dir, bool& found);


};



/*I!
nTriangles Int read:nTriangles
triangles TriangleList read:triangles write:setTriangles
action randomizeOrientation
action alignOrientation
action test
*/

#endif // TTRIANGLEPATCH_H
