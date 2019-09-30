#ifndef CAMERAGLVIEWER_H
#define CAMERAGLVIEWER_H

#include "ThermalCameraLib_global.h"
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include "Camera.h"

namespace mt4sd {
    class THERMALCAMERALIB_EXPORT CameraGLViewer : public QOpenGLWidget, protected QOpenGLFunctions
    {
        Q_OBJECT
        public:
            CameraGLViewer(QWidget *parent = nullptr);
            CameraGLViewer(mt4sd::Camera *camera, QWidget *parent = nullptr);

            void initializeGL();
            void resizeGL(int width, int height);
            void paintGL();

            /**
            *	@brief Clean the OpenGL visualization
            */
            void cleanGL();

        private:
            void printContextInformation();
            mt4sd::Camera *camera;
        };
}
#endif // CAMERAGLVIEWER_H
