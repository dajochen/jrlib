#include "element/misc/3DGrid/tStructured3DBlockMeshGrid.h"

#include "element/point/tPoint.h"

#include "classes/utils.h"

//------------------------------------------------------------------------------------------------

tStructured3DBlockMeshGrid::tStructured3DBlockMeshGrid(void *theowner): tStructured3DGrid(theowner)
{
  niSoll_ = 0;
  njSoll_ = 0;
  nkSoll_ = 0;
  for (int n=0; n<8;n++){
    corners_[n] = NULL;
  }
  for (int n=0; n<12;n++){
    edges_[n] = NULL;
  }
  for (int n=0; n<6;n++){
    faces_[n] = NULL;
  }

}
//------------------------------------------------------------------------------------------------

tStructured3DBlockMeshGrid::~tStructured3DBlockMeshGrid()
{
  for (int n=0; n<8;n++){
    if (corners_[n]){
      corners_[n]->removeDependent(this);
      corners_[n] = NULL;
    }
  }
  for (int n=0; n<12;n++){
    if (edges_[n]){
      edges_[n]->removeDependent(this);
      edges_[n] = NULL;
    }
  }
  for (int n=0; n<6;n++){
    if (faces_[n]){
      faces_[n]->removeDependent(this);
      faces_[n] = NULL;
    }
  }
}
//------------------------------------------------------------------------------------------------

iElement* tStructured3DBlockMeshGrid::intrface(void)
{
  if (iface == NULL){
    iface = new iStructured3DBlockMeshGrid(this);
  }
  return iface;
}
//------------------------------------------------------------------------------------------------

//int tStructured3DBlockMeshGrid::ni(void)
//{
//  update();
//  return ni_;
//};
////------------------------------------------------------------------------------------------------
//
//int tStructured3DBlockMeshGrid::nj(void)
//{
//  update();
//  return nj_;
//};
////------------------------------------------------------------------------------------------------
//
//int tStructured3DBlockMeshGrid::nk(void)
//{
//  update();
//  return nk_;
//};
////------------------------------------------------------------------------------------------------
//
//void tStructured3DBlockMeshGrid::setDot(int i, int j, int k, tVector value)
//{
//  int index = ijk(i,j,k);
//  if (dots.at(index)){
//    dots.at(index)->releaseOwner(this);
//  }
//  dots.setAt(index, new tPoint(this, value));
//}
////------------------------------------------------------------------------------------------------
//
//void tStructured3DBlockMeshGrid::clearDots(void)
//{
//  int i,j,k;
//  // Liste leeren und neue NULL-Liste erstellen.
//  for (int i=0;i<dots.count();i++){
//    tDot* d = dots.at(i);
//    if (d){
//      dots.at(i)->releaseOwner(this);
//    }
//  }
//  dots.clear();
//  for(k=0;k<nk_;k++){
//    for(j=0;j<nj_;j++){
//      for(i=0;i<ni_;i++){
//        dots.append(NULL);
//      }
//    }
//  }
//}
//------------------------------------------------------------------------------------------------

