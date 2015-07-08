//------------------------------------------------------------------------
// Modified intrface: jochen
//------------------------------------------------------------------------

#ifndef ILINKEDELEMENT_H_
#define ILINKEDELEMENT_H_

#include "element/tElement.h"


class iLinkedElement : public iElement
{
protected:
  iElement* linkedObjectIFace (void);

	public:
		iLinkedElement(tElement *el);
		virtual ~iLinkedElement();

		static tString theType(void) {return "LinkedElement";}
		virtual tString type(void) const {return iLinkedElement::theType();}

        virtual tString getPropertyName(int index);
        virtual tString getPropertyType(int index);
        virtual bool getPropertyValue(int index, tString type, void* value);
    virtual bool setPropertyValue(int index, tString type, void* value);
        virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);

    unsigned int nInheritedProperties(void);
    unsigned int nLinkedElementProperties(void);
    virtual int nProperties(void);

};
#endif /*ILINKEDELEMENT_H_*/
