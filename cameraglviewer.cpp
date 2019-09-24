#include "cameraglviewer.h"

#include <QSurfaceFormat>
#include <QPainter>
#include <QDebug>

mt4sd::CameraGLViewer::CameraGLViewer()
    :QOpenGLWidget()
{

}

void mt4sd::CameraGLViewer::initializeGL()
{
    // Initialize OpenGL Backend
    initializeOpenGLFunctions();

    printContextInformation();

    // Set global information
    glEnable(GL_CULL_FACE);
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

    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-0.5, -0.5, 0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.5, -0.5, 0);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.5, 0);
    glEnd();

    QPainter p(this);
    p.setPen(Qt::red);
    p.drawLine(rect().topLeft(), rect().bottomRight());
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
