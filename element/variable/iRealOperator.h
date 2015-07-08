//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tRealOperator.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef IREALOPERATOR_H_
#define IREALOPERATOR_H_

#include "tOperator.h"

class iRealOperator : public iOperator
{
	public:
		iRealOperator(tElement *el):iOperator(el){}

		static tString theType(void) {return "RealOperator";}
		virtual tString type(void) const {return iRealOperator::theType();}

		virtual bool getPropertyValue(int index, tString propType, void* value){
			if (index == 0 && propType == "String"){
			*(tString*)value =iRealOperator::theType();
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
#endif /*IREALOPERATOR_H_*/
