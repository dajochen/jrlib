#include <QtGui>
#include <QtOpenGL>

#include <math.h>
#include "GL/glu.h"

#include "tGLModelView.h"
#include "tModifierTools.h"
#include <jr>

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

tGLModelView::tGLModelView(void *theOwner, tModel *theModel, QWidget *parent)
  : QGLWidget(QGLFormat(QGL::SampleBuffers), parent),
    tModelView(theOwner)
{
  theParent = parent;

  if (parent){
    QHBoxLayout *mainLayout = new QHBoxLayout;
    parent->setLayout(mainLayout);
    mainLayout->addWidget(this);
    mainLayout->setContentsMargins(0,0,0,0);
  } else {
    setWindowModality(Qt::ApplicationModal);
  }

  colorBackground = QColor::fromRgbF(0.9882,0.98039,0.9568);
  // camera initialization
  ObjectPoint = tVector(0,0,0);
  EyePoint = tVector(10,0,0);
  UpDirection = tVector(0,0,1);
  ViewingAngle = 46.0;

  // mouse init
  mouseMode = mmIdle;
  fDoubleClickSelectionEnabled = true;

  // keyboard motion init
  setFocusPolicy(Qt::StrongFocus);
  modificationIncrement = 1.;
  /*speed = 0;
  turnSpeed = 0;
  pitchSpeed = 0;

  keyTimer = new QTimer(this);
  keyTimer->setInterval (1000/25); //msecs per frame
  connect(Timer, SIGNAL(timeout()), this, SLOT(animate()));*/

  //widget init
  setAutoFillBackground(false);
  setMinimumSize(200, 200);

  //animationTimer.setSingleShot(false);
  //connect(&animationTimer, SIGNAL(timeout()), this, SLOT(animate()));
  //animationTimer.start(25);
  //updateSlot();
  setModel(theModel);


  QColor Warning=Qt::red;
  Warning = Warning.light(180);
  QLineEdit *dummy = new QLineEdit();
  OkPal = dummy->palette();
  WrongPal = OkPal;
  WrongPal.setColor(QPalette::Text, Qt::black);
  WrongPal.setColor(QPalette::Base, Warning);
  delete dummy;
}

//-------------------------------------------------------------------------------

tGLModelView::~tGLModelView()
{
}
//-------------------------------------------------------------------------------

void tGLModelView::invalidate(tElement *sender)
{
  tElement::invalidate(sender);
  QGLWidget::update();
}
//-------------------------------------------------------------------------------

void tGLModelView::refresh(void)
{
  setWindowTitle (fmodel->name());
  //fSelectables->clear();
  //addToSelectable(fmodel);
}
//-------------------------------------------------------------------------------
/*
void tGLModelView::addToSelectable(tElement* el)
{
  tLayer *l = dynamic_cast<tLayer*>(el);
  fSelectables->append(el);
  if (l){
    for (int i=0; i<l->nElements(); i++){
      addToSelectable(l->element(i));
    }
  }
}*/
//-------------------------------------------------------------------------------

void tGLModelView::initializeGL()
{
  glEnable(GL_MULTISAMPLE);
}
//-------------------------------------------------------------------------------

void tGLModelView::initMouseMotion(const QPoint& position)
{
  stopKeyboardMotion();

  initialMousePos = position;
  lastMousePos = position;
}

//-------------------------------------------------------------------------------

tGLModelView::MouseModes tGLModelView::getMouseMode(QMouseEvent* event, const tGLModelView::MouseModes& baseMode )
{
  MouseModes mm = baseMode;

  //left:          mmRotate
  //right:         mmPan
  //right + Shift: mmRoll
  //
  //ALT + left: modify selection (move)

  if ( (event->button() == Qt::LeftButton && mm==mmIdle) || mm==mmRotate || mm==mmMoveElements ) {
    if (event->modifiers() & Qt::AltModifier) {
      mm = mmMoveElements;
    } else {
      mm = mmRotate;
    }
    stopKeyboardMotion();
  } else if ( (event->button() == Qt::RightButton && mm==mmIdle) || mm==mmRoll || mm==mmPan) {
    if ( event->modifiers() & Qt::ShiftModifier ){
      mm = mmRoll;
    } else {
      mm = mmPan;
    }
    stopKeyboardMotion();
  }

  if (disabledMouseModes.contains(mm)){
    mm = mmIdle;
  }

  return mm;
}
//-------------------------------------------------------------------------------

void tGLModelView::disableMouseMode(const int& mModes)
{
  tList<MouseModes> allMMs;
  allMMs.append(mmTurn);
  allMMs.append(mmRotate);
  allMMs.append(mmZoom);
  allMMs.append(mmPan);
  allMMs.append(mmRoll);
  allMMs.append(mmMoveElements);

  for (int i=0; i<allMMs.count(); i++){
    MouseModes m = allMMs.at(i);
    if (mModes&m && !disabledMouseModes.contains(m)){
      disabledMouseModes.append(m);
    }
  }
}
//-------------------------------------------------------------------------------

void tGLModelView::enableMouseMode(MouseModes m)
{
  if (disabledMouseModes.contains(m)){
    disabledMouseModes.removeAll(m);
  }
}
//-------------------------------------------------------------------------------

void tGLModelView::setView(tVector at, tVector eye, tVector up)
{
  EyePoint = at + (eye-at).normalize()*(EyePoint-ObjectPoint).length();			      // Standpunkt des Berachters
  UpDirection = up.normalize();		    // Koerperachse des aufrecht stehenden Betrachters
  ObjectPoint = at;
  QGLWidget::update();
}
//-------------------------------------------------------------------------------

void tGLModelView::mousePressEvent(QMouseEvent *event)
{
  mouseMode = getMouseMode(event);
  initMouseMotion(event->pos());
}
//-------------------------------------------------------------------------------

