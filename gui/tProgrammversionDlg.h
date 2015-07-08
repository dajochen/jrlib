#ifndef TPROGRAMMVERSIONDLG_H_
#define TPROGRAMMVERSIONDLG_H_

#include "ui_ProgrammversionDlg.h"

#include <QtGui>

class tProgrammversionDlg : public QDialog, Ui::ProgrammversionDlg {
  Q_OBJECT

public:
  tProgrammversionDlg(QWidget *parent=0, Qt::WindowFlags f=0);
  ~tProgrammversionDlg(void);
  
private slots:
  
protected:

private:

};

#endif /*TPROGRAMMVERSIONDLG_H_*/
