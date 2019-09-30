#ifndef CAMERAVIEWER_H
#define CAMERAVIEWER_H

#include <QWidget>

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

    private:
        Ui::CameraViewer *ui;

    public slots:
        void play();
        void stop();

    };
}

#endif // CAMERAVIEWER_H
