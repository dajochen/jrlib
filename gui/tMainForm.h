#ifndef TMAINFORM_H_
#define TMAINFORM_H_

#include "ui_mainform.h"

#include <QMdiArea>
#include <QComboBox>
#include <QHash>

#include "model/tModel.h"
#include "model/tSelectionSet.h"
#include "views/tModelView.h"
#include "views/tSelectionSummary.h"
#include "views/tPropertiesView.h"
#include "views/tPropertyEditor.h"
#include "views/tTableModelView.h"
#include "views/tElementCreator.h"


class tMainForm : public QMainWindow, Ui::MainForm {
  Q_OBJECT

private:
  QHash<tModelView *, tModel *> modelViews;
  //QList<tModel*> Models;
  //QList<tModelView*> Views;
  QMdiArea *Workspace;

  tPropertiesView *propertiesView;
  tPropertyEditor *propertyEditor;
  tTableModelView *elementView;
  tSelectionSummary *selectionSummary;
  tElementCreator *elementCreator;

  tGroup *copyPasteSelection;

  QPushButton *pushbutton1, *pushbutton2;
  QAction *aOrthogonal, *aPerspective, *aFlightMode, *aObjectMode, *aVertical;
  QToolBar *ToolBar1;
  QComboBox *comboBox1;

  QStringList recentlyOpenedFiles;
  tList<QAction*> rofActionList;
  QString lastSavedFile;

  void updateSettings(void);

  class extDescriptor {
  public:
      extDescriptor(QString e, QString d) : ext(e), descr(d){}
      const QString toString() const {return descr + " (" + ext +")"; }
      QString ext, descr;
  };
  class ExtentionList : public QList<extDescriptor> {
  public:
      QString toString() {
          QString ext;
          ext.append("All known (");
          for (int i=0; i<count();i++) {
              ext += " " + at(i).ext;
          }
          ext.append(")");
          for (int i=0; i<count();i++) {
              ext.append( ";;" + at(i).toString());
          }
          return ext;
      }
  };

protected:

public:
  tMainForm(QMainWindow *parent = 0);
  ~tMainForm(void);
  QAction* pluginAction(QString caption);
  tModel* createEmptyModel(const QString& name = "");
  tModel* getActiveModel(void);
  bool importToModel(QString fileName, tModel *m, bool createDefaultLayerOnDemand=false);
  void openFile(const QString& fileName);
  void saveFile(const QString& fileName);

private slots:
  void on_actionLaden_triggered();
  void on_actionSpeichern_triggered();
  //void on_actionOriginal_Zuschnitte_Speichern_triggered();
  //void on_actionVerzerrte_Zuschnitte_Speichern_triggered();
  void on_actionImportieren_triggered();
  void on_actionExportieren_triggered();
  void on_actionKopieren_triggered();
  void on_actionEinf_gen_triggered();
  //  void on_actionNeu_triggered();
  //void on_actionInit_triggered();
  void on_actionProgrammversion_triggered();
  void on_actionR_ckg_ngig_triggered();
  //void actionOrthogonal_toggeled (bool checked);
  //void actionPerspective_toggeled (bool checked);
  //void actionFlightMode_toggeled (bool checked);
  //void actionObjectMode_toggeled (bool checked);
  void on_menuRecent_Files_triggered(QAction *action);
  void windowActivated(QMdiSubWindow *w);
public slots:
  void viewDestroyed (QObject *view);
  void on_actionNeu_triggered();

};


#endif /*TMAINFORM_H_*/
