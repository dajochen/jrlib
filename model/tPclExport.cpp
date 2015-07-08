#include "model/tPclExport.h"


tPclExport::tPclExport()
{
  visibleOnly = true;
  dots = new std::map<tDot*,int>;
  nQuads = 0.;
  XML = NULL;
}
//-------------------------------------------------------------------------------------------------------

tPclExport::~tPclExport()
{
  dots->clear();
  delete dots;
//  dots.clear();
//  cells.clear();
}
//-------------------------------------------------------------------------------------------------------

bool tPclExport::exportToFile(QString fileName, tModel *m){

//  QDomElement root,tag;
  QFile file;
  QString docType;
  QDomElement tag,oldTag;

  docType = "poti_control";

  file.setFileName(fileName);

  if (file.open(QIODevice::WriteOnly)){
    XML = new QDomDocument(docType);
    root = XML->createElement(docType);
    XML->appendChild(root);

    exportModel(m);

    // XML in eine Datei schreiben
    QTextStream stream(&file);
    stream << XML->toString();
    file.close();
    delete XML;
    return true;
  } else {
//    fErrorMessages << "Can't write the given file: \"" + fileName + "\"";
    return false;
  }
}
//-------------------------------------------------------------------------------------------------------
/*
void tPclExport::exportElement(tElement *el){
  if (dynamic_cast<tModel*>(el)){
    exportModel(el);
  } else if (dynamic_cast<tGroup*>(el)){
    exportGroup(el);
  } else if (dynamic_cast<tSurface*>(el)){
    exportSurface(el);
  } else if (dynamic_cast<tStructured2DGrid*>(el)){
    exportStructured2DGrid(el);
  }
}
//-------------------------------------------------------------------------------------------------------
*/
void tPclExport::exportModel(tElement *el){

  tModel *M;
  int i,ni;

  M = dynamic_cast<tModel*>(el);
  if (M){
    root.setAttribute("caption","noName");
    ni = M->nElements();
//    currentCOOS.appendChild(XML->createElement ("geo_fromXML"));
    for(i=0;i<ni;i++){
      exportGroup(M->element(i));
    }
  }
}
//-------------------------------------------------------------------------------------------------------

void tPclExport::exportGroup(tElement *el){
  int i,ni,j,nj;
  tGroup *G,*comp;
  QDomElement tag,geo,quadEl;
  std::map<tDot*,int>::iterator it;
  tVector x;
  QString pos;

  G = dynamic_cast<tGroup*>(el);
  if (G){
    currentCOOS = XML->createElement("local_CooSys");
    currentCOOS.setAttribute("caption",G->intrface()->getPropertyString("name"));
    root.appendChild(currentCOOS);
    geo = XML->createElement ("geo_fromXML");
    currentCOOS.appendChild(geo);
    nQuads = 0;
    ni = G->nElements();
    for(i=0;i<ni;i++){
      // Die IST-Hydro PanelGroups sind hier in tGroup 's zusammengefasst.
      comp = dynamic_cast<tGroup*>(G->element(i));
      if (comp){
        // Die flaechigen Elemente durchgehen, und Quads erstellen
        nj = comp->nElements();
        compName = comp->intrface()->getPropertyString("name");
        for(j=0;j<nj;j++){
          if (dynamic_cast<tSurface*>(comp->element(j))){
            exportSurface(comp->element(j));
          } else if (dynamic_cast<tStructured2DGrid*>(comp->element(j))){
            exportStructured2DGrid(comp->element(j));
          }
        }
      }
    }
    // Die Punkte schreiben

    quadEl = geo.firstChildElement("Quad");
    if (quadEl.isNull()){
      quadEl = geo.firstChildElement("StructuredGrid");
    }

    if (!currentCOOS.isNull() && !quadEl.isNull()){
      for ( it=dots->begin(); it != dots->end(); it++ ){
        tag = XML->createElement("Point");
        x = it->first->vector();
        tag.setAttribute("number",QString::number(it->second));
        tag.setAttribute("position",QString("%1 %2 %3").arg(x.x,0,'g',12).arg(x.y,0,'g',12).arg(x.z,0,'g',12));
        geo.insertBefore(tag, quadEl);
      }
    } else {
      //Leere local_CooSys löschen
      root.removeChild(currentCOOS);
    }
    dots->clear();
    for (i=0;i<pclExportDot.count();i++){
      pclExportDot.at(i)->releaseOwner(this);
    }
    pclExportDot.clear();
  }
}
//-------------------------------------------------------------------------------------------------------

