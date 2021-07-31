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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    btosgWorld* myWorld;

    // Vehicle
    btosgVehicle *myVehicle;


private:
    Ui::MainWindow *ui;
    QtOSGWidget *osg_widget;
    osg::ref_ptr<osg::Group> root;
    osg::MatrixTransform* _m;
    SplineControl* pl;
    osg::Vec3f xaxis = osg::Vec3f(1.f,0.0f,0.0f);
    osg::Vec3f yaxis = osg::Vec3f(0.f,1.0f,0.0f);
    osg::Vec3f zaxis = osg::Vec3f(0.f,0.0f,1.0f);



//    osg::Vec3f yaxis(0.0f,1.0f,0.0f), zaxis(0.0f,0.0f,1.0f);
        osg::Matrix rot1;
        osg::Matrix rot2;
        osg::Matrix rot3;



};

class EventHandler : public osgGA::GUIEventHandler
{
public:
    // Create World
    btosgWorld* myWorld;
int ResetFlag=0;
    // Vehicle
    btosgVehicle *myVehicle;

    bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
    {
        osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
        if (!viewer) return false;
        switch(ea.getEventType())
        {
        case(osgGA::GUIEventAdapter::KEYDOWN):
            switch ( ea.getKey() ) {
            case osgGA::GUIEventAdapter::KEY_Down:
                myVehicle->vehicle->applyEngineForce(-1500, 2);
                myVehicle->vehicle->applyEngineForce(-1500, 3);
                return false;
            case osgGA::GUIEventAdapter::KEY_Up:
                myVehicle->vehicle->applyEngineForce(2500, 2);
                myVehicle->vehicle->applyEngineForce(2500, 3);
                return false;
            case osgGA::GUIEventAdapter::KEY_Left:
                myVehicle->vehicle->setSteeringValue(btScalar(0.4), 0);
                myVehicle->vehicle->setSteeringValue(btScalar(0.4), 1);
                return false;
            case osgGA::GUIEventAdapter::KEY_Right:
                myVehicle->vehicle->setSteeringValue(btScalar(-0.4), 0);
                myVehicle->vehicle->setSteeringValue(btScalar(-0.4), 1);
                return false;
            case 'b':
            case '0':
            case osgGA::GUIEventAdapter::KEY_Space:
                myVehicle->vehicle->setBrake(10000, 2);
                myVehicle->vehicle->setBrake(10000, 3);
                return false;
            }
            break;
        case(osgGA::GUIEventAdapter::KEYUP):
            switch ( ea.getKey() ) {
            case osgGA::GUIEventAdapter::KEY_Down:
            case osgGA::GUIEventAdapter::KEY_Up:
                myVehicle->vehicle->applyEngineForce(0, 2);
                myVehicle->vehicle->applyEngineForce(0, 3);
                return false;
            case osgGA::GUIEventAdapter::KEY_Left:
            case osgGA::GUIEventAdapter::KEY_Right:
                myVehicle->vehicle->setSteeringValue(btScalar(0), 0);
                myVehicle->vehicle->setSteeringValue(btScalar(0), 1);
                return false;
            case '0':
            case 'b':
            case osgGA::GUIEventAdapter::KEY_Space:
                myVehicle->vehicle->setBrake(5, 2);
                myVehicle->vehicle->setBrake(5, 3);
                return false;
            case 'S':
                std::cout << "tecla S" << std::endl;
                return false;
            case 'i':
                myVehicle->printInfo();
                break;
            case 'F':
                std::cout << "adding Force" << std::endl;

                myVehicle->vehicle->applyEngineForce(500, 2);
                myVehicle->vehicle->applyEngineForce(500, 3);

                int i;
                for( i=0 ; i<myVehicle->vehicle->getNumWheels() ; i++) {
                    btWheelInfo& iWheel = myVehicle->vehicle->getWheelInfo(i);
                    printf(" wheel %d, radius %f, rotation %f, eforce %f, steer %f\n",
                           i, iWheel.m_wheelsRadius, iWheel.m_rotation, iWheel.m_engineForce,iWheel.m_steering);
                }
                // handled = true;
                return false;
            case 'R':
            case 'r':
                ResetFlag = 1;
                std::cout << "tecla R" << std::endl;
                break;
            }
            break;
        case(osgGA::GUIEventAdapter::MOVE):
            //std::cout << "mouse move " << ea.getX() << " " << ea.getY() << std::endl;
            return false;
        default:
            return false;
        }
        return true;
    }
};

#endif // MAINWINDOW_H
