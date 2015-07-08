#include "tStlImport.h"

#include <QtCore>
#include <tList.h>
#include <tVector.h>
#include <tVectorStringConverter.h>
#include "tTrianglePatch.h"
#include "element/misc/tTriangle.h"

#include <iostream>
#include <string>
using namespace std;

tPoint* tStlImport::getNextPoint(const tVector &x, tList<tPoint*>& pts, double tolerance)
{
    for (int i=0; i<pts.count(); i++) {
        if ((x-pts.at(i)->vector()).length_squared() < tolerance) {
            return pts.at(i);
        }
    }
    tPoint *p =  new tPoint(NULL, x);
    pts.append(p);
    return p;
}

tStlImport::tStlImport(tLayer *l, QString stlFile)
{

    QFile file(stlFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    else {
        tList<tPoint*> pts;

        QTextStream stl(&file);

        tTrianglePatch *solid = NULL;
        int vCounter = 0;
        tVector vs[3];

        while (!stl.atEnd()) {
            QString line = stl.readLine();


            QRegExp solidTest("^\\s*(?!end)solid\\s+(.*)$");
            QRegExp loopBegin("^.*outer\\s+loop.*$");
            QRegExp vertexTest("^.*vertex(.*)$");

            if (solidTest.indexIn(line.toLower().simplified()) > -1) {
                QString caption = solidTest.capturedTexts().last();
                if (caption.isEmpty()) {caption = "noName";}
                solid = dynamic_cast<tTrianglePatch*>(l->addElement(iTrianglePatch::theType(),caption));//addLayer(caption);
                //cout << "parsing solid" << endl;
            } else if (loopBegin.indexIn(line.toLower().simplified()) > -1 ) {
                //cout << "new face" << endl;
                vCounter = 0;
            } else if (vertexTest.indexIn(line.toLower().simplified()) > -1) {
                vCounter++;
                QString loc = vertexTest.capturedTexts().last();
                vs[0] = vs[1];
                vs[1] = vs[2];
                vs[2] = tVectorStringConverter::toVector(loc);
                if (solid && vCounter == 3){
                    tList<tDot*> dotList;
                    double tol01 = (vs[0]-vs[1]).length_squared(),
                           tol12 = (vs[1]-vs[2]).length_squared(),
                           tol20 = (vs[2]-vs[0]).length_squared();
                    dotList.append( getNextPoint(vs[0], pts, min(tol20, tol01)*0.0001) );//new tPoint(NULL,vs[0]) );
                    dotList.append( getNextPoint(vs[1], pts, min(tol01, tol12)*0.0001) );//new tPoint(NULL,vs[1]) );
                    dotList.append( getNextPoint(vs[2], pts, min(tol20, tol12)*0.0001) );//new tPoint(NULL,vs[2]) );
                    tTriangle* t = new tTriangle(NULL); //dynamic_cast<tTriangle*>( solid->addElement(iTriangle::theType()) );
                    if (t){
                        t->setVertices(dotList);
                    }
                    solid->addTriangle(t);
                }
            }
        }
    }
}
