#include "element/curve/tFunctionCurve.h"

tFunctionCurve::tFunctionCurve(void *theOwner, tVariableNameSpace *externVariables): tCurve(theOwner)
{
  referenceVars = new tVariableNameSpace(this);
  referenceVars->inheritNameSpace(externVariables);

  t = dynamic_cast<tRealVariable*>(referenceVars->addRealVariable("t=0"));
  blockInvalidateList.append(t); // Wenn die Variabeln t ihren Wert aendern, darf dies nicht zu einem invalidate()
                                 // der Flaeche fuehern, die Flaeche selbst diese Werte setzt (siehe vectorAtAccurate()).

//  coordinates = new tVariableNameSpace(this);
//  coordinates->inheritNameSpace(referenceVars);
  ns = new tVariableNameSpace(this);
  ns->inheritNameSpace(referenceVars);

  x = dynamic_cast<tRealVariable*>(ns->addRealVariable("x=0"));
  y = dynamic_cast<tRealVariable*>(ns->addRealVariable("y=0"));
  z = dynamic_cast<tRealVariable*>(ns->addRealVariable("z=0"));
  X = dynamic_cast<tVectorVariable*>(ns->addVectorVariable("X=[x;y;z]"));
  X->addDependent(this);

}
//-----------------------------------------------------------------------------

tFunctionCurve::~tFunctionCurve()
{
  setElementLocked
  ns->releaseOwner(this);
  referenceVars->releaseOwner(this);

  X->removeDependent(this);

  clear();
}
//-----------------------------------------------------------------------------

void tFunctionCurve::clearRefList(void)
{
  for (int i=0;i<refList.count();i++){
    refList.at(i)->removeDependent(this);
  }
  refList.clear();

  for (int i=0;i<aliasList.count(); i++){
    QString alias = aliasList[i];
    x = dynamic_cast<tRealVariable*>(referenceVars->variable(alias+".x"));
    y = dynamic_cast<tRealVariable*>(referenceVars->variable(alias+".y"));
    z = dynamic_cast<tRealVariable*>(referenceVars->variable(alias+".z"));
    referenceVars->removeVariable(x);
    referenceVars->removeVariable(y);
    referenceVars->removeVariable(z);
    blockInvalidateList.removeAll(x);
    blockInvalidateList.removeAll(y);
    blockInvalidateList.removeAll(z);
    refVars.removeAll(x);
    refVars.removeAll(y);
    refVars.removeAll(z);
  }
  aliasList.clear();
}
//-----------------------------------------------------------------------------

void tFunctionCurve::clearFunctions(void)
{
//  ns->clear();
  for (int i=0; i< ns->count();i++){
    tVariable* var = ns->variable(i);
    if (var!=x && var!=y && var!=z && var!=X){
      ns->removeVariable(var);
    }
  }
}
//-----------------------------------------------------------------------------

void tFunctionCurve::clear(bool doSo)
{
  setElementLocked
  if (doSo){
    clearRefList();
    clearFunctions();
//    aliasList.clear();
//    blockInvalidateList.clear();
//    refVars.clear();
  }
}
//-----------------------------------------------------------------------------

iElement* tFunctionCurve::intrface(void)
{
  setElementLocked
	if (iface == NULL){
		iface = new iFunctionCurve(this);
	}
	return (iface);
}
//-----------------------------------------------------------------------------

void tFunctionCurve::refresh(void)
{
	// es gibt nichts zu tun.
}
//-----------------------------------------------------------------------------

tVector tFunctionCurve::vectorAtAccurate(tReal T)
{
  setElementLocked
  int i;
	tVector xx;
	update();

	t->setValue(T);

	for (i=0;i<refList.count();i++){
		xx = refList.at(i)->vectorAt(T);
		refVars.at(i*3+0)->setValue(xx.x);
		refVars.at(i*3+1)->setValue(xx.y);
		refVars.at(i*3+2)->setValue(xx.z);
	}

	return (X->value());
}
//-----------------------------------------------------------------------------

