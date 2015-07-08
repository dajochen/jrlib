/*
 * tVariable.h
 *
 *  Created on: 07.01.2009
 *      Author: Jochen
 */

#ifndef TVARIABLE_H_
#define TVARIABLE_H_

#include <QString>
#include "element/tElement.h"
#include "element/variable/tVariableNameSpace.h"

#include "tOperator.h"

#include "iVariable.h"

class tOperator;
class tVariableNameSpace;

class tVariable : public tElement
{

protected:
//	QString fname;
	tVariableNameSpace *fnameSpace;

	virtual tOperator* oper(void)=0;

public:
	tVariable(tVariableNameSpace *nameSpace);
	virtual ~tVariable();

	virtual void refresh(void)=0;
	iElement* intrface(void);

	virtual tVariableType type(void) = 0;
	virtual bool isValidVariable(void);

	virtual QString name(void);
	virtual void setName(QString name);

	virtual QString RHS(void);
	virtual void setRHS(QString rhs)=0;

	virtual QString fullString(void);
	virtual void setFullString(QString function);
};

/*I!
variableType Int read:type
optional isValid Bool read:isValidVariable
optional fullString String read:fullString write:setFullString
RHS String read:RHS write:setRHS
*/

#endif /* TVARIABLE_H_ */
