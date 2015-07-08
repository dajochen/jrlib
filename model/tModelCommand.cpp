#include "model/tModelCommand.h"
#include "classes/tVectorStringConverter.h"
#include "classes/utils.h"

tModelCommand::tModelCommand()
{
  model = NULL;
}
//-----------------------------------------------------------------------------

tModelCommand::~tModelCommand()
{
}
//-----------------------------------------------------------------------------

QString tModelCommand::execute(QStringList cmd)
{
  QString out, name, type, property, value;
  tElement *el = NULL;
  int i;
//  cmd = cmd.trimmed();
  if (model && cmd.count()>0){
    if (cmd.count() > 3 && cmd[0].startsWith("create",Qt::CaseInsensitive)
                        && cmd[2].toLower() == "as"){
      name = cmd[1];
      type = cmd[3];
      out = "create \"" + name + "\" as " + type;
      if (type.toLower() == "abspoint"){
        el = model->currentLayer()->addPoint();
      } else if (type.toLower() == "relpoint"){
        el = model->currentLayer()->addRelPoint();
      } else if (type.toLower() == "midpoint"){
        el = model->currentLayer()->addMidPoint();
      } else if (type.toLower() == "absbead"){
        el = model->currentLayer()->addAbsBead();
      } else if (type.toLower() == "absmagnet"){
        el = model->currentLayer()->addAbsMagnet();
      } else if (type.toLower() == "offsetpoint"){
        el = model->currentLayer()->addOffsetPoint();
      } else if (type.toLower() == "rotatedpoint"){
        el = model->currentLayer()->addRotatedPoint();
// Curves
      } else if (type.toLower() == "line"){
        el = model->currentLayer()->addLine();
      } else if (type.toLower() == "rotatedcurve"){
        el = model->currentLayer()->addRotatedCurve();
// Variables
      } else if (type.toLower() == "realVar"){
        el = model->currentLayer()->addRealVariable(name +"=1");
      } else if (type.toLower() == "vectorVar"){
        el = model->currentLayer()->addVectorVariable(name +"=1");
      }
      i = 4;
      if (el){
        el->intrface()->setPropertyString("name",name);
        while (i < cmd.count()){
          if (cmd[i].toLower() == "set"){
            i++;
            if (i<cmd.count() && cmd[i].contains("=")){
              property = cmd[i].left(cmd[i].indexOf("="));
              value = cmd[i].right(cmd[i].length()-cmd[i].indexOf("=")-1);
              out += " set " + property + "=" + value;
              out += setProperty(el, property, value);
            } else {
              out += "\n!Error: expecting \"property=value\"";
            }
          } else {
            out += "\n!Error: expecting set command here";
          }
          i++;
        }
      } else {
        out = "!Error: unknown element type: \"" + type +"\"";
      }
    } else if (cmd.count() > 1 && cmd[0].startsWith("select",Qt::CaseInsensitive)){
      out = "select " + cmd[1];
      model->setSelection(model->elementByName(cmd[1]));
    } else if (cmd[0].contains("=")){
      QStringList lhs;
      lhs = cmd[0].left(cmd[0].indexOf("=")).split(".");
      if (lhs.count() > 1){
        el = model->elementByName(lhs[0]);
        property = lhs[1];
        value = cmd[0].right(cmd[0].length()-cmd[0].indexOf("=")-1);
        out = cmd.join(" ");
        out += setProperty(el, property, value);
      } else {
        out = cmd.join(" ") + "\n Error: unable to process command. Expecting something like: elementName.property=value";
      }
    } else {
      out = "!Error processing command: " + cmd.join(" ");
    }
  }
  return out;
}
//-----------------------------------------------------------------------------

QString tModelCommand::setProperty(tElement *el, QString property, QString value)
{
  int index;
  iElement *intrface;
  QString type;
  QString out;

  intrface = el->intrface();
  index = intrface->getPropertyIndex(property);

  if (index > -1){
    type = intrface->getPropertyType(index);
    if (type == "String"){
      intrface->setPropertyValue(index, type, &value);
    } else if (type == "Bool"){
      bool boolValue;
      if (value.toLower() == "true"){
        boolValue = true;
      } else {
        boolValue = false;
      }
      intrface->setPropertyValue(index, type, &boolValue);
    } else if (type == "Int"){
      int intValue = (int)value.toDouble();
      intrface->setPropertyValue(index, type, &intValue);
    } else if (type == "Real"){
      tReal realValue = value.toDouble();
      intrface->setPropertyValue(index, type, &realValue);
    } else if (type == "Vector"){
      tVector vectorValue = tVectorStringConverter::toVector(value,QRegExp(";"));
      intrface->setPropertyValue(index, type, &vectorValue);
    } else if (type == "RGB"){
      tRGB rgbValue;
      rgbValue = tVectorStringConverter::toVector(value,QRegExp(";"));
      intrface->setPropertyValue(index, type, &rgbValue);
    } else {
      tElement *el;
      el = model->elementByName(value);
      if (!intrface->setPropertyValue(index, type, el)){
        out = "\n!Error: unable to handle properties of type \"" + property + "\"\n";
      }
    }
  } else {
    out = "\n!Error: Element has no property called \"" + property + "\"";
  }
  return out;


}
//-----------------------------------------------------------------------------
