//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tStickyMagnet.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef ISTICKYMAGNET_H_
#define ISTICKYMAGNET_H_

#include "tMagnet.h"

class iStickyMagnet : public iMagnet
{
	public:
		iStickyMagnet(tElement *el);
		virtual ~iStickyMagnet();

		static tString theType(void) {return "StickyMagnet";}
		virtual tString type(void) const {return iStickyMagnet::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iMagnet::nProperties()+2;}
		int nInheritedProperties(void) {return iMagnet::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*ISTICKYMAGNET_H_*/
