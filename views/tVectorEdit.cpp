#include "tVectorEdit.h"

tVectorEdit::tVectorEdit(QWidget *parent) : QWidget(parent)
{
  setupUi(this);
// Initialisierung der Gui  / Definition der Paletten mit denen die lineEdits eingef�rbt werden k�nnen
  QColor Warning=Qt::red;
  Warning = Warning.light(180);
  OkPal = lineEdit1->palette();
  WrongPal = lineEdit1->palette();
  WrongPal.setColor(QPalette::Text, Qt::black);
  WrongPal.setColor(QPalette::Base, Warning);

  setVector(tVector(0,0,0));
  lineEdit1->setFocus(Qt::OtherFocusReason);
  connect(lineEdit1,SIGNAL(editingFinished()),this,SLOT(lineEdit_changed()));
  connect(lineEdit2,SIGNAL(editingFinished()),this,SLOT(lineEdit_changed()));
  connect(lineEdit3,SIGNAL(editingFinished()),this,SLOT(lineEdit_changed()));
}
//-------------------------------------------------------------------------------

tVectorEdit::~tVectorEdit()
{
}
//-------------------------------------------------------------------------------

void tVectorEdit::lineEdit_changed(void)
{
  bool ok;
  tReal value;
  value = ((QLineEdit*)(sender()))->text().toFloat(&ok);
  if (ok){
    if ((QLineEdit*)(sender()) == lineEdit1)
      x.x = value;
    if ((QLineEdit*)(sender()) == lineEdit2)
      x.y = value;
    if ((QLineEdit*)(sender()) == lineEdit3)
      x.z = value;
  } else {
    ((QLineEdit*)(sender()))->setPalette(WrongPal);
    ((QLineEdit*)(sender()))->setFocus(Qt::OtherFocusReason);
  }
}
//-------------------------------------------------------------------------------
void tVectorEdit::setVector(tVector X)
{
  x = X;
  lineEdit1->setText(QString::number(x.x));
  lineEdit2->setText(QString::number(x.y));
  lineEdit3->setText(QString::number(x.z));
};
//-------------------------------------------------------------------------------

