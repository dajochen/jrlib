//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tTriangle.h (Mi. Sep. 17 22:40:38 2014)
//------------------------------------------------------------------------

#ifndef ITRIANGLE_H_
#define ITRIANGLE_H_

#include "tAbstractPolygon.h"

class iTriangle : public iAbstractPolygon
{
	public:
		iTriangle(tElement *el):iAbstractPolygon(el){}

		static tString theType(void) {return "Triangle";}
		virtual tString type(void) const {return iTriangle::theType();}

		virtual bool getPropertyValue(int index, tString propType, void* value){
			if (index == 0 && propType == "String"){
			*(tString*)value =iTriangle::theType();
				return true;
			} else {
				return iAbstractPolygon::getPropertyValue(index,propType,value);
			}
		}
		virtual QStringList inheritedTypes(void){
			return (iAbstractPolygon::inheritedTypes() << theType());
		}
		virtual bool isOfType(QString thetype){
			if (theType() == thetype) {
				return true;
			} else {
				return iAbstractPolygon::isOfType(thetype);
			}
		}
};
#endif /*ITRIANGLE_H_*/
