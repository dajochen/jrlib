#ifndef TCOMMONPROPERTY_H
#define TCOMMONPROPERTY_H

#include <QString>
#include "tElement.h"
#include "iUnifiedProperties.h"

class tUnifiedProperties : public tElement
{
public:
  tUnifiedProperties(void *theOwner);
  virtual ~tUnifiedProperties();

  iElement* intrface(void);
  virtual void refresh(void);

  tList<tElement*> elementList(void);
  void setElementList(tList<tElement*> list);
  void addElement(tElement* el);

  virtual void invalidate(tElement *sender);
  virtual void repaintElement(tElement *sender);

  QString unifiedType(void){return fUnifiedType;}

  QString unifiedProperty(void) {return fUnifiedProperty;}
  void setUnifiedProperty(QString value) {fUnifiedProperty = value; invalidate(this);}


  void* unifiedValue(void *writeTo);//writes the unified value into the pointer "writeTo" and returns a pointer to the private value.
  void setUnifiedValue(void* newValue);
  void updateLinkedPropertyData(void);



private:

  tList<tElement*> fElementList;
  QString fUnifiedProperty, fUnifiedType;
  bool isUpdating;

  void checkForModifiedProperties(void);
  void applyUnifiedValue(tElement *el2, void *newValue);



  // storage for the unified value.
  int iVal;
  tReal rVal;
  bool bVal;
  tVector vVal;
  tRGB rgbVal;
  QString strVal;
  //Elements
  tElement *elVal;
  //Lists
  tList<int> intList;
  tList<tReal> realList;
  tList<bool> boolList;
  tList<tVector> vectorList;
  tList<tRGB> rgbList;
  tList<QString> stringList;
  tList<tElement*> elList;
};

/*xIx!x
elementList ElementList read:elementList write:setElementList
commonProperty String read:commonProperty write:setCommonProperty
*/

#endif // TCOMMONPROPERTY_H

