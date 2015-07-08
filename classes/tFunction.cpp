#include "classes/tFunction.h"

#include <math.h>
#include "classes/utils.h"

tOperation::tOperation(QString str, QHash <QString,tOperation*> *VAR)
{
	QString left,right;
	QList<QString> pm,md,comp,boolean,exponent;
	QStringList strList;
	int pos;
	bool isValid;

	isCalculating = false;
	boolean << "&"; // Boolsche Operatoren
	boolean << "|";
	comp << "=="; // Vergleiche
	comp << "<=";
	comp << ">=";
	comp << "<";
	comp << ">";
	pm << "+"; //plus und minus
	pm << "-";
	md << "*";
	md << "/"; //mal, durch
	exponent << "^"; // hoch

	var = VAR;
	leftHand = NULL;
	rightHand = NULL;
	condition = NULL;

	opType = undefined_;

	value = str.toDouble(&isValid);
	if (isValid){
		// Der String enthaelt eine Zahl
		opType = isValue_;
	} else if(var->contains(str)){
		// Hinter dem String verbirgt sich eine Variable
		name = str;
		opType = isVariable_;
	}	else {
		pos = firstOccurence(boolean,str);
		if (pos>0){
			left = str.left(pos);
			right = str.right(str.length()-pos);
			if (right.startsWith("&")){
				opType = logicalAnd_;
				right.remove(0,1);
			} else if (right.startsWith("|")){
				opType = logicalOr_;
				right.remove(0,1);
			}	else {
				opType = undefined_;
			}
		} else {
			pos = firstOccurence(comp,str);
			if (pos>0){
				left = str.left(pos);
				right = str.right(str.length()-pos);
//				printf((right+"\n").toLatin1().data());
				if (right.startsWith("==")){
					opType = isEqual_;
					right.remove(0,2);
				} else if (right.startsWith("<=")){
					opType = isLessOrEqual_;
					right.remove(0,2);
				} else if (right.startsWith(">=")){
					opType = isGreaterOrEqual_;
					right.remove(0,2);
				} else if (right.startsWith("<")){
					opType = isLess_;
					right.remove(0,1);
				} else if (right.startsWith(">")){
					opType = isGreater_;
					right.remove(0,1);
				} else {
					opType = undefined_; // Sollte nicht vorkommen, sonst Bug.
				}
			} else {
			// Suche nach Plus- und Minuszeichen nur auf der obersten Klammerebene.
				pos = firstOccurence(pm,str);
				if (pos>=0){
					left = str.left(pos);
					if (left.length() == 0){
						left = "0.";
					}
					right = str.right(str.length()-pos-1);
					if (str.at(pos) == '+'){
						opType = plus_;
					} else {
						opType = minus_;
					}
				}	else {
					// Suche nach Mal- "^" und Durchzeichen nur auf der obersten Klammerebene.
					pos = firstOccurence(md,str);
					if (pos>0){
						left = str.left(pos);
						right = str.right(str.length()-pos-1);
						if (str.at(pos) == '*'){
							opType = multiply_;
						} else if (str.at(pos) == '/'){
							opType = divide_;
						} else if (str.at(pos) == '^'){
							opType = power_;
						} else {
							opType = undefined_; // sollte nicht vorkommen, sonst Programmierfehler
						}
					} else {
					// Suche nach "^"; nur auf der obersten Klammerebene.
						pos = firstOccurence(exponent,str);
						if (pos>0){
							left = str.left(pos);
							right = str.right(str.length()-pos-1);
							if (str.at(pos) == '^'){
								opType = power_;
							} else {
								opType = undefined_; // sollte nicht vorkommen, sonst Programmierfehler
							}
						} else if (str.endsWith(')') && ( str.startsWith('(')
										        		   				  ||str.startsWith("cos(")
													 				  				||str.startsWith("sin(")
													 				  				||str.startsWith("tan(")
													 				  				||str.startsWith("asin(")
													 				  				||str.startsWith("acos(")
												   				  				||str.startsWith("atan(")
												   				  				||str.startsWith("atan2(")
												   				  				||str.startsWith("min(")
												   				  				||str.startsWith("max(")
												   				  				||str.startsWith("sqrt(")
												   				  				||str.startsWith("abs(")
												   				  				||str.startsWith("round(")
												   				  				||str.startsWith("ceil(")
												   				  				||str.startsWith("floor(")
												   				  				||str.startsWith("step("))) {
							str.remove(str.length()-1,1);
							if (str.startsWith('(')){
								opType = bracket_;
								str.remove(0,1);
								left = str;
							} else if (str.startsWith("abs(")){
								opType = absolut_;
								str.remove(0,4);
								left = str;
							} else if (str.startsWith("round(")){
								opType = roundIt_;
								str.remove(0,6);
								left = str;
							} else if (str.startsWith("ceil(")){
								opType = ceilIt_;
								str.remove(0,5);
								left = str;
							} else if (str.startsWith("floor(")){
								opType = floorIt_;
								str.remove(0,6);
								left = str;
							} else if (str.startsWith("cos(")){
								opType = cosinus_;
								str.remove(0,4);
								left = str;
							} else if (str.startsWith("sin(")){
								opType = sinus_;
								str.remove(0,4);
								left = str;
							} else if (str.startsWith("tan(")){
								opType = tangens_;
								str.remove(0,4);
								left = str;
							} else if (str.startsWith("asin(")){
								opType = arcsin_;
								str.remove(0,5);
								left = str;
							} else if (str.startsWith("acos(")){
								opType = arccos_;
								str.remove(0,5);
								left = str;
							} else if (str.startsWith("atan(")){
								opType = arctan_;
								str.remove(0,5);
								left = str;
							} else if (str.startsWith("atan2(")){
								opType = arctan2_;
								str.remove(0,6);
								left = str.left(str.indexOf(';'));
								str.remove(0,str.indexOf(';')+1);
								right = str;
							} else if (str.startsWith("min(")){
								opType = minimum_;
								str.remove(0,4);
								left = str.left(str.indexOf(';'));
								str.remove(0,str.indexOf(';')+1);
								right = str;
							} else if (str.startsWith("max(")){
								opType = maximum_;
								str.remove(0,4);
								left = str.left(str.indexOf(';'));
								str.remove(0,str.indexOf(';')+1);
								right = str;
							} else if (str.startsWith("sqrt(")){
								opType = squareroot_;
								str.remove(0,5);
								left = str;
							} else if (str.startsWith("step(")){
								str.remove(0,5);
								strList = str.split(";", QString::SkipEmptyParts);
								if (strList.count() > 2){
									opType = step_;
									condition = new tOperation(strList[0],var);
									left = strList.at(1);
									right = strList.at(2);
								} else {
	  							opType = undefined_;
								}
							} else {
								opType = undefined_; // sollte nicht vorkommenm, ansonsten liegt ein Programmierfehler vor.
							}
						} else {
							name = str;
							value = 0;
							opType = undefined_;
// !!!!							opType = unknownVar;
						}
					}
				}
			}
		}
		if (opType != undefined_){
			if (!left.isEmpty()) leftHand = new tOperation(left,var);
			if (!right.isEmpty()) rightHand = new tOperation(right,var);
		}
	}
}
//--------------------------------------------------------------