void tGLModelView::mouseMoveEvent(QMouseEvent *event)
{
  MouseModes LastMM;

  LastMM = mouseMode;
  if (LastMM != mmIdle) {
    mouseMode = getMouseMode(event, LastMM);


    if (mouseMode == mmRotate) {
//      if (fMovingMode==FlightMode) {
//      } else {
        double size = sqrt(QApplication::desktop()->width()*QApplication::desktop()->width()
                          +QApplication::desktop()->height()*QApplication::desktop()->height()),
               acceleration = (sqrt( (event->x()-initialMousePos.x())*(event->x()-initialMousePos.x())
                                    +(event->y()-initialMousePos.y())*(event->y()-initialMousePos.y()))
                               /size+4.)*4;
        double Range = 4*tan(ViewingAngle*0.5/180*M_PI)*(EyePoint-ObjectPoint).length(),
               dx = (event->x()-lastMousePos.x())/size*acceleration*Range,
               dy =-(event->y()-lastMousePos.y())/size*acceleration*Range;


        tVector dir, right, newdir;

        dir = ObjectPoint-EyePoint,
        right = dir%UpDirection;
        right = right*(1./right.length());

        newdir = dir+UpDirection*dy+right*dx;
        newdir = newdir*(dir.length()/newdir.length());
        UpDirection = right%newdir;
        UpDirection = UpDirection*(1./UpDirection.length());

        EyePoint = ObjectPoint-newdir;
//      }
    } else if (mouseMode == mmRoll) {
//      if (fMovingMode==FlightMode) {
//      } else {

        double w = QApplication::desktop()->width();
        double beta = 2.*M_PI*(lastMousePos.x()-event->x())/w;
        UpDirection = UpDirection.rotate(ObjectPoint-EyePoint,beta);
        UpDirection = UpDirection*(1./UpDirection.length());
        //mousePos = event->pos();


//      }
    } else if (mouseMode == mmZoom) {
//      if (fMovingMode==FlightMode) {
//      } else {
        double h = QApplication::desktop()->height(),
               alpha = (event->y()-initialMousePos.y())/h;
        alpha = pow(alpha+1.,4);
        EyePoint = EyePoint*(alpha) +ObjectPoint*(1-alpha);
//      }
    } else if (mouseMode == mmPan) {
//      if (fMovingMode==FlightMode) {
//      } else {
        double Range = 4.*tan(ViewingAngle*0.5/180*M_PI)*(EyePoint-ObjectPoint).length();

        double w = QApplication::desktop()->width(),
               h = QApplication::desktop()->height();
               w = sqrt(w*w+h*h);
        double dx = (lastMousePos.x()-event->x())/w,
               dy = (event->y()-lastMousePos.y())/w;
        tVector dir = EyePoint-ObjectPoint,
                right = UpDirection %(EyePoint - ObjectPoint);
        right = right*(1./right.length());
        ObjectPoint = ObjectPoint + right*Range*dx + UpDirection*Range*dy;
        EyePoint = ObjectPoint+dir;
//      }
    } else if (mouseMode == mmMoveElements){
        if (activeSelectionSet()) {
            double Range = 6.*tan(ViewingAngle*0.5/180*M_PI)*(EyePoint-ObjectPoint).length();

            double w = QApplication::desktop()->width(),
                    h = QApplication::desktop()->height();
            w = sqrt(w*w+h*h);
            double dx = -(lastMousePos.x()-event->x())/w,
                    dy =  (lastMousePos.y()-event->y())/w;

            tVector right = (UpDirection %(EyePoint - ObjectPoint)).normalize();

            tVector shiftDx = right*Range*dx + UpDirection*Range*dy;
            //fmodel->shiftSelection(shiftDx);
            tModifierTools::shiftElements(shiftDx, activeSelectionSet()->elements());
        }
    }
    lastMousePos = event->pos();

    QGLWidget::update();//invalidate(this);
  }
}
//-------------------------------------------------------------------------------

void tGLModelView::wheelEvent ( QWheelEvent * event )
{
  double alpha, delta;

  delta = event->delta();
  alpha = -delta / (360.*8.)+1;
  alpha = qMax(alpha, 0.2);

  alpha = pow(alpha,4);
  EyePoint = EyePoint*(alpha) +ObjectPoint*(1-alpha);
  //MEyePoint =   EyePoint;
  event->accept();
  QGLWidget::update();//invalidate(this);
}
//-------------------------------------------------------------------------------

void tGLModelView::mouseReleaseEvent(QMouseEvent */*event*/)
{
  mouseMode = mmIdle;
}
//-------------------------------------------------------------------------------

void tGLModelView::mouseDoubleClickEvent(QMouseEvent *event)
{  

  if (fDoubleClickSelectionEnabled){
    tList<tElement*> selection;
    if (activeSelectionSet()) {
      if (event->modifiers() & Qt::ControlModifier){
          selection = activeSelectionSet()->elements();
      }

      double tolerance = 3.;

      selection.append(getCloseElements(fmodel, event->x(), event->y(), tolerance));
      activeSelectionSet()->setElements( selection );
    }
  }
  QGLWidget::update();
}
//-------------------------------------------------------------------------------