void tFunctionCurve::addFunction(QString func)
{
  setElementLocked
  if (func!=""){
    ns->addVariable(func);
    invalidate(this);
  }
}
//-----------------------------------------------------------------------------

void tFunctionCurve::addReference(tElement *reference, QString alias)
{
  setElementLocked
  tCurve *refSurf;
	tRealVariable *x,*y,*z;

	QString str;

	refSurf = dynamic_cast<tCurve*>(reference);


	if (refSurf && !refSurf->addDependent(this)){
    refSurf = NULL;
  }
  if (refSurf){
    if (alias == ""){
      alias = refSurf->intrface()->name();
    }
    if (alias!="" && !aliasList.contains(alias)){
			refList.append(refSurf);
			aliasList.append(alias);
			x = dynamic_cast<tRealVariable*>(referenceVars->addRealVariable(alias+".x:=0"));
			y = dynamic_cast<tRealVariable*>(referenceVars->addRealVariable(alias+".y:=0"));
			z = dynamic_cast<tRealVariable*>(referenceVars->addRealVariable(alias+".z:=0"));
			blockInvalidateList.append(x);
			blockInvalidateList.append(y);
			blockInvalidateList.append(z);
			refVars.append(x);
			refVars.append(y);
			refVars.append(z);
		}
		invalidate(this);
	}
}
//-----------------------------------------------------------------------------

tList<tElement*> tFunctionCurve::referenceCurves(void)
{
  setElementLocked
  tList<tElement*> list;
  for (int i=0; i<refList.count(); i++){
    list.append(refList.at(i));
  }
  return (list);
}
//-----------------------------------------------------------------------------

void tFunctionCurve::setReferenceCurves(const tList<tElement*>& list)
{
  setElementLocked
  QString funcs = functions();
  clearRefList();
  for (int i=0; i<list.count(); i++){
    addReference(list.at(i));
  }
  setFunctions(funcs);
}
//-----------------------------------------------------------------------------

QString tFunctionCurve::functions(void)
{
  setElementLocked
  QString funcs;
  for (int i=0;i<ns->count();i++){
    tRealVariable *rVar = dynamic_cast<tRealVariable*>(ns->variable(i));
    if (rVar){
      funcs += rVar->fullString() + ";;";
    }
  }
  return (funcs);
}
//-----------------------------------------------------------------------------

void tFunctionCurve::setFunctions(const QString& funcs)
{
  setElementLocked
  QStringList funcList = funcs.split(";;");
  clearFunctions();
  // zweimal setzten, beim ersten mal werden die Variablen nur erzeugt, so dass die Reihenfolge des Setzens egal ist.
  for (int i=0; i<funcList.count(); i++){
    addFunction(funcList[i]);
  }
  for (int i=0; i<funcList.count(); i++){
    addFunction(funcList[i]);
  }
}
//-----------------------------------------------------------------------------


//tElement* tFunctionCurve::lastAddedReference(void)
//{
//  setElementLocked
//  if (refList.count()>0){
//    return (refList.last());
//  } else {
//    return (NULL);
//  }
//}
////-----------------------------------------------------------------------------
//
//QString tFunctionCurve::functionsStringList(void)
//{
//  setElementLocked
//  int i;
//  QString str;
//  for (i=0; i<refVars.count(); i++){
//    str += refVars.at(i)->fullString() + ";; ";
//  }
//  return (str);
//}
//-----------------------------------------------------------------------------

QString tFunctionCurve::variableStringList(void)
{
  setElementLocked
//  int i;
  QString vars;

  for (int i=0;i<referenceVars->count();i++){
    tRealVariable *rVar = dynamic_cast<tRealVariable*>(referenceVars->variable(i));
    if (rVar){
      vars += rVar->name()+ ";";
    }
  }
  vars += ";";
  for (int i=0;i<ns->count();i++){
    tRealVariable *rVar = dynamic_cast<tRealVariable*>(ns->variable(i));
    if (rVar){
      vars += rVar->name() + ";";
    }
  }
  return (vars);
}
