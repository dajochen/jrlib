/*
 * tListVariable.h
 *
 *  Created on: 25.08.2009
 *      Author: Jochen
 */

#ifndef TLISTVARIABLE_H_
#define TLISTVARIABLE_H_

#include "tVariable.h"
#include "tListOperator.h"
#include "iListVariable.h"
#include "classes/tList.h"

class tListOperator;

class tListVariable : public tVariable{
private:
  tListOperator *op;

  virtual tOperator* oper(void);

public:
  tListVariable(tVariableNameSpace *nameSpace, QString function="");
  virtual ~tListVariable();

  virtual void refresh(void);
  iElement* intrface(void);

  virtual void setRHS(QString rhs);

  virtual tVariableType type(void){return vtList;};

  virtual void appendItem(QString itemName);
  bool isRealOnly(void);
  tReal minimum(void);
  tReal maximum(void);
};
/*I!
*/

#endif /* TLISTVARIABLE_H_ */
