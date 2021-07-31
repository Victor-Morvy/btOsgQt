#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "osgUtil/SmoothingVisitor"
#include "QtDebug"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    root = new osg::Group;

    osg_widget = ui->openGLWidget;

    auto _mViewer = osg_widget->getViewer();





    osg_widget->setGeodeSc(root.get());

}

MainWindow::~MainWindow()
{

    delete ui;
}


