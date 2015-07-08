//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tStructuredAbstractGrid.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef ISTRUCTUREDABSTRACTGRID_H_
#define ISTRUCTUREDABSTRACTGRID_H_

#include "element/tElement.h"

class iStructuredAbstractGrid : public iElement
{
	public:
		iStructuredAbstractGrid(tElement *el):iElement(el){}

		static tString theType(void) {return "StructuredAbstractGrid";}
		virtual tString type(void) const {return iStructuredAbstractGrid::theType();}

		virtual bool getPropertyValue(int index, tString propType, void* value){
			if (index == 0 && propType == "String"){
			*(tString*)value =iStructuredAbstractGrid::theType();
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
#endif /*ISTRUCTUREDABSTRACTGRID_H_*/