tVector tStructured3DBlockMeshGrid::faceCorrection(int i, int j, int k, tVector* vs)
{
  double ii = (double)i/(double)(ni_-1);
  double jj = (double)j/(double)(nj_-1);
  double kk = (double)k/(double)(nk_-1);

  tVector imp0( (1.0 - ii)*(1.0 - jj)*(1.0 - kk)     + ii*(1.0 - jj)*(1.0 - kk),
                (1.0 - jj)*(1.0 - ii)*(1.0 - kk)     + jj*(1.0 - ii)*(1.0 - kk),
                (1.0 - kk)*(1.0 - ii)*(1.0 - jj)     + kk*(1.0 - ii)*(1.0 - jj));

  tVector imp1( (1.0 - ii)*jj*(1.0 - kk)             + ii*jj*(1.0 - kk),
                (1.0 - jj)*ii*(1.0 - kk)             + jj*ii*(1.0 - kk) ,
                (1.0 - kk)*ii*(1.0 - jj)             + kk*ii*(1.0 - jj));

  tVector imp2( (1.0 - ii)*jj*kk                     + ii*jj*kk,
                (1.0 - jj)*ii*kk                     + jj*ii*kk,
                (1.0 - kk)*ii*jj                     + kk*ii*jj);

  tVector imp3( (1.0 - ii)*(1.0 - jj)*kk             + ii*(1.0 - jj)*kk,
                (1.0 - jj)*(1.0 - ii)*kk             + jj*(1.0 - ii)*kk,
                (1.0 - kk)*(1.0 - ii)*jj             + kk*(1.0 - ii)*jj);

  //Linearisierte Punkte auf den Kanten
  tVector P[12];
  if (dots.at(ijk(i    ,0,    0    ))) {P[0]  = dots.at(ijk(i    ,0    ,0    ))->vector();} else {P[0] = vs[0]*(1.-ii) + vs[1]*ii;}
  if (dots.at(ijk(i    ,nj_-1,0    ))) {P[1]  = dots.at(ijk(i    ,nj_-1,0    ))->vector();} else {P[1] = vs[3]*(1.-ii) + vs[2]*ii;}
  if (dots.at(ijk(i    ,nj_-1,nk_-1))) {P[2]  = dots.at(ijk(i    ,nj_-1,nk_-1))->vector();} else {P[2] = vs[7]*(1.-ii) + vs[6]*ii;}
  if (dots.at(ijk(i    ,0    ,nk_-1))) {P[3]  = dots.at(ijk(i    ,0    ,nk_-1))->vector();} else {P[3] = vs[4]*(1.-ii) + vs[5]*ii;}
  if (dots.at(ijk(0    ,j    ,0    ))) {P[4]  = dots.at(ijk(0    ,j    ,0    ))->vector();} else {P[4] = vs[0]*(1.-jj) + vs[3]*jj;}
  if (dots.at(ijk(ni_-1,j    ,0    ))) {P[5]  = dots.at(ijk(ni_-1,j    ,0    ))->vector();} else {P[5] = vs[1]*(1.-jj) + vs[2]*jj;}
  if (dots.at(ijk(ni_-1,j    ,nk_-1))) {P[6]  = dots.at(ijk(ni_-1,j    ,nk_-1))->vector();} else {P[6] = vs[5]*(1.-jj) + vs[6]*jj;}
  if (dots.at(ijk(0,    j    ,nk_-1))) {P[7]  = dots.at(ijk(0,    j    ,nk_-1))->vector();} else {P[7] = vs[4]*(1.-jj) + vs[7]*jj;}
  if (dots.at(ijk(0    ,0    ,k    ))) {P[8]  = dots.at(ijk(0    ,0    ,k    ))->vector();} else {P[8] = vs[0]*(1.-kk) + vs[4]*kk;}
  if (dots.at(ijk(ni_-1,0    ,k    ))) {P[9]  = dots.at(ijk(ni_-1,0    ,k    ))->vector();} else {P[9] = vs[1]*(1.-kk) + vs[5]*kk;}
  if (dots.at(ijk(ni_-1,nj_-1,k    ))) {P[10] = dots.at(ijk(ni_-1,nj_-1,k    ))->vector();} else {P[10] =vs[2]*(1.-kk) + vs[6]*kk;}
  if (dots.at(ijk(0    ,nj_-1,k    ))) {P[11] = dots.at(ijk(0    ,nj_-1,k    ))->vector();} else {P[11] =vs[3]*(1.-kk) + vs[7]*kk;}


//  P[0] = vs[0]*(1.-ii) + vs[1]*ii;
//  P[1] = vs[3]*(1.-ii) + vs[2]*ii;
//  P[2] = vs[7]*(1.-ii) + vs[6]*ii;
//  P[3] = vs[4]*(1.-ii) + vs[5]*ii;
//  P[4] = vs[0]*(1.-jj) + vs[3]*jj;
//  P[5] = vs[1]*(1.-jj) + vs[2]*jj;
//  P[6] = vs[5]*(1.-jj) + vs[6]*jj;
//  P[7] = vs[4]*(1.-jj) + vs[7]*jj;
//  P[8] = vs[0]*(1.-kk) + vs[4]*kk;
//  P[9] = vs[1]*(1.-kk) + vs[5]*kk;
//  P[10] =vs[2]*(1.-kk) + vs[6]*kk;
//  P[11] =vs[3]*(1.-kk) + vs[7]*kk;

/*
  tVector corx0 = (P[0] - dots.at(ijk(i,0,    0    ))->vector())*imp0.x;
  tVector corx1 = (P[1] - dots.at(ijk(i,nj_-1,0    ))->vector())*imp1.x;
  tVector corx2 = (P[2] - dots.at(ijk(i,nj_-1,nk_-1))->vector())*imp2.x;
  tVector corx3 = (P[3] - dots.at(ijk(i,0,    nk_-1))->vector())*imp3.x;

  tVector cory0 = (P[4] - dots.at(ijk(0,     j,    0    ))->vector())*imp0.y;
  tVector cory1 = (P[5] - dots.at(ijk(ni_-1, j,    0    ))->vector())*imp1.y;
  tVector cory2 = (P[6] - dots.at(ijk(ni_-1, j,    nk_-1))->vector())*imp2.y;
  tVector cory3 = (P[7] - dots.at(ijk(0,     j,    nk_-1))->vector())*imp3.y;

  tVector corz0 = (P[8] - dots.at(ijk(0,     0,    k))->vector())*imp0.z;
  tVector corz1 = (P[9] - dots.at(ijk(ni_-1, 0,    k))->vector())*imp0.z;
  tVector corz2 = (P[10]- dots.at(ijk(ni_-1, nj_-1,k))->vector())*imp0.z;
  tVector corz3 = (P[11]- dots.at(ijk(0,     nj_-1,k))->vector())*imp0.z;
*/
  tVector magImp = imp0 + imp1 + imp2 + imp3;
  imp0.x /= magImp.x;
  imp1.x /= magImp.x;
  imp2.x /= magImp.x;
  imp3.x /= magImp.x;
  imp0.y /= magImp.y;
  imp1.y /= magImp.y;
  imp2.y /= magImp.y;
  imp3.y /= magImp.y;
  imp0.z /= magImp.z;
  imp1.z /= magImp.z;
  imp2.z /= magImp.z;
  imp3.z /= magImp.z;

  tVector PLin;
  PLin = ( P[0] * imp0.x
         + P[1] * imp1.x
         + P[2] * imp2.x
         + P[3] * imp3.x
         + P[4] * imp0.y
         + P[5] * imp1.y
         + P[6] * imp2.y
         + P[7] * imp3.y
         + P[8] * imp0.z
         + P[9] * imp1.z
         + P[10] * imp2.z
         + P[11] * imp3.z) * (1./3.);

//  tVector correction = (corx0 + corx1 + corx2 + corx3
//                      + cory0 + cory1 + cory2 + cory3
//                      + corz0 + corz1 + corz2 + corz3)*(-1.);
//  return PLin + correction;
  return PLin;

}
//------------------------------------------------------------------------------------------------

