#include "tPropertyDelegate.h"

#include <QComboBox>

#include "tTableModelView.h"
#include "tVectorEdit.h"
#include "classes/tVectorStringConverter.h"

#define jrNone "None"
#define jrBool "Bool"
#define jrInt "Int"
#define jrReal "Real"
#define jrVector "Vector"
#define jrString "String"
#define jrRGB "RGB"
#define jrElement "Element"


tPropertyDelegate::tPropertyDelegate(QObject *parent)
  : QItemDelegate(parent),
    tElement(NULL),
    selection(NULL)
{
  currentIndex = -1;
}
//-----------------------------------------------------------------------------

tPropertyDelegate::~tPropertyDelegate()
{
    setSelection(NULL);
    setReferenceModel(NULL);
    removeElementSelectors();
}
//-----------------------------------------------------------------------------

void tPropertyDelegate::setSelection(tGroup *sel)
{
    if (selection){
        selection->removeDependent(this);
    }
    selection = sel;
    if (selection){
        selection->addDependent(this);
    }
}
//-----------------------------------------------------------------------------

void tPropertyDelegate::addElementSelector(tModelView *modelView)
{
  fElementSelector.append(modelView);
  modelView->addOwner(this);
}
//-----------------------------------------------------------------------------

void tPropertyDelegate::removeElementSelectors()
{
    for (int i=0; i< fElementSelector.count(); i++){
        fElementSelector.at(i)->releaseOwner(this);
    }
    fElementSelector.clear();
}
//-----------------------------------------------------------------------------

void tPropertyDelegate::setReferenceModel(tModel *m)
{
  if (fGeometryModel){
    fGeometryModel->removeDependent(this);
  }
  if (m){
    m->addDependent(this);
  }
  fGeometryModel=m;
  invalidate(this);
}
//-----------------------------------------------------------------------------

void tPropertyDelegate::refresh(void)
{
}
//-----------------------------------------------------------------------------

void tPropertyDelegate::lockSelection() const
{
  //if (fGeometryModel){
  //  fGeometryModel->lockElement();
    for (int i=0;i<selection->nElements();i++){
      selection->element(i)->lockElement();
    }
  //}
}
//-----------------------------------------------------------------------------

void tPropertyDelegate::unlockSelection() const
{
  //if (fGeometryModel){
  //  fGeometryModel->unlockElement();
    for (int i=0;i<selection->nElements();i++){
      selection->element(i)->unlockElement();
    }
  //}
}
//-----------------------------------------------------------------------------

QWidget* tPropertyDelegate::createEditor(QWidget *parent,
     const QStyleOptionViewItem & option ,
     const QModelIndex & index ) const
{
  //tList<tElement*> selectionList = selection->elements(); //fGeometryModel->selection();
  lockSelection();
  QWidget *editor;

  // Für die Zeit der Bearbeitung werden alle weiteren Threads blockiert.
  //if (fGeometryModel){

    if (selection->nElements()){
      QString currentType = selection->element(0)->intrface()->getPropertyType(currentIndex);

      if (currentType == jrInt){
        QSpinBox *box;
        box = new QSpinBox(parent);
        box->setMaximum(10000);
        box->setMinimum(-10000);
        editor = box;
      } else if (currentType == jrReal || currentType == jrString){
        editor = QItemDelegate::createEditor(parent,option,index);
      } else if (currentType == jrVector){
        editor = new tVectorEdit(NULL);
      } else if (currentType == jrRGB){
        QColor color;
        tRGB value;
        tVector x = tVectorStringConverter::toVector(index.data().toString(),QRegExp(";"));
        color.setRgb((int)x.x, (int)x.y, (int)x.z);
        color = QColorDialog::getColor(color);
        value.setColor(color.red(),color.green(),color.blue());
        for (int i=0;i<selection->nElements();i++){
          selection->element(i)->intrface()->setPropertyValue(currentIndex, currentType, &value);
        }
        editor = NULL;
      } else if (currentType == jrBool){
        editor = new QComboBox(parent);
      } else if (currentType.endsWith("List")){
        if (   currentType.startsWith("Int")
               || currentType.startsWith("Real")
               || currentType.startsWith("Bool")
               || currentType.startsWith("String") ){
          editor = QItemDelegate::createEditor(parent,option,index);
        } else {
          tTableModelView *tmv = new tTableModelView(NULL, fGeometryModel, tmvEnhancedSelection, true, true);
          tmv->setSelectionSet(new tSelectionSet(NULL));
          editor = tmv;
        }
      } else {
        tElement *el;
        if (selection->element(0)->intrface()->getPropertyValue(currentIndex, currentType, &el)){
            tTableModelView *tmv = new tTableModelView(NULL, fGeometryModel, tmvSingleSelection, true);

            tmv->setSelectionSet(new tSelectionSet(NULL));
            editor = tmv;
        } else {
          editor = NULL;
        }
      }
    } else {
      editor = NULL;
    }

  //}
  unlockSelection();
  return editor;
}
//-----------------------------------------------------------------------------

void tPropertyDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
  //tList<tElement*> selectionList = fGeometryModel->selection();

  //if (fGeometryModel) {
    lockSelection();
    if (selection->nElements()){
      QString currentType = selection->element(0)->intrface()->getPropertyType(currentIndex);
      if (currentType == jrInt){
        int value = index.model()->data(index, Qt::EditRole).toInt();
        QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
        spinBox->setValue(value);
      } else if (currentType == jrReal || currentType == jrString){
        QItemDelegate::setEditorData(editor, index);
      } else if (currentType == jrVector){
        tVectorEdit *e = static_cast<tVectorEdit*>(editor);
        tVector x = tVectorStringConverter::toVector(index.data().toString(),QRegExp(";"));
        e->setVector(x);
      } else if (currentType == jrRGB){
        // nichts zu tun
      } else if (currentType == jrBool){
        QComboBox *cb = static_cast<QComboBox*>(editor);
        cb->addItem("true");
        cb->addItem("false");
        if (index.data().toString() == "true"){
          cb->setCurrentIndex(0);
        } else {
          cb->setCurrentIndex(1);
        }
      } else if (currentType.endsWith("List")){
        if (   currentType.startsWith("Int")
               || currentType.startsWith("Real")
               || currentType.startsWith("Bool")
               || currentType.startsWith("String") ){
          QItemDelegate::setEditorData(editor, index);
        } else {
          QString type;
          tList<tElement*> list;
          tTableModelView *tmv = static_cast<tTableModelView*>(editor);

          type = currentType;
          type.remove(type.length()-4,4);
          tmv->availableTypes()->setTypeFilter(QStringList(type));
          if (selection->element(0)->intrface()->getPropertyValue(currentIndex, currentType, &list)){
             tmv->selectionSet()->setElements(list);
          }
        }
      } else {
        tElement *el;
        tTableModelView *tmv = static_cast<tTableModelView*>(editor);
        tmv->selectionSet()->clear();
        tmv->availableTypes()->setTypeFilter(QStringList(currentType));
        if (selection->element(0)->intrface()->getPropertyValue(currentIndex, currentType, &el)){
          tmv->selectionSet()->append(el);
        }
      }
    }
    unlockSelection();

}
//-----------------------------------------------------------------------------

void tPropertyDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                    const QModelIndex &index) const
{
  //tList<tElement*> selectionList = fGeometryModel->selection();

  //if (fGeometryModel) {
    lockSelection();
    if (selection->nElements()){
      QString currentType = selection->element(0)->intrface()->getPropertyType(currentIndex);
      //????if (fSelection->intrface()){
      int i;
      if (currentType == jrInt){
        QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
        spinBox->interpretText();
        int value = spinBox->value();
        for (i=0;i<selection->nElements();i++){
          selection->element(i)->intrface()->setPropertyValue(currentIndex, currentType, &value);
        }
      } else if (currentType == jrReal){
        QItemDelegate::setModelData(editor, model, index);
        tReal value = index.data().toString().toFloat();
        for (i=0;i<selection->nElements();i++){
          selection->element(i)->intrface()->setPropertyValue(currentIndex, currentType, &value);
        }
      } else if (currentType == jrString){
        QItemDelegate::setModelData(editor, model, index);
        QString value = index.data().toString();
        for (i=0;i<selection->nElements();i++){
          selection->element(i)->intrface()->setPropertyValue(currentIndex, currentType, &value);
        }
      } else if (currentType == jrVector){
        tVectorEdit *e =static_cast<tVectorEdit*>(editor);
        tVector value = e->vector();
        for (i=0;i<selection->nElements();i++){
          selection->element(i)->intrface()->setPropertyValue(currentIndex, currentType, &value);
        }
      } else if (currentType == jrBool){
        bool value;
        QComboBox *cb = static_cast<QComboBox*>(editor);
        if (cb->currentIndex() == 0){
          value = true;
        } else {
          value = false;
        }
        for (i=0;i<selection->nElements();i++){
          selection->element(i)->intrface()->setPropertyValue(currentIndex, currentType, &value);
        }
      } else if (currentType == jrRGB){
        // nix zu tun. Alles bereits erledigt.
      } else if (currentType.endsWith("List")) {
        if (currentType.startsWith("Int")){
          tList<int> value;
          QItemDelegate::setModelData(editor, model, index);
          QStringList strList = index.data().toString().split(";",QString::KeepEmptyParts);
          for (i=0;i<strList.count();i++){
            value.append((int)strList.at(i).toFloat());
          }
          for (i=0;i<selection->nElements();i++){
            selection->element(i)->intrface()->setPropertyValue(currentIndex, currentType, &value);
          }
        } else if (currentType.startsWith("Real")){
          tList<tReal> value;
          QItemDelegate::setModelData(editor, model, index);
          QStringList strList = index.data().toString().split(";",QString::KeepEmptyParts);
          for (i=0;i<strList.count();i++){
            value.append(strList.at(i).toFloat());
          }
          for (i=0;i<selection->nElements();i++){
            selection->element(i)->intrface()->setPropertyValue(currentIndex, currentType, &value);
          }
        } else if (currentType.startsWith("String")){
          tList<QString> value;
          QItemDelegate::setModelData(editor, model, index);
          QStringList strList = index.data().toString().split(";",QString::KeepEmptyParts);
          for (i=0;i<strList.count();i++){
            value.append(strList.at(i));
          }
          for (i=0;i<selection->nElements();i++){
            selection->element(i)->intrface()->setPropertyValue(currentIndex, currentType, &value);
          }
        } else if (currentType.startsWith("Bool")){
          tList<bool> value;
          QItemDelegate::setModelData(editor, model, index);
          QStringList strList = index.data().toString().split(";",QString::KeepEmptyParts);
          for (i=0;i<strList.count();i++){
            if (strList.at(i)=="true" || strList.at(i)=="True" || strList.at(i)=="1" ){
              value.append(true);
            } else {
              value.append(false);
            }
          }
          for (i=0;i<selection->nElements();i++){
            selection->element(i)->intrface()->setPropertyValue(currentIndex, currentType, &value);
          }
        } else {
          tTableModelView *tmv = static_cast<tTableModelView*>(editor);
          tList<tElement*> value = tmv->selectionSet()->elements();
          for (i=0;i<selection->nElements();i++){
            selection->element(i)->intrface()->setPropertyValue(currentIndex, currentType, &value);
          }
        }
      } else {
        tTableModelView *tmv = static_cast<tTableModelView*>(editor);
        tElement *value = tmv->selectionSet()->first();
        for (i=0;i<selection->nElements();i++){
          selection->element(i)->intrface()->setPropertyValue(currentIndex, currentType, value);
        }
      }

    }
    unlockSelection();
  //}
}
//-----------------------------------------------------------------------------

void tPropertyDelegate::updateEditorGeometry(QWidget *editor,
     const QStyleOptionViewItem &option, const QModelIndex& /*index*/ ) const
{
  //tList<tElement*> selectionList = fGeometryModel->selection();

  lockSelection();
  if (selection->nElements()>0){
    QString currentType = selection->element(0)->intrface()->getPropertyType(currentIndex);

    if (currentType != jrVector){
      editor->setGeometry(option.rect);
    }
  }
  unlockSelection();
}
//-----------------------------------------------------------------------------


