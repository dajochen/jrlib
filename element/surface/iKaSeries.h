//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tKaSeries.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef IKASERIES_H_
#define IKASERIES_H_

#include "element/surface/tPropSurface.h"

class iKaSeries : public iPropSurface
{
	public:
		iKaSeries(tElement *el);
		virtual ~iKaSeries();

		static tString theType(void) {return "KaSeries";}
		virtual tString type(void) const {return iKaSeries::theType();}

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
#endif /*IKASERIES_H_*/
