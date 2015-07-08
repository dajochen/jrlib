//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tDuct19A.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef IDUCT19A_H_
#define IDUCT19A_H_

#include "element/surface/tSurface.h"

class iDuct19A : public iSurface
{
	public:
		iDuct19A(tElement *el);
		virtual ~iDuct19A();

		static tString theType(void) {return "Duct19A";}
		virtual tString type(void) const {return iDuct19A::theType();}

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
#endif /*IDUCT19A_H_*/
