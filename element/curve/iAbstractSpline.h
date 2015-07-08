//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tAbstractSpline.h (Di. Okt. 7 22:08:28 2014)
//------------------------------------------------------------------------

#ifndef IABSTRACTSPLINE_H_
#define IABSTRACTSPLINE_H_

#include "element/curve/tDotListCurve.h"

class iAbstractSpline : public iDotListCurve
{
	public:
		iAbstractSpline(tElement *el);
		virtual ~iAbstractSpline();

		static tString theType(void) {return "AbstractSpline";}
		virtual tString type(void) const {return iAbstractSpline::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iDotListCurve::nProperties()+1;}
		int nInheritedProperties(void) {return iDotListCurve::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*IABSTRACTSPLINE_H_*/
