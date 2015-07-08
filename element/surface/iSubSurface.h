//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tSubSurface.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef ISUBSURFACE_H_
#define ISUBSURFACE_H_

#include "element/surface/tSurface.h"

class iSubSurface : public iSurface
{
	public:
		iSubSurface(tElement *el);
		virtual ~iSubSurface();

		static tString theType(void) {return "SubSurface";}
		virtual tString type(void) const {return iSubSurface::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iSurface::nProperties()+2;}
		int nInheritedProperties(void) {return iSurface::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*ISUBSURFACE_H_*/
