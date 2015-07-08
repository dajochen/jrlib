#include "tProgrammversionDlg.h"

tProgrammversionDlg::tProgrammversionDlg(QWidget *parent,Qt::WindowFlags f) : QDialog(parent,f)
{
  setupUi(this);	
  textBrowser->setHtml("<h1>JRcad</h1><p>Version 0.0.1</p>");
}

tProgrammversionDlg::~tProgrammversionDlg(void)
{
}
