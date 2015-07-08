/*
 * tRealOperator.h
 *
 *  Created on: 25.08.2009
 *      Author: Jochen
 */

#ifndef TREALOPERATOR_H_
#define TREALOPERATOR_H_

#include "tOperator.h"
#include "element/variable/tRealVariable.h"
#include "iRealOperator.h"

enum tRealOperatorType{ // ohne weitere Argumente
                        rotInvalid, rotIsVariable, rotIsValue,
                        // benoetigt ein Argument
                        rotBracket,
                        rotSinus, rotCosinus, rotTangens, rotArccos, rotArcsin, rotArctan,
                        rotSquareroot, rotAbsolut, rotRoundIt, rotCeilIt, rotFloorIt,
                        // benoetigt zwei Argumente
                        rotPlus, rotMinus, rotMultiply, rotDivide, rotModulo, rotPower,
                        rotArctan2,
                        rotIsEqual, rotIsLess, rotIsLessOrEqual, rotIsGreater, rotIsGreaterOrEqual, rotLogicalAnd, rotLogicalOr,
                        // benoetigt drei Argumente
                        rotStep,
                        // beliebig viele Argumente
                        rotMinimum, rotMaximum
                      };

class tRealVariable;

class tRealOperator : public tOperator {
private:
	tReal fvalue;
  tRealVariable *variable;
  tRealOperatorType opType;

  tReal toValue(QString term, bool *ok);
  virtual void clear(void);

public:
	tRealOperator(tElement *theowner);
	virtual ~tRealOperator();

	virtual void refresh(void);
	iElement* intrface(void);

	virtual tReal value(void);
  virtual void setValue(tReal v);

  virtual void init(QString term, tVariableNameSpace* nameSpace);
	virtual QString toString(void);

  tVariableType type(void){return vtReal;};
	virtual bool isValidOperator(void);
};
/*I!
*/


#endif /* TREALOPERATOR_H_ */
