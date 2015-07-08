//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tPropSurface.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef IPROPSURFACE_H_
#define IPROPSURFACE_H_

#include "element/surface/tSurface.h"

class iPropSurface : public iSurface
{
	public:
		iPropSurface(tElement *el);
		virtual ~iPropSurface();

		static tString theType(void) {return "PropSurface";}
		virtual tString type(void) const {return iPropSurface::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iSurface::nProperties()+18;}
		int nInheritedProperties(void) {return iSurface::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*IPROPSURFACE_H_*/
