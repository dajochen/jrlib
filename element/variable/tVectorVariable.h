/*
 * tVectorVariable.h
 *
 *  Created on: 14.01.2009
 *      Author: Jochen
 */

#ifndef TVECTORVARIABLE_H_
#define TVECTORVARIABLE_H_

#include "tVariable.h"
#include "tVectorOperator.h"
#include "iVectorVariable.h"

class tVectorOperator;

class tVectorVariable : public tVariable {
private:
	tVector fvalue;
	tVectorOperator *op;

	virtual tOperator* oper(void);

public:
	tVectorVariable(tVariableNameSpace *nameSpace, QString function="");
	virtual ~tVectorVariable();
	virtual void refresh(void);
	iElement* intrface(void);

	tVector value(void);
	void setValue(tVector value);

	virtual void setRHS(QString rhs);

  virtual tVariableType type(void){return vtVector;};
};

/*I!
optional value Vector read:value write:setValue
*/

#endif /* TVECTORVARIABLE_H_ */
