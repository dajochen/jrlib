//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tNetPoint.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef INETPOINT_H_
#define INETPOINT_H_

#include "element/point/tDot.h"

class iNetPoint : public iDot
{
	public:
		iNetPoint(tElement *el):iDot(el){}

		static tString theType(void) {return "NetPoint";}
		virtual tString type(void) const {return iNetPoint::theType();}

		virtual bool getPropertyValue(int index, tString propType, void* value){
			if (index == 0 && propType == "String"){
			*(tString*)value =iNetPoint::theType();
				return true;
			} else {
				return iDot::getPropertyValue(index,propType,value);
			}
		}
		virtual QStringList inheritedTypes(void){
			return (iDot::inheritedTypes() << theType());
		}
		virtual bool isOfType(QString thetype){
			if (theType() == thetype) {
				return true;
			} else {
				return iDot::isOfType(thetype);
			}
		}
};
#endif /*INETPOINT_H_*/
