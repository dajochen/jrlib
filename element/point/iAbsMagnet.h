//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tAbsMagnet.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef IABSMAGNET_H_
#define IABSMAGNET_H_

#include "element/point/tDot.h"

class iAbsMagnet : public iDot
{
	public:
		iAbsMagnet(tElement *el);
		virtual ~iAbsMagnet();

		static tString theType(void) {return "AbsMagnet";}
		virtual tString type(void) const {return iAbsMagnet::theType();}

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
#endif /*IABSMAGNET_H_*/
