#ifndef CAMERAVIEWER_H
#define CAMERAVIEWER_H

#include <QWidget>

namespace Ui {
class CameraViewer;
}

class CameraViewer : public QWidget
{
    Q_OBJECT

public:
    explicit CameraViewer(QWidget *parent = nullptr);
    ~CameraViewer();

private:
    Ui::CameraViewer *ui;
};

#endif // CAMERAVIEWER_H
