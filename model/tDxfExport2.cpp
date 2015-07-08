#include "tDxfExport2.h"

#ifdef BUILD_WITH_DXFLIB

tDxfExport2::tDxfExport2(QString fileName, tModel *m, tBasicPlane *pl)
{
    plane=pl;
    if (pl) plane->addOwner(this);

    func(fileName,m);

}

tDxfExport2::~tDxfExport2()
{
    if (plane) plane->addOwner(this);
}

void tDxfExport2::exportElement(tElement *el)
{
}


void tDxfExport2::func(QString fName, tModel* m)
{
    DL_Codes::version exportVersion = DL_Codes::AC1015;
    dw = dxf.out(fName.toStdString().data(), exportVersion);
    if (dw==NULL) {
        printf("Cannot open file 'myfile.dxf' for writing.");
        // abort function e.g. with return
    }

    //Prepare:
    writeHeader();

    dw->sectionTables();
    {//Initial Tables
        //a standard viewport
        dxf.writeVPort(*dw);

        //the linetypes
        writeDefaultLineTypes();

        //all our jr-Layers
        writeLayers(m);

        writeDefaultTables();
        writeDimentsions();

        //Declare Blocks
        dxf.writeBlockRecord(*dw);
        //if there are further blocks in future...
        //dxf.writeBlockRecord(*dw, "myblock2");
        dw->tableEnd();
    }

    //Write Blocks
    dw->sectionBlocks();
    writeDefaultBlocks();


    // The Entities:
    writeEntities(m);

    //Finalize:
    dxf.writeObjects(*dw);
    dxf.writeObjectsEnd(*dw);


    dw->dxfEOF();
    dw->close();
    delete dw;
}


void tDxfExport2::writeHeader()
{
    dxf.writeHeader(*dw);

/* // Variables will be used:
   // int variable:
   dw->dxfString(9, "$INSUNITS");
   dw->dxfInt(70, 4);
   // real (double, float) variable:
   dw->dxfString(9, "$DIMEXE");
   dw->dxfReal(40, 1.25);
   // string variable:
   dw->dxfString(9, "$TEXTSTYLE");
   dw->dxfString(7, "Standard");
   // vector variable:
   dw->dxfString(9, "$LIMMIN");
   dw->dxfReal(10, 0.0);
   dw->dxfReal(20, 0.0);
*/
    dw->sectionEnd();
}

void tDxfExport2::writeDefaultLineTypes()
{
    dw->tableLineTypes(25);
    dxf.writeLineType(*dw, DL_LineTypeData("BYBLOCK", 0));
    dxf.writeLineType(*dw, DL_LineTypeData("BYLAYER", 0));
    dxf.writeLineType(*dw, DL_LineTypeData("CONTINUOUS", 0));
    dxf.writeLineType(*dw, DL_LineTypeData("ACAD_ISO02W100", 0));
    dxf.writeLineType(*dw, DL_LineTypeData("ACAD_ISO03W100", 0));
    dxf.writeLineType(*dw, DL_LineTypeData("ACAD_ISO04W100", 0));
    dxf.writeLineType(*dw, DL_LineTypeData("ACAD_ISO05W100", 0));
    dxf.writeLineType(*dw, DL_LineTypeData("BORDER", 0));
    dxf.writeLineType(*dw, DL_LineTypeData("BORDER2", 0));
    dxf.writeLineType(*dw, DL_LineTypeData("BORDERX2", 0));
    dxf.writeLineType(*dw, DL_LineTypeData("CENTER", 0));
    dxf.writeLineType(*dw, DL_LineTypeData("CENTER2", 0));
    dxf.writeLineType(*dw, DL_LineTypeData("CENTERX2", 0));
    dxf.writeLineType(*dw, DL_LineTypeData("DASHDOT", 0));
    dxf.writeLineType(*dw, DL_LineTypeData("DASHDOT2", 0));
    dxf.writeLineType(*dw, DL_LineTypeData("DASHDOTX2", 0));
    dxf.writeLineType(*dw, DL_LineTypeData("DASHED", 0));
    dxf.writeLineType(*dw, DL_LineTypeData("DASHED2", 0));
    dxf.writeLineType(*dw, DL_LineTypeData("DASHEDX2", 0));
    dxf.writeLineType(*dw, DL_LineTypeData("DIVIDE", 0));
    dxf.writeLineType(*dw, DL_LineTypeData("DIVIDE2", 0));
    dxf.writeLineType(*dw, DL_LineTypeData("DIVIDEX2", 0));
    dxf.writeLineType(*dw, DL_LineTypeData("DOT", 0));
    dxf.writeLineType(*dw, DL_LineTypeData("DOT2", 0));
    dxf.writeLineType(*dw, DL_LineTypeData("DOTX2", 0));
    dw->tableEnd();
}

void tDxfExport2::writeDefaultTables()
{
    dxf.writeStyle(*dw);
    dxf.writeView(*dw);
    dxf.writeUcs(*dw);

    dw->tableAppid(1);
    dw->tableAppidEntry(0x12);
    dw->dxfString(2, "ACAD");
    dw->dxfInt(70, 0);
    dw->tableEnd();

}

