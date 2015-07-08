//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tGroup.h (Do. Sep. 25 23:02:24 2014)
//------------------------------------------------------------------------

#ifndef IGROUP_H_
#define IGROUP_H_

#include "element/tElement.h"

class iGroup : public iElement
{
	public:
		iGroup(tElement *el);
		virtual ~iGroup();

		static tString theType(void) {return "Group";}
		virtual tString type(void) const {return iGroup::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iElement::nProperties()+2;}
		int nInheritedProperties(void) {return iElement::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*IGROUP_H_*/
