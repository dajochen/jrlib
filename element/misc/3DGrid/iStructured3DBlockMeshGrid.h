//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tStructured3DBlockMeshGrid.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef ISTRUCTURED3DBLOCKMESHGRID_H_
#define ISTRUCTURED3DBLOCKMESHGRID_H_

#include "element/misc/3DGrid/tStructured3DGrid.h"

class iStructured3DBlockMeshGrid : public iStructured3DGrid
{
	public:
		iStructured3DBlockMeshGrid(tElement *el);
		virtual ~iStructured3DBlockMeshGrid();

		static tString theType(void) {return "Structured3DBlockMeshGrid";}
		virtual tString type(void) const {return iStructured3DBlockMeshGrid::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iStructured3DGrid::nProperties()+6;}
		int nInheritedProperties(void) {return iStructured3DGrid::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*ISTRUCTURED3DBLOCKMESHGRID_H_*/
