#include "tSelectionSet.h"

tSelectionSet::tSelectionSet(void *theOwner, bool allowDublicates, int maxSelectableItems)
  : tGroup(theOwner)
{
    fAllowDublicates = allowDublicates;
    fMaxSelectableItems = maxSelectableItems;
}

tSelectionSet::~tSelectionSet()
{
}

void tSelectionSet::addDependent(tElement *el)
{
    tGroup::addDependent(el);
}

tElement *tSelectionSet::append(tElement *el)
{
    while (member.count() > fMaxSelectableItems+1 && fMaxSelectableItems != -1) {
        removeElement(0);
    }
    if (fAllowDublicates || !contains(el)){
        return tGroup::append(el);
    } else {
        return NULL;
    }
}

tElement *tSelectionSet::prepend(tElement *el)
{
    while (nElements() > fMaxSelectableItems+1 && fMaxSelectableItems != -1) {
        removeElement(nElements()-1);
    }
    if (fAllowDublicates || !contains(el)){
        return tGroup::prepend(el);
    } else {
        return NULL;
    }
}

void tSelectionSet::setElements(const tList<tElement *> &l)
{
    tList<tElement*> filtered;

    for (int i=0;
         i < l.count()
         &&  ( filtered.count() < fMaxSelectableItems
               || fMaxSelectableItems<0
             );
         i++){
        tElement *el = l.at(i);
        if (fAllowDublicates || !filtered.contains(el)) {
            filtered.append(el);
        }
    }

    tGroup::setElements(filtered);

}





