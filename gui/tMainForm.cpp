#include "tMainForm.h"

#include <QToolBar>
#include <QMdiSubWindow>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <string.h>

#include "model/tModelIO.h"

#include "element/curve/tDistortedSpline.h"
#include "model/DXFReader.h"
#include "model/tPatExport.h"
#include "model/tPclExport.h"
#include "model/tAbaqusMesh.h"
#include "model/tStlExport.h"
#include "model/tDxfExport2.h"
#include "model/tVtkExport.h"
#include "model/tFreeShipExport.h"

//#include "model/dxfTools.h"

#include "views/jrgui.h"
#include "views/tGLModelView.h"
#include "views/tCopyPasteOptionsDlg.h"

#include "tProgrammversionDlg.h"

#include "classes/utils.h"

#include "model/tStlImport.h"


tMainForm::tMainForm(QMainWindow *parent): QMainWindow(parent)
{
  QStringList args;
  args = QApplication::arguments();

  if (args.contains("-h")){
    QMessageBox ibox(QMessageBox::Information, "info", "Options are:\n      -nogui\n      -quit\n      -h\n      <filename>\n      <filename>\n      <filename>\n\ne.g.: cad -nogui test.jr -quit", QMessageBox::Ok);
    ibox.exec();
    exit(0);
  } else if (args.contains("-nogui")){
    args.removeAll("-nogui");
    tModel *model;
    tModelIO *IO;
    model = new tModel(this);
    IO = new tModelIO(model);
    for (int i=1;i<args.count();i++){
      if (args.at(i)=="-quit"){
        exit(0);
      } else {
        IO->fromXmlFile(args.at(i));
      }
    }
    delete IO;
    model->releaseOwner(this);
    exit(0);
  } else {
    setupUi(this);

    Workspace = new QMdiArea(this);
    setCentralWidget (Workspace);
    connect(Workspace, SIGNAL(subWindowActivated(QMdiSubWindow*)),this,SLOT(windowActivated(QMdiSubWindow*)));
    ToolBar1 = new QToolBar(this);
    ToolBar1->setAllowedAreas(Qt::TopToolBarArea);

    aOrthogonal = ToolBar1->addAction("Parallel",this,SLOT(actionOrthogonal_toggeled(bool)));
    aOrthogonal->setCheckable(true);
    aPerspective = ToolBar1->addAction("Fluchtpunkt",this,SLOT(actionPerspective_toggeled(bool)));
    aPerspective->setCheckable(true);
    ToolBar1->addSeparator();
    aFlightMode = ToolBar1->addAction("Betrachter",this,SLOT(actionFlightMode_toggeled(bool)));
    aFlightMode->setCheckable(true);
    aObjectMode = ToolBar1->addAction("Objekt",this,SLOT(actionObjectMode_toggeled(bool)));
    aObjectMode->setCheckable(true);
    ToolBar1->addSeparator();
    comboBox1 = new QComboBox;
    comboBox1->addItem("free");
    comboBox1->addItem("X-Axis");
    comboBox1->addItem("Y-Axis");
    comboBox1->addItem("Z-Axis");
    aVertical = ToolBar1->addWidget(comboBox1);
    addToolBar (ToolBar1);

    elementView = new tTableModelView(this, structureWidgetContents);
    elementView->intrface()->setName("global Model View (tMainForm)");

    propertiesView = new tPropertiesView(this, selectionWidgetContents);
    selectionSummary = new tSelectionSummary(this, selectionSummaryContents);

    propertyEditor = new tPropertyEditor(this, propertyEditorWidget);
    propertyEditor->setPropertiesView(propertiesView);

    elementCreator = new tElementCreator(this, createElementWidgetContents);


    copyPasteSelection = new tGroup(this);

    updateSettings();

    for (int i=1;i<args.count();i++){
      if (args.at(i)=="-quit"){
        exit(0);
      } else {
        openFile(args.at(i));
      }
    }
  }
}
//-----------------------------------------------------------------------------

tMainForm::~tMainForm(void){
    elementCreator->releaseOwner(this);
    selectionSummary->releaseOwner(this);
    propertyEditor->releaseOwner(this);
    propertiesView->releaseOwner(this);
    elementView->releaseOwner(this);


  copyPasteSelection->releaseOwner(this);

  delete comboBox1;
  delete ToolBar1;
  delete Workspace;
}
//-----------------------------------------------------------------------------

