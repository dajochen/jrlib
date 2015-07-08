/*
 * tListOperator.h
 *
 *  Created on: 25.08.2009
 *      Author: Jochen
 */

#ifndef TLISTOPERATOR_H_
#define TLISTOPERATOR_H_

#include "tOperator.h"
#include "element/variable/tListVariable.h"
#include "iListOperator.h"

enum tListOperatorType{ // ohne weitere Argumente
                        lotInvalid, lotIsVariable, lotIsList
                      };

class tListVariable;

class tListOperator : public tOperator {
private:
  tVariableNameSpace *localNS;
  tListVariable *variable;
  tList<tVariable*> element;
  tListOperatorType opType;
  virtual void clear(void);

public:
  tListOperator(tElement *theowner);
  virtual ~tListOperator();

  virtual void refresh(void);
  iElement* intrface(void);

  void init(QString term, tVariableNameSpace* nameSpace);
  QString toString(void);

  tVariableType type(void){return vtList;};
  virtual bool isValidOperator(void);

  bool isRealOnly(void);
  tReal minimum(void);
  tReal maximum(void);
  void appendItem(QString itemName, tVariableNameSpace* nameSpace);
};
/*I!
*/


#endif /* TLISTOPERATOR_H_ */
