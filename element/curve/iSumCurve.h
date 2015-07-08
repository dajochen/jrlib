//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tSumCurve.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef ISUMCURVE_H_
#define ISUMCURVE_H_

#include "element/curve/tCurve.h"

class iSumCurve : public iCurve
{
	public:
		iSumCurve(tElement *el);
		virtual ~iSumCurve();

		static tString theType(void) {return "SumCurve";}
		virtual tString type(void) const {return iSumCurve::theType();}

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
#endif /*ISUMCURVE_H_*/