void tMainForm::updateSettings()
{
  QDomDocument doc("jrCADSettings");
  QDomElement root,el,el2;
  QAction *act;
  QFile file(QDir::home().path()+"/.jrCAD");

  if (file.open(QIODevice::ReadOnly)){
    doc.setContent(&file);
    file.close();
  }
  root = doc.documentElement();
  if (root.isNull()){
    root = doc.createElement("jrCADSettings");
    doc.appendChild(root);
  }
  el = root.firstChildElement("version_0");
  if (el.isNull()){
    el = doc.createElement("version_0");
    root.appendChild(el);
  }
  root = el;

//Die zuletzt goeffneten Dateien
  el = root.firstChildElement("recentlyOpenedFiles");
  if (el.isNull()){
    el = doc.createElement("recentlyOpenedFiles");
    root.appendChild(el);
  }

  if (recentlyOpenedFiles.count() == 0){
    // Werte aus der conifg-Datei lesen
    el2 = el.firstChildElement("string");
    while (!el2.isNull()){
      recentlyOpenedFiles.append(el2.attribute("value",""));
      el2 = el2.nextSiblingElement("string");
    }
  } else {
    // Update der xml-Datei durchf���hren.
    do {
      el2 = el.firstChildElement("string");
      el.removeChild(el2);
    } while (!el2.isNull());
    for (int i=0;i<recentlyOpenedFiles.count() && i<10 ;i++){
      el2 = doc.createElement("string");
      el2.setAttribute("value",recentlyOpenedFiles.at(i));
      el.appendChild(el2);
    }
  }

  // Menu aktualisieren.
  menuRecent_Files->clear();
  rofActionList.clear();
  for (int i=0;i<recentlyOpenedFiles.count() && i<10 ;i++){
    act = new QAction(menuRecent_Files);
    rofActionList.append(act);
    act->setObjectName(QString::fromUtf8("actionRECENT_OPEN"));
    act->setText(recentlyOpenedFiles.at(i));
    menuRecent_Files->addAction(act);
  }
// Die zuletzt gespeicherte Datei
  el = root.firstChildElement("lastSavedFile");
  if (el.isNull()){
    el = doc.createElement("lastSavedFile");
    root.appendChild(el);
  }
  if (lastSavedFile.isEmpty()){
    lastSavedFile = el.attribute("value","");
  } else {
    el.setAttribute("value",lastSavedFile);
  }

  if (file.open(QIODevice::WriteOnly)){
    QTextStream out(&file);
    out << doc.toString(2);
    file.close();
  }
}
//-----------------------------------------------------------------------------

QAction* tMainForm::pluginAction(QString caption){
  QAction* action = new QAction(caption,this);
  menuModell->insertAction(pluginPlaceholder, action);
  return action;
}
//-----------------------------------------------------------------------------

void tMainForm::viewDestroyed (QObject *view)
{
  tModelView *v = static_cast<tGLModelView*>(view);
  if (v){
      tModel *m = modelViews[v];
      if (m){
        if (elementCreator) {
            elementCreator->setModel(NULL);
            elementCreator->setSelectionSet(NULL, this);
        }
        if (selectionSummary) {
            selectionSummary->setModel(NULL);
            selectionSummary->setSelectionSet(NULL, this);
        }
        if (elementView) {
            elementView->setModel(NULL);
            elementView->setSelectionSet(NULL, this);
        }
        if (propertyEditor) {
            propertyEditor->removeModelViews();
        }
        if (propertiesView) {
            propertiesView->setModel(NULL);
            propertiesView->setSelectionSet(NULL, this);
        }

        m->releaseOwner(this);

        modelViews.remove(v);

      }
  }
}
//-----------------------------------------------------------------------------

void tMainForm::windowActivated(QMdiSubWindow *subWidget)
{
  if (subWidget){
    QWidget* widget = subWidget->widget();
    tGLModelView *glv = dynamic_cast<tGLModelView*>(widget);

    if (glv) {
      if (propertiesView) {
          propertiesView->setModel(glv->model());
          propertiesView->setSelectionSet(glv->selectionSet(this), this );
      }
      if (propertyEditor) {
          propertyEditor->removeModelViews();
          propertyEditor->addModelView(glv);
      }
      if (elementView) {
          elementView->setModel(glv->model());
          elementView->setSelectionSet(glv->selectionSet(this), this);
      }
      if (selectionSummary) {
          selectionSummary->setModel(glv->model());
          selectionSummary->setSelectionSet(glv->selectionSet(this), this);
      }
      if (elementCreator) {
          elementCreator->setModel(glv->model());
          elementCreator->setSelectionSet(glv->selectionSet(this), this);
      }


/*      if (glv->projection() == Ortho)
        aOrthogonal->trigger();
      else
        aPerspective->trigger();
      if (glv->movingMode() == FlightMode)
        aFlightMode->trigger();
      else
        aObjectMode->trigger();
*/
    }
  }
}
//-----------------------------------------------------------------------------

