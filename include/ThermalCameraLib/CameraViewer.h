#ifndef CAMERAVIEWER_H
#define CAMERAVIEWER_H

#include <QWidget>
#include "Camera.h"

namespace Ui {
    class CameraViewer;
}

namespace mt4sd {

    class CameraViewer : public QWidget
    {
        Q_OBJECT

    public:
        explicit CameraViewer(QWidget *parent = nullptr);
        ~CameraViewer();

        void setCamera(mt4sd::Camera *camera);
        mt4sd::Camera * getCamera();

    public slots:
        void play();
        void stop();
        void snapshot();

    private:
        Ui::CameraViewer *ui;
    };
}

#endif // CAMERAVIEWER_H
