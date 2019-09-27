#include "CameraGLViewer.h"

#include <QSurfaceFormat>
#include <QPainter>
#include <QDebug>

mt4sd::CameraGLViewer::CameraGLViewer(mt4sd::Camera *camera)
    :QOpenGLWidget()
{
    this->camera = camera;

    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setSwapInterval(1);
    setFormat(format);
}

void mt4sd::CameraGLViewer::initializeGL()
{
    // Initialize OpenGL Backend
    initializeOpenGLFunctions();

    connect(this, SIGNAL(frameSwapped()), this, SLOT(update())); //Just wheter you want a continue rendering
    printContextInformation();

    // Set global information
    //glEnable(GL_CULL_FACE);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//    glClearColor(0, 0, 0, 1);
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_LIGHT0);
//    glEnable(GL_LIGHTING);
//    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
//    glEnable(GL_COLOR_MATERIAL);
}

void mt4sd::CameraGLViewer::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}

void mt4sd::CameraGLViewer::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    glBegin(GL_TRIANGLES);
//    glColor3f(1.0, 0.0, 0.0);
//    glVertex3f(-0.5, -0.5, 0);
//    glColor3f(0.0, 1.0, 0.0);
//    glVertex3f(0.5, -0.5, 0);
//    glColor3f(0.0, 0.0, 1.0);
//    glVertex3f(0.0, 0.5, 0);
//    glEnd();

//    QPainter p(this);
//    p.setPen(Qt::red);
//    p.drawLine(rect().topLeft(), rect().bottomRight());

    QPainter p(this);
    p.drawImage(this->rect(), *this->camera->getDisplayFrame());
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
