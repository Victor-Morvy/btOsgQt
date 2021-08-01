#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "osgUtil/SmoothingVisitor"
#include "QtDebug"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    osg_widget = ui->openGLWidget;

//    osgViewer::Viewer* _mViewer = osg_widget->getViewer();
////////////////////////////////////////////
///
///
    btosgVec3 up(0., 0., 1.);
    btosgVec3 gravity = up*-9.8;
    myWorld.dynamic->setGravity(gravity);

    // Car
    myVehicle = new btosgVehicle(&myWorld);
    myVehicle->setPosition(btosgVec3(up*3.));
    myVehicle->setName("Vehicle");
    myVehicle->setMass(800.);
    myWorld.addObject( myVehicle );
    myVehicle->printInfo();


    osgUtil::SmoothingVisitor* sv = new osgUtil::SmoothingVisitor;

    myVehicle->pNode->accept(*sv);

//    osg::StateSet* state = myVehicle->pNode->getOrCreateStateSet();
//    state->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
//    myVehicle->pNode->setStateSet(state);

//    osg::StateSet* stateSet = myVehicle->pNode->getOrCreateStateSet();
//      osg::Material* material = new osg::Material;
//      material->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );
//      stateSet->setAttributeAndModes( material, osg::StateAttribute::ON );
//      stateSet->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );

      osg::StateSet* stateSet2 = myWorld.scene->getOrCreateStateSet();
      stateSet2->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );

//    osgUtil::SmoothingVisitor sv;
//    myVehicle->pNode->accept(sv);

    // Wheels
    osg::ref_ptr<osg::Material> matCylinder = new osg::Material;
    matCylinder->setAmbient (osg::Material::FRONT_AND_BACK, osg::Vec4(0.0, 0.,  0.,  1.0));
    matCylinder->setDiffuse (osg::Material::FRONT_AND_BACK, osg::Vec4(0.6, 0.4, 0.1, 1.0));
    matCylinder->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4(0.,  0.,  0.,  1.0));
    matCylinder->setShininess(osg::Material::FRONT_AND_BACK, 64);

    // Plane
    btosgPlane *myRamp = new btosgPlane(osg::Vec3(50.,50.,50.) - up*50.);
    myRamp->setPosition(0.,0.,0.);
    myWorld.addObject( myRamp );
    myRamp->setName("Ramp");
    myRamp->body->setFriction(100.);
    osg::ref_ptr<osg::Material> matRamp = new osg::Material;
    matRamp->setAmbient (osg::Material::FRONT_AND_BACK, osg::Vec4(0., 0., 0., 1.0));
    matRamp->setDiffuse (osg::Material::FRONT_AND_BACK, osg::Vec4(0.7, 0.8, 0.0, 1.0));
    matRamp->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4(0, 0, 0, 1.0));
    matRamp->setShininess(osg::Material::FRONT_AND_BACK, 64);
    myRamp->setMaterial(matRamp);

    // Creating the viewer
    viewer = osg_widget->getViewer();

    // Setup camera
    osg::Matrix matrix;
    matrix.makeLookAt( osg::Vec3(0.,8.,5.), osg::Vec3(0.,0.,1.), up );
    viewer->getCamera()->setViewMatrix(matrix);

    // add the Event handler
    event_handler = new EventHandler();
    viewer->addEventHandler(event_handler);

    // Light
    osg::ref_ptr<osg::LightSource> ls = new osg::LightSource;
    ls->getLight()->setPosition(osg::Vec4(2.5,-10+30*up[1],-10+30.*up[2],1.));
    ls->getLight()->setAmbient(osg::Vec4(0.1, 0.1, 0.1, 1.0));
    ls->getLight()->setDiffuse(osg::Vec4(1.0, 1.0, 1.0, 1.0));
    ls->getLight()->setSpecular(osg::Vec4(0.2, 0.2, 0.2, 1.0));
    myWorld.scene->addChild(ls.get());

    viewer->getCamera()->addChild( myWorld.scene );

    osg::ref_ptr<osgGA::TrackballManipulator> manipulator = new osgGA::TrackballManipulator;
    viewer->setCameraManipulator( manipulator );

    // Set the desired home coordinates for the manipulator
    osg::Vec3d eye(osg::Vec3(0., -5., -5.)+up*20.);
    osg::Vec3d center(0., 0., 0.);

    // Make sure that OSG is not overriding our home position
    manipulator->setAutoComputeHomePosition(false);
    // Set the desired home position of the Trackball Manipulator
    manipulator->setHomePosition(eye, center, up);
    // Force the camera to move to the home position
    manipulator->home(0.0);

    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::update));

    timer->start(16);

}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::update()
{

    myWorld.stepSimulation(timer->interval(),10);
}


