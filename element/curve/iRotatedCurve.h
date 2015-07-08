//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tRotatedCurve.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef IROTATEDCURVE_H_
#define IROTATEDCURVE_H_

#include "element/curve/tCurve.h"

class iRotatedCurve : public iCurve
{
	public:
		iRotatedCurve(tElement *el);
		virtual ~iRotatedCurve();

		static tString theType(void) {return "RotatedCurve";}
		virtual tString type(void) const {return iRotatedCurve::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iCurve::nProperties()+3;}
		int nInheritedProperties(void) {return iCurve::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*IROTATEDCURVE_H_*/
