#ifndef _TVECTOREDIT_H_
#define _TVECTOREDIT_H_

#include <QtGui>
#include "ui_VectorEdit.h"

#include "classes/tVector.h"

class tVectorEdit : public QWidget, private Ui::vectorEdit {

Q_OBJECT

private:
  QPalette OkPal, WrongPal;  //mit den Paletten werden lineEdits markiert, bei denen die eingegebene Zahl nicht richtig gelesen werden konnte.
  tVector x;

private slots:
  void lineEdit_changed(void);

public:
  tVectorEdit(QWidget *parent = NULL);
  virtual ~tVectorEdit();
  void setVector(tVector X);
  tVector vector(void){return x;}
};

#endif //_TVECTOREDIT_H_