void tGLModelView::keyPressEvent(QKeyEvent *event)
{
  if (mouseMode != mmIdle) {
    event->ignore();
  } else {
    stopKeyboardMotion();
    if (event->modifiers() & Qt::AltModifier){
      tVector up = UpDirection.normalize();
      tVector right = ((ObjectPoint-EyePoint)%UpDirection).normalize();
      tVector lookDir = up%right;

      double shiftRange = 0.1*tan(ViewingAngle*0.5/180*M_PI)*(EyePoint-ObjectPoint).length();
      double rotRange = M_PI*0.25;

      if (event->key() == Qt::Key_Greater){
          modificationIncrement *= 2;//10;
          event->accept();
      } else if (event->key() == Qt::Key_Less){
        modificationIncrement *= 0.5;//0.1;
        event->accept();
      } else {
          if (activeSelectionSet()) {
              if (event->key() == Qt::Key_0){
                  tModifierTools::removeDoublicateElements(fmodel);
                event->accept();
              } else if (event->key() == Qt::Key_Left && activeSelectionSet()){
                  tModifierTools::shiftElements(right*(-shiftRange*modificationIncrement), activeSelectionSet()->elements());
                  event->accept();
              } else if (event->key() == Qt::Key_Right && activeSelectionSet()){
                  tModifierTools::shiftElements(right*(shiftRange*modificationIncrement), activeSelectionSet()->elements());
                  event->accept();
              } else if (event->key() == Qt::Key_Up) {
                  if ((event->modifiers() & Qt::ShiftModifier && activeSelectionSet())) {
                      translateDialog dlg(theParent, lookDir, shiftRange*modificationIncrement);
                      bool okVec = true, okDouble = true;
                      do {
                          if (!okVec)    {dlg.direction->setPalette(WrongPal);} else {dlg.direction->setPalette(OkPal);}
                          if (!okDouble) {dlg.distance->setPalette(WrongPal);}  else {dlg.distance->setPalette(OkPal);}
                          if (dlg.exec()){
                              tVector dir = tVectorStringConverter::toVector(dlg.direction->text(), QRegExp("[\\s;]+"), &okVec);
                              double dist = dlg.distance->text().toDouble(&okDouble);

                              if (okVec && okDouble) {
                                  tModifierTools::shiftElements(dir.normalize(dist), activeSelectionSet()->elements());
                                  //                      fmodel->shiftSelection(dir.normalize(dist));
                              }
                          }
                      } while (!okVec || !okDouble);
                  } else {
                      tModifierTools::shiftElements(up*shiftRange*modificationIncrement, activeSelectionSet()->elements());
                      //            fmodel->shiftSelection(up*shiftRange*modificationIncrement);
                  }
                  event->accept();
              } else if (event->key() == Qt::Key_Down) {
                  tModifierTools::shiftElements(up*(-shiftRange*modificationIncrement), activeSelectionSet()->elements());
                  //        fmodel->shiftSelection(up*(-shiftRange*modificationIncrement));
                  event->accept();
              } else if (event->key() == Qt::Key_R) {
                  double angle = rotRange*modificationIncrement;
                  if (event->modifiers() & Qt::ShiftModifier){
                      angle *= -1;
                  }
                  rotateDialog dlg(theParent, EyePoint, lookDir, angle/M_PI*180.);
                  bool okCenter = true, okAxis = true, okAngle = true;
                  do {
                      if (!okCenter) {dlg.point->setPalette(WrongPal);}  else {dlg.point->setPalette(OkPal);}
                      if (!okAxis)   {dlg.axis->setPalette(WrongPal);}   else {dlg.axis->setPalette(OkPal);}
                      if (!okAngle)  {dlg.angle->setPalette(WrongPal);}  else {dlg.angle->setPalette(OkPal);}
                      if (dlg.exec()){
                          tVector center = tVectorStringConverter::toVector(dlg.point->text(), QRegExp("[\\s;]+"),&okCenter);
                          tVector axis = tVectorStringConverter::toVector(dlg.axis->text(),    QRegExp("[\\s;]+"),&okAxis);
                          angle = dlg.angle->text().toDouble(&okAngle)/180.*M_PI;

                          if (okCenter && okAxis && okAngle) {
                              tModifierTools::rotateElements(center, axis.normalize()*(angle), activeSelectionSet()->elements());
                              //                fmodel->rotateSelection(center, axis.normalize()*(angle));
                          }
                      }
                  } while (!okCenter || !okAxis || !okAngle);
                  event->accept();
              } else if (event->key() == Qt::Key_F) {
                  if (event->modifiers() & Qt::ShiftModifier){
                    tModifierTools::flipElements(EyePoint, up, activeSelectionSet()->elements());
                  } else {
                      tModifierTools::flipElements(EyePoint, right, activeSelectionSet()->elements());
                  }
                  event->accept();
              }
          }
      }
    } else {// if (event->modifiers() == Qt::NoModifier) {

      if (event->key() == Qt::Key_X ||
          event->key() == Qt::Key_Y ||
          event->key() == Qt::Key_Z ||
          event->key() == Qt::Key_P) {

        tVector lookDir = ObjectPoint-EyePoint,
            newLookDir,
            newUpDir;
        double distToObject = lookDir.length();
        if (event->key() == Qt::Key_X) {
          newLookDir = tVector(1.,0.,0.);
          newUpDir = tVector(0.,1.,0.);
        } else if (event->key() == Qt::Key_Y) {
          newLookDir = tVector(0.,1.,0.);
          newUpDir = tVector(0.,0.,1.);
        } else if (event->key() == Qt::Key_Z) {
          newLookDir = tVector(0.,0.,1.);
          newUpDir = tVector(1.,0.,0.);
        } else if (event->key() == Qt::Key_P) {
          if (   activeSelectionSet()
              && activeSelectionSet()->nElements(iBasicPlane::theType()) > 0 ) {
              tBasicPlane *pl = dynamic_cast<tBasicPlane*>(activeSelectionSet()->elements(iBasicPlane::theType()).at(0));
              newLookDir = pl->normal()*(-1.);
              newUpDir = pl->horizontalDir() % newLookDir;
          }
        }

        if (event->modifiers() & Qt::ShiftModifier){
          newLookDir = newLookDir*(-1.);
        }

        if (lookDir*newLookDir == distToObject){
          UpDirection = UpDirection % lookDir;
          UpDirection = UpDirection.normalize();
        } else {
          UpDirection = newUpDir;
        }

        EyePoint = ObjectPoint - newLookDir*distToObject;

        QGLWidget::update();//invalidate(this);
        event->accept();
      } else if (event->key() == Qt::Key_F9){

        double l = (model()->xMax()-model()->xMin()).length();

        if (l!=0) {
          tVector eyeDir = (EyePoint-ObjectPoint).normalize();
          ObjectPoint = (model()->xMax()-model()->xMin())*0.5;
          EyePoint = ObjectPoint + eyeDir * (l*0.6 /tan(ViewingAngle*0.5/180.*M_PI));
        } else {
          tVector eyeDir = (EyePoint-ObjectPoint);
          ObjectPoint.setZero();
          EyePoint = ObjectPoint + eyeDir;
        }
        QGLWidget::update();
        event->accept();
      } else if (event->key() == Qt::Key_C){
        EyePoint = EyePoint - ObjectPoint;
        ObjectPoint.setZero();
        QGLWidget::update();//invalidate(this);
        event->accept();
      } else if (event->key() == Qt::Key_Plus){
        double alpha = -0.01;
        alpha = pow(alpha+1.,4);
        EyePoint = EyePoint*(alpha) +ObjectPoint*(1-alpha);
        QGLWidget::update();//invalidate(this);
        event->accept();
      } else if (event->key() == Qt::Key_Minus){
        double alpha = 0.01;
        alpha = pow(alpha+1.,4);
        EyePoint = EyePoint*(alpha) +ObjectPoint*(1-alpha);
        QGLWidget::update();//invalidate(this);
        event->accept();
      } else if (event->key() == Qt::Key_Delete){
        tList<tElement*> selection = activeSelectionSet()->elements();
        activeSelectionSet()->clear();
        fmodel->deleteElements(selection);
        event->accept();
      }

      /*
    else if (event->key() == KeyForward) {
      if (!event->isAutoRepeat() && speed < 1) {
        speed = 1;
        Timer->start();
      }
    } else if (event->key() == KeyBackward) {
      if (!event->isAutoRepeat() && speed > -1) {
        speed = -1;
        Timer->start();
      }
    } else if (event->key() == KeyTurnLeft) {
      if (!event->isAutoRepeat() && turnSpeed < 1) {
        turnSpeed = 1;
        Timer->start();
      }
    } else if (event->key() == KeyTurnRight) {
      if (!event->isAutoRepeat() && turnSpeed > -1) {
        turnSpeed = -1;
        Timer->start();
      }
    } else if (event->key() == KeyPitchDown) {
      if (!event->isAutoRepeat() && pitchSpeed < 1) {
        pitchSpeed = 1;
        Timer->start();
      }
    } else if (event->key() == KeyPitchUp) {
      if (!event->isAutoRepeat() && pitchSpeed > -1) {
        pitchSpeed = -1;
        Timer->start();
      }
    } */
      else {
        event->ignore();
      }
    }
    QGLWidget::update();//invalidate(this);
  }
}
//-------------------------------------------------------------------------------

