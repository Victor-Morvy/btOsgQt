#ifndef GAMEWORLD_H
#define GAMEWORLD_H


#include "btosgVehicle.h"
#include <osgViewer/Viewer>

#include <osgUtil/SmoothingVisitor>

#include <osg/Camera>
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/TrackballManipulator>
#include <osgGA/NodeTrackerManipulator>

class GameWorld
{
public:
    GameWorld();
    ~GameWorld();

    static GameWorld* getHandle();


    static GameWorld* _obj;

    void setViewer (osgViewer::Viewer* _viewer);

    void update();

    osg::ref_ptr<osgGA::TrackballManipulator> manipulator;
    btosgWorld* myWorld;
    btosgVehicle *myVehicle;
    osgViewer::Viewer* viewer;

};

#endif // GAMEWORLD_H
