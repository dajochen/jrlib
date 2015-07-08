//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tOffsetCurve.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef IOFFSETCURVE_H_
#define IOFFSETCURVE_H_

#include "element/curve/tCurve.h"

class iOffsetCurve : public iCurve
{
	public:
		iOffsetCurve(tElement *el);
		virtual ~iOffsetCurve();

		static tString theType(void) {return "OffsetCurve";}
		virtual tString type(void) const {return iOffsetCurve::theType();}

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
#endif /*IOFFSETCURVE_H_*/
