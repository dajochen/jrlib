#include "tMainForm.h"

#include <QToolBar>
#include <QMdiSubWindow>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <string.h>

#include "model/tModelIO.h"
#include "model/DXFReader.h"
#include "model/export/tExporterTool.h"


#include "views/jrgui.h"
#include "views/tGLModelView.h"
#include "views/tCopyPasteOptionsDlg.h"

#include "tProgrammversionDlg.h"

#include "classes/utils.h"

#include "model/tStlImport.h"


tMainForm::tMainForm(QMainWindow *parent): QMainWindow(parent)
{
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
void tMainForm::on_actionNeu_triggered()
{
  createEmptyModel();
}
//-----------------------------------------------------------------------------

void tMainForm::on_actionExportieren_triggered()
{
    tExporterTool exporter(getActiveModel(), getActiveSelectionSet());
    exporter.exportToFile(exporter.selectExportFile(this));
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
  tGLModelView *glv = NULL;
  QMdiSubWindow *window = Workspace->currentSubWindow();
  if (window){
    glv = dynamic_cast<tGLModelView*>(window->widget());
    if (glv){
      return glv->model();
    }
  } else {
    return NULL;
  }
  return NULL;
}
//-----------------------------------------------------------------------------

tSelectionSet* tMainForm::getActiveSelectionSet(void)
{
  tGLModelView *glv = NULL;
  QMdiSubWindow *window = Workspace->currentSubWindow();
  if (window){
    glv = dynamic_cast<tGLModelView*>(window->widget());
    if (glv){

        return glv->selectionSet(this);
    }
  } else {
    return NULL;
  }
  return NULL;
}
//-----------------------------------------------------------------------------
