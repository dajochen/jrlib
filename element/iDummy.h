//------------------------------------------------------------------------
//Automically generated interface class
//generated from tDummy.h (Mi 9. Feb 00:13:28 2011)
//------------------------------------------------------------------------
#ifndef IDUMMY_H_
#define IDUMMY_H_

#include "element/iElement.h"

class iDummy : public iElement
{
	public:
		iDummy(tElement *el):iElement(el){};
		virtual bool getPropertyValue(unsigned int index, tString type, void* value){
			if (index == 0 && type == "String"){
			*(QString*)value = "Dummy";
				return true;
			} else {
				return iElement::getPropertyValue(index,type,value);
			}
		};
		virtual QStringList inheritedTypes(void){
			QString type;
			iDummy::getPropertyValue(0,"String",&type);
			return (iElement::inheritedTypes() << type);
		};
		virtual bool isOfType(QString thetype){
			if ("Dummy"==thetype) {
				return true;
			} else {
				return iElement::isOfType(thetype);
			}
		};
    virtual tString name(void){return "*";};
};
#endif /*IDUMMY_H_*/
