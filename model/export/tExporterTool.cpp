#include "tExporterTool.h"


#include "model/tPatExport.h"
#include "model/tPclExport.h"
#include "model/tAbaqusMesh.h"
#include "model/tStlExport.h"
#include "model/tDxfExport2.h"
#include "model/tVtkExport.h"
#include "model/tFreeShipExport.h"



#include <QFileDialog>
#include <QMessageBox>


tExporterTool::tExporterTool(tModel *m, tSelectionSet *s)
    : model(m),
      selectionSet(s)
{
    if (model)
        model->addOwner(this);
    if (selectionSet){
        selectionSet->addOwner(this);
    }
}

tExporterTool::~tExporterTool()
{
    if (model)
        model->releaseOwner(this);
    if (selectionSet){
        selectionSet->releaseOwner(this);
    }
}

QString tExporterTool::selectExportFile(QWidget *parent)
{
    if (model) {
    QStringList extensions;
#ifdef BUILD_WITH_DXFLIB
    extensions.append("DXF (*.dxf)");
#endif
    extensions.append("ISThydro (*.pcl)");
    extensions.append("Visualization Toolkit (VTK) (*.vts)");
    extensions.append("StereoLithography (*.stl)");
    extensions.append("MultiSurf Patches (*.pat)");
    extensions.append("Abqus Input File (*.inp)");
    extensions.append("Free Ship Input File (*.freeShipInput)");
    extensions.append("All Files (*.*)");

    QString filter = "*.*";
#ifdef BUILD_WITH_DXFLIB
    filter = "*.dxf";
#endif

    return QFileDialog::getSaveFileName(NULL,"Geometriedaten exportieren",
                                              "\\",extensions.join(";;"),&filter);
    } else {
      QMessageBox::information(parent, "Export", "No model active. Nothing to be done.", QMessageBox::Ok);
      return "";
    }

}

bool tExporterTool::exportToFile(QString fileName)
{
    if (!fileName.isNull() && model) {
      if (fileName.endsWith(".pat",Qt::CaseInsensitive)) {
        tPatExport pat;
        pat.exportToFile(fileName, model);
        return true;
      } else if (fileName.endsWith(".pcl",Qt::CaseInsensitive)) {
        tPclExport pcl;
        pcl.exportToFile(fileName, model);
        return true;
      } else if (fileName.endsWith(".inp",Qt::CaseInsensitive)) {
        tAbaqusMesh abq;
        abq.exportToFile(fileName, model);
        return true;
      } else if (fileName.endsWith(".stl",Qt::CaseInsensitive)) {
        tStlExport stl;
        stl.exportToFile(fileName, model);
        return true;
#ifdef BUILD_WITH_VTK
      } else if (fileName.endsWith(".vts",Qt::CaseInsensitive)) {
        tVtkExport(fileName, model);
        return true;
#endif
#ifdef BUILD_WITH_DXFLIB
      } else if (fileName.endsWith(".dxf",Qt::CaseInsensitive)) {
          //tGLModelView *glView = NULL;
          //tSelectionSet *selSet = NULL;
          tBasicPlane* plane = NULL;

          //QMdiSubWindow *window = Workspace->currentSubWindow();
          //if (window) glView = dynamic_cast<tGLModelView*>(window->widget());
          //if (glView) selSet = glView->selectionSet(this);

          if (selectionSet && selectionSet->nElements()>0) {
              plane = dynamic_cast<tBasicPlane*>(selectionSet->elements(iPlane::theType()).at(0));
          }

          tDxfExport2 dxf(fileName, model, plane);
/*        dxf.addElements(M->elements());
          dxf.exportToFile(fileName);*/
          return true;
#endif
      } else if (fileName.endsWith(".freeShipInput",Qt::CaseInsensitive)) {
        tFreeShipExport fs;
        fs.exportToFile(fileName, model);
        return true;
      }
      return false;
    } else {
      return false;
    }

}
