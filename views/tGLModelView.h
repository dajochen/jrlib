#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include <QBrush>
#include <QFont>
#include <QImage>
#include <QPen>
#include <QTimer>

#include "views/tModelView.h"
#include "classes/tVectorStringConverter.h"

class QPaintEvent;
class QWidget;

class tGLModelView : public QGLWidget, public tModelView
{
  Q_OBJECT

public:

  tGLModelView(void *theOwner, tModel *theModel, QWidget *parent  /*= 0*/);
  ~tGLModelView();

  QSize sizeHint() const;

  enum MouseModes {mmIdle=1,mmTurn=2,mmRotate=4,mmZoom=8,mmPan=16,mmRoll=32,mmMoveElements=64} mouseMode;
  void disableMouseMode(const int& mModes);
  void enableMouseMode(MouseModes m);

  bool doubleClickSelectionEnabled(void){return fDoubleClickSelectionEnabled;}
  void setDoubleClickSelectionEnabled(bool enabled){fDoubleClickSelectionEnabled = enabled;}

  void setView(tVector at, tVector eye, tVector up);

public slots:

protected:
  virtual void invalidate(tElement *sender);
  virtual void refresh(void);
  virtual void paintEvent(QPaintEvent *event);
  virtual void initializeGL();
  virtual void resizeGL(int width, int height);
  virtual void showEvent(QShowEvent *event);

  virtual void mousePressEvent(QMouseEvent *event);
  virtual void mouseReleaseEvent(QMouseEvent *event);
  virtual void mouseMoveEvent(QMouseEvent *event);
  virtual void wheelEvent(QWheelEvent *event);
  virtual void mouseDoubleClickEvent(QMouseEvent *event);

  virtual void keyPressEvent(QKeyEvent *event);
  virtual void keyReleaseEvent(QKeyEvent *event);

  virtual void paintData(void);
  virtual void paintElement(tElement *E, iElement *I=NULL);


  //virtual void printPolygon(tElement* el, const tRGB& rgb);

  //virtual void addToSelectable(tElement *el);
  virtual void paintCone(tVector tip, tVector dir, tReal diameter, int res);
  virtual void paintText(const tVector &loc, const QString &text);
  virtual void paintTextItems(QPainter *painter);

protected:
  void stopKeyboardMotion(void) {}
  void initMouseMotion(const QPoint& position);

  //virtual void selectCloseElement(tElement *el, int x, int y, double tolerance);
  virtual tList<tElement*> getCloseElements(tElement *el, int x, int y, double tolerance);
  tReal calcDisplayDistance(tElement *el, int x, int y);

  MouseModes getMouseMode(QMouseEvent* event, const MouseModes& baseMode=mmIdle);

  void setupViewport(int width, int height);

  tReal refSize;
  tVector unityUp, unityRight;
  tVector defaultN;

  tVector EyePoint,			      // Standpunkt des Berachters
          UpDirection,		    // Koerperachse des aufrecht stehenden Betrachters
          ObjectPoint;		    // point to look at.
  double ViewingAngle;

  QPoint initialMousePos, lastMousePos;
  tList<MouseModes> disabledMouseModes;
  bool fDoubleClickSelectionEnabled;


  double modificationIncrement; // KeySpeed during modification etc.

  //int speed, turnSpeed, pitchSpeed, SpeedFactor; //Motion speed during motion with keys
  //QTimer *keyTimer;


  QColor colorBackground;

  //temp. objects during painting:
  bool paintSolids;
  //class to queue text elements temporarily
  class textElement {
    public:
      tVector location;
      QString text;
      textElement (const tVector &loc, const QString& txt){location=loc;text=txt;}
  };
  QList<textElement> textItems;


  QWidget *theParent; // is necessary as the MdiArea in which the widget will be located does not generate modal dialogs correctly.
  QPalette OkPal, WrongPal;

  class translateDialog : public QDialog {
    public:
      QLineEdit *direction,
                *distance;
    translateDialog(QWidget *parent, tVector dir, double dist) :
        QDialog(parent),
        direction(new QLineEdit(tVectorStringConverter::toString(dir,";"),this)),
        distance(new QLineEdit(QString::number(dist),this))
    {
        setWindowTitle("Edit translation");
        QGridLayout *layout = new QGridLayout(this);
        QPushButton *ok = new QPushButton("Ok"),
                *cancel = new QPushButton("Cancel");
        ok->setDefault(true);
        connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
        connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));
        layout->addWidget(direction,0,1);                 layout->addWidget(new QLabel("direction"),0,0);
        layout->addWidget(new QLabel("distance"),1,0);    layout->addWidget(distance,1,1);
        layout->addWidget(cancel, 2,0);                   layout->addWidget(ok, 2,1);
    }
  };

  class rotateDialog : public QDialog {
    public:
      QLineEdit *point, *axis, *angle;

      rotateDialog(QWidget *parent, tVector p, tVector a, double alpha) :
        QDialog (parent),
        point (new QLineEdit(tVectorStringConverter::toString(p, ";"),this)),
        axis  (new QLineEdit(tVectorStringConverter::toString(a,";"),this)),
        angle (new QLineEdit(QString::number(alpha),this))
      {
          //setWindowModality(Qt::WindowModal);
          setWindowTitle("Edit rotation");
          QGridLayout *layout = new QGridLayout(this);
          QPushButton *ok = new QPushButton("Ok"),
                  *cancel = new QPushButton("Cancel");
          ok->setDefault(true);
          connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
          connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));
          layout->addWidget(new QLabel("center"),0,0);       layout->addWidget(point,0,1);
          layout->addWidget(new QLabel("axis"),1,0);         layout->addWidget(axis,1,1);
          layout->addWidget(new QLabel("angle [°]"),2,0);    layout->addWidget(angle,2,1);
          layout->addWidget(cancel, 3,0),                    layout->addWidget(ok, 3,1);
      }
  };
};

#endif
