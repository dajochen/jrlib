#ifndef TVTKEXPORT_H
#define TVTKEXPORT_H

#include "tModel.h"

#define vtkRenderingCore_AUTOINIT 4(vtkInteractionStyle,vtkRenderingFreeType,vtkRenderingFreeTypeOpenGL,vtkRenderingOpenGL)
#define vtkRenderingVolume_AUTOINIT 1(vtkRenderingVolumeOpenGL)

#include <vtkStructuredGrid.h>
#include <vtkXMLStructuredGridWriter.h>
#include <vtkSmartPointer.h>
#include <vtkMultiBlockDataSet.h>

class tVtkExport
{
public:
    tVtkExport(QString fileName, tModel *m);
    ~tVtkExport();
private:
    void exportElement(tElement *el);
    void exportGroup(tGroup *g);
    void exportSurface(tSurface *s);
    bool test(QStringList argv, int argc);
    //vtkSmartPointer<vtkXMLStructuredGridWriter> writer;
    QString fName;
    vtkSmartPointer<vtkMultiBlockDataSet> data;
};

#endif // TVTKEXPORT_H
