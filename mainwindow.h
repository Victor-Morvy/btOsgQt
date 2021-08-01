#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtCore>
#include <QOpenGLWidget>
#include <osgViewer/Viewer>
#include <osg/Drawable>
#include <osg/ShapeDrawable>
#include <osgGA/TrackballManipulator>
#include <osg/Material>
#include <QMouseEvent>

//#include "draw.h"
#include "OsgQtWidget.h"
#include "mathfunies.h"

#include <osg/Material>

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <BulletDynamics/Vehicle/btRaycastVehicle.h>

#include <osg/Texture2D>


#include "followupdater.h"
#include "btosgVehicle.h"
//#include "PaintBezier.h"

#include "gameworld.h"


#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void update(); //ms

    btosgWorld* myWorld;
    btosgVehicle *myVehicle;

    QTimer* timer;
    osgViewer::Viewer* viewer;


private:
    Ui::MainWindow *ui;
    QtOSGWidget *osg_widget;


};


#endif // MAINWINDOW_H