void tGLModelView::keyReleaseEvent(QKeyEvent */*event*/)
{
/*  if (!event->isAutoRepeat() && (event->key() == KeyForward || event->key() == KeyBackward)) {
    speed = 0;
    Timer->stop();
  } if (!event->isAutoRepeat() && (event->key() == KeyTurnRight || event->key() == KeyTurnLeft)) {
    turnSpeed = 0;
    if (!speed && !pitchSpeed) Timer->stop();
  } if (!event->isAutoRepeat() && (event->key() == KeyPitchUp || event->key() == KeyPitchDown)) {
    pitchSpeed = 0;
    if (!speed && !turnSpeed) Timer->stop();
  } else {
    event->ignore();
  }*/
}
//-------------------------------------------------------------------------------

void tGLModelView::paintEvent(QPaintEvent */*event*/)
{
  tModelView::update();
  makeCurrent();

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  //background
  qglClearColor(colorBackground);

  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT2);
  glEnable(GL_MULTISAMPLE);

  //static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
  tVector right = (ObjectPoint-EyePoint) % UpDirection;

  static GLfloat lightPosition[4] = { (GLfloat)(-UpDirection.x*10.), (GLfloat)(-UpDirection.y*10.), (GLfloat)(-UpDirection.z*10.), 1.0 };
  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
  static GLfloat lightPosition1[4] = { (GLfloat)(-right.x*10.), (GLfloat)(-right.y*10.), (GLfloat)(-right.z*10.), 0.4 };
  glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);
  static GLfloat lightPosition2[4] = { (GLfloat)(right.x*10.), (GLfloat)(right.y*10.), (GLfloat)(right.z*10.), 0.4 };
  glLightfv(GL_LIGHT2, GL_POSITION, lightPosition2);

  setupViewport(width(), height());

  glMatrixMode(GL_MODELVIEW);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  //shading
  glShadeModel(GL_FLAT);
  glDisable(GL_CULL_FACE);
  //glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);

  glMatrixMode(GL_MODELVIEW);
//  glPopMatrix();


  glLoadIdentity();
//  if (fMovingMode == FlightMode) {
//    tVector viewingDirection = ObjectPoint-EyePoint;
//    gluLookAt(EyePoint.x,EyePoint.y,EyePoint.z,
//              EyePoint.x+viewingDirection.x,EyePoint.y+viewingDirection.y,EyePoint.z+viewingDirection.z,
//              UpDirection.x,UpDirection.y,UpDirection.z);
//  } else {// ObjectMode
    gluLookAt(EyePoint.x,EyePoint.y,EyePoint.z,
              ObjectPoint.x,ObjectPoint.y,ObjectPoint.z,
              UpDirection.x,UpDirection.y,UpDirection.z);
//  }


  textItems.clear();
  paintData();
  glFlush();

  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  paintTextItems(&painter);
  painter.end();

}
//-------------------------------------------------------------------------------

void tGLModelView::resizeGL(int width, int height)
{
  setupViewport(width, height);
}
//-------------------------------------------------------------------------------

void tGLModelView::showEvent(QShowEvent *event)
{
  Q_UNUSED(event);
}
//-------------------------------------------------------------------------------

QSize tGLModelView::sizeHint() const
{
  return QSize(400, 400);
}
//-------------------------------------------------------------------------------

//void GLWidget::animate()
//{
  //keyboard motion implementieren
//}

//void GLWidget::updateSlot()
//{
//  setWindowTitle(fmodel->name());
//  update();
//}

//-------------------------------------------------------------------------------

void tGLModelView::setupViewport(int width, int height)
{
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

//  if (fProjection == Ortho) {
    GLfloat range = tan(ViewingAngle*0.5/180.*M_PI)*(EyePoint-ObjectPoint).length();
    GLfloat aspect = float(width)/float(height);
    if (width <= height) {
      glOrtho (-range,range,-range/aspect,range/aspect,-1000.0*range,1000.0*range);
    } else {
      glOrtho (-range*aspect,range*aspect,-range,range,-1000.0*range,1000.0*range);
    }
//  } else {
//    gluPerspective (ViewingAngle,aspect,0.01,1000);
//  }
}
//-------------------------------------------------------------------------------

