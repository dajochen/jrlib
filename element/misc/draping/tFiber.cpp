#include "tFiber.h"

tFiber::tFiber() {
    fiber_= new tPolygonCurve(this);
    fiber_->setIsLoop(false);
    fiber_->setTResolution(60);
    startNodeID = 0.;

}

tFiber::~tFiber()
{
    fiber_->removeAllVertices();
    fiber_->releaseOwner(this);
}


void tFiber::appendNode(tDot *d)
{
    fiber_->addVertex(d);
}

void tFiber::prependNode(tDot *d)
{
    fiber_->addVertex(0,d);
    startNodeID++;
}

tDot* tFiber::fiberNode(int id) {
    if ((id-startNodeID)>=fiber_->nVertices() || (id-startNodeID)<0){
        return NULL;
    } else {
        return fiber_->vertex(id-startNodeID);
    }
}
