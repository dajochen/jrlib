//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tMagnet.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef IMAGNET_H_
#define IMAGNET_H_

#include "element/point/tDot.h"

class iMagnet : public iDot
{
	public:
		iMagnet(tElement *el);
		virtual ~iMagnet();

		static tString theType(void) {return "Magnet";}
		virtual tString type(void) const {return iMagnet::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iDot::nProperties()+3;}
		int nInheritedProperties(void) {return iDot::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*IMAGNET_H_*/
