//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tBasicPlane.h (Mi. Jan. 29 20:14:48 2014)
//------------------------------------------------------------------------

#ifndef IBASICPLANE_H_
#define IBASICPLANE_H_

#include "element/tElement.h"

class iBasicPlane : public iElement
{
	public:
		iBasicPlane(tElement *el);
		virtual ~iBasicPlane();

		static tString theType(void) {return "BasicPlane";}
		virtual tString type(void) const {return iBasicPlane::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iElement::nProperties()+3;}
		int nInheritedProperties(void) {return iElement::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*IBASICPLANE_H_*/
