#include "CameraViewer.h"
#include "ui/ui_cameraviewer.h"

mt4sd::CameraViewer::CameraViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraViewer)
{
    ui->setupUi(this);
}

mt4sd::CameraViewer::~CameraViewer()
{
    delete ui;
}
