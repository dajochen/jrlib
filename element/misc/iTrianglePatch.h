//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tTrianglePatch.h (Do. Okt. 16 20:04:42 2014)
//------------------------------------------------------------------------

#ifndef ITRIANGLEPATCH_H_
#define ITRIANGLEPATCH_H_

#include "element/tPaintableElement.h"

class iTrianglePatch : public iPaintableElement
{
	public:
		iTrianglePatch(tElement *el);
		virtual ~iTrianglePatch();

		static tString theType(void) {return "TrianglePatch";}
		virtual tString type(void) const {return iTrianglePatch::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iPaintableElement::nProperties()+2;}
		int nInheritedProperties(void) {return iPaintableElement::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

		//Actions:
		virtual int nActions(void) {return iPaintableElement::nActions()+3;}
		int nInheritedActions(void) {return iPaintableElement::nActions();}
		virtual QString getActionName(int index);
		virtual void runAction(int index);

};
#endif /*ITRIANGLEPATCH_H_*/
