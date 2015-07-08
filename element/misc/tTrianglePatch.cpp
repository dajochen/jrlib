#include "tTrianglePatch.h"

#include "tPoint.h"
#include "tLayer.h"
tTrianglePatch::tTrianglePatch(void *theOwner) :
    tPaintableElement(theOwner)
{
    tris = new tGroup(this, iTriangle::theType());
    tris->addDependent(this);
    helper_ = new tLayer(this);
}

tTrianglePatch::~tTrianglePatch()
{
    tris->clear();
    tris->removeDependent(this);
    tris->releaseOwner(this);
    helper_->releaseOwner(this);
}

iElement *tTrianglePatch::intrface()
{
    if (iface == NULL){
        iface = new iTrianglePatch(this);
    }
    return iface;
}

void tTrianglePatch::refresh()
{

}

void tTrianglePatch::randomizeOrientation()
{
    qsrand(2);

    tGroup* helper = new tGroup(this); // Add Points, so that they wont be deleted due to missing dependencies
    // Get random value between 0-100
    for (int i=0; i<nTriangles(); i++){
        int randomValue = qrand() % 2;
        if (randomValue == 1) {
            tList<tElement*> verts = triangle(i)->vertices();
            verts.reverse();
            helper->setElements(verts);
            triangle(i)->setVertices(verts);
            helper->clear();
        }
    }
    helper->releaseOwner(this);
}

void tTrianglePatch::alignOrientation()
{
    tList<tTriangle*> processedTris;

    for (int i=0; i<nTriangles(); i++) {
        tTriangle* tri = triangle(i);
        orientNeighbours(tri,processedTris);

    }
    processedTris.clear();
}

void tTrianglePatch::test()
{
    tVector x(0,0,0),n(0,0,0);
    double area;
    for (int i=0 ;i<nTriangles(); i++) {
        tTriangle *tri = triangle(i);
        tVector xx(0,0,0);
        for (int j=0; j<tri->nVertices(); j++){
            xx = xx+tri->vertex(j)->vector();
        }
        double a = tri->area();
        x = x + xx * (a/double(tri->nVertices()));
        n = n + tri->normal()*a;
        area += a;
    }
    x = x * (1./area);
    n = n * (1./area);

    tGroup *foundTri = new tGroup(this);


    tLayer *l = dynamic_cast<tLayer*>(helper_);
    l->clear();
    tPoint *p = l->addPoint(x + n*10);
    tVector y = projectPointToPatch( p->vector(), tVector(0,1,0), foundTri).x;

    tTriangle *tt = dynamic_cast<tTriangle*>(foundTri->last());
    tt->intrface()->setColor(tRGB(0,100,0));
    l->addElement(tt);

    y.setZero();
    for (int i=0; i<3; i++){
        y = y + tt->vertex(i)->vector();
    }
    y = y * (1./3.);
    l->addPoint(y);




    double distance = 110.44;
    //y = walkOnPatch(y, tVector(0,1,0), tVector(1,0,0),distance);
    //tElement *el = l->addPoint(y);
    //el->intrface()->setColor(tRGB(200,0,0));

    //y = walkOnPatch(y, tVector(0,1,0), tVector(1,1,0),distance);
    tVector walkDir = tVector(0.3,0,-1);
    tVector upDir = tVector(0,1,0);
    tTriangle *initialTri = NULL;
    y = walkOnPatch(y, walkDir, upDir, distance, initialTri).x;
 //   el = l->addPoint(y);
 //   el->intrface()->setColor(tRGB(0,200,0));

    foundTri->clear();
    foundTri->releaseOwner(this);

}

tPatchLocation tTrianglePatch::projectPointToPatch(tVector p, tVector projDir, tGroup *foundTri)
{
    tPatchLocation loc;
    loc.tri = NULL;
    loc.x.setZero();
    double dd = -1;
    //tVector projPt = tVector(0,0,0);
    for (int i=0; i<nTriangles(); i++){
        tVector pp = p;
        if (projectPointToTriangle(triangle(i), pp, projDir)) {
            if (foundTri != NULL) {
               foundTri->append(triangle(i));
            }
            double dist_sqr = (pp-p).length_squared();
            if (dist_sqr < dd || dd < 0) {
                loc.x = pp;
                loc.tri = triangle(i);
                //projPt = pp;
                dist_sqr = dd;
            }
        }
    }
    return loc;
    //return projPt;
    //return tVector(0,0,0);
}
/**
 * @brief tTrianglePatch::walkOnPatch
 * @param start
 * @param walkDir
 * @param upDir
 * @param distance: Total distance to walk
 * @param walkUprightOnPatch: If set to true (default) upDir is adjusted from triangle to triangle such that an upright observer
 * is normal each triangle plane met on its way (e.g. walking on a cylinder results in a helix). Else the observer walks on a
 * plane intersecting the patch. (e.g. walk path is intersection curve btw plane and this clinder).
 * @return
 */
