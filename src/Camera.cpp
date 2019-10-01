#include "Camera.h"

mt4sd::Camera::Camera():
    frameWidth(0), frameHeight(0), displayableFame(nullptr)
{

}

mt4sd::Camera::~Camera()
{

}

bool mt4sd::Camera::save(const char *filename)
{
    if (displayableFame == nullptr)
        return false;

    return displayableFame->save(QString(filename));
}
