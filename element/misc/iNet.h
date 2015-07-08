//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tNet.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef INET_H_
#define INET_H_

#include "element/tElement.h"

class iNet : public iElement
{
	public:
		iNet(tElement *el):iElement(el){}

		static tString theType(void) {return "Net";}
		virtual tString type(void) const {return iNet::theType();}

		virtual bool getPropertyValue(int index, tString propType, void* value){
			if (index == 0 && propType == "String"){
			*(tString*)value =iNet::theType();
				return true;
			} else {
				return iElement::getPropertyValue(index,propType,value);
			}
		}
		virtual QStringList inheritedTypes(void){
			return (iElement::inheritedTypes() << theType());
		}
		virtual bool isOfType(QString thetype){
			if (theType() == thetype) {
				return true;
			} else {
				return iElement::isOfType(thetype);
			}
		}
};
#endif /*INET_H_*/
