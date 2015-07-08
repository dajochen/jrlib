/*
 * tOperator.h
 *
 *  Created on: 07.01.2009
 *      Author: Jochen
 */

#ifndef TOPERATOR_H_
#define TOPERATOR_H_

enum tVariableType{ vtReal, vtVector, vtList };

#include <QString>

#include "element/tElement.h"
#include "element/variable/tVariableNameSpace.h"
#include "iOperator.h"

class tVariable;
class tVariableNameSpace;

class tOperator : public tElement {
private:

  QString reverseString(QString s);

protected:
  tList<tOperator*> arg;
  virtual void clear(void)=0;
  int startsWith(QStringList e, QString s);
  int firstOccurence(QStringList e, QString s);

public:
	tOperator(tElement *theowner);
	virtual ~tOperator();
	virtual void refresh(void)=0;
	iElement* intrface(void);

  virtual void init(QString term, tVariableNameSpace* nameSpace) = 0;
	virtual QString toString(void)=0;

	virtual tVariableType type(void)=0;
	virtual bool isValidOperator(void)=0;
};

/*I!
*/


#endif /* TOPERATOR_H_ */
