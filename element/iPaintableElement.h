//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tPaintableElement.h (Do. Okt. 16 19:49:22 2014)
//------------------------------------------------------------------------

#ifndef IPAINTABLEELEMENT_H_
#define IPAINTABLEELEMENT_H_

#include "element/tElement.h"

class iPaintableElement : public iElement
{
	public:
		iPaintableElement(tElement *el):iElement(el){}

		static tString theType(void) {return "PaintableElement";}
		virtual tString type(void) const {return iPaintableElement::theType();}

		virtual bool getPropertyValue(int index, tString propType, void* value){
			if (index == 0 && propType == "String"){
			*(tString*)value =iPaintableElement::theType();
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
#endif /*IPAINTABLEELEMENT_H_*/
