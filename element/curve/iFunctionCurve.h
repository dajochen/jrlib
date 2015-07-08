//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tFunctionCurve.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef IFUNCTIONCURVE_H_
#define IFUNCTIONCURVE_H_

#include "element/curve/tCurve.h"

class iFunctionCurve : public iCurve
{
	public:
		iFunctionCurve(tElement *el);
		virtual ~iFunctionCurve();

		static tString theType(void) {return "FunctionCurve";}
		virtual tString type(void) const {return iFunctionCurve::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iCurve::nProperties()+4;}
		int nInheritedProperties(void) {return iCurve::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*IFUNCTIONCURVE_H_*/