tList<tElement*> tGLModelView::getCloseElements(tElement *el, int x, int y, double tolerance)
{
    tList<tElement*> found;
    if (el->intrface()->visibility()) {
        tLayer *l = dynamic_cast<tLayer*>(el);
        if (l){
            for (int i=0; i<l->nElements(); i++) {
                found.append( getCloseElements(l->element(i), x, y, tolerance) );
            }
        } else {
            double dist = calcDisplayDistance(el,x,y);
            if (dist < tolerance && dist >= 0) {
                found.append( el );
            }
        }
    }
    return found;
}
//-------------------------------------------------------------------------------

tReal tGLModelView::calcDisplayDistance(tElement *el, int x, int y) {

  iElement *I;
  tReal dist;
  GLint viewport[4];
  GLdouble modelview[16], projection[16];

  glGetDoublev(GL_MODELVIEW_MATRIX, modelview); //Aktuelle Modelview Matrix in einer Variable ablegen
  glGetDoublev(GL_PROJECTION_MATRIX, projection); //Aktuelle Projection[s] Matrix in einer Variable ablegen
  glGetIntegerv(GL_VIEWPORT, viewport); // Aktuellen Viewport in einer Variable ablegen

  // Errechnen des Punktes, welcher mit den beiden Matrizen multipliziert (X/Y_new/Z) ergibt:
  dist = -1;


  if (el){
    el->lockElement();
    I = el->intrface();
    if (I->visibility()){
      if (tDot* d = dynamic_cast<tDot*>(el)) {
        tVector xx,p;
        xx = d->vector();
        gluProject(xx.x,xx.y,xx.z,modelview,projection,viewport,&p.x,&p.y,&p.z);
        p.y = viewport[3]	-p.y-1;
        p = p-tVector(x,y,p.z);
        dist = p.length();
      } else if (tCurve* c = dynamic_cast<tCurve*>(el)){
        int t, tRes;
        tReal l, l1,r1, r2;
        tVector *cache, P1,P2, X, X1, X2, R1, R2;

        X.x = x;
        X.y = y;
        X.z = 0;
        P1.setZero();
        P2.setZero();
        tRes = c->tResolution();
        if (tRes>0){
          cache = c->tCache();
          X2 = cache[0];
          gluProject(X2.x,X2.y,X2.z,modelview,projection,viewport,&P2.x,&P2.y,&l1);
          P2.y = viewport[3] -P2.y-1;
          R2 = P2-X;
          r2 = R2.length();

          for (t=0;t<tRes;t++) {
            X2 = cache[t+1];
            // Werte vom vorherigen Punkt uebernehmen
            P1 = P2;
            R1 = R2;
            r1 = r2;
            // Die Werte fuer den zweiten Punkt berechnen
            gluProject(X2.x,X2.y,X2.z,modelview,projection,viewport,&P2.x,&P2.y,&l1);
            P2.y = viewport[3] -P2.y-1;
            R2 = P2-X;
            r2 = R2.length();
            // Abstand bestimmen
            l = (P1-P2).length();
            l1 = (R1%R2).length()/l;
            if (r1 < l && r2 < l) {
              //l1 = l1;
            } else {
              l1 = qMin(r1,r2);
            }
            if (l1 < dist || dist < 0){
              dist = l1;
            }
          }
        }
      } else if (tSurface* s = dynamic_cast<tSurface*>(el)){
        int u, v, nu, nv, uDiv, vDiv, uRes, vRes;
        tReal l, l1, r1, r2;
        tVector *cache, P1,P2, X, X1, X2, R1, R2;

        X.x = x;
        X.y = y;
        X.z = 0;
        P1.setZero();
        P2.setZero();
        uRes = s->uRes();
        vRes = s->vRes();
        uDiv = s->uDiv();
        vDiv = s->vDiv();
        nu = uDiv * uRes;
        nv = vDiv * vRes;

        if (nu > 0 && nv>0){
          cache = s->uvCache();

          for (u=0;u<=nu;u+=uRes){
            v = 0;
            X2 = cache[v*(nu+1)+u];
            gluProject(X2.x,X2.y,X2.z,modelview,projection,viewport,&P2.x,&P2.y,&l1);
            P2.y = viewport[3] -P2.y-1;
            R2 = P2-X;
            r2 = R2.length();
            for (v=0;v<nv;v++) {
              // Werte vom vorherigen Punkt uebernehmen
              P1 = P2;
              R1 = R2;
              r1 = r2;
              // Die Werte fuer den zweiten Punkt berechnen
              X2 = cache[(v+1)*(nu+1)+u];
              gluProject(X2.x,X2.y,X2.z,modelview,projection,viewport,&P2.x,&P2.y,&l1);
              P2.y = viewport[3] -P2.y-1;
              R2 = P2-X;
              r2 = R2.length();
              // Abstand bestimmen
              l = (P1-P2).length();
              l1 = (R1%R2).length()/l;
              if (r1 < l && r2 < l) {
                //l1 = l1;
              } else {
                l1 = qMin(r1,r2);
              }
              if (l1 < dist || dist < 0){
                dist = l1;
              }
            }
          }
          for (v=0;v<=nv;v+=vRes){
            u = 0;
            X2 = cache[v*(nu+1)+u];
            gluProject(X2.x,X2.y,X2.z,modelview,projection,viewport,&P2.x,&P2.y,&l1);
            P2.y = viewport[3] -P2.y-1;
            R2 = P2-X;
            r2 = R2.length();
            for (u=0;u<nu;u++) {
              // Werte vom vorherigen Punkt uebernehmen
              P1 = P2;
              R1 = R2;
              r1 = r2;
              // Die Werte fuer den zweiten Punkt berechnen
              X2 = cache[v*(nu+1)+u+1];
              gluProject(X2.x,X2.y,X2.z,modelview,projection,viewport,&P2.x,&P2.y,&l1);
              P2.y = viewport[3] -P2.y-1;
              R2 = P2-X;
              r2 = R2.length();
              // Abstand bestimmen
              l = (P1-P2).length();
              l1 = (R1%R2).length()/l;
              if (r1 < l && r2 < l) {
                //l1 = l1;
              } else {
                l1 = qMin(r1,r2);
              }
              if (l1 < dist || dist < 0){
                dist = l1;
              }
            }
          }
        }
      }
    }
    el->unlockElement();
  }
  return dist;
}
//------------------------------------------------------------------------------------

