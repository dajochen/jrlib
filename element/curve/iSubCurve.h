//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tSubCurve.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef ISUBCURVE_H_
#define ISUBCURVE_H_

#include "element/curve/tCurve.h"

class iSubCurve : public iCurve
{
	public:
		iSubCurve(tElement *el);
		virtual ~iSubCurve();

		static tString theType(void) {return "SubCurve";}
		virtual tString type(void) const {return iSubCurve::theType();}

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
#endif /*ISUBCURVE_H_*/
