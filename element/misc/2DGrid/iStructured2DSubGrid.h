//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tStructured2DSubGrid.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef ISTRUCTURED2DSUBGRID_H_
#define ISTRUCTURED2DSUBGRID_H_

#include "element/misc/2DGrid/tStructured2DGrid.h"

class iStructured2DSubGrid : public iStructured2DGrid
{
	public:
		iStructured2DSubGrid(tElement *el);
		virtual ~iStructured2DSubGrid();

		static tString theType(void) {return "Structured2DSubGrid";}
		virtual tString type(void) const {return iStructured2DSubGrid::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iStructured2DGrid::nProperties()+9;}
		int nInheritedProperties(void) {return iStructured2DGrid::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*ISTRUCTURED2DSUBGRID_H_*/
