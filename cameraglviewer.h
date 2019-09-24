#ifndef CAMERAGLVIEWER_H
#define CAMERAGLVIEWER_H

#include "ThermalCameraLib_global.h"
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

namespace mt4sd {
    class THERMALCAMERALIB_EXPORT CameraGLViewer : public QOpenGLWidget, protected QOpenGLFunctions
    {
    public:
        CameraGLViewer();

        void initializeGL();
        void resizeGL(int width, int height);
        void paintGL();

        /**
        *	@brief Clean the OpenGL visualization
        */
        void cleanGL();

    private:
        void printContextInformation();
    };
}
#endif // CAMERAGLVIEWER_H
