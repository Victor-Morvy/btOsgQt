#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "osgUtil/SmoothingVisitor"
#include "QtDebug"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    myWorld = GameWorld::getHandle()->myWorld;

    osg_widget = ui->openGLWidget;

    myVehicle = GameWorld::getHandle()->myVehicle;

    viewer = osg_widget->getViewer();

    GameWorld::getHandle()->setViewer(viewer);

    btosgVec3 up(0., 0., 1.);
    osg::Matrix matrix;
    matrix.makeLookAt( osg::Vec3(0.,8.,5.), osg::Vec3(0.,0.,1.), up );
    viewer->getCamera()->setViewMatrix(matrix);

    viewer->getCamera()->addChild( myWorld->scene );

    viewer->setCameraManipulator( GameWorld::getHandle()->manipulator );

//    osg::ref_ptr<osgGA::NodeTrackerManipulator> nodeTracker = new
//    osgGA::NodeTrackerManipulator;
//    nodeTracker->setHomePosition( osg::Vec3(0, -10.0, 0), osg::Vec3(), osg::Z_AXIS );
//    nodeTracker->setTrackerMode( osgGA::NodeTrackerManipulator::NODE_CENTER_AND_ROTATION );
//    nodeTracker->setRotationMode( osgGA::NodeTrackerManipulator::TRACKBALL );
//    nodeTracker->setTrackNode( myVehicle->pNode );
//    osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> keySwitch = new osgGA::KeySwitchMatrixManipulator;
//    keySwitch->addMatrixManipulator( '1', "Trackball", new osgGA::TrackballManipulator );
//    keySwitch->addMatrixManipulator( '2', "NodeTracker", nodeTracker.get() );
//    viewer->setCameraManipulator( keySwitch.get() );

    viewer->addEventHandler(new FollowUpdater(myVehicle->pNode));

    timer = new QTimer(this);

    realTimer = new QElapsedTimer();

    connect(timer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::update));

    timer2 = new QTimer(this);

    connect(timer2, &QTimer::timeout, this, QOverload<>::of(&MainWindow::realTimeUpdate));

    timer->start(16);
    timer2->start(0);

    realTimer->start();

}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::update()
{

    GameWorld::getHandle()->update();

}

void MainWindow::realTimeUpdate()
{
    dt = realTimer->elapsed() - lastTime;

    myWorld->stepSimulation(dt,1);

    lastTime = realTimer->elapsed();
}
