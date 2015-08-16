#ifndef TEXPORTERTOOL_H
#define TEXPORTERTOOL_H

#include "model/tModel.h"
#include "model/tSelectionSet.h"

class tExporterTool
{
private:
    tModel *model;
    tSelectionSet *selectionSet;

public:
    tExporterTool(tModel *m, tSelectionSet *s);
    virtual ~tExporterTool();

    QString selectExportFile(QWidget *parent = NULL);
    bool exportToFile(QString fileName);
};

#endif // TEXPORTERTOOL_H
