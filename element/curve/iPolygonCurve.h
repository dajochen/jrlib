//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tPolygonCurve.h (Do. Okt. 16 19:57:19 2014)
//------------------------------------------------------------------------

#ifndef IPOLYGONCURVE_H_
#define IPOLYGONCURVE_H_

#include "tAbstractSpline.h"

class iPolygonCurve : public iAbstractSpline
{
	public:
		iPolygonCurve(tElement *el);
		virtual ~iPolygonCurve();

		static tString theType(void) {return "PolygonCurve";}
		virtual tString type(void) const {return iPolygonCurve::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iAbstractSpline::nProperties()+1;}
		int nInheritedProperties(void) {return iAbstractSpline::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*IPOLYGONCURVE_H_*/
