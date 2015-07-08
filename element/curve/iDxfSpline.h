//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tDxfSpline.h (Sa. Mär. 21 22:43:43 2015)
//------------------------------------------------------------------------

#ifndef IDXFSPLINE_H_
#define IDXFSPLINE_H_

#include "tAbstractSpline.h"

class iDxfSpline : public iAbstractSpline
{
	public:
		iDxfSpline(tElement *el):iAbstractSpline(el){}

		static tString theType(void) {return "DxfSpline";}
		virtual tString type(void) const {return iDxfSpline::theType();}

		virtual bool getPropertyValue(int index, tString propType, void* value){
			if (index == 0 && propType == "String"){
			*(tString*)value =iDxfSpline::theType();
				return true;
			} else {
				return iAbstractSpline::getPropertyValue(index,propType,value);
			}
		}
		virtual QStringList inheritedTypes(void){
			return (iAbstractSpline::inheritedTypes() << theType());
		}
		virtual bool isOfType(QString thetype){
			if (theType() == thetype) {
				return true;
			} else {
				return iAbstractSpline::isOfType(thetype);
			}
		}
};
#endif /*IDXFSPLINE_H_*/