tOperation::~tOperation(void)
{
	if (leftHand) delete leftHand;
	if (rightHand) delete rightHand;
	if (condition) delete condition;
}
//--------------------------------------------------------------

int tOperation::firstOccurence(QList<QString> e, QString s)
{
	int i,pos,nBrackets;
	bool isStarting;

	QString str;
	pos = s.length()-1;
	str = s;
	isStarting = false;
	while (!isStarting && !str.isEmpty()){
		if (str.at(pos) == ')'){
			nBrackets = 1;
			str.remove(pos,1);
			pos--;
			while (nBrackets != 0 && !str.isEmpty()){
				if (str.at(pos) == ')') nBrackets++;
				else if (str.at(pos) == '(') nBrackets--;
  			str.remove(pos,1);
				pos--;
			}
		}
	  if (!str.isEmpty()){
			if (str.at(pos)== '('){
					return -1; // Der Term ist nicht g�ltig. Es wurde eine Klammer zuviel wurde geoeffnet.
			} else {
				for (i=0;i<e.count() && !isStarting;i++){
					isStarting = str.endsWith(e.at(i));
				}
				i--;
				if (isStarting){
					return pos-(e.at(i).length()-1);
				} else {
					str.remove(pos,1);
					pos--;
				}
			}
	  }
	}
	return -1;
}

