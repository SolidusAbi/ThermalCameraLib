#ifndef CAMERAVIEWER_H
#define CAMERAVIEWER_H

#include <QDockWidget>

namespace Ui {
class CameraViewer;
}

class CameraViewer : public QDockWidget
{
    Q_OBJECT

public:
    explicit CameraViewer(QWidget *parent = nullptr);
    ~CameraViewer();

private:
    Ui::CameraViewer *ui;
};

#endif // CAMERAVIEWER_H
