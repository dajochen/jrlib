#include "element/point/tFunctionPoint.h"

tFunctionPoint::tFunctionPoint(void *theOwner, tVariableNameSpace *externVariables): tDot(theOwner)
{
  referenceVars = new tVariableNameSpace(this);
  referenceVars->inheritNameSpace(externVariables);

  ns = new tVariableNameSpace(this);
  ns->inheritNameSpace(referenceVars);

  x = dynamic_cast<tRealVariable*>(ns->addRealVariable("x=0"));
  y = dynamic_cast<tRealVariable*>(ns->addRealVariable("y=0"));
  z = dynamic_cast<tRealVariable*>(ns->addRealVariable("z=0"));
  Xpos = dynamic_cast<tVectorVariable*>(ns->addVectorVariable("X=[x;y;z]"));
  Xpos->addDependent(this);

}
//-----------------------------------------------------------------------------

tFunctionPoint::~tFunctionPoint()
{
  setElementLocked
  ns->releaseOwner(this);
  referenceVars->releaseOwner(this);

  Xpos->removeDependent(this);

  clear();
}
//-----------------------------------------------------------------------------

void tFunctionPoint::clearRefList(void)
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

void tFunctionPoint::clearFunctions(void)
{
//  ns->clear();
  for (int i=0; i< ns->count();i++){
    tVariable* var = ns->variable(i);
    if (var!=x && var!=y && var!=z && var!=Xpos){
      ns->removeVariable(var);
    }
  }
}
//-----------------------------------------------------------------------------

void tFunctionPoint::clear(bool doSo)
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

iElement* tFunctionPoint::intrface(void)
{
  setElementLocked
	if (iface == NULL){
		iface = new iFunctionPoint(this);
	}
	return (iface);
}
//-----------------------------------------------------------------------------

void tFunctionPoint::refresh(void)
{
  setElementLocked
  int i;
  tVector xx;
  update();

//  t->setValue(T);

  for (i=0;i<refList.count();i++){
    xx = refList.at(i)->vector();
    refVars.at(i*3+0)->setValue(xx.x);
    refVars.at(i*3+1)->setValue(xx.y);
    refVars.at(i*3+2)->setValue(xx.z);
  }

  X = Xpos->value();
}
//-----------------------------------------------------------------------------

/*tVector tFunctionPoint::vectorAtAccurate(tReal T)
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

	return (Xpos->value());
}*/
//-----------------------------------------------------------------------------

void tFunctionPoint::addFunction(QString func)
{
  setElementLocked
  if (func!=""){
    ns->addVariable(func);
    invalidate(this);
  }
}
//-----------------------------------------------------------------------------

void tFunctionPoint::addReference(tElement *reference, QString alias)
{
  setElementLocked
  tDot *refDot;
	tRealVariable *x,*y,*z;

	QString str;

	refDot = dynamic_cast<tDot*>(reference);


	if (refDot && !refDot->addDependent(this)){
    refDot = NULL;
  }
  if (refDot){
    if (alias == ""){
      alias = refDot->intrface()->name();
    }
    if (alias!="" && !aliasList.contains(alias)){
			refList.append(refDot);
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

tList<tElement*> tFunctionPoint::referenceDots(void)
{
  setElementLocked
  tList<tElement*> list;
  for (int i=0; i<refList.count(); i++){
    list.append(refList.at(i));
  }
  return (list);
}
//-----------------------------------------------------------------------------

void tFunctionPoint::setReferenceDots(const tList<tElement*>& list)
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

QString tFunctionPoint::functions(void)
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

void tFunctionPoint::setFunctions(const QString& funcs)
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

QString tFunctionPoint::variableStringList(void)
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
