//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tPropHubSurface.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef IPROPHUBSURFACE_H_
#define IPROPHUBSURFACE_H_

#include "element/surface/tSurface.h"

class iPropHubSurface : public iSurface
{
	public:
		iPropHubSurface(tElement *el);
		virtual ~iPropHubSurface();

		static tString theType(void) {return "PropHubSurface";}
		virtual tString type(void) const {return iPropHubSurface::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iSurface::nProperties()+6;}
		int nInheritedProperties(void) {return iSurface::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*IPROPHUBSURFACE_H_*/
