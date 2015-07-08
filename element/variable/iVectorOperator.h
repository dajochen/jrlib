//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tVectorOperator.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef IVECTOROPERATOR_H_
#define IVECTOROPERATOR_H_

#include "tOperator.h"

class iVectorOperator : public iOperator
{
	public:
		iVectorOperator(tElement *el):iOperator(el){}

		static tString theType(void) {return "VectorOperator";}
		virtual tString type(void) const {return iVectorOperator::theType();}

		virtual bool getPropertyValue(int index, tString propType, void* value){
			if (index == 0 && propType == "String"){
			*(tString*)value =iVectorOperator::theType();
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
#endif /*IVECTOROPERATOR_H_*/