void tGLModelView::paintData()
{
  refSize = tan(ViewingAngle*0.5/180*M_PI)*(EyePoint-ObjectPoint).length();
  unityUp = UpDirection*(1./UpDirection.length());
  unityRight = ((EyePoint-ObjectPoint)%unityUp);
  unityRight = unityRight*(1./unityRight.length());

  // Normalenvektor fuer die Beleuchtung, wenn es sonst keinen gibt.
  defaultN = EyePoint-ObjectPoint;
  defaultN = defaultN*(1./defaultN.length());

  for (int i=0;fmodel && i<2;i++){
    if (i==0) {
      paintSolids = true;
      glDisable(GL_BLEND);
      glDepthFunc(GL_LEQUAL);
      glDepthMask(GL_TRUE);
    } if (i==1) {
      paintSolids = false;
      glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
      glEnable(GL_BLEND);
      glDepthFunc(GL_LEQUAL);
      glDepthMask(GL_TRUE);
    }

    paintElement(fmodel);
  }

  // Koordinatensystem
  glNormal3f(defaultN.x,defaultN.y,defaultN.z);
  glColor3ub (128,128,128);
  tVector xx, yy, zz;
  xx = tVector(0.1*refSize,0,0);
  yy = tVector(0,0.1*refSize,0);
  zz = tVector(0,0,0.1*refSize);

  glBegin (GL_LINES);
    glVertex3f (0,0,0);
    glVertex3f (xx.x, xx.y ,xx.z);
  glEnd();
  paintCone(xx,xx*0.4,xx.length()*0.1,10);
  glBegin (GL_LINES);
    glVertex3f (0,0,0);
    glVertex3f (yy.x, yy.y ,yy.z);
  glEnd();
  paintCone(yy,yy*0.4,yy.length()*0.1,10);
  glBegin (GL_LINES);
    glVertex3f (0,0,0);
    glVertex3f (zz.x, zz.y ,zz.z);
  glEnd();
  paintCone(zz,zz*0.4,zz.length()*0.1,10);

  paintText(xx*1.02,"x");
  paintText(yy*1.02,"y");
  paintText(zz*1.02,"z");
}
//-------------------------------------------------------------------------------
/**
 Paints element el. If interface object is given, I is used instead of the elements interface.
 */
