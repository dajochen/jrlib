//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tCSpline.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef ICSPLINE_H_
#define ICSPLINE_H_

#include "element/curve/tCurve.h"

class iCSpline : public iCurve
{
	public:
		iCSpline(tElement *el);
		virtual ~iCSpline();

		static tString theType(void) {return "CSpline";}
		virtual tString type(void) const {return iCSpline::theType();}

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
#endif /*ICSPLINE_H_*/