tPatchLocation tTrianglePatch::walkOnPatch(tPatchLocation start, tVector& walkDir, tVector& upDir, double& distance, bool walkUprightOnPatch)
{

    tGroup *helper = new tGroup(this, iTriangle::theType());

    tPatchLocation location;
    location.x = start.x;
    location.tri = start.tri;

    if (start.tri == NULL) {
        location = projectPointToPatch(start.x, upDir, helper);
    }

    helper->clear();
    helper->releaseOwner(this);

    tLayer *l = dynamic_cast<tLayer*>(helper_);
    tVector leftHand = upDir % walkDir;
    int counter = 0;

    bool found = true;

    while (found && location.tri && distance > 0){
        counter ++;
        location.tri->intrface()->setColor(tRGB(180,200,0));
        l->addElement(location.tri);

        int edgeIndex = -1;
        tVector x0 = location.x;

        if (walkUprightOnPatch) {
            upDir = location.tri->normal();
        }

        found = walkOnTri(location.tri, location.x, walkDir, upDir, distance, edgeIndex);
        if (found && edgeIndex >= 0) {
            walkDir = location.x-x0;

            if (!walkUprightOnPatch){
                upDir = walkDir % leftHand;
            }

            tDot *d0 = location.tri->vertex(edgeIndex),
                 *d1 = location.tri->vertex(edgeIndex+1);
            location.tri->intrface()->setColor(tRGB(180,200,200));
            location.tri = neighbour(d0,d1, location.tri);
        } else {
        }
    }
    return location;
}

void tTrianglePatch::paintGL(const tVector &EyePoint, const tVector &ObjectPoint, const tRGB &rgb, const tVector &defaultN, const bool &isSelected)
{
    int count = nTriangles();
    for (int i=0; i<count; i++) {
        triangle(i)->paintGL(EyePoint,ObjectPoint, rgb, defaultN, isSelected);
    }
    //!!!!paintElement(helper());
}

tPatchLocation tTrianglePatch::walkOnPatch(tVector start, tVector &walkDir, tVector &upDir, double &distance, bool walkUprightOnPatch)
{
    tPatchLocation pl;
    pl.x = start;
    pl.tri = NULL;

    return walkOnPatch(pl, walkDir, upDir, distance, walkUprightOnPatch);
}

/**
 * @brief tTrianglePatch::walkOnTri
 * walks along the given triangle towards the given direction walkDir. While walking in to this direction starting from the point start, it
 * walks along the intersection between the triangle and a plane constructed from the in-plane vectors walkdir and upDir, which originate from the
 * startpoint
 * @param tri
 * @param start
 * @param walkDir
 * @param upDir
 * @param distance
 * @return
 */
bool tTrianglePatch::walkOnTri(tTriangle *tri, tVector &start, const tVector &walkDir, const tVector &upDir, double &distance, int &edgeIndex)
{
    tVector X[3];
    if (projectPointToTriangle(tri, start, upDir)) {
        tVector leftHand = upDir % walkDir;

        double refSize = -1e-6 * sqrt(tri->area()),
               foundR2 = -1;
        for (int i=0; tri && i<tri->nVertices(); i++) {
            tVector x0 = tri->vertex(i)->vector(),
                    x1 = tri->vertex((i+1)%tri->nVertices())->vector();

            tVector edgeDir = (x1-x0).normalize();


            bool found;
            tVector interPt = intersectPlaneToAxis(start,leftHand,x0,edgeDir, found);

            X[i] = interPt;
            double r0 = (interPt-x0)*edgeDir,
                   r1 = (interPt-x1)*(edgeDir*(-1)),
                   r2 = ((interPt-start) * walkDir);


            if ( found
                 && r0 >= refSize && r1 >=refSize // found location lies between start and end of edge
                 && r2 > 0 && r2 > foundR2) { // goes into the correct direction and takes the one with the farest progress

                foundR2 = r2;
                tVector track = interPt-start;
                double trackLength = track.length();

                if ( distance > trackLength) {
                    start = interPt;
                    distance -= trackLength;
                    edgeIndex = i;
                } else {
                    track = track.normalize(distance);
                    start = start + track;
                    distance = 0;
                    edgeIndex = -1;
                }
            }
        }

        if (foundR2 > -1) {
            tLayer *l = dynamic_cast<tLayer*>(helper_);
            tPoint *p = l->addPoint(start);
            p->intrface()->setColor(tRGB::MSColor(5));
            return true;

            for (int i=0; i<3;i++){
                helper_->addPoint(X[i])->intrface()->setColor(tRGB(0,200,200));
            }
        }
    }
    return false;
}

/**
 * @brief tTrianglePatch::projectPointToTriangle projects a point p on the given tri using the direction projDir. Return true, if the projected
 * point is located inside the triangle. If it is located inside, the coordiante of the given point p is overwritten by the projected location.
 * @param tri
 * @param p
 * @param projDir
 * @return
 */
