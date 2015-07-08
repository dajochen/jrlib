/*
 * tVectorOperator.h
 *
 *  Created on: 25.08.2009
 *      Author: Jochen
 */

#ifndef TVECTOROPERATOR_H_
#define TVECTOROPERATOR_H_

#include "tOperator.h"
#include "element/variable/tVectorVariable.h"
#include "iVectorOperator.h"

enum tVectorOperatorType{ // ohne weitere Argumente
													votInvalid, votIsVariable,
													// benoetigt ein Argument
													votBracket,
													// benoetigt zwei Argumente
													votPlus, votMinus, votProduct, votCrossProduct,
													// benoetigt drei Argumente
													votStep, votIsValue
												};
class tVectorVariable;

class tVectorOperator : public tOperator{
private:
	tVector fvalue;
  tVectorVariable *variable;
  tVectorOperatorType opType;

  virtual void clear(void);

public:
	tVectorOperator(tElement *theowner);
	virtual ~tVectorOperator();

	virtual void refresh(void);
	iElement* intrface(void);

  void init(QString term, tVariableNameSpace* nameSpace);
	QString toString(void);

	tVector value(void);
  void setValue(tVector v);

	tVariableType type(void){return vtVector;};
	virtual bool isValidOperator(void);
};
/*I!
*/

#endif /* TVECTOROPERATOR_H_ */