void tMainForm::on_actionExportieren_triggered()
{
	QString fname;
	tModel *M;

  M = getActiveModel();
  if (M){
    QStringList extensions;
#ifdef BUILD_WITH_DXFLIB
    extensions.append("DXF (*.dxf)");
#endif
    extensions.append("ISThydro (*.pcl)");
    extensions.append("Visualization Toolkit (VTK) (*.vts)");
    extensions.append("StereoLithography (*.stl)");
    extensions.append("Abqus Input File (*.inp)");
    extensions.append("MultiSurf (*.pat)");
    extensions.append("Free Ship Input File (*.freeShipInput)");
    extensions.append("All Files (*.*)");

    QString filter = "*.*";
#ifdef BUILD_WITH_DXFLIB
    filter = "*.dxf";
#endif

    fname = QFileDialog::getSaveFileName(this,"Geometriedaten exportieren",
                                              "\\",extensions.join(";;"),&filter);

    if (!fname.isNull()) {
      if (fname.endsWith(".pat",Qt::CaseInsensitive)) {
        tPatExport pat;
        pat.exportToFile(fname,M);
      } else if (fname.endsWith(".pcl",Qt::CaseInsensitive)) {
        tPclExport pcl;
        pcl.exportToFile(fname,M);
      } else if (fname.endsWith(".inp",Qt::CaseInsensitive)) {
        tAbaqusMesh abq;
        abq.exportToFile(fname,M);
      } else if (fname.endsWith(".stl",Qt::CaseInsensitive)) {
        tStlExport stl;
        stl.exportToFile(fname,M);
#ifdef BUILD_WITH_VTK
      } else if (fname.endsWith(".vts",Qt::CaseInsensitive)) {
        tVtkExport(fname,M);
#endif
#ifdef BUILD_WITH_DXFLIB
      } else if (fname.endsWith(".dxf",Qt::CaseInsensitive)) {
          tGLModelView *glView = NULL;
          tSelectionSet *selSet = NULL;
          tBasicPlane* plane = NULL;
          QMdiSubWindow *window = Workspace->currentSubWindow();
          if (window) glView = dynamic_cast<tGLModelView*>(window->widget());
          if (glView) selSet = glView->selectionSet(this);
          if (selSet && selSet->nElements()>0) {
              plane = dynamic_cast<tBasicPlane*>(selSet->element(0));
          }

          tDxfExport2 dxf(fname, M, plane);
/*        dxf.addElements(M->elements());
          dxf.exportToFile(fname);*/
#endif
      } else if (fname.endsWith(".freeShipInput",Qt::CaseInsensitive)) {
        tFreeShipExport fs;
        fs.exportToFile(fname, M);
      }
    }
  } else {
    QMessageBox::information(this, "Export", "No model active. Nothing to be done.", QMessageBox::Ok);
  }
}
//-----------------------------------------------------------------------------
void tMainForm::on_actionKopieren_triggered()
{
    /*
  tModel *M;

  copyPasteSelection->clear();
  M = getActiveModel();
  M->lockElement();
  if (M){
    tList<tElement*> sel = M->selection();
    for (int i=0;i<sel.count(); i++){
      copyPasteSelection->append(sel.at(i));
    }
  }
  M->unlockElement();
*/
}
//-----------------------------------------------------------------------------

void tMainForm::on_actionEinf_gen_triggered()
{
  tModel *M;

  M = getActiveModel();
  M->lockElement();
  if (M){
    tList<tCopyPasteOption> options;

    tCopyPasteOptionsDlg *Dlg = new tCopyPasteOptionsDlg(this);
    Dlg->exec();
    if (Dlg->result() == QDialog::Accepted){

      if (Dlg->convertDotsToRelPoint->checkState()== Qt::Checked){
        options.append(cpoDotsToRelPoints);
      }

      for (int i=0;i<copyPasteSelection->nElements(); i++){
  //      char dbg[500];
  //      strcpy(dbg,qPrintable(copyPasteSelection->element(i)->intrface()->name()));
        M->currentLayer()->addDeepCopy(copyPasteSelection->element(i), options);
      }
    }
    delete Dlg;
  }
  M->unlockElement();
}
//-----------------------------------------------------------------------------

