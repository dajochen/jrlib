//------------------------------------------------------------------------
//Automically generated interface class
//generated from tStructured2DSurfaceGrid.h (Fr. Mär 30 10:52:42 2012)
//------------------------------------------------------------------------
#ifndef ISTRUCTURED2DSURFACEGRID_H_
#define ISTRUCTURED2DSURFACEGRID_H_

#include "iStructured2DGrid.h"

class iStructured2DSurfaceGrid : public iStructured2DGrid
{
	public:
		iStructured2DSurfaceGrid(tElement *el);
		virtual ~iStructured2DSurfaceGrid();

		static tString theType(void) {return "Structured2DSurfaceGrid";};
		virtual tString type(void) const {return iStructured2DSurfaceGrid::theType();};

		virtual tString getPropertyName(unsigned int index);
		virtual tString getPropertyType(unsigned int index);
		virtual bool getPropertyValue(unsigned int index, tString type, void* value);
		virtual bool isReadOnly(unsigned int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual unsigned int nProperties(void) {return iStructured2DGrid::nProperties()+9;};
		unsigned int nInheritedProperties(void) {return iStructured2DGrid::nProperties();};
		virtual bool setPropertyValue(unsigned int index, tString type, void* value);
};
#endif /*ISTRUCTURED2DSURFACEGRID_H_*/
