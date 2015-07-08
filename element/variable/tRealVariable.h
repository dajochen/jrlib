/*
 * tRealVariable.h
 *
 *  Created on: 14.01.2009
 *      Author: Jochen
 */

#ifndef TREALVARIABLE_H_
#define TREALVARIABLE_H_

#include "tVariable.h"
#include "tRealOperator.h"
#include "iRealVariable.h"

class tRealOperator;

class tRealVariable : public tVariable {
private:
	tReal fvalue;
	tRealOperator *op;

	virtual tOperator* oper(void);

public:
	tRealVariable(tVariableNameSpace *nameSpace, QString function="");
	virtual ~tRealVariable();

	virtual void refresh(void);
	iElement* intrface(void);

	tReal value(void);
	void setValue(tReal value);

	virtual void setRHS(QString rhs);

  virtual tVariableType type(void){return vtReal;};

};

/*I!
optional value Real read:value write:setValue
*/

#endif /* TREALVARIABLE_H_ */