//--------------------------------------------------------------
/*
int tOperation::firstOccurence(QList<QString> e, QString s)
{
	int i,pos,nBrackets;
	bool isStarting;

	QString str;
	pos = 0;
	str = s;
	isStarting = false;
	while (!isStarting && !str.isEmpty()){
		if (str.at(0) == '('){
			nBrackets = 1;
			str.remove(0,1);
			pos++;
			while (nBrackets != 0 && !str.isEmpty()){
				if (str.at(0) == '(') nBrackets++;
				else if (str.at(0) == ')') nBrackets--;
  			str.remove(0,1);
				pos++;
			}
		}
	  if (!str.isEmpty()){
			if (str.at(0)== ')'){
					return -1; // Der Term ist nicht g�ltig. Eine Klammer zuviel wurde geschlossen.
			} else {
				for (i=0;i<e.count() && !isStarting;i++){
					isStarting = str.startsWith(e.at(i));
				}
				if (isStarting){
					return pos;
				} else {
					str.remove(0,1);
					pos++;
				}
			}
	  }
	}
	return -1;
}
*/
//--------------------------------------------------------------
/*
int tOperation::firstOccurence(QSet<QString> e, QString s)
{
	int i,length,nBrackets;

	length = s.length();
	for (i=0;i<length;i++){
		if (s.at(i) == '('){
			nBrackets = 1;
			for (i=i+1;i<length && nBrackets != 0;i++){
				if (s.at(i) == '(') nBrackets++;
				else if (s.at(i) == ')') nBrackets--;
			}
		}
		if (i<length) {
		  if (e.contains(s.at(i))){
				return i;
		  }	else if (s.at(i) == ')'){
				return -1; // Der Term ist nicht g�ltig. Eine Klammer zuviel wurde geschlossen.
			}
		}
	}
	return -1;
}
//--------------------------------------------------------------
*/
double tOperation::calc(bool *isValid=NULL,double defaultValue=0.)
{
	tOperation *o;
	double l,r;
	bool lValid,rValid,condValid;

  if (isCalculating){
  	// Das Element wurde durch Rekurion von sich slebst aufgerufen. Die Rekusrion muss hier abgebrochen werden.
    if (isValid) *isValid = false;
  	isCalculating = false;
  	return defaultValue;
  } else {
	  if (isValid) *isValid = true;
  	isCalculating = true;
  }

	if (opType == isValue_){
		// Die Rekursion hat nun ein erfolgreiches Ende.
		isCalculating = false;
		return value;
	}	else if (opType == isVariable_){
		// Der Inhalt der Variable kann zur�ck gegeben werden
		o = var->value(name);
		r = o->calc(isValid,defaultValue);
		isCalculating = false;
		return r;
	} else if (opType == step_){
		if (condition->calc(&condValid,defaultValue) != 0 && condValid){
			if (leftHand)	r = leftHand->calc(isValid,defaultValue); else r = defaultValue;
		} else {
			if (condValid){
				if (rightHand) r = rightHand->calc(isValid,defaultValue); else r = defaultValue;
			} else {
				if (isValid) *isValid = false;
				r = defaultValue;
			}
		}
		isCalculating = false;
		return r;
	} else {
		if (leftHand)	l = leftHand->calc(&lValid,defaultValue); else l = defaultValue;
		if (rightHand) r = rightHand->calc(&rValid,defaultValue); else r = defaultValue;
		isCalculating = false;
		if (isValid) *isValid = true;
		if (lValid && leftHand){
			if (opType == bracket_){
				return l;
			} else if (opType == sinus_){
				return sin(l);
			} else if (opType == cosinus_){
				return cos(l);
			} else if (opType == tangens_){
				return tan(l);
			} else if (opType == arcsin_){
				return acos(l);
			} else if (opType == arccos_){
				return asin(l);
			} else if (opType == arctan_){
				return atan(l);
			} else if (opType == squareroot_){
				return sqrt(l);
			} else if (opType == absolut_){
				return fabs(l);
			} else if (opType == roundIt_){
				return round(l);
			} else if (opType == ceilIt_){
				return ceil(l);
			} else if (opType == floorIt_){
				return floor(l);
			} else if (rValid && rightHand){
				if (opType == plus_){
					return l+r;
				} else if (opType == minus_){
					return l-r;
				} else if (opType == multiply_){
					return l*r;
				} else if (opType == divide_ && r != 0){
					return l/r;
				} else if (opType == power_){
					return pow(l,r);
				} else if (opType == arctan2_){
					return atan2(l,r);
				} else if (opType == minimum_){
					return min(l,r);
				} else if (opType == maximum_){
					return max(l,r);
				} else if (opType == isEqual_){
					if (l==r)
					  return 1.0;
					else
						return 0.0;
				} else if (opType == isLess_){
					if (l<r)
					  return 1.0;
					else
						return 0.0;
				} else if (opType == isGreater_){
					if (l>r)
					  return 1.0;
					else
						return 0.0;
				} else if (opType == isLessOrEqual_){
					if (l<=r)
					  return 1.0;
					else
						return 0.0;
				} else if (opType == isGreaterOrEqual_){
					if (l>=r)
					  return 1.0;
					else
						return 0.0;
				} else if (opType == logicalAnd_){
					if (l!= 0 && r != 0)
					  return 1.0;
					else
						return 0.0;
				} else if (opType == logicalOr_){
					if (l!= 0 || r != 0)
					  return 1.0;
					else
						return 0.0;
				}
			}
		}
	}
		// ein Operand hat einen ung�ltigen Wert angenommen (Bsp: Division durch Null)
  	// oder bei der Berechnung einer der Operanden trat eine unzul�ssige Operation auf.
	if (isValid) *isValid = false;
  isCalculating = false;
	return defaultValue;
}

