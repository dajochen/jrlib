/*
 * tAbaqusMesh.cpp
 *
 *  Created on: 07.06.2011
 *      Author: jochen
 */

#include "model/tAbaqusMesh.h"
#include <QFile>

tAbaqusMesh::tAbaqusMesh()
{
}
//-------------------------------------------------------------------------------------------------------

tAbaqusMesh::~tAbaqusMesh()
{
}
//-------------------------------------------------------------------------------------------------------

bool tAbaqusMesh::exportToFile(QString fileName, tModel *m)
{
  QFile file;
  file.setFileName(fileName);

  if (file.open(QIODevice::WriteOnly)){

    QTextStream stream(&file);

    exportModel(m, stream);

    for(int i=0;i<lockedElements.count();i++){
      lockedElements.at(i)->unlockElement();
    }

    file.close();
    return true;
  } else {
    //    fErrorMessages << "Can't write the given file: \"" + fileName + "\"";
    return false;
  }
}
//-------------------------------------------------------------------------------------------------------

void tAbaqusMesh::exportLayer(tElement *el)
{
  tLayer *L = dynamic_cast<tLayer*>(el);
  int i,ni;

  if (L){
    ni = L->nElements();
    for(i=0;i<ni;i++){
      tElement* e = L->element(i);
      exportStructured3DGrid(e);
      exportStructured2DGrid(e);
      exportLayer(e);
    }
  }

}
//-------------------------------------------------------------------------------------------------------

void tAbaqusMesh::exportModel(tElement *el, QTextStream& stream)
{

  exportLayer(el);


  QList<tDot*> dotList;
  dotList.append(NULL);// Dummy Node, so the List will start at "1" instead of "0"

  for (int i=0;i<abqSets.count(); i++){
    const AbqElementSet& abqElementSet = abqSets.at(i);
    for (int j=0;j<abqElementSet.abqElements.count(); j++){
      const AbqElement& element = abqElementSet.abqElements.at(j);
      for (int k=0;k<element.vertices.count();k++){
        tDot* d = element.vertices.at(k);
        if (!dotList.contains(d)){
          dotList.append(d);
        }
      }
    }
  }



  if (abqSets.count()>0){
    int i;
    //Alle Nodes schreiben
    stream << "*NODE" << endl;
      for (i=1;i<dotList.count();i++) {
      tDot *d = dotList[i];
      tVector pos;
      if (d){
        pos = d->vector();
      } else {
        pos.setZero();
      }
      stream << dotList.indexOf(d) << ", "
             << pos.x << ", "
             << pos.y << ", "
             << pos.z << endl;
    }

    //Alle Elemente schreiben
    int set, elCounter=1;
    for (set=0; set<abqSets.count(); set++){
      const AbqElementSet& abqSet = abqSets.at(set);
      stream << "*ELEMENT" << ", TYPE=" << abqSet.type;
      if (!abqSet.caption.isEmpty()){
        stream << ", ELSET=" << abqSet.caption;
      } else {
        stream << ", ELSET=EALL";
      }
      stream  << endl;
      for (int el=0;el<abqSet.abqElements.count(); el++){
        const AbqElement& abqElement = abqSet.abqElements.at(el);
        stream << elCounter++ << ",";
        for (int d=0; d<abqElement.vertices.count(); d++){
          stream << dotList.indexOf(abqElement.vertices.at(d));
          if (d<abqElement.vertices.count()-1){
            stream << ",";
          }
          if (d>0 && d%14==0){
            stream << endl;
          }
        }
        stream << endl;
      }
    }

    //Alle NodeSets schreiben
    QMap<QString, QList<tDot*> >::iterator iter;
    for (iter=nodeSets_.begin(); iter!=nodeSets_.end(); iter++){
      QList<tDot*>& nodeSet = iter.value();
      stream << "*NSET,NSET=" << iter.key();
      int counter = 0;
      for (int i=0;i<nodeSet.count(); i++){
        if (dotList.contains(nodeSet.at(i))){
          if (counter > 0 ) {
            stream << ",";
          }
          if (counter%15==0){
            stream << endl;
          }
          stream << dotList.indexOf(nodeSet.at(i));
          counter ++;
        }
      }
      stream << endl;
    }


  }
}
//-------------------------------------------------------------------------------------------------------

