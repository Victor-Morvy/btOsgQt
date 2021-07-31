QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    btosg.cpp \
    followupdater.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    OsgQtWidget.h \
    btosg.h \
    btosgHUD.h \
    btosgVehicle.h \
    followupdater.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += /usr/local/include
#INCLUDEPATH += /usr/local/include/osgbCollision
INCLUDEPATH += /usr/local/include/BulletDynamics
INCLUDEPATH += /home/victor/tests/MathFunies
INCLUDEPATH += /usr/local/include/bullet


unix|win32: LIBS += -L"/usr/local/lib" -losg -losgGA -losgAnimation -losgDB -losgViewer -losgWidget -losgUtil -losgSim -losgUI -losgShadow -losgSim \
                    -losgManipulator  -losgFX -losgPresentation -lBulletCollision -lBulletDynamics -lLinearMath -lBulletSoftBody -lBulletInverseDynamics \
                    -lBullet3Common -lBullet3Geometry -lBullet3Collision -lBullet3Dynamics -lBullet2FileLoader -lBulletInverseDynamicsUtils -lBulletWorldImporter

#LIBS += -L"/usr/local/lib"
LIBS += -L"/usr/local/lib64" -losgQt5
#-lBulletCollision -lBulletDynamics -lLinearMath

LIBS += -L"/home/victor/tests/build-MathFunies-Desktop_Qt_5_15_2_GCC_64bit-Debug" -lMathFunies





# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
