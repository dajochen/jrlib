//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tDrapedPatch.h (Di. Okt. 14 23:53:08 2014)
//------------------------------------------------------------------------

#ifndef IDRAPEDPATCH_H_
#define IDRAPEDPATCH_H_

#include "element/tPaintableElement.h"

class iDrapedPatch : public iPaintableElement
{
	public:
		iDrapedPatch(tElement *el);
		virtual ~iDrapedPatch();

		static tString theType(void) {return "DrapedPatch";}
		virtual tString type(void) const {return iDrapedPatch::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iPaintableElement::nProperties()+5;}
		int nInheritedProperties(void) {return iPaintableElement::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

		//Actions:
		virtual int nActions(void) {return iPaintableElement::nActions()+1;}
		int nInheritedActions(void) {return iPaintableElement::nActions();}
		virtual QString getActionName(int index);
		virtual void runAction(int index);

};
#endif /*IDRAPEDPATCH_H_*/
