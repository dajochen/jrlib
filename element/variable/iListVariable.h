//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tListVariable.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef ILISTVARIABLE_H_
#define ILISTVARIABLE_H_

#include "tVariable.h"

class iListVariable : public iVariable
{
	public:
		iListVariable(tElement *el):iVariable(el){}

		static tString theType(void) {return "ListVariable";}
		virtual tString type(void) const {return iListVariable::theType();}

		virtual bool getPropertyValue(int index, tString propType, void* value){
			if (index == 0 && propType == "String"){
			*(tString*)value =iListVariable::theType();
				return true;
			} else {
				return iVariable::getPropertyValue(index,propType,value);
			}
		}
		virtual QStringList inheritedTypes(void){
			return (iVariable::inheritedTypes() << theType());
		}
		virtual bool isOfType(QString thetype){
			if (theType() == thetype) {
				return true;
			} else {
				return iVariable::isOfType(thetype);
			}
		}
};
#endif /*ILISTVARIABLE_H_*/