tVector tStructured3DBlockMeshGrid::volumeCorrection(int i, int j, int k, tVector* vs)
{
  double ii = (double)i/(double)(ni_-1);
  double jj = (double)j/(double)(nj_-1);
  double kk = (double)k/(double)(nk_-1);

  tVector imp0( (1.0 - ii)*(1.0 - jj)*(1.0 - kk)     + ii*(1.0 - jj)*(1.0 - kk),
                (1.0 - jj)*(1.0 - ii)*(1.0 - kk)     + jj*(1.0 - ii)*(1.0 - kk),
                (1.0 - kk)*(1.0 - ii)*(1.0 - jj)     + kk*(1.0 - ii)*(1.0 - jj));

  tVector imp1( (1.0 - ii)*jj*(1.0 - kk)             + ii*jj*(1.0 - kk),
                (1.0 - jj)*ii*(1.0 - kk)             + jj*ii*(1.0 - kk) ,
                (1.0 - kk)*ii*(1.0 - jj)             + kk*ii*(1.0 - jj));

  tVector imp2( (1.0 - ii)*jj*kk                     + ii*jj*kk,
                (1.0 - jj)*ii*kk                     + jj*ii*kk,
                (1.0 - kk)*ii*jj                     + kk*ii*jj);

  tVector imp3( (1.0 - ii)*(1.0 - jj)*kk             + ii*(1.0 - jj)*kk,
                (1.0 - jj)*(1.0 - ii)*kk             + jj*(1.0 - ii)*kk,
                (1.0 - kk)*(1.0 - ii)*jj             + kk*(1.0 - ii)*jj);

  //Linearisierte Punkte auf den Kanten
  tVector P[12];
  P[0] = vs[0]*(1.-ii) + vs[1]*ii;
  P[1] = vs[3]*(1.-ii) + vs[2]*ii;
  P[2] = vs[7]*(1.-ii) + vs[6]*ii;
  P[3] = vs[4]*(1.-ii) + vs[5]*ii;
  P[4] = vs[0]*(1.-jj) + vs[3]*jj;
  P[5] = vs[1]*(1.-jj) + vs[2]*jj;
  P[6] = vs[5]*(1.-jj) + vs[6]*jj;
  P[7] = vs[4]*(1.-jj) + vs[7]*jj;
  P[8] = vs[0]*(1.-kk) + vs[4]*kk;
  P[9] = vs[1]*(1.-kk) + vs[5]*kk;
  P[10] =vs[2]*(1.-kk) + vs[6]*kk;
  P[11] =vs[3]*(1.-kk) + vs[7]*kk;

  //Linearisierte Punkte auf den Faces
  tVector FLin[6];
  FLin[0] = (P[0] * (1.-jj) + P[1]*jj + P[4]*(1.-ii) + P[5]*ii) * 0.5;
  FLin[2] = (P[3] * (1.-jj) + P[2]*jj + P[7]*(1.-ii) + P[6]*ii) * 0.5;

  FLin[1] = (P[9] * (1.-jj) + P[10]*jj + P[5]*(1.-kk) + P[6]*kk) * 0.5;
  FLin[3] = (P[8] * (1.-jj) + P[11]*jj + P[4]*(1.-kk) + P[7]*kk) * 0.5;

  FLin[4] = (P[0] * (1.-kk) + P[3]*kk + P[8]*(1.-ii) + P[9]*ii) * 0.5;
  FLin[5] = (P[1] * (1.-kk) + P[2]*kk + P[11]*(1.-ii) + P[10]*ii) * 0.5;


  tVector magImp = imp0 + imp1 + imp2 + imp3;
  imp0.x /= magImp.x;
  imp1.x /= magImp.x;
  imp2.x /= magImp.x;
  imp3.x /= magImp.x;
  imp0.y /= magImp.y;
  imp1.y /= magImp.y;
  imp2.y /= magImp.y;
  imp3.y /= magImp.y;
  imp0.z /= magImp.z;
  imp1.z /= magImp.z;
  imp2.z /= magImp.z;
  imp3.z /= magImp.z;

  tVector PLin;
  PLin = ( P[0] * imp0.x
         + P[1] * imp1.x
         + P[2] * imp2.x
         + P[3] * imp3.x
         + P[4] * imp0.y
         + P[5] * imp1.y
         + P[6] * imp2.y
         + P[7] * imp3.y
         + P[8] * imp0.z
         + P[9] * imp1.z
         + P[10] * imp2.z
         + P[11] * imp3.z) * (1./3.);

  tVector cor0 =  (FLin[0] - dots.at(ijk(i,     j,     0    ))->vector())*(1.-kk)
                 +(FLin[2] - dots.at(ijk(i,     j,     nk_-1))->vector())*kk;
  tVector cor1 =  (FLin[3] - dots.at(ijk(0,     j,     k    ))->vector())*(1.-ii)
                 +(FLin[1] - dots.at(ijk(ni_-1, j,     k    ))->vector())*ii;
  tVector cor2 =  (FLin[4] - dots.at(ijk(i,     0,     k    ))->vector())*(1.-jj)
                + (FLin[5] - dots.at(ijk(i,     nj_-1, k    ))->vector())*jj;

//  tVector cor0a =  (FLin[0] - dots.at(ijk(i,     j,     0    ))->vector())*(1.-kk),
//          cor0b =  (FLin[2] - dots.at(ijk(i,     j,     nk_-1))->vector())*kk;
//  tVector cor1a =  (FLin[3] - dots.at(ijk(0,     j,     k    ))->vector())*(1.-ii),
//          cor1b =  (FLin[1] - dots.at(ijk(ni_-1, j,     k    ))->vector())*ii;
//  tVector cor2a =  (FLin[4] - dots.at(ijk(i,     0,     k    ))->vector())*(1.-jj),
//          cor2b =  (FLin[5] - dots.at(ijk(i,     nj_-1, k    ))->vector())*jj;
  tVector correction = (cor0 + cor1 + cor2)*(-1./2.) ;
  correction.setZero();
  return PLin + correction;
}
//------------------------------------------------------------------------------------------------

