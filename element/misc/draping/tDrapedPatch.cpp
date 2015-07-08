#include "tDrapedPatch.h"

tDrapedPatch::tDrapedPatch(void *theOwner)
    : tPaintableElement(theOwner),
    patch_(NULL),
    initialPoint_(NULL),
    initialPointProjectionDir_(NULL),
    initialFiberDir_(NULL),
    meshSize_(0.),
    isDrapingUptoDate(false)
{
    helper = new tLayer(this);
    initialFiber = NULL;
}

tDrapedPatch::~tDrapedPatch()
{
    setInitialPoint(NULL);
    setInitialFiberDir(NULL);
    setPatch(NULL);

    helper->clear();
    helper->releaseOwner(this);
}

iElement* tDrapedPatch::intrface(void)
{
    if (iface == NULL){
        iface = new iDrapedPatch(this);
    }
    return iface;
}

void tDrapedPatch::refresh(void)
{
    // nothing to do...
}

void tDrapedPatch::setInitialPoint(tElement *el)
{
    setElementLocked;
    if (el != initialPoint_) {
        if (initialPoint_){
            initialPoint_->removeDependent(this);
        }
        initialPoint_ = dynamic_cast<tDot*>(el);
        if (initialPoint_ && !initialPoint_->addDependent(this)){
            initialPoint_ = NULL;
        }
        invalidate(this);
    }
}

void tDrapedPatch::setInitialPointProjectionDir(tElement *el)
{
    setElementLocked;
    if (el != initialPointProjectionDir_) {
        if (initialPointProjectionDir_){
            initialPointProjectionDir_->removeDependent(this);
        }
        initialPointProjectionDir_ = dynamic_cast<tLine*>(el);
        if (initialPointProjectionDir_ && !initialPointProjectionDir_->addDependent(this)){
            initialPointProjectionDir_ = NULL;
        }
        invalidate(this);
    }
}

void tDrapedPatch::setInitialFiberDir(tElement *el)
{
    setElementLocked;
    if (el != initialFiberDir_) {
        if (initialFiberDir_){
            initialFiberDir_->removeDependent(this);
        }
        initialFiberDir_ = dynamic_cast<tLine*>(el);
        if (initialFiberDir_ && !initialFiberDir_->addDependent(this)){
            initialFiberDir_ = NULL;
        }
        invalidate(this);
    }
}

void tDrapedPatch::setPatch(tElement *el)
{
    setElementLocked;
    if (el != patch_) {
        if (patch_){
            patch_->removeDependent(this);
        }
        patch_ = dynamic_cast<tTrianglePatch*>(el);
        if (patch_ && !patch_->addDependent(this)){
            patch_ = NULL;
        }
        invalidate(this);
    }
}


void tDrapedPatch::setMeshSize(double mSize)
{
    if (meshSize_ != mSize){
        meshSize_ = mSize;
        invalidate(this);
    }
}

void tDrapedPatch::runDrapingSimulation()
{
    //if (isDrapingUptoDate == false) {
        if (patch_
            && meshSize_ > 0.
            && initialPoint_
            && initialPointProjectionDir_ && initialPointProjectionDir_->length()
            && initialFiberDir_ && initialFiberDir_->length()) {
            clearDrapData();
            initialFiber = new tInitialFiber(patch_,
                                             initialPoint_,
                                             initialFiberDir_->end()->vector()-initialFiberDir_->start()->vector(),
                                             initialPointProjectionDir_->end()->vector()-initialPointProjectionDir_->start()->vector(),
                                             meshSize_);

        }
        isDrapingUptoDate = true;
        //}
}

void tDrapedPatch::paintGL(const tVector &EyePoint, const tVector &ObjectPoint, const tRGB &rgb, const tVector &defaultN, const bool& isSelected)
{
    if (initialFiber) {
        initialFiber->fiber()->paintGL(EyePoint,ObjectPoint,rgb, defaultN, isSelected);
    }
}

void tDrapedPatch::clearDrapData()
{
    if (initialFiber){
        delete initialFiber;
    }
}
