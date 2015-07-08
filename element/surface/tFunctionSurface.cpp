#include "element/surface/tFunctionSurface.h"

tFunctionSurface::tFunctionSurface(void *theOwner, tVariableNameSpace *externVariables): tSurface(theOwner)
{
	ns = new tVariableNameSpace(this);
	ns->inheritNameSpace(externVariables);
	clear();
//	u = dynamic_cast<tRealVariable*>(ns.addRealVariable("u=0"));
//	v = dynamic_cast<tRealVariable*>(ns.addRealVariable("v=0"));
//	blockInvalidateList.append(u); // Wenn die Variabeln u,v ihren Wert aendern, darf dies nicht zu einem invalidate()
//	blockInvalidateList.append(v); // der Flaeche fuehern, die Flaeche selbst diese Werte setzt (siehe vectorAtAccurate()).
//
//	x = dynamic_cast<tRealVariable*>(ns.addRealVariable("x=0")); // Der Ergebnisvektor
//	y = dynamic_cast<tRealVariable*>(ns.addRealVariable("y=0"));
//	z = dynamic_cast<tRealVariable*>(ns.addRealVariable("z=0"));
//	X = dynamic_cast<tVectorVariable*>(ns.addVectorVariable("X=[x;y;z]"));
}
//-----------------------------------------------------------------------------

tFunctionSurface::~tFunctionSurface()
{
  setElementLocked
  ns->releaseOwner(this);
	clear();
}
//-----------------------------------------------------------------------------

void tFunctionSurface::clear(bool doSo)
{
  setElementLocked
	int i;
  if (doSo){
    for (i=0;i<refList.count();i++){
      refList.at(i)->removeDependent(this);
    }
    refList.clear();
    aliasList.clear();
    blockInvalidateList.clear();
    refVars.clear();
    ns->clear();
    u = dynamic_cast<tRealVariable*>(ns->addRealVariable("u=0"));
    v = dynamic_cast<tRealVariable*>(ns->addRealVariable("v=0"));
    blockInvalidateList.append(u); // Wenn die Variabeln u,v ihren Wert aendern, darf dies nicht zu einem invalidate()
    blockInvalidateList.append(v); // der Flaeche fuehern, die Flaeche selbst diese Werte setzt (siehe vectorAtAccurate()).
    x = dynamic_cast<tRealVariable*>(ns->addRealVariable("x=0"));
    y = dynamic_cast<tRealVariable*>(ns->addRealVariable("y=0"));
    z = dynamic_cast<tRealVariable*>(ns->addRealVariable("z=0"));
    blockInvalidateList.append(x);
    blockInvalidateList.append(y);
    blockInvalidateList.append(z);
    X = dynamic_cast<tVectorVariable*>(ns->addVectorVariable("X=[x;y;z]"));
  }
}
//-----------------------------------------------------------------------------

iElement* tFunctionSurface::intrface(void)
{
  setElementLocked
	if (iface == NULL){
		iface = new iFunctionSurface(this);
	}
	return iface;
}
//-----------------------------------------------------------------------------

void tFunctionSurface::refresh(void)
{
	// es gibt nichts zu tun.
}
//-----------------------------------------------------------------------------

tVector tFunctionSurface::vectorAtAccurate(tReal U, tReal V)
{
  setElementLocked
  int i;
	tVector xx;
	update();

	u->setValue(U);
	v->setValue(V);

	for (i=0;i<refList.count();i++){
		xx = refList.at(i)->vectorAt(U, V);
		refVars.at(i*3+0)->setValue(xx.x);
		refVars.at(i*3+1)->setValue(xx.y);
		refVars.at(i*3+2)->setValue(xx.z);
	}

	return X->value();
}
//-----------------------------------------------------------------------------

void tFunctionSurface::addFunction(QString func)
{
  setElementLocked
//  tRealVariable *rVar;

//  rVar = dynamic_cast<tRealVariable*>(ns.addRealVariable(func));
	ns->addVariable(func);
  invalidate(this);
}
//-----------------------------------------------------------------------------

void tFunctionSurface::addReference(tElement *reference, QString alias)
{
  setElementLocked
  tSurface *refSurf;
	tRealVariable *x,*y,*z;

	QString str;
//	char dbg[500];
//  str = reference->intrface()->name();
//  strcpy(dbg, str.toLatin1().data());
//  str = reference->intrface()->type();
//  strcpy(dbg, str.toLatin1().data());

	refSurf = dynamic_cast<tSurface*>(reference);


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
			x = dynamic_cast<tRealVariable*>(ns->addRealVariable(alias+".x:=0"));
			y = dynamic_cast<tRealVariable*>(ns->addRealVariable(alias+".y:=0"));
			z = dynamic_cast<tRealVariable*>(ns->addRealVariable(alias+".z:=0"));
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

tElement* tFunctionSurface::lastAddedReference(void)
{
  setElementLocked
  if (refList.count()>0){
    return refList.last();
  } else {
    return NULL;
  }
}
//-----------------------------------------------------------------------------

QString tFunctionSurface::functionsStringList(void)
{
  setElementLocked
  int i;
  QString str;
  for (i=0; i<refVars.count(); i++){
    str += refVars.at(i)->fullString() + ";; ";
  }
  return str;
}
//-----------------------------------------------------------------------------
QString tFunctionSurface::variableStringList(void)
{
  setElementLocked
  int i;
  QString str;
  if (u &&v && x &&y &&z){
  str = u->name() + ";"
      + v->name() + ";"
      + x->name() + ";"
      + y->name() + ";"
      + z->name() + ";";
  }
  for (i=0; i<refVars.count(); i++){
    str += refVars.at(i)->name() + "; ";
  }
  return str;
}