QString tOperation::toString(QStringList *usedVars=NULL){

	QString l,r,defaultValue,result;

  defaultValue = "*error*";

  if (isCalculating){
  	// Das Element wurde durch Rekurion von sich slebst aufgerufen. Die Rekusrion muss hier abgebrochen werden.
  	isCalculating = false;
  	return "Infinite Rekursion!";
  } else {
  	isCalculating = true;
  }

	if (opType == isValue_){
		// Die Rekursion hat nun ein erfolgreiches Ende.
		isCalculating = false;
		return QString::number(value);
	}	else if (opType == isVariable_){
		// Der Inhalt der Variable kann zur�ck gegeben werden
		r = name;
		if (usedVars){
			if (var->contains(name)){
				if (usedVars->contains(name)){
					// Variable ist bekannt, sie soll aber nun an den Anfang gestellt werden.
					usedVars->removeAll(name);
				} else {
					// Variable ist unbekannt, es wird gepr�ft, ob sie auf weiteren unbekannten variablen basiert.

				}
				usedVars->prepend(name);
			}
		}
//		o = var->value(name);
//		r = o->toString();;
		isCalculating = false;
		return r;
	} else if (opType == step_){
		result = "step(" + condition->toString(usedVars) + ";" + leftHand->toString(usedVars) + ";" + rightHand->toString(usedVars) + ")";
		isCalculating = false;
		return result ;
	} else {
//		if (leftHand)	l = leftHand->calc(&lValid,defaultValue); else l = defaultValue;
//		if (rightHand) r = rightHand->calc(&rValid,defaultValue); else r = defaultValue;
		if (leftHand)	l = leftHand->toString(usedVars);//calc(&lValid,defaultValue); else l = defaultValue;
		if (rightHand) r = rightHand->toString(usedVars);//calc(&rValid,defaultValue); else r = defaultValue;
		isCalculating = false;
//		if (lValid && leftHand){
		if (leftHand){
			if (opType == bracket_){
				return l;
			} else if (opType == sinus_){
				result = "sin(" + l + ")";
				return result;
			} else if (opType == cosinus_){
				result = "cos(" + l + ")";
				return result;
			} else if (opType == tangens_){
				result = "tan(" + l + ")";
				return result;
			} else if (opType == arcsin_){
				result = "acos(" + l + ")";
				return result;
			} else if (opType == arccos_){
				result = "asin(" + l + ")";
				return result;
			} else if (opType == arctan_){
				result = "atan(" + l + ")";
				return result;
			} else if (opType == squareroot_){
				result = "sqrt(" + l + ")";
				return result;
			} else if (opType == absolut_){
				result = "fabs(" + l + ")";
				return result;
			} else if (opType == roundIt_){
				result = "round(" + l + ")";
				return result;
			} else if (opType == ceilIt_){
				result = "ceil(" + l + ")";
				return result;
			} else if (opType == floorIt_){
				result = "floor(" + l + ")";
				return result;
			} else if (rightHand){
				if (opType == plus_){
					result = l + "+" + r;
					return result;
				} else if (opType == minus_){
					result = l + "-" + r;
					return result;
				} else if (opType == multiply_){
					result = l + "*" + r;
					return result;
				} else if (opType == divide_ && r != 0){
					result = l + "/" + r;
					return result;
				} else if (opType == power_){
					result = l + "^" + r;
					return result;
				} else if (opType == arctan2_){
					result = "atan2(" + l + ";" + r + ")";
					return result;
				} else if (opType == minimum_){
					result = "min(" + l + ";" + r + ")";
					return result;
				} else if (opType == maximum_){
					result = "max(" + l + ";" + r + ")";
					return result;
				} else if (opType == isEqual_){
					result = l + "==" + r;
					return result;
				} else if (opType == isLess_){
					result = l + "<" + r;
					return result;
				} else if (opType == isGreater_){
					result = l + ">" + r;
					return result;
				} else if (opType == isLessOrEqual_){
					result = l + "<=" + r;
					return result;
				} else if (opType == isGreaterOrEqual_){
					result = l + ">=" + r;
					return result;
				} else if (opType == logicalAnd_){
					result = l + "&&" + r;
					return result;
				} else if (opType == logicalOr_){
					result = l + "||" + r;
					return result;
				}
			}
		}
	}
	// ein Operand hat einen ung�ltigen Wert angenommen (Bsp: Division durch Null)
  // oder bei der Berechnung einer der Operanden trat eine unzul�ssige Operation auf.
  isCalculating = false;
	return defaultValue;

}

