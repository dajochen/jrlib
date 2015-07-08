//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tMidCurve.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef IMIDCURVE_H_
#define IMIDCURVE_H_

#include "element/curve/tCurve.h"

class iMidCurve : public iCurve
{
	public:
		iMidCurve(tElement *el);
		virtual ~iMidCurve();

		static tString theType(void) {return "MidCurve";}
		virtual tString type(void) const {return iMidCurve::theType();}

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
#endif /*IMIDCURVE_H_*/