//void tAbaqusMesh::exportGroup(tElement *el)
//{
//  // zukünftig Element-Sets erstellen.
//
//}
//-------------------------------------------------------------------------------------------------------

void tAbaqusMesh::exportStructured3DGrid(tElement *el)
{
  tStructured3DGrid *G = dynamic_cast<tStructured3DGrid*>(el);
  if (G){
    G->lockElement();
    lockedElements.append(G);

    int ni = G->ni();
    int nj = G->nj();
    int nk = G->nk();

    if (ni%2==1 && nj%2 ==1 && nk%2 ==1){
      AbqElementSet abqElementSet;
      abqElementSet.caption = G->intrface()->name();
      abqElementSet.type = "C3D20";

      for (int i=0;i<ni-2; i+=2){
        for (int j=0;j<nj-2; j+=2){
          for (int k=0;k<nk-2; k+=2){
            AbqElement abqElement;
            abqElement.vertices.append(G->gridAt(i,   j,   k));
            abqElement.vertices.append(G->gridAt(i+2, j,   k));
            abqElement.vertices.append(G->gridAt(i+2, j+2, k));
            abqElement.vertices.append(G->gridAt(i,   j+2, k));

            abqElement.vertices.append(G->gridAt(i,   j,   k+2));
            abqElement.vertices.append(G->gridAt(i+2, j,   k+2));
            abqElement.vertices.append(G->gridAt(i+2, j+2, k+2));
            abqElement.vertices.append(G->gridAt(i,   j+2, k+2));

            abqElement.vertices.append(G->gridAt(i+1, j,   k));
            abqElement.vertices.append(G->gridAt(i+2, j+1, k));
            abqElement.vertices.append(G->gridAt(i+1, j+2, k));
            abqElement.vertices.append(G->gridAt(i,   j+1, k));

            abqElement.vertices.append(G->gridAt(i+1, j,   k+2));
            abqElement.vertices.append(G->gridAt(i+2, j+1, k+2));
            abqElement.vertices.append(G->gridAt(i+1, j+2, k+2));
            abqElement.vertices.append(G->gridAt(i,   j+1, k+2));

            abqElement.vertices.append(G->gridAt(i,   j,   k+1));
            abqElement.vertices.append(G->gridAt(i+2, j,   k+1));
            abqElement.vertices.append(G->gridAt(i+2, j+2, k+1));
            abqElement.vertices.append(G->gridAt(i,   j+2, k+1));

            abqElementSet.abqElements.append(abqElement);
          }
        }
      }
      abqSets.append(abqElementSet);



      // Collect FaceElements.
      tList<QString> faceNames = G->faceNames();
      for (int f=0;f<6 && f<faceNames.count() ;f++){
        QString caption = faceNames.at(f);
        if (!caption.isEmpty()){
          int i0=0, j0=0, k0=0, i1=ni, j1=nj, k1=nk;
          if (f==0){
            k0=0; k1=1;
          } else if (f==1){
            i0=ni-1; i1=ni;
          } else if (f==2) {
            k0=nk-1; k1=nk;
          } else if (f==3){
            i0=0; i1=1;
          } else if (f==4){
            j0=0; j1=1;
          } else if (f==5){
            j0=nj-1; j1=nj;
          }
          QList<tDot*>& nodeSet = nodeSets_[caption];
          for (int i=i0;i<i1; i++){
            for (int j=j0;j<j1; j++){
              for (int k=k0;k<k1; k++){
                nodeSet.append(G->gridAt(i,j,k));
              }
            }
          }
        }
      }
    }
  }
}
//-------------------------------------------------------------------------------------------------------
/*void tAbaqusMesh::exportStructured3DGrid(tElement *el)
{
  tStructured3DGrid *G = dynamic_cast<tStructured3DGrid*>(el);
  if (G){
    G->lockElement();
    lockedElements.append(G);

    AbqElementSet abqElementSet;
    abqElementSet.caption = G->intrface()->name();
    abqElementSet.type = "C3D8";
    int ni = G->ni();
    int nj = G->nj();
    int nk = G->nk();

    for (int i=0;i<ni-1; i++){
      for (int j=0;j<nj-1; j++){
        for (int k=0;k<nk-1; k++){
          AbqElement abqElement;
          abqElement.vertices.append(G->gridAt(i,   j,   k));
          abqElement.vertices.append(G->gridAt(i+1, j,   k));
          abqElement.vertices.append(G->gridAt(i+1, j+1, k));
          abqElement.vertices.append(G->gridAt(i,   j+1, k));
          abqElement.vertices.append(G->gridAt(i,   j,   k+1));
          abqElement.vertices.append(G->gridAt(i+1, j,   k+1));
          abqElement.vertices.append(G->gridAt(i+1, j+1, k+1));
          abqElement.vertices.append(G->gridAt(i,   j+1, k+1));
          abqElementSet.abqElements.append(abqElement);
        }
      }
    }
    abqSets.append(abqElementSet);



    // Collect FaceElements.
    tList<QString> faceNames = G->faceNames();
    for (int f=0;f<6 && f<faceNames.count() ;f++){
      QString caption = faceNames.at(f);
      if (!caption.isEmpty()){
        int i0=0, j0=0, k0=0, i1=ni, j1=nj, k1=nk;
        if (f==0){
          k0=0; k1=1;
        } else if (f==1){
          i0=ni-1; i1=ni;
        } else if (f==2) {
          k0=nk-1; k1=nk;
        } else if (f==3){
          i0=0; i1=1;
        } else if (f==4){
          j0=0; j1=1;
        } else if (f==5){
          j0=nj-1; j1=nj;
        }
        QList<tDot*>& nodeSet = nodeSets_[caption];
        for (int i=i0;i<i1; i++){
          for (int j=j0;j<j1; j++){
            for (int k=k0;k<k1; k++){
              nodeSet.append(G->gridAt(i,j,k));
            }
          }
        }
      }
    }

  }
}
//-------------------------------------------------------------------------------------------------------
*/
void tAbaqusMesh::exportStructured2DGrid(tElement *el)
{
  tStructured2DGrid *G = dynamic_cast<tStructured2DGrid*>(el);
  if (G){
    G->lockElement();
    lockedElements.append(G);

    bool isReversed = !G->orientation();

    int ni = G->ni();
    int nj = G->nj();

    if (ni%2==1 && nj%2 ==1){

      AbqElementSet abqElementSet;
      abqElementSet.caption = G->intrface()->name();
      abqElementSet.type = "S8";

      for (int i=0;i<ni-2; i+=2){
        for (int j=0;j<nj-2; j+=2){
          AbqElement abqElement;
          if (!isReversed){
            abqElement.vertices.append(G->gridAt(i,   j  ));
            abqElement.vertices.append(G->gridAt(i+2, j  ));
            abqElement.vertices.append(G->gridAt(i+2, j+2));
            abqElement.vertices.append(G->gridAt(i,   j+2));
            abqElement.vertices.append(G->gridAt(i+1, j  ));
            abqElement.vertices.append(G->gridAt(i+2, j+1  ));
            abqElement.vertices.append(G->gridAt(i+1, j+2));
            abqElement.vertices.append(G->gridAt(i,   j+1));
          } else {
            abqElement.vertices.append(G->gridAt(i,   j  ));
            abqElement.vertices.append(G->gridAt(i,   j+2));
            abqElement.vertices.append(G->gridAt(i+2, j+2));
            abqElement.vertices.append(G->gridAt(i+2, j  ));
            abqElement.vertices.append(G->gridAt(i,   j+1));
            abqElement.vertices.append(G->gridAt(i+1, j+2));
            abqElement.vertices.append(G->gridAt(i+2, j+1  ));
            abqElement.vertices.append(G->gridAt(i+1, j  ));

          }
          abqElementSet.abqElements.append(abqElement);
        }
      }
      abqSets.append(abqElementSet);

    }
  }

}
//-------------------------------------------------------------------------------------------------------