bool tMainForm::importToModel(QString fileName, tModel *m, bool createDefaultLayerOnDemand)
{
  if (m){
    bool opened = false;

    if (fileName.toLower().endsWith(".jr",Qt::CaseInsensitive)) {
      tModelIO *IO = new tModelIO(m);
      opened = IO->fromXmlFile(fileName);
      delete IO;
    } if (fileName.toLower().endsWith(".msf",Qt::CaseInsensitive) || fileName.toLower().endsWith(".ms2",Qt::CaseInsensitive)) {
/*      if (createDefaultLayerOnDemand){
        m->setCurrentLayer(m->addLayer("Default Layer"));
      }
      m->importMultiSurf(fileName);
      opened = true;*/
#ifdef BUILD_WITH_DXFLIB
    } else if (fileName.endsWith(".dxf",Qt::CaseInsensitive)) {
      if (createDefaultLayerOnDemand){
        m->setCurrentLayer(m->addLayer("Default Layer"));
      }
      DXFReader(m, fileName);
      opened = true;
#endif
    } else if (fileName.endsWith(".stl",Qt::CaseInsensitive)) {
      if (createDefaultLayerOnDemand){
        m->setCurrentLayer(m->addLayer("Default Layer"));
      }
      tStlImport(m->currentLayer(), fileName);
      opened = true;
    } else if (fileName.endsWith(".igs",Qt::CaseInsensitive) || fileName.endsWith(".iges",Qt::CaseInsensitive)) {
      QMessageBox::information(NULL,"Modell laden","Unknown file format.");
      return false;
    }


    if (opened){
      m->setName(m->name() + fileName);
      if (recentlyOpenedFiles.contains(fileName)){
        recentlyOpenedFiles.removeAll(fileName);
      } else if (recentlyOpenedFiles.count()>10){
        recentlyOpenedFiles.removeLast();
      }
      recentlyOpenedFiles.prepend(fileName);
      updateSettings();
    }
    return opened;
  } else {
    return false;
  }
}

//-----------------------------------------------------------------------------
void tMainForm::openFile(const QString& fileName)
{
  tModel *model;

  model = createEmptyModel();
  importToModel(fileName, model, true);

}
//-----------------------------------------------------------------------------

void tMainForm::saveFile(const QString& fileName)
{
  bool saved = false;
  if (fileName.endsWith(".jr",Qt::CaseInsensitive)) {
    tModel *model;
    tModelIO *IO;
    model = getActiveModel();
    if (model){
      IO = new tModelIO(model);
      IO->toXmlFile(fileName);
      delete IO;
      saved = true;
    }
  }
  if (saved){
    lastSavedFile = fileName;
    updateSettings();
  }

}
//-----------------------------------------------------------------------------
/*
void tMainForm::keyReleaseEvent (QKeyEvent *event)
{
  tModel* model = getActiveModel();
  if (model){
    if (event->key()==Qt::Key_F4){
      model->doublicateFirstSelectedElement();
    }
  }
}*/

//-----------------------------------------------------------------------------

void tMainForm::on_actionImportieren_triggered()
{
  QString fname;
  tModel *M;

  QString defaultFile;
  if (recentlyOpenedFiles.count()==0){
    defaultFile = QDir::homePath();
  } else {
    defaultFile = recentlyOpenedFiles.first();
  }

  M = getActiveModel();
  if (M) {

    ExtentionList extensions;

    extensions.append(extDescriptor("*.jr", "jrCAD xml-File"));
    extensions.append(extDescriptor("*.msf *.ms2", "MultiSurf"));
#ifdef BUILD_WITH_DXFLIB
    extensions.append(extDescriptor("*.dxf", "Draw Exchange Format"));
#endif
    extensions.append(extDescriptor("*.stl", "StereoLithogrphy"));
    QString ext = extensions.toString();

    fname = QFileDialog::getOpenFileName(this,
                                         "Geometriemodell laden",
                                         defaultFile,
                                         ext);

    importToModel(fname, M);
  }
}

//-----------------------------------------------------------------------------

void tMainForm::on_actionLaden_triggered()
{
  QString defaultFile;
  if (recentlyOpenedFiles.count()==0){
    defaultFile = QDir::homePath();
  } else {
    defaultFile = recentlyOpenedFiles.first();
  }

  ExtentionList extensions;

  extensions.append(extDescriptor("*.jr", "jrCAD xml-File"));
  extensions.append(extDescriptor("*.msf *.ms2", "MultiSurf"));
#ifdef BUILD_WITH_DXFLIB
  extensions.append(extDescriptor("*.dxf", "Draw Exchange Format"));
#endif
  extensions.append(extDescriptor("*.stl", "StereoLithogrphy"));
  QString ext = extensions.toString();

  //"jrCAD xml-File (*.jr);;MultiSurf (*.msf *.ms2);;Initial Graphics Exchange Standard (*.iges *.igs);;Draw Exchange Format (*.dxf)")
  openFile(QFileDialog::getOpenFileName(this,
                                        "Geometriemodell laden",
                                        defaultFile,
                                        ext));
}
//-----------------------------------------------------------------------------

