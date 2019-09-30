#include "cameraviewer.h"
#include "ui/ui_cameraviewer.h"

CameraViewer::CameraViewer(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::CameraViewer)
{
    ui->setupUi(this);
}

CameraViewer::~CameraViewer()
{
    delete ui;
}
