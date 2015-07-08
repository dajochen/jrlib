//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tWageningenBSeries.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef IWAGENINGENBSERIES_H_
#define IWAGENINGENBSERIES_H_

#include "element/surface/tPropSurface.h"

class iWageningenBSeries : public iPropSurface
{
	public:
		iWageningenBSeries(tElement *el);
		virtual ~iWageningenBSeries();

		static tString theType(void) {return "WageningenBSeries";}
		virtual tString type(void) const {return iWageningenBSeries::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iPropSurface::nProperties()+2;}
		int nInheritedProperties(void) {return iPropSurface::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*IWAGENINGENBSERIES_H_*/