void tGLModelView::paintElement(tElement *el, iElement* I)
{
  double FR = 1.;
  tReal pointSize;
  bool isSelected = false;
  tRGB rgb;

  if (el){
    el->lockElement();
    if (!I) {I = el->intrface();}

    if (I){
      if (I->visibility()){

        // Elemente ohne direkten Zeichenauftrag abarbeiten.
        if (tLayer* layer = dynamic_cast<tLayer*>(el)){
          int i, ni = layer->nElements();
          for (i=0;i<ni;i++) {
            paintElement(layer->element(i));
          }
        } else {

          // Alle Elemente mit direktem Zeichenauftrag abarbeiten.
          rgb = I->color();

          if ((paintSolids && rgb.alpha>=255) || (!paintSolids &&rgb.alpha<255)){

            if (activeSelectionSet() && activeSelectionSet()->contains(el)){
              isSelected = true;
              glLineWidth(3);
              rgb = tRGB(255, 95,9, 255);
              //glColor4ub (rgb.red, rgb.green, rgb.blue, rgb.alpha);//some orange for selections
              //glColor4ub ((rgb.red+255)/2,(rgb.green+255)/2,rgb.blue+255/2,(rgb.alpha+255)/2);
              pointSize = 0.012;
            } else {
              isSelected = false;
              glLineWidth(1);
              glColor4ub (rgb.red, rgb.green, rgb.blue, rgb.alpha);
              pointSize = 0.008;
            }


            if (tDot* d = dynamic_cast<tDot*>(el)) {
              double x,y,z;
              tVector ud,rd;
              ud = unityUp*refSize*pointSize;
              rd = unityRight*refSize*pointSize;
              x = d->x();
              y = d->y();
              z = d->z();
              glNormal3f(defaultN.x,defaultN.y,defaultN.z);
              glBegin(GL_POLYGON);
                glVertex3d (x+ud.x+rd.x, y+ud.y+rd.y, z+ud.z+rd.z);
                glVertex3d (x+ud.x-rd.x, y+ud.y-rd.y, z+ud.z-rd.z);
                glVertex3d (x-ud.x-rd.x, y-ud.y-rd.y, z-ud.z-rd.z);
                glVertex3d (x-ud.x+rd.x, y-ud.y+rd.y, z-ud.z+rd.z);
              glEnd();
            } else if (tPaintableElement* pe = dynamic_cast<tPaintableElement*>(el)) {
                pe->paintGL(EyePoint, ObjectPoint, rgb, defaultN, isSelected);
          /*  } else if (tCurve* c = dynamic_cast<tCurve*>(el)) {
                c->paintGL(EyePoint, ObjectPoint, rgb, defaultN, isSelected);


              tVector *x;
              tReal pos = c->arrowheadPos();
              int tRes = c->tResolution();
              glNormal3f(defaultN.x,defaultN.y,defaultN.z);
              //iCurve* intrface;
              //intrface = dynamic_cast<iCurve*>(c->intrface());
              x = c->tCache();
              if (isSelected) {
                glLineWidth(c->lineWidth()*3);
              } else {
                glLineWidth(c->lineWidth());
              }
              glBegin(GL_LINE_STRIP);
                for (int t=0;t<=tRes;t++) {
                  glVertex3d (x->x,x->y,x->z);
                  x++;
                }
              glEnd();
              glLineWidth(1);
              if (pos != 0.) {
                paintCone(c->vectorAt(fabs(pos)),c->gradientAt(fabs(pos))*(pos/fabs(pos))*0.5,c->length()*0.1,10);
              }*/
            } else if (tSurface* s = dynamic_cast<tSurface*>(el)) {
              glNormal3f(defaultN.x,defaultN.y,defaultN.z);
              //iSurface* intrface;
              //intrface = dynamic_cast<iSurface*>(s->intrface());
              int ndu = s->uDiv();
              int ndv = s->vDiv();
              int nru = s->uRes();
              int nrv = s->vRes();
              int nu = ndu*nru;
              int nv = ndv*nrv;
              tVector *cache,x;
              cache = s->uvCache();
              for (int v=0;v<=nv;v+=nrv) {
                if (isSelected && (v == 0 || v==nv)) {
                    glLineWidth(3);
                } else {
                    glLineWidth(1);
                }
                glBegin(GL_LINE_STRIP);
                for (int u=0;u<=nu;u++) {
                  x = cache[v*(nu+1)+u];
                  glVertex3d (x.x,x.y,x.z);
                }
                glEnd();
              }
              for (int u=0;u<=nu;u+=nru) {
                if (isSelected && (u == 0 || u==nu)) {
                  glLineWidth(3);
                } else {
                  glLineWidth(1);
                }
                glBegin(GL_LINE_STRIP);
                for (int v=0;v<=nv;v++) {
                  x = cache[v*(nu+1)+u];
                  glVertex3d (x.x,x.y,x.z);
                }
                glEnd();
              }
//            } else if (dynamic_cast<tAbstractPolygon*>(el)) {
//                printPolygon(el, rgb);
   /*         } else if (tTrianglePatch *tp = dynamic_cast<tTrianglePatch*>(el)) {
                int count = tp->nTriangles();
                for (int i=0; i<count; i++) {
                    printPolygon(tp->triangle(i), rgb);
                }
                paintElement(tp->helper());*/
            } else if (tQuad* q = dynamic_cast<tQuad*>(el)) {
                tDot *d;
                tVector n;
                tVector x;
                int i;

                n = q->normalVector();
                if (n*(EyePoint-ObjectPoint)<0 && rgb.alpha == 255){
                    glColor4ub (255, 0, 0, 255);
                }

                glNormal3f(n.x,n.y,n.z);
                // Die Flaeche
                glBegin(GL_QUADS);
                for (i=0;i<4 ;i++){
                    d = q->c(i);
                    if (d){
                        x = d->vector();
                    } else {
                        x.setZero();
                    }
                    glVertex3f( x.x, x.y, x.z);
                }
                glEnd();
                // Die Kanten
                if (rgb.alpha>250 || 1==1){
                    glLineWidth(3);
                    glColor4ub ((unsigned char)(rgb.red*0.8+255*0.2),
                                (unsigned char)(rgb.green*0.8+255*0.2),
                                (unsigned char)(rgb.blue*0.8+255*0.2),255
                                );
                    glBegin(GL_LINE_LOOP);
                    for (i=0;i<4;i++){
                        d = q->c(i);
                        if (d){
                            x = d->vector();
                        } else {
                            x.setZero();
                        }
                        glVertex3f( x.x, x.y, x.z);
                    }
                    glEnd();

                }
                // ggf. Verfeinerungspunkte
                if (tRefinedQuad *rQuad = dynamic_cast<tRefinedQuad*>(q)){
                    for (int i=0;i<4;i++){
                        tList<tElement*> l = rQuad->dotList(i);
                        for (int j=0; j<l.count();j++){
                            paintElement(l.at(j));
                        }
                    }
                }
            } else if ( tBasicPlane* pl = dynamic_cast<tBasicPlane*>(el)) {

                tVector center = pl->center();
                tVector normal = pl->normal();
                tVector right  = pl->horizontalDir();

                tVector up = normal % right;

                double l = 0.6* (model()->xMax()-model()->xMin()).length();
                if (l==0) {
                    l = 2.0*(2.*FR*sqrt(tan(M_PI*0.25)));
                } else {
                    tVector modelCenter = (model()->xMax()-model()->xMin())*0.5;
                    double dist = (modelCenter-center) * normal;
                    center = modelCenter - normal*dist;
                }

                glNormal3f(normal.x,normal.y,normal.z);

                if (isSelected) {
                    glLineWidth(3);
                } else {
                    glLineWidth(1);
                }

                tVector x;
                glBegin(GL_LINE_LOOP);
                    x = center + up*l + right*l;
                    glVertex3d(x.x,x.y,x.z);
                    x = center + up*l - right*l;
                    glVertex3d(x.x,x.y,x.z);
                    x = center - up*l - right*l;
                    glVertex3d(x.x,x.y,x.z);
                    x = center - up*l + right*l;
                    glVertex3d(x.x,x.y,x.z);
                glEnd();
            } else if (tStructured2DGrid* grid = dynamic_cast<tStructured2DGrid*>(el)){
              int i,j,ni,nj;
              tVector x;
              tDot *d;
              glNormal3f(defaultN.x,defaultN.y,defaultN.z);
              ni = grid->ni();
              nj = grid->nj();
              for (i=0;i<ni;i++){
                glBegin(GL_LINE_STRIP);
                for (j=0;j<nj;j++){
                  d = grid->gridAt(i,j);
                  if (d){
                    x = d->vector();
                    glVertex3d (x.x,x.y,x.z);
                  }
                }
                glEnd();
              }
              for (j=0;j<nj;j++){
                glBegin(GL_LINE_STRIP);
                for (i=0;i<ni;i++){
                  d = grid->gridAt(i,j);
                  if (d){
                    x = d->vector();
                    glVertex3d (x.x,x.y,x.z);
                  }
                }
                glEnd();
              }
            } else if (tStructured3DGrid* grid = dynamic_cast<tStructured3DGrid*>(el)){
              int i, ni, j, nj, k,nk;
              ni = grid->ni();
              nj = grid->nj();
              nk = grid->nk();
              for (i=0;i<ni;i++){
                for (j=0;j<nj;j++){
                  for (k=0;k<nk;k++){
                    tDot *d = grid->gridAt(i,j,k);
                    if (d){
                      double x,y,z, ps;;
                      tVector ud,rd;
                      if (k==0||j==0||i==0 || k==nk-1 || j==nj-1 || i==ni-1){
                        ps = pointSize*1.3;
                      } else {
                        ps = pointSize*0.6;
                      }
                      ud = unityUp*refSize*ps;
                      rd = unityRight*refSize*ps;
                      x = d->x();
                      y = d->y();
                      z = d->z();
                      glNormal3f(defaultN.x,defaultN.y,defaultN.z);
                      glBegin(GL_POLYGON);
                        glVertex3d (x+ud.x+rd.x, y+ud.y+rd.y, z+ud.z+rd.z);
                        glVertex3d (x+ud.x-rd.x, y+ud.y-rd.y, z+ud.z-rd.z);
                        glVertex3d (x-ud.x-rd.x, y-ud.y-rd.y, z-ud.z-rd.z);
                        glVertex3d (x-ud.x+rd.x, y-ud.y+rd.y, z-ud.z+rd.z);
                      glEnd();
                    }
                  }
                }
              }
            } else if (tLinkedElement *linkedEl = dynamic_cast<tLinkedElement*>(el)){
              paintElement(linkedEl->linkedElement(), linkedEl->intrface());
            }
          }
        }
      }
    }
    el->unlockElement();
  }
}
/*
void tGLModelView::printPolygon(tElement *el, const tRGB& rgb)
{
    tAbstractPolygon* poly = dynamic_cast<tAbstractPolygon*>(el);
    if (poly) {
        poly->paintGL(EyePoint, ObjectPoint, rgb, defaultN, false);

        tDot *d;
        tVector n;
        tVector x;
        int i;

        n = poly->normal();
        if (n*(EyePoint-ObjectPoint)<0 && rgb.alpha == 255){
            //glColor4ub (200, 230, 230, 255);
            glColor4ub (230, 190, 200, 55);
        } else {
            glColor4ub (rgb.red, rgb.green, rgb.blue, rgb.alpha);
        }

        glNormal3f(n.x,n.y,n.z);
        // Die Flaeche
        glBegin(GL_POLYGON);
        for (i=0;i<poly->nVertices() ;i++){
            d = poly->vertex(i);
            if (d){
                x = d->vector();
            } else {
                x.setZero();
            }
            glVertex3f( x.x, x.y, x.z);
        }
        glEnd();
        // Die Kanten
        if (rgb.alpha>250 || 1==1){
            glLineWidth(3);
            glColor4ub ((unsigned char)(rgb.red*0.8+255*0.2),
                        (unsigned char)(rgb.green*0.8+255*0.2),
                        (unsigned char)(rgb.blue*0.8+255*0.2),255
                        );
            glBegin(GL_LINE_LOOP);
            for (i=0;i<poly->nVertices();i++){
                d = poly->vertex(i);
                if (d){
                    x = d->vector();
                } else {
                    x.setZero();
                }
                glVertex3f( x.x, x.y, x.z);
            }
            glEnd();

        }
    }
}
*/
//-------------------------------------------------------------------------------

