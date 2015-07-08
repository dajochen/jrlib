//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tListOperator.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef ILISTOPERATOR_H_
#define ILISTOPERATOR_H_

#include "tOperator.h"

class iListOperator : public iOperator
{
	public:
		iListOperator(tElement *el):iOperator(el){}

		static tString theType(void) {return "ListOperator";}
		virtual tString type(void) const {return iListOperator::theType();}

		virtual bool getPropertyValue(int index, tString propType, void* value){
			if (index == 0 && propType == "String"){
			*(tString*)value =iListOperator::theType();
				return true;
			} else {
				return iOperator::getPropertyValue(index,propType,value);
			}
		}
		virtual QStringList inheritedTypes(void){
			return (iOperator::inheritedTypes() << theType());
		}
		virtual bool isOfType(QString thetype){
			if (theType() == thetype) {
				return true;
			} else {
				return iOperator::isOfType(thetype);
			}
		}
};
#endif /*ILISTOPERATOR_H_*/
