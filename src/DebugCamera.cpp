#include "DebugCamera.h"

mt4sd::DebugCamera::DebugCamera():
    Camera()
{
    if (connect()){
        frameWidth = 640;
        frameHeight = 480;
        imgBuff = new float[getFrameSize()];
        displayableFrame = new QImage(new uchar[getFrameSize()], getFrameWidth(), getFrameHeight(), QImage::Format::Format_Grayscale8);
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
    for (size_t pixel_idx=0; pixel_idx<getFrameSize(); ++pixel_idx){
        imgBuff[pixel_idx] = pixel_idx / static_cast<float>(getFrameSize());
    }

    return displayableFrame;
}
