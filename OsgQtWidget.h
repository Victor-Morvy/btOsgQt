#ifndef OSGQTWIDGET_H
#define OSGQTWIDGET_H

#include <QtCore>
#include <QOpenGLWidget>
#include <osgViewer/Viewer>
#include <osg/Drawable>
#include <osg/ShapeDrawable>
#include <osgGA/TrackballManipulator>
#include <osg/Material>
#include <QMouseEvent>

class QtOSGWidget : public QOpenGLWidget
{
public:


  QtOSGWidget(QWidget* parent = nullptr, qreal scaleX=1, qreal scaleY=1)
      : QOpenGLWidget(parent)
        , _mGraphicsWindow(new osgViewer::GraphicsWindowEmbedded( this->x(), this->y(),
                                                                 this->width(), this->height() ) )
      , m_scaleX(scaleX)
      , m_scaleY(scaleY)
      {



      camera = new osg::Camera;
      camera->setViewport( 0, 0, this->width(), this->height() );
      camera->setClearColor( osg::Vec4( 0.2f, 0.2f, 0.30f, 1.f ) );
      float aspectRatio = static_cast<float>( this->width()) / static_cast<float>( this->height() );
      camera->setProjectionMatrixAsPerspective( 30.f, aspectRatio, 1.f, 1000.f );
      camera->setGraphicsContext( _mGraphicsWindow );

      _mViewer = new osgViewer::Viewer;

      _mViewer->setCamera(camera);
//      _mViewer->setSceneData(geode);
      osgGA::TrackballManipulator* manipulator = new osgGA::TrackballManipulator;
      manipulator->setAllowThrow( false );
      this->setMouseTracking(true);
      _mViewer->setCameraManipulator(manipulator);
      _mViewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);
      _mViewer->realize();


//      osg::ref_ptr<osg::Camera> camera = new osg::Camera;
//      camera->setViewport( 0, 0, this->width(), this->height() );
//      camera->setClearColor( osg::Vec4( 0.9f, 0.9f, 1.f, 1.f ) );
//      float aspectRatio = static_cast<float>( this->width()) / static_cast<float>( this->height() );
//      camera->setProjectionMatrixAsPerspective( 30.f, aspectRatio, 1.f, 1000.f );
//  //    camera->setGraphicsContext( _mGraphicsWindow );

//      _mViewer->setCamera(camera);
//      osgGA::TrackballManipulator* manipulator = new osgGA::TrackballManipulator;
//      manipulator->setAllowThrow( false );
//      setMouseTracking(true);
//      _mViewer->setCameraManipulator(manipulator);
//      _mViewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);
//      _mViewer->realize();

      }


  virtual ~QtOSGWidget(){}

  void setScale(qreal X, qreal Y)
  {
      m_scaleX = X;
      m_scaleY = Y;
      this->resizeGL(this->width(), this->height());
  }

protected:

  virtual void paintGL() {
    _mViewer->frame();
  }

  virtual void resizeGL( int width, int height )
  {
      this->getEventQueue()->windowResize(this->x()*m_scaleX, this->y() * m_scaleY, width*m_scaleX, height*m_scaleY);
      _mGraphicsWindow->resized(this->x()*m_scaleX, this->y() * m_scaleY, width*m_scaleX, height*m_scaleY);
      osg::Camera* camera = _mViewer->getCamera();
      camera->setViewport(0, 0, this->width()*m_scaleX, this->height()* m_scaleY);
  }

  virtual void initializeGL(){
//      osg::Geode* geode = dynamic_cast<osg::Geode*>(_mViewer->getSceneData());
//      osg::StateSet* stateSet = geode->getOrCreateStateSet();
//      osg::Material* material = new osg::Material;
//      material->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );
//      stateSet->setAttributeAndModes( material, osg::StateAttribute::ON );
//      stateSet->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );
  }

  virtual void mouseMoveEvent(QMouseEvent* event)
  {
      this->getEventQueue()->mouseMotion(event->x()*m_scaleX, event->y()*m_scaleY);
  }

  virtual void mousePressEvent(QMouseEvent* event)
  {
      unsigned int button = 0;
      switch (event->button()){
      case Qt::LeftButton:
          button = 1;
          break;
      case Qt::MiddleButton:
          button = 2;
          break;
      case Qt::RightButton:
          button = 3;
          break;
      default:
          break;
      }
      this->getEventQueue()->mouseButtonPress(event->x()*m_scaleX, event->y()*m_scaleY, button);
  }

  virtual void mouseReleaseEvent(QMouseEvent* event)
  {
      unsigned int button = 0;
      switch (event->button()){
      case Qt::LeftButton:
          button = 1;
          break;
      case Qt::MiddleButton:
          button = 2;
          break;
      case Qt::RightButton:
          button = 3;
          break;
      default:
          break;
      }
      this->getEventQueue()->mouseButtonRelease(event->x()*m_scaleX, event->y()*m_scaleY, button);
  }

  virtual void wheelEvent(QWheelEvent* event)
  {
      int delta = event->delta();
      osgGA::GUIEventAdapter::ScrollingMotion motion = delta > 0 ?
                  osgGA::GUIEventAdapter::SCROLL_UP : osgGA::GUIEventAdapter::SCROLL_DOWN;
      this->getEventQueue()->mouseScroll(motion);
  }



  virtual bool event(QEvent* event)
  {
      bool handled = QOpenGLWidget::event(event);
      this->update();
      return handled;
  }

public:

  virtual osg::ref_ptr<osgViewer::Viewer>
  getViewer()
  {
      return _mViewer;
  }

  void
  setCamera(osg::Camera* camera)
  {
      _mViewer->setCamera(camera);
  }

  void
  setGeodeSc(osg::Group* geode)
  {
        _mViewer->setSceneData(geode);
  }

  osg::Camera*
  getCamera()
  {
      return camera;
  }
private:

  osgGA::EventQueue* getEventQueue() const {
    osgGA::EventQueue* eventQueue = _mGraphicsWindow->getEventQueue();
    return eventQueue;
  }
    osg::Camera* camera;

  osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> _mGraphicsWindow;
  osg::ref_ptr<osgViewer::Viewer> _mViewer;
  qreal m_scaleX, m_scaleY;
};

#endif // OSGQTWIDGET_H
