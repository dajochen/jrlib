//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tOperator.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef IOPERATOR_H_
#define IOPERATOR_H_

#include "element/tElement.h"

class iOperator : public iElement
{
	public:
		iOperator(tElement *el):iElement(el){}

		static tString theType(void) {return "Operator";}
		virtual tString type(void) const {return iOperator::theType();}

		virtual bool getPropertyValue(int index, tString propType, void* value){
			if (index == 0 && propType == "String"){
			*(tString*)value =iOperator::theType();
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
#endif /*IOPERATOR_H_*/
