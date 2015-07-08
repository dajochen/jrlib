//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tStructured3DGrid.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef ISTRUCTURED3DGRID_H_
#define ISTRUCTURED3DGRID_H_

#include "element/misc/tStructuredAbstractGrid.h"

class iStructured3DGrid : public iStructuredAbstractGrid
{
	public:
		iStructured3DGrid(tElement *el);
		virtual ~iStructured3DGrid();

		static tString theType(void) {return "Structured3DGrid";}
		virtual tString type(void) const {return iStructured3DGrid::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iStructuredAbstractGrid::nProperties()+4;}
		int nInheritedProperties(void) {return iStructuredAbstractGrid::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*ISTRUCTURED3DGRID_H_*/
