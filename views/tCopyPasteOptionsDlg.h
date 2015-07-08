#ifndef TCOPYPASTEOPTIONDLG_H_
#define TCOPYPASTEOPTIONDLG_H_

#include "ui_CopyPasteOptionsDlg.h"

#include <QDialog>

enum tCopyPasteOption{cpoDotsToRelPoints};

class tCopyPasteOptionsDlg : public QDialog, public Ui::CopyPasteOptionsDlg {
  Q_OBJECT

public:
  tCopyPasteOptionsDlg(QWidget *parent=0, Qt::WindowFlags f=0);
  ~tCopyPasteOptionsDlg(void);
  
private slots:
  
protected:

private:

};

#endif /*TCOPYPASTEOPTIONDLG_H_*/