void tGLModelView::paintCone(tVector tip, tVector dir, tReal diameter, int res)
{
  tVector right, up, base;
  tReal l;
  tReal sinPhi, cosPhi, sinPhi0, cosPhi0, phi;
  int i;
  base = tip-dir;
  up = dir % tVector(dir.length_squared(),0,0);
  if (up.length_squared()==0.){
    up = dir % tVector(0., dir.length_squared(), 0.);
  }
  l = up.length();
  if (l){
    up = up*(0.5*diameter/l);
    right = dir % up;
    right = right *(0.5*diameter/right.length());
    l = up*right;
    l = right.length();
    l = up.length();
    glBegin(GL_TRIANGLES);
    sinPhi = 0.;
    cosPhi = 1.;
    for (i=0;i<=res;i++){
      phi = 2.*M_PI*(tReal)(i+1)/(tReal)res;
      sinPhi0 = sinPhi;
      cosPhi0 = cosPhi;
      sinPhi = sin(phi);
      cosPhi = cos(phi);
      glVertex3d (tip.x,tip.y,tip.z);
      glVertex3d (base.x+right.x*sinPhi0 + up.x*cosPhi0,
                  base.y+right.y*sinPhi0 + up.y*cosPhi0,
                  base.z+right.z*sinPhi0 + up.z*cosPhi0);
      glVertex3d (base.x+right.x*sinPhi + up.x*cosPhi,
                  base.y+right.y*sinPhi + up.y*cosPhi,
                  base.z+right.z*sinPhi + up.z*cosPhi);
    }
    glEnd();
  }
}
//-------------------------------------------------------------------------------

void tGLModelView::paintText(const tVector &loc,const QString &text)
{
  textItems << textElement(loc, text);
}
//-------------------------------------------------------------------------------

void tGLModelView::paintTextItems(QPainter *painter)
{
  double winX, winY, winZ;
  GLint viewport[4];
  GLdouble modelview[16], projection[16];

  glGetDoublev(GL_MODELVIEW_MATRIX, modelview); //Aktuelle Modelview Matrix in einer Variable ablegen
  glGetDoublev(GL_PROJECTION_MATRIX, projection); //Aktuelle Projection[s] Matrix in einer Variable ablegen
  glGetIntegerv(GL_VIEWPORT, viewport); // Aktuellen Viewport in einer Variable ablegen

  foreach (textElement item, textItems){
    tVector loc = item.location;
    gluProject(loc.x,loc.y,loc.z,modelview,projection,viewport,&winX,&winY,&winZ);
    painter->drawText(winX, viewport[3]-winY-1, item.text);
  }
}
//-------------------------------------------------------------------------------