void tMainForm::on_actionSpeichern_triggered()
{
  QString defaultFile;
  if (lastSavedFile==""){
    defaultFile = QDir::homePath();
  } else {
    defaultFile = lastSavedFile;
  }
  saveFile(QFileDialog::getSaveFileName(this,
                                        "Geometriemodell speichern",
                                        defaultFile,
                                        "jrCAD xml-File (*.jr)"));
}
//-----------------------------------------------------------------------------
/*
void tMainForm::on_actionOriginal_Zuschnitte_Speichern_triggered()
{
 exportCuttings("Initial Cutting");
}
//-----------------------------------------------------------------------------

void tMainForm::on_actionVerzerrte_Zuschnitte_Speichern_triggered()
{
  exportCuttings("Arranged Cutting");
}*/
//-----------------------------------------------------------------------------
/*
void tMainForm::exportCuttings(QString type)
{
  QString defaultFile;
  if (lastSavedFile==""){
    defaultFile = QDir::homePath();
  } else {
    defaultFile = lastSavedFile;
  }
  QString baseName = QFileDialog::getSaveFileName(this,
                                          "Zuschitte speichern, Basisdateinamen wählen",
                                          defaultFile,
                                          "DXF-File (*.dxf)");

  QString log;

  tModel *model = getActiveModel();
  if (model){
    //????tGroup* group = new tGroup(this);
    //group->setElements( model->selection() );

    tLayer* top = dynamic_cast<tLayer*>(model->elementByName("PropGeo - Cutting File", iLayer::theType()));
    if (top){
      tList<tElement*> compounds = top->elements(iLayer::theType());
      for (int i=0;i<compounds.count();i++){
        tLayer* comp = dynamic_cast<tLayer*>(compounds.at(i));
        tLayer* cutting = dynamic_cast<tLayer*>(comp->elementByName(type,iLayer::theType()));
        if (cutting){
          log += "Processing Cutting: " + type + " to file: " + baseName + "...dxf\n";

          tList<tElement*> fabrics = cutting->elements(iLayer::theType());

          for (int j=0; j<fabrics.count(); j++){
            //model->setSelection(fabrics.at(j));
            tLayer* fabric = dynamic_cast<tLayer*>(fabrics.at(j));
            QString fileName = baseName + "_" + comp->intrface()->name() + "_" + fabric->intrface()->name() + ".dxf";
            log += "writing: " + fileName + "\n";

            tDxfExport dxf;

            dxf.defaultLayer = "CUT";
            dxf.addElement(fabric);

            dxf.defaultLayer = "TEXT";
            tList<tElement*> offsets = fabric->elements(iLayer::theType());
            for (int k=0; k<offsets.count(); k++ ){

              tLayer *l = dynamic_cast<tLayer*>(offsets.at(k));
              if (l){
                dxf.addText( l->intrface()->name(),
                             (l->xMin()+l->xMax())*0.5 );

                tLayer *contur = dynamic_cast<tLayer*>(l->elementByName("Contur", iLayer::theType()));
                if (contur){
                  tList<tElement*> list = contur->elements(iCurve::theType());
                  tCurve *c = dynamic_cast<tCurve*>(list.at(0));
                  if (c){
                    int tRes = c->tResolution();
                    double area = 0.;
                    tVector x0, x;
                    x0 = c->vectorAt(0.);
                    for (int i=1; i<=tRes; i++){
                      double t = double(i)/double(tRes);
                      x = c->vectorAt(t);
                      area += 0.5*( ( x.x+x0.x ) * (x.y-x0.y ) ) / 1.0e6;
                      x0 = x;
                    }
                    log += "Layer: " + l->intrface()->name() + ": Area: " + QString::number(area)+ "\n";
                  }
                }
              }

            }

            dxfPoint xMin = dxf.content().getBoundingBox().Min();
            xMin.x *= -1;
            xMin.y *= -1;
            dxf.content().shift(xMin.x, xMin.y);

            dxf.exportToFile(fileName);
            {
              QString defaultFile;
              if (lastSavedFile==""){
                defaultFile = QDir::homePath();
              } else {
                defaultFile = lastSavedFile;
              }
              QString baseName = QFileDialog::getSaveFileName(this,
                                                      "Zuschitte speichern, Basisdateinamen wählen",
                                                      defaultFile,
                                                      "DXF-File (*.dxf)");

              QString log;

              tModel *model = getActiveModel();
              if (model){
                //????tGroup* group = new tGroup(this);
                //group->setElements( model->selection() );

                tLayer* top = dynamic_cast<tLayer*>(model->elementByName("PropGeo - Cutting File", iLayer::theType()));
                if (top){
                  tList<tElement*> compounds = top->elements(iLayer::theType());
                  for (int i=0;i<compounds.count();i++){
                    tLayer* comp = dynamic_cast<tLayer*>(compounds.at(i));
                    tLayer* cutting = dynamic_cast<tLayer*>(comp->elementByName(type,iLayer::theType()));
                    if (cutting){
                      log += "Processing Cutting: " + type + " to file: " + baseName + "...dxf\n";

                      tList<tElement*> fabrics = cutting->elements(iLayer::theType());

                      for (int j=0; j<fabrics.count(); j++){
                        //model->setSelection(fabrics.at(j));
                        tLayer* fabric = dynamic_cast<tLayer*>(fabrics.at(j));
                        QString fileName = baseName + "_" + comp->intrface()->name() + "_" + fabric->intrface()->name() + ".dxf";
                        log += "writing: " + fileName + "\n";

                        tDxfExport dxf;

                        dxf.defaultLayer = "CUT";
                        dxf.addElement(fabric);

                        dxf.defaultLayer = "TEXT";
                        tList<tElement*> offsets = fabric->elements(iLayer::theType());
                        for (int k=0; k<offsets.count(); k++ ){

                          tLayer *l = dynamic_cast<tLayer*>(offsets.at(k));
                          if (l){
                            dxf.addText( l->intrface()->name(),
                                         (l->xMin()+l->xMax())*0.5 );

                            tLayer *contur = dynamic_cast<tLayer*>(l->elementByName("Contur", iLayer::theType()));
                            if (contur){
                              tList<tElement*> list = contur->elements(iCurve::theType());
                              tCurve *c = dynamic_cast<tCurve*>(list.at(0));
                              if (c){
                                int tRes = c->tResolution();
                                double area = 0.;
                                tVector x0, x;
                                x0 = c->vectorAt(0.);
                                for (int i=1; i<=tRes; i++){
                                  double t = double(i)/double(tRes);
                                  x = c->vectorAt(t);
                                  area += 0.5*( ( x.x+x0.x ) * (x.y-x0.y ) ) / 1.0e6;
                                  x0 = x;
                                }
                                log += "Layer: " + l->intrface()->name() + ": Area: " + QString::number(area)+ "\n";
                              }
                            }
                          }

                        }

                        dxfPoint xMin = dxf.content().getBoundingBox().Min();
                        xMin.x *= -1;
                        xMin.y *= -1;
                        dxf.content().shift(xMin.x, xMin.y);

                        dxf.exportToFile(fileName);

                      }
                    }

                  }
                }

                //model->selection()->setElements( group->elements() );
                //group->releaseOwner(this);
              }

              QMessageBox mb(QMessageBox::Information, "Export Info:", "Expand for details", QMessageBox::Ok);
              mb.setDetailedText(log);
              mb.exec();

            }
          }
        }

      }
    }

    //model->selection()->setElements( group->elements() );
    //group->releaseOwner(this);
  }

  QMessageBox mb(QMessageBox::Information, "Export Info:", "Expand for details", QMessageBox::Ok);
  mb.setDetailedText(log);
  mb.exec();

}*/
//-----------------------------------------------------------------------------

