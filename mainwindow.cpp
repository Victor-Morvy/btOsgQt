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

    GameWorld::getHandle()->update();

    myWorld->stepSimulation(timer->interval(),10);
}