//--------------------------------------------------------------
//--------------------------------------------------------------


tFunction::tFunction()
{
}
//--------------------------------------------------------------

tFunction::tFunction(QString func)
{
	setFunc(func);
}
//--------------------------------------------------------------

tFunction::~tFunction()
{
  QHash<QString, tOperation*>::const_iterator i = var.constBegin();
  while (i != var.constEnd()) {
    delete i.value();
    ++i;
  }
}
//--------------------------------------------------------------

float tFunction::calc(QString func, bool *isValid, double defaultValue)
{
	tOperation *o;
	double result;
//	printf(("Calculating: "+ func+ "...").toLatin1().data());
	if (var.contains(func)){
		o = var.value(func);
		result = o->calc(isValid, defaultValue);
//		printf(("to: "+ QString::number(result)+"\n").toLatin1().data());
		return result;
	} else {
		func.remove(" ");
	  o = new tOperation(func,&var);
	  result = o->calc(isValid, defaultValue);
	  delete o;
		return result;
	}
}
//--------------------------------------------------------------

void tFunction::setFunc(QString func)
{
	int pos;
	double result;
	tOperation *o,*h;
	QString name;

	func.remove(" ");

	pos = func.indexOf(":=");
	if (pos > 0){
  	name = func.left(pos);
	  func = func.right(func.length()-pos-2);
	  h = new tOperation(func,&var);
	  result = h->calc();
	  o = new tOperation(QString::number(result),&var);
	  delete h;

	  if (var.contains(name)){
	    delete var.value(name);
	  	var.remove(name);
	  }
	  var.insert(name,o);
	} else {
		pos = func.indexOf("=");
		if (pos>0){
			name = func.left(pos);

			func = func.right(func.length()-pos-1);
			if (func.length() > 0){
				o = new tOperation(func,&var);
				if (var.contains(name)){
					delete var.value(name);
					var.remove(name);
				}
				var.insert(name,o);
			}
		}
	}
}
//--------------------------------------------------------------

QStringList tFunction::toStringList(QString func){
	QString result;
	QStringList usedVars;

	result = func;
	tOperation *o;

	if (var.contains(func)){
		o = var.value(func);
		if (o->getOpType() == isValue_){
			result = func + ":=" + o->toString();
		} else {
			result = func + "=" + o->toString(&usedVars);
		}
	} else {
		result = func;
	}

	usedVars << result;
	return usedVars;
}

