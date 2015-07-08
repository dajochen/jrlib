//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tPolyCurve.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef IPOLYCURVE_H_
#define IPOLYCURVE_H_

#include "element/curve/tCurve.h"

class iPolyCurve : public iCurve
{
	public:
		iPolyCurve(tElement *el);
		virtual ~iPolyCurve();

		static tString theType(void) {return "PolyCurve";}
		virtual tString type(void) const {return iPolyCurve::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iCurve::nProperties()+6;}
		int nInheritedProperties(void) {return iCurve::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*IPOLYCURVE_H_*/
