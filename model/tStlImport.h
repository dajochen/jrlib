#ifndef TSTLIMPORT_H
#define TSTLIMPORT_H

#include <QString>
#include "tLayer.h"

class tStlImport
{
private:
    tPoint* getNextPoint (const tVector& x, tList<tPoint*>& pts, double tolarance);
public:
    tStlImport(tLayer *l, QString stlFile);
};

#endif // TSTLIMPORT_H