void tStructured3DBlockMeshGrid::refresh(void)
{
  int i,j,k;
  tReal ii,jj,kk;

  ni_= max(niSoll_,2);
  nj_= max(njSoll_,2);
  nk_= max(nkSoll_,2);

  // Liste leeren und neue NULL-Liste erstellen.
  clearDots();

  // Werte von den Randflächen auf die Dots übertragen
  for (int f=0;f<6;f++){
    tSurface* face;
    face = faces_[f];
    if (face){
      if (f==0){
        k=0;
        for (i=0;i<ni_;i++){
          ii = (double)i/(double)(ni_-1);
          for (j=0;j<nj_;j++){
            jj = (double)j/(double)(nj_-1);
            setDot(i,j,k, face->vectorAt(ii, jj));
          }
        }
      } else if (f==1) {
        i = ni_-1;
        for (j=0;j<nj_;j++){
          jj = (double)j/(double)(nj_-1);
          for (k=0;k<nk_;k++){
            kk = (double)k/(double)(nk_-1);
            setDot(i,j,k, face->vectorAt(jj, kk));
          }
        }
      } else if (f==2) {
        k = nk_-1;
        for (i=0;i<ni_;i++){
          ii = (double)i/(double)(ni_-1);
          for (j=0;j<nj_;j++){
            jj = (double)j/(double)(nj_-1);
            setDot(i,j,k, face->vectorAt(ii, jj));
          }
        }
      } else if (f==3) {
        i = 0;
        for (j=0;j<nj_;j++){
          jj = (double)j/(double)(nj_-1);
          for (k=0;k<nk_;k++){
            kk = (double)k/(double)(nk_-1);
            setDot(i,j,k, face->vectorAt(jj, kk));
          }
        }
      } else if (f==4) {
        j = 0;
        for (i=0;i<ni_;i++){
          ii = (double)i/(double)(ni_-1);
          for (k=0;k<nk_;k++){
            kk = (double)k/(double)(nk_-1);
            setDot(i,j,k, face->vectorAt(ii, kk));
          }
        }
      } else if (f==5) {
        j = nj_-1;
        for (i=0;i<ni_;i++){
          ii = (double)i/(double)(ni_-1);
          for (k=0;k<nk_;k++){
            kk = (double)k/(double)(nk_-1);
            setDot(i,j,k, face->vectorAt(ii, kk));
          }
        }
      }
    }
  }
  // Die Edges abarbeiten
  for (int e=0;e<12;e++){
    tCurve *edge;
    edge = edges_[e];
    if (edge){
      if (e==0){
        j=0; k=0;
        for (i=0;i<ni_;i++){
          ii = (double)i/(double)(ni_-1);
          setDot(i,j,k, edge->vectorAt(ii));
        }
      } else if (e==1){
        j=nj_-1; k=0;
        for (i=0;i<ni_;i++){
          ii = (double)i/(double)(ni_-1);
          setDot(i,j,k, edge->vectorAt(ii));
        }
      } else if (e==2){
        j=nj_-1; k=nk_-1;
        for (i=0;i<ni_;i++){
          ii = (double)i/(double)(ni_-1);
          setDot(i,j,k, edge->vectorAt(ii));
        }
      } else if (e==3){
        j=0; k=nk_-1;
        for (i=0;i<ni_;i++){
          ii = (double)i/(double)(ni_-1);
          setDot(i,j,k, edge->vectorAt(ii));
        }
      } else if (e==4){
        i=0; k=0;
        for (j=0;j<nj_;j++){
          jj = (double)j/(double)(nj_-1);
          setDot(i,j,k, edge->vectorAt(jj));
        }
      } else if (e==5){
        i=ni_-1; k=0;
        for (j=0;j<nj_;j++){
          jj = (double)j/(double)(nj_-1);
          setDot(i,j,k, edge->vectorAt(jj));
        }
      } else if (e==6){
        i=ni_-1; k=nk_-1;
        for (j=0;j<nj_;j++){
          jj = (double)j/(double)(nj_-1);
          setDot(i,j,k, edge->vectorAt(jj));
        }
      } else if (e==7){
        i=0; k=nk_-1;
        for (j=0;j<nj_;j++){
          jj = (double)j/(double)(nj_-1);
          setDot(i,j,k, edge->vectorAt(jj));
        }
      } else if (e==8){
        i=0; j=0;
        for (k=0;i<nk_;k++){
          kk = (double)k/(double)(nk_-1);
          setDot(i,j,k, edge->vectorAt(kk));
        }
      } else if (e==9){
        i=ni_; j=0;
        for (k=0;i<nk_;k++){
          kk = (double)k/(double)(nk_-1);
          setDot(i,j,k, edge->vectorAt(kk));
        }
      } else if (e==10){
        i=ni_-1; j=nj_-1;
        for (k=0;i<nk_;k++){
          kk = (double)k/(double)(nk_-1);
          setDot(i,j,k, edge->vectorAt(kk));
        }
      } else if (e==11){
        i=0; j=nj_-1;
        for (k=0;i<nk_;k++){
          kk = (double)k/(double)(nk_-1);
          setDot(i,j,k, edge->vectorAt(kk));
        }
      }
    }
  }

  //Die Ecken
  for (int c=0;c<8;c++){
    tDot *corner;
    corner = corners_[c];
    if (corner){
      if (c==0){
        setDot(0,  0,  0, tVector(corners_[c]->vector()));
      } else if (c==1){
        setDot(ni_-1,0,  0, tVector(corners_[c]->vector()));
      } else if (c==2){
        setDot(ni_-1,nj_-1,0, tVector(corners_[c]->vector()));
      } else if (c==3){
        setDot(0,  nj_-1,0, tVector(corners_[c]->vector()));
      } else if (c==4){
        setDot(0,  0,  nk_-1, tVector(corners_[c]->vector()));
      } else if (c==5){
        setDot(ni_-1,0,  nk_-1, tVector(corners_[c]->vector()));
      } else if (c==6){
        setDot(ni_-1,nj_-1,nk_-1, tVector(corners_[c]->vector()));
      } else if (c==7){
        setDot(0,  nj_-1,nk_-1, tVector(corners_[c]->vector()));
      }
    }
  }

  //Pruefen, ob zumindest die Ecken gesetzt sind.
  tDot* ds[8];
  ds[0] = dots.at(ijk(0,     0,     0));
  ds[1] = dots.at(ijk(ni_-1, 0,     0));
  ds[2] = dots.at(ijk(ni_-1, nj_-1, 0));
  ds[3] = dots.at(ijk(0,     nj_-1, 0));
  ds[4] = dots.at(ijk(0,     0,     nk_-1));
  ds[5] = dots.at(ijk(ni_-1, 0,     nk_-1));
  ds[6] = dots.at(ijk(ni_-1, nj_-1, nk_-1));
  ds[7] = dots.at(ijk(0,     nj_-1, nk_-1));

  if (ds[0] && ds[1] && ds[2] && ds[3] && ds[4] && ds[5] && ds[6] && ds[7]){
    tVector vs[8];
    for(i=0;i<8;i++){
      vs[i] = ds[i]->vector();
    }
    // Noch nicht definierte Kanten durch Interpolation auffüllen
    for (i=1;i<ni_-1;i++){
      ii = (double)i/(double)(ni_-1);
      if (!dots.at(ijk(i, 0,     0    ))) {setDot(i, 0,     0, vs[0]*(1.-ii)+vs[1]*ii); }
      if (!dots.at(ijk(i, nj_-1, 0    ))) {setDot(i, nj_-1, 0, vs[3]*(1.-ii)+vs[2]*ii); }
      if (!dots.at(ijk(i, nj_-1, nk_-1))) {setDot(i, nj_-1, nk_-1, vs[7]*(1.-ii)+vs[6]*ii); }
      if (!dots.at(ijk(i, 0,     nk_-1))) {setDot(i, 0,     nk_-1, vs[4]*(1.-ii)+vs[5]*ii); }
    }
    for (j=1;j<nj_-1;j++){
      jj = (double)j/(double)(nj_-1);
      if (!dots.at(ijk(0,     j, 0    ))) {setDot(0,     j, 0, vs[0]*(1.-jj)+vs[3]*jj); }
      if (!dots.at(ijk(ni_-1, j, 0    ))) {setDot(ni_-1, j, 0, vs[1]*(1.-jj)+vs[2]*jj); }
      if (!dots.at(ijk(ni_-1, j, nk_-1))) {setDot(ni_-1, j, nk_-1, vs[5]*(1.-jj)+vs[6]*jj); }
      if (!dots.at(ijk(0,     j, nk_-1))) {setDot(0,     j, nk_-1, vs[4]*(1.-jj)+vs[7]*jj); }
    }
    for (k=1;k<nk_-1;k++){
      kk = (double)k/(double)(nk_-1);
      if (!dots.at(ijk(0,     0,     k))) {setDot(0,     0,     k, vs[0]*(1.-kk)+vs[4]*kk); }
      if (!dots.at(ijk(ni_-1, 0,     k))) {setDot(ni_-1, 0,     k, vs[1]*(1.-kk)+vs[5]*kk); }
      if (!dots.at(ijk(ni_-1, nj_-1, k))) {setDot(ni_-1, nj_-1, k, vs[2]*(1.-kk)+vs[6]*kk); }
      if (!dots.at(ijk(0,     nj_-1, k))) {setDot(0,     nj_-1, k, vs[3]*(1.-kk)+vs[7]*kk); }
    }
    // Noch nicht definierte Faces durch Interpolation auffüllen
    //Faces 0 und 2
    for (i=1;i<ni_-1;i++){
      ii = (double)i/(double)(ni_-1);
      for (j=1;j<nj_-1;j++){
        jj = (double)j/(double)(nj_-1);
        tVector P;
        if (!dots.at(ijk(i, j, 0))) {
          P = faceCorrection(i, j, 0, vs);
          setDot(i, j, 0, P);
        }

        if (!dots.at(ijk(i, j, nk_-1))) {
          P = faceCorrection(i, j, nk_-1, vs);
          setDot(i, j, nk_-1, P);
        }
      }
    }
    //Faces 4 und 5
    for (i=1;i<ni_-1;i++){
      ii = (double)i/(double)(ni_-1);
      for (k=1;k<nk_-1;k++){
        kk = (double)k/(double)(nk_-1);
        tVector P;
        if (!dots.at(ijk(i, 0, k))) {
          P = faceCorrection(i, 0, k, vs);
          setDot(i, 0, k, P);
        }

        if (!dots.at(ijk(i, nj_-1, k))) {
          P = faceCorrection(i, nj_-1, k, vs);
          setDot(i, nj_-1, k, P);
        }
      }
    }
    //Faces 3 und 1
    for (j=1;j<nj_-1;j++){
      jj = (double)j/(double)(nj_-1);
      for (k=1;k<nk_-1;k++){
        kk = (double)k/(double)(nk_-1);
        tVector P;
        if (!dots.at(ijk(0, j, k))) {
          P = faceCorrection(0, j, k, vs);
          setDot(0, j, k, P);
        }

        if (!dots.at(ijk(ni_-1, j, k))) {
          P = faceCorrection(ni_-1, j, k, vs);
          setDot(ni_-1, j, k, P);
        }
      }
    }

    // Und nun das Volumen....
    for (i=1;i<ni_-1;i++){
      for (j=1;j<nj_-1;j++){
        for (k=1;k<nk_-1;k++){
          tVector P;
          P = volumeCorrection(i, j, k, vs);
//          P = faceCorrection(i, j, k, vs);
          setDot(i, j, k, P);
        }
      }
    }

  } else {
    clearDots();
  }

}
//------------------------------------------------------------------------------------------------

