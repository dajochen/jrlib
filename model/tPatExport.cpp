#include "model/tPatExport.h"


tPatExport::tPatExport()
{
	visibleOnly = true;
}
//-------------------------------------------------------------------------------------------------------

tPatExport::~tPatExport()
{
}
//-------------------------------------------------------------------------------------------------------

bool tPatExport::exportToFile(QString fileName, tElement *el)
{
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    return false;
  } else {
    QTextStream out(&file);
		isFirstSurface = true;
    /*
    out.setRealNumberNotation(QTextStream::SmartNotation);
    out.setRealNumberPrecision(5);
    out.setNumberFlags(QTextStream::ForcePoint);
    out.setFieldAlignment(QTextStream::AlignLeft);
    out.setFieldWidth(20);
    out.setPadChar(' ');
    */

    exportElement(el,&out);

    file.close();
    return true;
	}
}
//-------------------------------------------------------------------------------------------------------
void tPatExport::exportElement(tElement *el, QTextStream *out)
{
  if (el){
    el->lockElement();
//    if (dynamic_cast<tModel*>(el)){
//      exportModel(el,out);
//    } else
    if (dynamic_cast<tLayer*>(el)){
      exportLayer(el,out);
    } else if (dynamic_cast<tSurface*>(el)){
      exportSurface(el,out);
    } else if (dynamic_cast<tStructured2DGrid*>(el)){
      exportStructured2DGrid(el,out);
    }
    el->unlockElement();
  }
}

//-------------------------------------------------------------------------------------------------------
//void tPatExport::exportModel(tElement *el, QTextStream *out)
//{
//	int i,ni;
//	tModel *M;
//
//	M = dynamic_cast<tModel*>(el);
//	if (M){
//		ni = M->nElements();
//		for(i=0;i<ni;i++){
//      exportElement(M->element(i),out);
//		}
//	}
//}
//
////-------------------------------------------------------------------------------------------------------
//void tPatExport::exportGroup(tElement *el, QTextStream *out)
//{
//	int i,ni;
//  tGroup *G;
//
//	G = dynamic_cast<tGroup*>(el);
//	if (G){
//		ni = G->nElements();
//		for(i=0;i<ni;i++){
//      exportElement(G->element(i),out);
//		}
//	}
//}
////-------------------------------------------------------------------------------------------------------
void tPatExport::exportLayer(tElement *el, QTextStream *out)
{
  int i,ni;
  tLayer *l;
  el->lockElement();
  l = dynamic_cast<tLayer*>(el);
  if (l){
    ni = l->nElements();
    for(i=0;i<ni;i++){
      exportElement(l->element(i),out);
    }
  }
  el->unlockElement();
}
//-------------------------------------------------------------------------------------------------------

void tPatExport::exportSurface(tElement *el, QTextStream *out)
{
  el->lockElement();
	iElement *I;
	tRGB tt;
	tVector X;
	int i,j,ni,nj,color;
	bool orientation;
	tSurface *S;

  S = dynamic_cast<tSurface*>(el);
 	if (S){
 		if (S->hasInterface()){
 			I = S->intrface();
      orientation = S->orientation();
 			if (visibleOnly && !I->visibility()){
 				ni = 0;
 				nj = 0;
 			} else {
	 			ni = I->getPropertyInt("u Divisions");
	 			nj = I->getPropertyInt("v Divisions");
 			}
 			color = I->color().getMSColorIndex();
 		} else {
 			ni = 10;
 			nj = 10;
 			color = 1;
 		}
 		if (ni>0 && nj>0 ){
 			if (!isFirstSurface){
 				*out << 0 << "\t" << 0 << "\t" << 0 << "\t" << 0 << endl;
 			} else {
 				isFirstSurface = false;
 			}

			for (i=0;i<=ni;i++){
	 			for (j=0;j<=nj;j++){
          if (orientation){
	 				  X = S->vectorAt((double)i/(double)ni,(double)j/(double)nj);
          } else {
            X = S->vectorAt((double)i/(double)ni,(double)(nj-j)/(double)nj);
          }
	 				if (j == 0){
	 					*out << 0;
	 				} else {
	 					*out << color;
	 				}
	 				*out << "\t" << X.x << "\t" << X.y << "\t" << X.z << endl;
	 			}
			}
 		}
 	}
  el->unlockElement();

}
//-------------------------------------------------------------------------------------------------------

void tPatExport::exportStructured2DGrid(tElement *el, QTextStream *out)
{
  iElement *I;
  tRGB tt;
  tVector X;
  int i,j,ni,nj,color;
  tStructured2DGrid *grid;

  grid = dynamic_cast<tStructured2DGrid*>(el);
  if (grid){
    ni = grid->ni();
    nj = grid->nj();
    if (grid->hasInterface()){
      I = grid->intrface();
      if (visibleOnly && !I->visibility()){
        ni = 0;
        nj = 0;
      }
      color = I->color().getMSColorIndex();
    } else {
      color = 1;
    }
    if (ni>0 && nj>0){
      if (!isFirstSurface){
        *out << 0 << "\t" << 0 << "\t" << 0 << "\t" << 0 << endl;
      } else {
        isFirstSurface = false;
      }

      for (i=0;i<ni;i++){
        for (j=0;j<nj;j++){
          if (grid->orientation()){
            X = grid->gridAt(i,j)->vector();
          } else {
            X = grid->gridAt(i,nj-j-1)->vector();
          }
          if (j == 0){
            *out << 0;
          } else {
            *out << color;
          }
          *out << "\t" << X.x << "\t" << X.y << "\t" << X.z << endl;
        }
      }
    }
  }
}
//-------------------------------------------------------------------------------------------------------
