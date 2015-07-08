//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tThreePointPlane.h (Mi. Jan. 29 20:51:14 2014)
//------------------------------------------------------------------------

#ifndef ITHREEPOINTPLANE_H_
#define ITHREEPOINTPLANE_H_

#include "tBasicPlane.h"

class iThreePointPlane : public iBasicPlane
{
	public:
		iThreePointPlane(tElement *el);
		virtual ~iThreePointPlane();

		static tString theType(void) {return "ThreePointPlane";}
		virtual tString type(void) const {return iThreePointPlane::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iBasicPlane::nProperties()+3;}
		int nInheritedProperties(void) {return iBasicPlane::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*ITHREEPOINTPLANE_H_*/
