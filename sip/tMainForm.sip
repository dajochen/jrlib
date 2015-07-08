class tMainForm : QMainWindow {
%TypeHeaderCode
#include "gui/tMainForm.h"
%End

public:
  tMainForm();
  virtual ~tMainForm();

  tConnectiveModel* createEmptyModel(const QString& name = "");
  tConnectiveModel* getActiveModel();
  bool importToModel(QString fileName, tModel *m, bool createDefaultLayerOnDemand=false);
  void openFile(const QString& fileName);
  void saveFile(const QString& fileName);
  QAction* pluginAction(QString caption);
//  void createEmptyModel(const QString& name = "");
//  tCModel* getActiveModel();
//  bool importToModel(QString fileName, tModel *m, bool createDefaultLayerOnDemand=false);
//  void openFile(const QString& fileName);
//  void saveFile(const QString& fileName);
  

//signals:
//    void runPythonCode(QString);
 
public slots:
    void on_actionNeu_triggered();
//    void runPythonCode();
 
private:
   void openFile(QString fileName);
//public:
//    QGraphicsView * viewer;
//    QGraphicsScene * scene;
//    QPlainTextEdit * editor;
//    QPushButton * pb_commit;
};
