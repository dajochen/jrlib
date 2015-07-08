//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tConnectiveModel.h (Mi. Jul 3 23:41:04 2013)
//------------------------------------------------------------------------

#ifndef ICONNECTIVEMODEL_H_
#define ICONNECTIVEMODEL_H_

#include "model/tModel.h"

class iConnectiveModel : public iModel
{
	public:
		iConnectiveModel(tElement *el):iModel(el){};

		static tString theType(void) {return "ConnectiveModel";}
		virtual tString type(void) const {return iConnectiveModel::theType();}

		virtual bool getPropertyValue(unsigned int index, tString propType, void* value){
			if (index == 0 && propType == "String"){
			*(tString*)value =iConnectiveModel::theType();
				return true;
			} else {
				return iModel::getPropertyValue(index,propType,value);
			}
		}
		virtual QStringList inheritedTypes(void){
			return (iModel::inheritedTypes() << theType());
		}
		virtual bool isOfType(QString thetype){
			if (theType() == thetype) {
				return true;
			} else {
				return iModel::isOfType(thetype);
			}
		}
};
#endif /*ICONNECTIVEMODEL_H_*/
