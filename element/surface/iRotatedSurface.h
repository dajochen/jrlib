//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tRotatedSurface.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef IROTATEDSURFACE_H_
#define IROTATEDSURFACE_H_

#include "element/surface/tSurface.h"

class iRotatedSurface : public iSurface
{
	public:
		iRotatedSurface(tElement *el);
		virtual ~iRotatedSurface();

		static tString theType(void) {return "RotatedSurface";}
		virtual tString type(void) const {return iRotatedSurface::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iSurface::nProperties()+3;}
		int nInheritedProperties(void) {return iSurface::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*IROTATEDSURFACE_H_*/