void tMainForm::on_actionNeu_triggered()
{
  createEmptyModel();
}
//-----------------------------------------------------------------------------
/*
void tMainForm::on_actionInit_triggered()
{

  tModel* model = getActiveModel();
  if (model){
    tLayer *dxfInput = model->addLayer("dxf-Rein");
    tLayer *dxfOutput = model->addLayer("dxf-Raus");
    tLayer *meshIn = model->addLayer("Basis");
    tLayer *meshOut = model->addLayer("Verzerrung");

    model->setCurrentLayer(dxfInput);

    QString defaultFile;
    if (recentlyOpenedFiles.count()==0){
      defaultFile = QDir::homePath();
    } else {
      defaultFile = recentlyOpenedFiles.first();
    }
    importToModel(QFileDialog::getOpenFileName(this,
                                          "DXF-Kontur",
                                          defaultFile,
                                          "Draw Exchange Format (*.dxf)"),
                  model);

    tList<tHermiteSpline*> splList;
    for (int i=0; i<dxfInput->nElements(); i++){
      tHermiteSpline *spl = dynamic_cast<tHermiteSpline*>(dxfInput->element(i));
      if (spl){
        splList.append(spl);
      }
    }

    tVector xMin, xMax;
    for (int i=0; i<splList.count(); i++){
      tVector x;
      x = splList.at(i)->xMin();
      if (i==0){
        xMin = x;
      } else {
        xMin = tVector(min(x.x, xMin.x), min(x.y, xMin.y), min(x.z, xMin.z));
      }

      x = splList.at(i)->xMax();
      if (i==0){
        xMax = x;
      } else {
        xMax = tVector(max(x.x, xMax.x), max(x.y, xMax.y), max(x.z, xMax.z));
      }
    }

    //Mesh In
    tPoint* p[4];
    p[0] = meshIn->addPoint(xMin);
    p[1] = meshIn->addPoint(xMin + tVector(1,0,0) * ((xMax-xMin)*tVector(1,0,0)));
    p[2] = meshIn->addPoint(xMin + tVector(0,1,0) * ((xMax-xMin)*tVector(0,1,0)));
    p[3] = meshIn->addPoint(xMax);

    tLine *l0, *l1;
    l0 = meshIn->addLine(p[0], p[1]);
    l1 = meshIn->addLine(p[2], p[3]);

    tSurface* inFace = meshIn->addRuled(l0, l1);

    tGroup *gIn = meshIn->addGroup();
    gIn->intrface()->setName("Input mesh group");
    gIn->append(inFace);
    //-----------------

    //Mesh Out
    tRelPoint* r[4];
    r[0] = meshOut->addRelPoint(p[0], tVector(0,xMax.y-xMin.y,0));
    r[1] = meshOut->addRelPoint(p[1], tVector(0,xMax.y-xMin.y,0));
    r[2] = meshOut->addRelPoint(p[2], tVector(0,xMax.y-xMin.y,0));
    r[3] = meshOut->addRelPoint(p[3], tVector(0,xMax.y-xMin.y,0));
    l0 = meshOut->addLine(r[0], r[1]);
    l1 = meshOut->addLine(r[2], r[3]);
    tSurface* outFace = meshOut->addRuled(l0, l1);

    tGroup *gOut = meshOut->addGroup();
    gOut->intrface()->setName("Output mesh group");
    gOut->append(outFace);
    //-------


    for (int i=0; i<splList.count(); i++){
      tHermiteSpline *splIn = splList.at(i);

      tDistortedSpline *splOut = dynamic_cast<tDistortedSpline*>(dxfOutput->addElement(iDistortedSpline::theType()));
      splOut->setBaseSpline(splIn);
      splOut->setBaseFaces(gIn);
      splOut->setDistortedFaces(gOut);

//      tHermiteSpline *splOut = dxfOutput->addHermiteSpline();
//      splOut->setTResolution(100);
//      splOut->intrface()->setName(splIn->intrface()->name());
//
//      tLayer* subLayer;
//      subLayer = dynamic_cast<tLayer*>(dxfOutput->addElement(iLayer::theType()));
//      subLayer->intrface()->setName(splIn->intrface()->name()+"_vertices");
//      subLayer->intrface()->setVisibility(false);
//
//      tList<tElement*> pInList = splIn->vertices(),
//                       pOutList;
//
//      for (int j=0; j<pInList.count(); j++){
//        tPoint *d = dynamic_cast<tPoint*>(pInList.at(j));
//        if (d){
//          tStickyMagnet* sMag = new tStickyMagnet(NULL);
//          sMag->setReferenceDot(d);
//          sMag->addStickyFace(inFace);
//
//          tAbsMagnet* aMag = dynamic_cast<tAbsMagnet*>(subLayer->addElement(iAbsMagnet::theType()));
//          aMag->intrface()->setName(d->intrface()->name());
//          aMag->setReference(outFace);
//
//          bool ok;
//          new tPropertyLinker(aMag, "uPosition",
//                              sMag, "uPosition", &ok);
//          new tPropertyLinker(aMag, "vPosition",
//                              sMag, "vPosition", &ok);
//          pOutList.append(aMag);
//        }
//      }
//      splOut->setVertices(pOutList);
    }

  }
}*/
//-----------------------------------------------------------------------------

