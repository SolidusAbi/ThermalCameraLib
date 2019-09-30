#include "CameraViewer.h"
#include "ui_cameraviewer.h"

CameraViewer::CameraViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraViewer)
{
    ui->setupUi(this);
}

CameraViewer::~CameraViewer()
{
    delete ui;
}
