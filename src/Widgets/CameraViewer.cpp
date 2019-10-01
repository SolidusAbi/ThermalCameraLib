#include "ui/ui_cameraviewer.h"
#include "CameraViewer.h"

#include <QAction>
#include <QDebug>

mt4sd::CameraViewer::CameraViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraViewer)
{
    ui->setupUi(this);
    ui->snapshotButton->setDefaultAction(ui->actionSnapshot);
    ui->playButton->setDefaultAction(ui->actionPlay);
    ui->stopButton->setDefaultAction(ui->actionStop);

    connect(ui->actionSnapshot, &QAction::triggered, this, &mt4sd::CameraViewer::snapshot);
    connect(ui->actionPlay, &QAction::triggered, ui->cameraViewer, &mt4sd::CameraGLViewer::resume);
    connect(ui->actionStop, &QAction::triggered, ui->cameraViewer, &mt4sd::CameraGLViewer::pause);
}

mt4sd::CameraViewer::~CameraViewer()
{
    disconnect(ui->actionSnapshot);
    disconnect(ui->actionPlay);
    disconnect(ui->actionStop);

    delete ui;
}

void mt4sd::CameraViewer::play()
{
    //TODO
}

void mt4sd::CameraViewer::stop()
{
    //TODO
}

void mt4sd::CameraViewer::snapshot()
{
    qDebug() << "Hola bebé!!!!";
}

void mt4sd::CameraViewer::setCamera(mt4sd::Camera *camera)
{
    ui->cameraViewer->setCamera(camera);
}

mt4sd::Camera * mt4sd::CameraViewer::getCamera()
{
    return ui->cameraViewer->getCamera();
}
