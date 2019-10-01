#include "CameraGLViewer.h"

#include <QSurfaceFormat>
#include <QPainter>
#include <QDebug>

mt4sd::CameraGLViewer::CameraGLViewer(QWidget *parent)
    :QOpenGLWidget(parent)
{
    this->camera = nullptr;
    prepareFormat();
}


mt4sd::CameraGLViewer::CameraGLViewer(mt4sd::Camera *camera, QWidget *parent)
    :QOpenGLWidget(parent)
{
    this->camera = camera;
    prepareFormat();
}

mt4sd::CameraGLViewer::~CameraGLViewer(){
    disconnect(SIGNAL(frameSwapped()), this);
    delete camera;
}

void mt4sd::CameraGLViewer::initializeGL()
{
    // Initialize OpenGL Backend
    initializeOpenGLFunctions();

    connect(this, SIGNAL(frameSwapped()), this, SLOT(update())); //Just wheter you want a continue rendering
    printContextInformation();

    // Set global information
    //glEnable(GL_CULL_FACE); //Si lo activo, deja de verse...
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void mt4sd::CameraGLViewer::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}

void mt4sd::CameraGLViewer::paintGL()
{
    if (camera != nullptr){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        QPainter p(this);
        p.drawImage(this->rect(), *this->camera->getDisplayFrame());
    }
}

void mt4sd::CameraGLViewer::resume()
{
    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
}

void mt4sd::CameraGLViewer::pause()
{
    disconnect(SIGNAL(frameSwapped()), this);
}

void mt4sd::CameraGLViewer::printContextInformation()
{
    QString glType;
    QString glVersion;
    QString glProfile;

    // Get Version Information
    glType = (context()->isOpenGLES()) ? "OpenGL ES" : "OpenGL";
    glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

    // Get Profile Information
#define CASE(c) case QSurfaceFormat::c: glProfile = #c; break
    switch (format().profile()) {
        CASE(NoProfile);
        CASE(CoreProfile);
        CASE(CompatibilityProfile);
    }
#undef CASE

    // qPrintable() will print our QString w/o quotes around it.
    qDebug() << qPrintable(glType) << qPrintable(glVersion) << "(" << qPrintable(glProfile) << ")";
}

void mt4sd::CameraGLViewer::prepareFormat()
{
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setSwapInterval(1);

    setFormat(format);
}

