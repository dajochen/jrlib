//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tDotListCurve.h (Sa. Okt. 4 13:40:59 2014)
//------------------------------------------------------------------------

#ifndef IDOTLISTCURVE_H_
#define IDOTLISTCURVE_H_

#include "element/curve/tCurve.h"

class iDotListCurve : public iCurve
{
	public:
		iDotListCurve(tElement *el);
		virtual ~iDotListCurve();

		static tString theType(void) {return "DotListCurve";}
		virtual tString type(void) const {return iDotListCurve::theType();}

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
#endif /*IDOTLISTCURVE_H_*/
