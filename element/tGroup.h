#ifndef TGROUPELEMENT_H_
#define TGROUPELEMENT_H_

#include "element/tElement.h"
#include "element/iGroup.h"

  // palim
class tGroup : public tElement
{
protected:
  tList<tElement*> member;
  QString fAllowedType;
  void refresh(void);

public:
  tGroup(void* theOwner, const QString& allowedType="");
  virtual ~tGroup();

  //returns info about the element group
  virtual int nElements();
  virtual int nElements(QString type);
  virtual tElement* element(int index);
  virtual tList<tElement*> elements(QString type="", bool recursive=false);
  virtual tElement* elementByName(const QString& name, const QString &type = "");

  virtual tElement* last(void);
  virtual tElement* first(void);
  bool contains(tElement* el);
  //adds new Elements
  virtual tElement* append(tElement* el);
  virtual tElement* prepend(tElement* el);
  virtual void append(const tList<tElement*> &l);
  virtual void setElements(const tList<tElement*> &l);
  //removes Elements

  virtual void removeElement(int i);

  virtual bool removeAllElements(tElement *el);
  virtual void removeAllElements(QString name, QString type="");
  virtual void clear(void);
  virtual void removeAllButLast(void);
  virtual void removeAllButFirst(void);
  //Modifies the order of the element list
  virtual void reverse(void);

  virtual tVector xMin(void);
  virtual tVector xMax(void);

  virtual void moveElement(int from, int to) {member.move(from,to); invalidate(this);}

  virtual iElement* intrface(void);
};

/*I!
nElements Int read:nElements
groupedElements ElementList read:elements write:setElements
*/


#endif /*TOWNERELEMENT_H_*/


