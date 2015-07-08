#ifndef TLINKEDELEMENT_H
#define TLINKEDELEMENT_H

#include <QString>
#include "tElement.h"
#include "surface/tSurface.h"
#include "iLinkedElement.h"

class tLinkedElement : public tElement
{
private:
  tElement *fReference, *fLinkedElement;
  QString fLinkedProperty;
public:
  tLinkedElement(void *theOwner, tElement *ref=NULL, QString prop="");
  virtual ~tLinkedElement();

  iElement* intrface(void);
  virtual void refresh(void);

  QString property(void);
  void setProperty(QString property);
  tElement* reference(void);
  void setReference(tElement *el);

  tElement* linkedElement(void){update(); return fLinkedElement;}

  operator tSurface*() {return dynamic_cast<tSurface*>(fReference);}
};

#endif // TLINKEDELEMENT_H

/*xIx!x
reference Element read:reference write:setReference
linkedProperty String read:property write:setProperty
*/
