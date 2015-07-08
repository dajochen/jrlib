//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tDistortedSpline.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef IDISTORTEDSPLINE_H_
#define IDISTORTEDSPLINE_H_

#include "element/curve/tDotListCurve.h"

class iDistortedSpline : public iDotListCurve
{
	public:
		iDistortedSpline(tElement *el);
		virtual ~iDistortedSpline();

		static tString theType(void) {return "DistortedSpline";}
		virtual tString type(void) const {return iDistortedSpline::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iDotListCurve::nProperties()+3;}
		int nInheritedProperties(void) {return iDotListCurve::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*IDISTORTEDSPLINE_H_*/
