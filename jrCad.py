#!/usr/bin/python

import sys
sys.path.append('sip')
 
from PyQt4.QtCore import *
from PyQt4.QtGui import *
from pyJR import *


class jrWindow(tMainForm):
    def __init__(self):
        super(jrWindow, self).__init__()
        self.initPlugins()
        
    
    def initPlugins(self):
        plug = self.pluginAction("Verzerrte Zuschnitte speichern")
        plug.triggered.connect(self.storeArrangedCuttings)
        plug = self.pluginAction("Original Zuschnitte speichern")
        plug.triggered.connect(self.storeOriginalCuttings)
        #self.connect(plug, SIGNAL('triggered()'), self.plug1Func)
        
    def storeArrangedCuttings(self):
        self.storeCuttings("Arranged Cutting")
        
    def storeOriginalCuttings(self):
        self.storeCuttings("Original Cutting")

    def storeCuttings(self, mode):
        lastSavedFile = ""
        defaultFile = ""
        if len(lastSavedFile)==0:
          defaultFile = QDir.homePath();
        else:
          defaultFile = lastSavedFile;

        baseName = QFileDialog.getSaveFileName(self,
                                               "Zuschitte speichern, Basisdateinamen waaehlen",
                                               defaultFile,
                                               "DXF-File (*.dxf)");
        log = ""
        
        model = getActiveModel;
        if model is not none:
          g = new tGroup(self);
          g->setElements( model->selection()->elements() );
        
          tLayer* top = dynamic_cast<tLayer*>(model->elementByName("PropGeo - Cutting File", iLayer::theType()));
          if (top){
            tList<tElement*> compounds = top->elements(iLayer::theType());
            for (int i=0;i<compounds.count();i++){
              tLayer* comp = dynamic_cast<tLayer*>(compounds.at(i));
              tLayer* cutting = dynamic_cast<tLayer*>(comp->elementByName(type,iLayer::theType()));
              if (cutting){
                log += "Processing Cutting: " + type + " to file: " + baseName + "...dxf\n";
        
                tList<tElement*> fabrics = cutting->elements(iLayer::theType());
        
                for (int j=0; j<fabrics.count(); j++){
                  //model->setSelection(fabrics.at(j));
                  tLayer* fabric = dynamic_cast<tLayer*>(fabrics.at(j));
                  QString fileName = baseName + "_" + comp->intrface()->name() + "_" + fabric->intrface()->name() + ".dxf";
                  log += "writing: " + fileName + "\n";
        
                  tDxfExport dxf;
        
                  dxf.defaultLayer = "CUT";
                  dxf.addElement(fabric);
        
                  dxf.defaultLayer = "TEXT";
                  tList<tElement*> offsets = fabric->elements(iLayer::theType());
                  for (int k=0; k<offsets.count(); k++ ){
        
                    tLayer *l = dynamic_cast<tLayer*>(offsets.at(k));
                    if (l){
                      dxf.addText( l->intrface()->name(),
                                   (l->xMin()+l->xMax())*0.5 );
        
                      tLayer *contur = dynamic_cast<tLayer*>(l->elementByName("Contur", iLayer::theType()));
                      if (contur){
                        tList<tElement*> list = contur->elements(iCurve::theType());
                        tCurve *c = dynamic_cast<tCurve*>(list.at(0));
                        if (c){
                          int tRes = c->tResolution();
                          double area = 0.;
                          tVector x0, x;
                          x0 = c->vectorAt(0.);
                          for (int i=1; i<=tRes; i++){
                            double t = double(i)/double(tRes);
                            x = c->vectorAt(t);
                            area += 0.5*( ( x.x+x0.x ) * (x.y-x0.y ) ) / 1.0e6;
                            x0 = x;
                          }
                          log += "Layer: " + l->intrface()->name() + ": Area: " + QString::number(area)+ "\n";
                        }
                      }
                    }
        
                  }
        
                  dxfPoint xMin = dxf.content().getBoundingBox().Min();
                  xMin.x *= -1;
                  xMin.y *= -1;
                  dxf.content().shift(xMin.x, xMin.y);
        
                  dxf.exportToFile(fileName);
        
                }
              }
        
            }
          }
        
          model->selection()->setElements( g->elements() );
          g->releaseOwner(self);
        }
        
        QMessageBox mb(QMessageBox::Information, "Export Info:", "Expand for details", QMessageBox::Ok);
        mb.setDetailedText(log);
        mb.exec();
        


        
        
        
     
#class RunScript(QObject):
#    def __init__(self, mainWindow):
#        QObject.__init__(self)
#        self.mainWindow = mainWindow
#	 
#    def runScript(self, script):
#       mainWindow = self.mainWindow
#       exec(str(script))
       
       
	 
a = QApplication(sys.argv)

w = jrWindow()
w.show()
a.exec_()
