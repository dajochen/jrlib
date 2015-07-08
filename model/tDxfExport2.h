#ifndef TDXFEXPORT2_H
#define TDXFEXPORT2_H

#ifdef BUILD_WITH_DXFLIB
#include "model/tModel.h"
#include "element/plane/tBasicPlane.h"

#include <dl_dxf.h>

/**
* Uses dxflib for exporting jr-Entities to dxf. For information to dxflib see:
* http://www.ribbonsoft.com/doc/dxflib/2.5/reference/index.html
*/
class tDxfExport2
{


public:
    tDxfExport2(QString fileName, tModel *m, tBasicPlane *pl=NULL);
    ~tDxfExport2();

protected:
    tBasicPlane *plane;
    DL_Dxf dxf;
    DL_WriterA* dw;

    void exportElement(tElement *el);


    void writeHeader(void);
    void writeDefaultLineTypes(void);
    void writeDefaultTables(void);
    void writeDimentsions(void);
    void writeDefaultBlocks(void);

    // jr-related functions
    void writeEntities(tModel* m);
    void writeLayers(tModel *m);
    void writeLines(tModel *m);
    void writePolylines(tModel *m);

    //helper functions:
    tList<tLayer*> layers(tModel *m);


    void func(QString fName, tModel *m);
};

#endif // BUILD_WITH_DXFLIB
#endif // TDXFEXPORT2_H
