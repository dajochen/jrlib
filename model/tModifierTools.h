#ifndef TMODIFIERTOOLS_H
#define TMODIFIERTOOLS_H

#include "tVector.h"
#include "tList.h"
#include "tElement.h"
#include "tPoint.h"
#include "tRelPoint.h"
#include "tLayer.h"

class tModifierTools
{
public:
    tModifierTools();
    static void shiftElements(const tVector &dx, tList<tElement*> elements);
    static void rotateElements(const tVector &origin, const tVector &domega, tList<tElement*> elements);
    static void flipElements(const tVector &origin, const tVector &flipAxis, tList<tElement*> elements);
    static void removeDoublicateElements(tLayer *l);

protected:
    static void addSupportingPoints(tElement *el, tList<tPoint *> &pList, tList<tRelPoint *> &rpList);
};

#endif // TMODIFIERTOOLS_H
