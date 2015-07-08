//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tOffsetCurve2.h (Fr. Sep. 12 22:42:55 2014)
//------------------------------------------------------------------------

#ifndef IOFFSETCURVE2_H_
#define IOFFSETCURVE2_H_

#include "element/curve/tCurve.h"

class iOffsetCurve2 : public iCurve
{
	public:
		iOffsetCurve2(tElement *el);
		virtual ~iOffsetCurve2();

		static tString theType(void) {return "OffsetCurve2";}
		virtual tString type(void) const {return iOffsetCurve2::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iCurve::nProperties()+2;}
		int nInheritedProperties(void) {return iCurve::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*IOFFSETCURVE2_H_*/