void tMainForm::on_actionR_ckg_ngig_triggered()
{
}
//-----------------------------------------------------------------------------

void tMainForm::on_actionProgrammversion_triggered()
{
	tProgrammversionDlg *Dlg = new tProgrammversionDlg(this);
	Dlg->exec();
	delete Dlg;
}
//-----------------------------------------------------------------------------

/*
void tMainForm::actionOrthogonal_toggeled (bool checked)
{
  aPerspective->setChecked(!checked);
  tGLModelView *m = dynamic_cast<tGLModelView*>(Workspace->activeSubWindow());
  if (m)
    m->setProjection(Ortho);
}
//-----------------------------------------------------------------------------

void tMainForm::actionPerspective_toggeled (bool checked)
{
  aOrthogonal->setChecked(!checked);
  tGLModelView *m = dynamic_cast<tGLModelView*>(Workspace->activeSubWindow());
  if (m)
    m->setProjection(Perspective);
}
//-----------------------------------------------------------------------------

void tMainForm::actionFlightMode_toggeled (bool checked)
{
  aObjectMode->setChecked(!checked);
  tGLModelView *m = dynamic_cast<tGLModelView*>(Workspace->activeSubWindow());
  if (m)
    m->setMovingMode (FlightMode);
}
//-----------------------------------------------------------------------------

void tMainForm::actionObjectMode_toggeled (bool checked)
{
  aFlightMode->setChecked(!checked);
  tGLModelView *m = dynamic_cast<tGLModelView*>(Workspace->activeSubWindow());
  if (m)
    m->setMovingMode (ObjectMode);
}*/
//-----------------------------------------------------------------------------
void tMainForm::on_menuRecent_Files_triggered(QAction *action)
{
  int index;

  index = rofActionList.firstIndexOf(action);
  if (index >=0 && index<recentlyOpenedFiles.count()){
    openFile(recentlyOpenedFiles.at(index));
  }
}
//-----------------------------------------------------------------------------

