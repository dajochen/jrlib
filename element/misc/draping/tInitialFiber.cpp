#include "tInitialFiber.h"

tInitialFiber::tInitialFiber(tTrianglePatch *patch, tDot* refPoint, const tVector fiberDir, const tVector projDir, const double meshSize)
    : tFiber()
{
    tDot *d = NULL;
    tVector walkDir = fiberDir;
    tVector upDir = projDir*(-1.);
    tPatchLocation knot;
    double step = meshSize;

    int i = 0; // Fiber ID
    int j = 0;
    knot.x = refPoint->vector();
    knot.tri = NULL;
    knot = patch->projectPointToPatch(knot.x,projDir);
    // walk into direction of fiber
    d = new tPoint(NULL, knot.x);
    appendNode(d);
    mesh[NodeLocation(i,j++)] = d;
    do {
        step = meshSize;
        knot = patch->walkOnPatch(knot, walkDir, upDir, step, true);
        d = new tPoint(NULL, knot.x);
        appendNode(d);
        mesh[NodeLocation(i,j++)] = d;
    } while(step <= 0);

    // counter direction of fiber
    j = -1;
    walkDir = fiberDir*(-1.);
    upDir = projDir*(-1.);
    knot.x = refPoint->vector();
    knot.tri = NULL;
    step = meshSize;

    do {
        step = meshSize;
        knot = patch->walkOnPatch(knot, walkDir, upDir, step, true);
        d = new tPoint(NULL, knot.x);
        prependNode(d);
        mesh[NodeLocation(i,j--)] = d;
    } while (step <= 0);

    addParallelFiber(0,1);

}

void tInitialFiber::addParallelFiber(int i, int di)
{
    QMap<int, tDot*> jFiber;

    QHashIterator<NodeLocation, tDot *> iter(mesh);
    while (iter.hasNext()) {
        iter.next();
        if (iter.key().i == i) {
            jFiber[iter.key().j] = iter.value();
        }
    }
}



tParallelFiber::tParallelFiber(tFiber *referenceFiber, bool rightHand)
{

}
