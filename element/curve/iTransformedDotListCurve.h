//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tTransformedDotListCurve.h (Fr. Sep. 12 21:28:20 2014)
//------------------------------------------------------------------------

#ifndef ITRANSFORMEDDOTLISTCURVE_H_
#define ITRANSFORMEDDOTLISTCURVE_H_

#include "element/curve/tDotListCurve.h"

class iTransformedDotListCurve : public iDotListCurve
{
	public:
		iTransformedDotListCurve(tElement *el);
		virtual ~iTransformedDotListCurve();

		static tString theType(void) {return "TransformedDotListCurve";}
		virtual tString type(void) const {return iTransformedDotListCurve::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iDotListCurve::nProperties()+4;}
		int nInheritedProperties(void) {return iDotListCurve::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*ITRANSFORMEDDOTLISTCURVE_H_*/