//tDot* tStructured3DBlockMeshGrid::gridAt(int i, int j, int k)
//{
//  update();
//  i = min(i, ni_-1); i = max(i,0);
//  j = min(j, nj_-1); j = max(j,0);
//  k = min(k, nk_-1); k = max(k,0);
//
//  return dots.at(ijk(i,j,k));
////  return dots.at(k*ni_*nj_ + j*ni_ + i);
//}
//------------------------------------------------------------------------------------------------

void tStructured3DBlockMeshGrid::setCorner(int c, tElement* el)
{
  c = c % 8;
  tDot *d = dynamic_cast<tDot*>(el);
  if (corners_[c]){
    corners_[c]->removeDependent(this);
  }
  if (d && d->addDependent(this)){
    corners_[c] = d;
  } else {
    corners_[c] = NULL;
  }
  invalidate(this);
}
//------------------------------------------------------------------------------------------------

void tStructured3DBlockMeshGrid::setCorners(tList<tElement*> list)
{
  while (list.count()<8){
    list.append(NULL);
  }
  for (int i=0;i<list.count();i++){
    setCorner(i,list.at(i));
  }
}
//------------------------------------------------------------------------------------------------

tDot* tStructured3DBlockMeshGrid::corner(int index)
{
  return corners_[index%8];
}
//------------------------------------------------------------------------------------------------

