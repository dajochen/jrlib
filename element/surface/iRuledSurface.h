//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tRuledSurface.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef IRULEDSURFACE_H_
#define IRULEDSURFACE_H_

#include "element/surface/tSurface.h"

class iRuledSurface : public iSurface
{
	public:
		iRuledSurface(tElement *el);
		virtual ~iRuledSurface();

		static tString theType(void) {return "RuledSurface";}
		virtual tString type(void) const {return iRuledSurface::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iSurface::nProperties()+1;}
		int nInheritedProperties(void) {return iSurface::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*IRULEDSURFACE_H_*/