void tPclExport::exportSurface(tElement *el){
  tSurface *surf;
  int nDots;
  int ni,nj;
  QDomElement tag,geo;
  QString dotList;
//  tDot *dot;

  nDots = dots->size()+1;

  surf = dynamic_cast<tSurface*>(el);
  if (surf){
    geo = currentCOOS.firstChildElement("geo_fromXML");
    geo.appendChild(tag);
    ni = surf->uDiv()*surf->uRes();//Unterteilung der Flaeche
    nj = surf->vDiv()*surf->vRes();
/*
    for (i=0;i<=ni;i++){
      for (j=0;j<=nj;j++){
        if (surf->orientation()){
          dot = new tPoint(this,surf->vectorAt((tReal)i/(tReal)ni,(tReal)j/(tReal)nj));
        } else {
          dot = new tPoint(this,surf->vectorAt((tReal)(ni-i)/(tReal)ni,(tReal)j/(tReal)nj));
        }
        dotList.append(QString::number(nDots + (i*(nj+1)+j)) + " ");
        pclExportDot.append(dot);
        (*dots)[dot] = nDots + (i*(nj+1)+j);
      }
    }
    tag = XML->createElement("StructuredGrid");
    geo.appendChild(tag);
    tag.setAttribute("ni",QString::number(ni));
    tag.setAttribute("nj",QString::number(nj));
    tag.setAttribute("component",compName);
    tag.setAttribute("vertices",dotList);*/
    //*/
    for (int i=0;i<ni;i++){
      for (int j=0;j<nj;j++){
        tag = XML->createElement("Quad");
        tag.setAttribute("component",compName);
        tag.setAttribute("number",nQuads++);
        if (surf->orientation()){
          tag.setAttribute("points",QString::number(nDots + i*(nj+1)+j)+" "+
                                    QString::number(nDots + i*(nj+1)+j+1)+" "+
                                    QString::number(nDots + (i+1)*(nj+1)+j+1)+" "+
                                    QString::number(nDots + (i+1)*(nj+1)+j));
        } else {
          tag.setAttribute("points",QString::number(nDots + i*(nj+1)+j)+" "+
                                    QString::number(nDots + (i+1)*(nj+1)+j)+" "+
                                    QString::number(nDots + (i+1)*(nj+1)+j+1)+" "+
                                    QString::number(nDots + i*(nj+1)+j+1));
        }
        geo.appendChild(tag);
      }
    }
   //*/
  }
}
//-------------------------------------------------------------------------------------------------------

void tPclExport::exportStructured2DGrid(tElement *el){

  tStructured2DGrid *grid;
//  QString name;
  int i,j,k,ni,nj,id[4];
//  bool allDotsAvaialbe;
  QDomElement tag,geo;
  tDot *dot;
  QString dotList;

  std::map<tDot*,int>::iterator it;

//  allDotsAvaialbe = true;

  grid = dynamic_cast<tStructured2DGrid*>(el);
  if (grid){
    geo = currentCOOS.firstChildElement("geo_fromXML");
    geo.appendChild(tag);

    ni = grid->ni(); // Anzahl der Gitterpunkte in i-Richtung
    nj = grid->nj();

    for (i=0;i<ni;i++){
      for (j=0;j<nj;j++){
        if (grid->orientation()){
          dot = grid->gridAt(ni-1-i,j);
        } else{
          dot = grid->gridAt(i,j);
        }
        if (!dot){
//          allDotsAvaialbe = false;
        } else {
          it = dots->find(dot);
          if (it == dots->end()){
            // Dot ist noch nicht Teil der map "dots".
            // Hinzufuegen:
            (*dots)[dot] = dots->size()+1;
            dotList.append(QString::number((*dots)[dot]) + " ");
          } else {
            // Bestehender Punkt, Nummer Lesen und in dotList Eintragen.
            dotList.append(QString::number(it->second) + " ");
          }
        }
      }
    }
/*
    tag = XML->createElement("StructuredGrid");
    geo.appendChild(tag);
    tag.setAttribute("ni",QString::number(ni-1));
    tag.setAttribute("nj",QString::number(nj-1));
    tag.setAttribute("component",compName);
    tag.setAttribute("vertices",dotList);
*/

    tDot *dot[4];
    for (i=0;i<ni-1;i++){
      for (j=0;j<nj-1;j++){
        dot[0] = grid->gridAt(i,j);
        dot[1] = grid->gridAt(i+1,j);
        dot[2] = grid->gridAt(i+1,j+1);
        dot[3] = grid->gridAt(i,j+1);
        if (dot[0] && dot[1] && dot[2] && dot[3]){
          for (k=0;k<4;k++){
            it = dots->find(dot[k]);
            if (it == dots->end()){
              id[k] = dots->size()+1;
              (*dots)[dot[k]]=id[k];
            } else {
              id[k] = it->second;
            }
          }
          tag = XML->createElement("Quad");
          tag.setAttribute("component",compName);
          tag.setAttribute("number",nQuads++);
          if (grid->orientation()){
            tag.setAttribute("points",QString::number(id[0])+" "+QString::number(id[1])+" "+QString::number(id[2])+" "+QString::number(id[3]));
          } else {
            tag.setAttribute("points",QString::number(id[3])+" "+QString::number(id[2])+" "+QString::number(id[1])+" "+QString::number(id[0]));
          }
          geo.appendChild(tag);
        }
      }
    }
  }
}
//-------------------------------------------------------------------------------------------------------