tModel* tMainForm::createEmptyModel(const QString& name)
{
  tModel *Model;

  Model = new tModel(this);
  //Model->setCurrentLayer( Model->addLayer("Layer_0") );

  if (name != ""){
    Model->setName(name);
  } else {
    Model->setName("Modell "+QString::number(modelViews.count()+1));
  }

  tSelectionSet* selectionSet = new tSelectionSet(NULL, true);

  tGLModelView *glView = new tGLModelView(this, Model,this);
  glView->setSelectionSet(selectionSet, this);
  glView->setDoubleClickSelectionEnabled(true);
  connect (glView,SIGNAL(destroyed(QObject*)),this,SLOT(viewDestroyed(QObject*)));


  modelViews[glView] = Model;
  QMdiSubWindow *child = Workspace->addSubWindow(glView);

  child->setAttribute(Qt::WA_DeleteOnClose);
  child->showMaximized();



  //Models.append (Model);

  if (qApp->arguments().contains("debug")) {
    // Demo
    tPoint *p0,*p1,*p2;
    tCSpline *c1,*c2;
    tRGB color;

    color = tRGB::MSColor(14);
    p0 = Model->currentLayer()->addPoint(tVector(0.0,0.0,0.0));
    p0->intrface()->setColor(color);
    p0->intrface()->setName("p0");
    p1 = Model->currentLayer()->addPoint(tVector(1.0,1.0,1.0));
    p1->intrface()->setColor(color);
    p2 = Model->currentLayer()->addPoint(tVector(3.0,0.0,-1.0));
    p2->intrface()->setColor(color);
    color = tRGB::MSColor(10);
    c1 = Model->currentLayer()->addCSpline();
    c1->addVortex(p0);
    c1->addVortex(p1);
    c1->addVortex(p2);
    c1->intrface()->setColor(color);

    color = tRGB::MSColor(13);
    p0 = Model->currentLayer()->addPoint(tVector(0.0,4.0,0.0));
    p0->intrface()->setColor(color);
    p1 = Model->currentLayer()->addPoint(tVector(1.0,6.0,1.0));
    p1->intrface()->setColor(color);
    p2 = Model->currentLayer()->addPoint(tVector(3.0,3.0,-1.0));
    p2->intrface()->setColor(color);
    color = tRGB::MSColor(11);
    color = tRGB::MSColor(9);
    c2 = Model->currentLayer()->addCSpline();
    c2->addVortex(p0);
    c2->addVortex(p1);
    c2->addVortex(p2);
    c2->intrface()->setColor(color);

    tRuledSurface *r = Model->currentLayer()->addRuled(c1,c2);
    r->intrface()->setColor(color);
  }


  return Model;
}
//-----------------------------------------------------------------------------

tModel* tMainForm::getActiveModel(void)
{
  tGLModelView *activeView = NULL;
  QMdiSubWindow *window = Workspace->currentSubWindow();
  if (window){
    activeView = dynamic_cast<tGLModelView*>(window->widget());
    if (activeView){
      return activeView->model();
    }
  } else {
    return NULL;
  }
  return NULL;
}

//-----------------------------------------------------------------------------
/*
 *void tMainForm::on_command_returnPressed(void)
{
  int i;
  QStringList cmdList,l;
  QString cmd;
  bool splitAtSpaces = true;

  tConnectiveModel *model;
  tModelCommand modelCmd;

  cmd = command->text();
  cmd.replace("\"","\"\""); //Gaensefuesschen beruecksichtigen
  l = cmd.split("\"",QString::KeepEmptyParts);
  for (i=0;i<l.count();i++){
    if (l.at(i) == ""){
      splitAtSpaces = !splitAtSpaces;
    } else {
      if (splitAtSpaces){
        cmdList << l.at(i).split(QRegExp("\\s+"),QString::SkipEmptyParts);
      } else {
        cmdList << l.at(i);
      }
    }
  }
  cmd = cmdList[0].toLower();
  if (cmd.startsWith("!") || cmd.startsWith("#") || cmd.startsWith("//")){
    // Kommentar
    cmd = command->text();
  } else {
    if (cmd.toLower() == "new"){
      if (cmdList.count() > 1){
        createEmptyModel(cmdList[1]);
        cmd += " \""+cmdList[1]+"\"";
      } else {
        createEmptyModel();
      }
    } else if (cmd == "exit"){
      close();
      cmd = "exit ";
    } else {
    	model = getActiveModel();
      if (model) {
        modelCmd.setModel(model);
        cmd = modelCmd.execute(cmdList);
      } else {
        cmd = "!Error: unknown command or no active workspace";
      }
    }
  }
  lastCommands->append(cmd);
  command->setText("");
  command->setFocus(Qt::OtherFocusReason);
}*/
//-----------------------------------------------------------------------------
