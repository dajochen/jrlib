//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tStructured2DGrid.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef ISTRUCTURED2DGRID_H_
#define ISTRUCTURED2DGRID_H_

#include "element/misc/tStructuredAbstractGrid.h"

class iStructured2DGrid : public iStructuredAbstractGrid
{
	public:
		iStructured2DGrid(tElement *el);
		virtual ~iStructured2DGrid();

		static tString theType(void) {return "Structured2DGrid";}
		virtual tString type(void) const {return iStructured2DGrid::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iStructuredAbstractGrid::nProperties()+1;}
		int nInheritedProperties(void) {return iStructuredAbstractGrid::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*ISTRUCTURED2DGRID_H_*/
