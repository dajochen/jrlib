//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tBSpline.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef IBSPLINE_H_
#define IBSPLINE_H_

#include "element/curve/tCurve.h"

class iBSpline : public iCurve
{
	public:
		iBSpline(tElement *el);
		virtual ~iBSpline();

		static tString theType(void) {return "BSpline";}
		virtual tString type(void) const {return iBSpline::theType();}

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
#endif /*IBSPLINE_H_*/