tList<tElement*> tStructured3DBlockMeshGrid::corners(void)
{
  tList<tElement*> list;
  for (int i=0;i<8;i++){
    list.append(corners_[i]);
  }
  return list;
}
//------------------------------------------------------------------------------------------------

tList<tElement*> tStructured3DBlockMeshGrid::edges(void)
{
  tList<tElement*> list;
  for (int i=0;i<12;i++){
    list.append(edges_[i]);
  }
  return list;
}
//------------------------------------------------------------------------------------------------

void tStructured3DBlockMeshGrid::setEdge(int e, tElement* el)
{
  e = e % 12;
  tCurve *c = dynamic_cast<tCurve*>(el);
  if (edges_[e]){
    edges_[e]->removeDependent(this);
  }
  if (c && c->addDependent(this)){
    edges_[e] = c;
  } else {
    edges_[e] = NULL;
  }
  invalidate(this);
}
//------------------------------------------------------------------------------------------------

void tStructured3DBlockMeshGrid::setEdges(tList<tElement*> list)
{
  while (list.count()<12){
    list.append(NULL);
  }
  for (int i=0;i<list.count();i++){
    setEdge(i,list.at(i));
  }
}
//------------------------------------------------------------------------------------------------

tList<tElement*> tStructured3DBlockMeshGrid::faces(void)
{
  tList<tElement*> list;
  for (int i=0;i<6;i++){
    list.append(faces_[i]);
  }
  return list;
}
//------------------------------------------------------------------------------------------------

void tStructured3DBlockMeshGrid::setFace(int f, tElement* el)
{
  f = f % 6;
  tSurface *s = dynamic_cast<tSurface*>(el);
  if (faces_[f]){
    faces_[f]->removeDependent(this);
  }
  if (s && s->addDependent(this)){
    faces_[f] = s;
  } else {
    faces_[f] = NULL;
  }
  invalidate(this);

}
//------------------------------------------------------------------------------------------------

void tStructured3DBlockMeshGrid::setFaces(tList<tElement*> list)
{
  while (list.count()<6){
    list.append(NULL);
  }
  for (int i=0;i<list.count();i++){
    setFace(i,list.at(i));
  }
}
//------------------------------------------------------------------------------------------------

