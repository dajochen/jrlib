#include "views/tModelView.h"

tModelView::tModelView(void *theOwner)
  : tElement(theOwner),
    fmodel(NULL),
    fActiveKey(NULL)
{
}
//------------------------------------------------------------------------------

tModelView::~tModelView()
{
  setModel(NULL);
  removeSelectionSets();
  fActiveKey = NULL;
  //setSelectionSet(NULL);
  //fSelectables->clear();
  //fSelectables->releaseOwner(this);
}
//------------------------------------------------------------------------------
/**
 Set the connectiveModel and connect its changed() signal to the the invalidate slot of the derived class.
 The connection is effective only if "this" is a class which is derived from tModelView and QWidget (e.g.: tTableModelView).
 If the tModelView controlles the group "selectables" of the old model, it will also controll the
 selectables of the new model.
 */
void tModelView::setModel(tModel *theModel)
{
  if (theModel != fmodel){
    if (fmodel){
      fmodel->removeDependent(this);
    }
    fmodel = theModel;
    if (fmodel){
      fmodel->addDependent(this);
    }
    invalidate(this);
  }
}

tSelectionSet *tModelView::selectionSet(void *key)
{
     return selectionSets.value(key,NULL);
}

void tModelView::setSelectionSet(tSelectionSet *newSet, void* key)
{
    if (selectionSets.contains(key) && selectionSets.value(key) == newSet){
        // everythin up to date. Nothing to do.
    } else {
        if (newSet) {
            newSet->addDependent(this);
        }

        tSelectionSet* existingSet = selectionSets.value(key);
        if (existingSet) {
            existingSet->removeDependent(this);
        }

        if (selectionSets.isEmpty()) {
            //The first one is active by default.
            fActiveKey = key;
        }
        selectionSets[key] = newSet;

        invalidate(this);
    }
}

void tModelView::removeSelectionSets()
{
    QList<void*> keys = selectionSets.keys();
    for (int i=0; i< keys.count(); i++) {
        setSelectionSet(NULL, keys[i]);
    }
}

void tModelView::activateSelectionSet(void *key)
{
    fActiveKey = key;
    invalidate(this);
}

tSelectionSet *tModelView::activeSelectionSet()
{
    return selectionSets.value(fActiveKey,NULL);
}

void *tModelView::activeKey()
{
  return fActiveKey;
}
//------------------------------------------------------------------------------

void tModelView::repaintElement(tElement *sender)
{
  invalidate(sender);
}
