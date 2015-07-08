#ifndef TFUNCTION_H_
#define TFUNCTION_H_

#include <QString>
#include <QStringList>
#include <QHash>

enum tOperationType{isVariable_,isValue_,undefined_,bracket_,
										plus_,minus_,multiply_,divide_,power_,
										sinus_,cosinus_,tangens_,arccos_,arcsin_,arctan_,
										arctan2_,minimum_,maximum_,
										step_,absolut_,roundIt_,ceilIt_,floorIt_,
										isEqual_,isLess_,isLessOrEqual_,isGreater_,isGreaterOrEqual_,
										logicalAnd_,logicalOr_,
										squareroot_};

class tOperation
{
	private:
		tOperationType opType;
	  QHash<QString, tOperation*> *var;
	  double value;
	  QString name;
	  tOperation *leftHand,*rightHand,*condition;
	  bool isCalculating;// W�hrend das Element ausgwertet wird, wird die Variable auf true gesetzt. Hiermit k�nnen Rekursionen �berpr�ft und abgebrochen werden.

	  int firstOccurence(QList<QString> e, QString s);

	public:
	  tOperation(QString str, QHash<QString,tOperation*> *VAR);
	  ~tOperation(void);
	  double calc(bool *isValid,double defaultValue);
	  QString toString(QStringList *usedVars);
	  tOperationType getOpType(void) {return opType;};
};

class tFunction
{
private:
	QHash <QString,tOperation*> var;

public:
	tFunction();
	tFunction(QString func);
	virtual ~tFunction();

	float calc(QString func, bool *isValid=NULL, double defaultValue = 0.);
	void setFunc(QString func);
	bool isFunc(QString func){return var.contains(func);};

	QStringList toStringList(QString func);
};

#endif /*TFUNCTION_H_*/