void tDxfExport2::writeDimentsions()
{
    double arrowSize = 2.5,
            extensionLineExtension = 1.25,
            extensionLineOffset = 0.625,
            dimensionGap = 0.625,
            dimensionTextSize = 2.5;


    dxf.writeDimStyle(*dw,
        arrowSize,
        extensionLineExtension,
        extensionLineOffset,
        dimensionGap,
        dimensionTextSize);
}

void tDxfExport2::writeDefaultBlocks()
{


    dxf.writeBlock(*dw,
        DL_BlockData("*Model_Space", 0, 0.0, 0.0, 0.0));
    dxf.writeEndBlock(*dw, "*Model_Space");

    dxf.writeBlock(*dw,
        DL_BlockData("*Paper_Space", 0, 0.0, 0.0, 0.0));
    dxf.writeEndBlock(*dw, "*Paper_Space");

    dxf.writeBlock(*dw,
        DL_BlockData("*Paper_Space0", 0, 0.0, 0.0, 0.0));
    dxf.writeEndBlock(*dw, "*Paper_Space0");

/*
    dxf.writeBlock(*dw,
        DL_BlockData("myblock2", 0, 0.0, 0.0, 0.0));
    // ...
    // write block entities e.g. with dxf.writeLine(), ..
    // ...
    dxf.writeEndBlock(*dw, "myblock2");
 */
    dw->sectionEnd();

}


void tDxfExport2::writeEntities(tModel *m)
{
    dw->sectionEntities();
        writeLines(m);
        writePolylines(m);
    dw->sectionEnd();
}

void tDxfExport2::writeLayers(tModel *m)
{

    tList<tElement*> layers = m->elements(iLayer::theType(), true);

    dw->tableLayers(layers.count()+1);

    dxf.writeLayer(*dw,
        DL_LayerData("0", 0),
        DL_Attributes(
            std::string(""),      // leave empty
            DL_Codes::black,      // default color
            100,                  // default width        writeTables(m);
            "CONTINUOUS"));       // default line style

    DL_Codes::color colors[] = { DL_Codes::black, DL_Codes::green, DL_Codes::red, DL_Codes::brown, DL_Codes::yellow, DL_Codes::cyan, DL_Codes::magenta, DL_Codes::gray,
                                 DL_Codes::blue, DL_Codes::l_blue, DL_Codes::l_green, DL_Codes::l_cyan, DL_Codes::l_red, DL_Codes::l_magenta, DL_Codes::l_gray, DL_Codes::white};

    for (int i=0;i<layers.count(); i++) {
        dxf.writeLayer(*dw,
                       DL_LayerData(layers.at(i)->intrface()->name().toStdString().data(), 0),
                       DL_Attributes(
                           std::string(""),
                           colors[i%16],
                           100,
                           "CONTINUOUS"));
    }

    dw->tableEnd();
}

void tDxfExport2::writeLines(tModel *m)
{
    tList<tLayer*> lrs = layers(m);
    for (int i=0; i<lrs.count(); i++) {
        tLayer* layer = lrs.at(i);
        tList<tElement*> lines = layer->elements(iLine::theType());
        for (int j=0; j<lines.count(); j++) {
            tLine* line = dynamic_cast<tLine*>(lines.at(j));

            tVector x0 = line->start()->vector(),
                    x1 = line->end()->vector();
            if (plane) {
                x0 = plane->projectToPlaneCoords(x0)*1000.;
                x1 = plane->projectToPlaneCoords(x1)*1000.;
            }

            dxf.writeLine(*dw,
                            DL_LineData(x0.x,   // start point
                                        x0.y,
                                        0,
                                       x1.x,   // end point
                                       x1.y,
                                       0),
                            DL_Attributes(layer->intrface()->name().toStdString().data(), 256, -1, "BYLAYER"));
        }
    }
}

void tDxfExport2::writePolylines(tModel *m)
{
    tList<tLayer*> lrs = layers(m);
    for (int i=0; i<lrs.count(); i++) {
        tLayer* layer = lrs.at(i);

        tList<tElement*> curves = layer->elements(iCurve::theType());
        for (int j=0; j<curves.count(); j++) {
            tLine* line = dynamic_cast<tLine*>(curves.at(j));
            tCurve* curve = dynamic_cast<tCurve*>(curves.at(j));

            if (!line) {
                int tRes = curve->tResolution();
                dxf.writePolyline( *dw,
                                   DL_PolylineData(tRes+1, 0, 0, 0 ),
                                   DL_Attributes(layer->intrface()->name().toStdString().data(), 256, -1, "BYLAYER"));
                for (int t=0;t<=tRes;t++){
                    tVector x  = curve->tCache()[t];
                    if (plane) {
                        x = plane->projectToPlaneCoords(x)*1000.;
                    }
                    dxf.writeVertex(*dw,
                                    DL_VertexData(x.x,x.y,x.z, 0.));
                }
                dxf.writePolylineEnd(*dw);
            }
        }
    }
}

tList<tLayer *> tDxfExport2::layers(tModel *m)
{
    tList<tElement*> elements = m->elements(iLayer::theType(), true);
    tList<tLayer*> lrs;

    for (int i=0;i<elements.count(); i++) {
        lrs.append(dynamic_cast<tLayer*>(elements.at(i)));
    }
    return lrs;
}

#endif // BUILD_WITH_DXFLIB