bool tTrianglePatch::projectPointToTriangle(tTriangle *tri, tVector &p, const tVector &projDir)
{
    tVector n = tri->normal();

    bool found = false;

    tVector x = intersectTriPlaneToAxis(tri, p, projDir, found);

    if (found) {
        // check if point is located within the triangle
        bool allLeft = true;
        for (int j=0;j<tri->nVertices(); j++) {
            tVector x0 = tri->vertex(j)->vector(),
                    x1 = tri->vertex((j+1)%tri->nVertices())->vector();
            tVector dx = x1-x0;
            tVector left = n % dx;
            double dist = left * (x-x0);
            bool isLeft = dist >= -1e-6*dx.length_squared()/fabs(dist) ? true : false;
            //bool isLeft = dist >= 0 ? true : false;
            if (!isLeft) {
                allLeft = false;
            }
        }
        if (allLeft == true) {
            p = x;
            return true;
        }

    } else {
        // projDir parallel to triangle
    }
    return false;

}

void tTrianglePatch::orientNeighbours(tTriangle *tri, tList<tTriangle *> &processedTris)
{
    tGroup* helper = new tGroup(this); // Add Points, so that they wont be deleted due to missing dependencies
    if (!processedTris.contains(tri)) {
        processedTris.append(tri);
        tList<tTriangle*> neighbrs = neighbours(tri);
        for (int i=0; i<neighbrs.count(); i++) {
            tTriangle* n = neighbrs.at(i);
            if (n && !processedTris.contains(n)) {
                // check the orientation of the neighbours
                tDot *d0 = dynamic_cast<tDot*>(tri->vertex(i)),
                     *d1 = dynamic_cast<tDot*>(tri->vertex((i+1)%tri->nVertices()));
                tVector x0 = d0->vector(),
                        x1 = d1->vector();
                bool orientationMatch = false;
                for (int j=0; j<n->nVertices() && orientationMatch==false;j++){
                    tDot *e0 = dynamic_cast<tDot*>(n->vertex(j)),
                         *e1 = dynamic_cast<tDot*>(n->vertex((j+1)%n->nVertices()));
                    x0 = e0->vector();
                    x1 = e1->vector();
                    if (d0 && d1 && e0 && e1 &&
                        d0 == e1 && d1 == e0) {
                        orientationMatch = true;
                    }
                }
                if (orientationMatch == false) {
                    tList <tElement*> verts = n->vertices();
                    verts.reverse();
                    helper->setElements(verts);
                    n->setVertices(verts);
                    helper->clear();

                }
                orientNeighbours(n, processedTris);
            }
        }
    }
    helper->releaseOwner(this);

}

tVector tTrianglePatch::intersectTriPlaneToAxis(tTriangle *tri, const tVector &p, const tVector &dir, bool &found)
{
    // axis defined by point p and direction dir
    // tri defines the plane to intersect
    tVector x0 = tri->vertex(0)->vector();
    tVector n = tri->normal();

    return intersectPlaneToAxis(x0,n,p,dir, found);

}

tVector tTrianglePatch::intersectPlaneToAxis(const tVector &x, const tVector &n, const tVector &p, const tVector &dir, bool &found)
{
    if (n * dir != 0) {
        double d = ( (x-p) * n ) / (dir * n);
        tVector X = p + dir*d;
        found = true;
        return X;
    } else {
        found = false;
        return tVector(0.,0.,0.);
    }
}

tList<tTriangle*> tTrianglePatch::neighbours(tTriangle *tri)
{
    tList<tTriangle*> neighbrs;
    if (tri){
        tList<tElement*> vertices = tri->vertices();
        for (int i=0; i<vertices.count(); i++){
            tDot *d0 = dynamic_cast<tDot*>(vertices.at(i)),
                 *d1 = dynamic_cast<tDot*>(vertices.at((i+1)%vertices.count()));

            neighbrs.append(neighbour(d0,d1, tri));
        }
    }
    return neighbrs;
}

tTriangle* tTrianglePatch::neighbour(tDot *d0, tDot *d1, tTriangle *notThis)
{

    tTriangle *neighbour = NULL;
    if (d0 && d1) {
        tList<tElement*> D0 = d0->dependents(true),
                         D1 = d1->dependents(true);
        tTriangle *found = NULL;
        for (int j=0; j<D0.count() && found==NULL; j++) {
            tTriangle *tt = dynamic_cast<tTriangle*>(D0.at(j));
            if (tt         // the dependent must be a triangle
                && tt!=notThis // it must not be the considered tri
                && D1.contains(tt) && tris->contains(tt) // only triangles listed in the patch are allowed
               ) {
                found = tt;
            }
        }
        neighbour = found;
    }

    return neighbour;
}

