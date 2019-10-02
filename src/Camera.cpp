#include "Camera.h"

mt4sd::Camera::Camera():
    frameWidth(0), frameHeight(0), displayableFrame(nullptr)
{

}

mt4sd::Camera::~Camera()
{

}

bool mt4sd::Camera::save(const char *filename)
{
    if (displayableFrame == nullptr)
        return false;

    return displayableFrame->save(QString(filename));
}
