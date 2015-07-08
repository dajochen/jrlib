#ifndef TSELECTIONSET_H
#define TSELECTIONSET_H


#include "element/tGroup.h"



class tSelectionSet : public tGroup
{


public:
    tSelectionSet(void *theOwner, bool allowDublicates=false, int maxSelectableItems=-1);
    virtual ~tSelectionSet();
    virtual void addDependent(tElement *el);

    virtual tElement* append(tElement* el);
    virtual tElement* prepend(tElement* el);
    virtual void setElements(const tList<tElement *> &l);

    bool allowDublicates(void) {return fAllowDublicates;}
    int maxSelectableItems(void) {return fMaxSelectableItems;}

private:
    bool fAllowDublicates;   // allows to add an element several times
    int fMaxSelectableItems; // restricts the number of selected elements
};

#endif // TSELECTIONSET_H
