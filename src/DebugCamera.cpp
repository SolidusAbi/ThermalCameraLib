#include "DebugCamera.h"
#include <colormap.h>

mt4sd::DebugCamera::DebugCamera():
    Camera()
{
    if (connect()){
        frameWidth = 640;
        frameHeight = 480;
        imgBuff = new double[getFrameSize()];
        displayableFrame = new QImage(new uchar[getFrameSize()*3], getFrameWidth(), getFrameHeight(), QImage::Format::Format_RGB888);
    }
}

mt4sd::DebugCamera::~DebugCamera()
{

}

bool mt4sd::DebugCamera::connect()
{
    return true;
}

bool mt4sd::DebugCamera::disconnect()
{
    return true;
}

QImage * mt4sd::DebugCamera::getDisplayFrame()
{
    size_t stride = 3;
    colormap::Colormap *colormap = new colormap::MATLAB::Jet;

    for (size_t pixel_idx=0; pixel_idx<getFrameSize(); ++pixel_idx){
        imgBuff[pixel_idx] = pixel_idx / static_cast<double>(getFrameSize());

        displayableFrame->bits()[0 + pixel_idx*stride] = static_cast<uchar>(colormap->getColor(imgBuff[pixel_idx]).r * 255);
        displayableFrame->bits()[1 + pixel_idx*stride] = static_cast<uchar>(colormap->getColor(imgBuff[pixel_idx]).g * 255);
        displayableFrame->bits()[2 + pixel_idx*stride] = static_cast<uchar>(colormap->getColor(imgBuff[pixel_idx]).b * 255);
    }

    delete colormap;
    return displayableFrame;
}
