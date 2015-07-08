//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tPolygon.h (Mi. Sep. 17 22:29:19 2014)
//------------------------------------------------------------------------

#ifndef IPOLYGON_H_
#define IPOLYGON_H_

#include "tAbstractPolygon.h"

class iPolygon : public iAbstractPolygon
{
	public:
		iPolygon(tElement *el):iAbstractPolygon(el){}

		static tString theType(void) {return "Polygon";}
		virtual tString type(void) const {return iPolygon::theType();}

		virtual bool getPropertyValue(int index, tString propType, void* value){
			if (index == 0 && propType == "String"){
			*(tString*)value =iPolygon::theType();
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
#endif /*IPOLYGON_H_*/
