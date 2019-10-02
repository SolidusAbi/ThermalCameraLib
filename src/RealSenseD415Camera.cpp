#include "RealSenseD415Camera.h"

#include <QDebug>

mt4sd::RealSenseD415Camera::RealSenseD415Camera() :
    Camera(), pipe(), cfg(), profile(), alignTo(), align(alignTo), colorMap()
{}

mt4sd::RealSenseD415Camera::~RealSenseD415Camera()
{
    // Will be disconnected automatically before being destroyed
}

bool mt4sd::RealSenseD415Camera::connect()
{
    try {
        profile = pipe.start(cfg);
        //alignTo = findStreamToAlign(profile.get_streams());
        align   = rs2::align(alignTo);
        return true;

    } catch (const std::runtime_error& error) {
            //logger->e(getName() + ": Error in connect, " + error.what());
            qDebug() << error.what();
            //qDebug() << "RealSense D415: Error in connect, " + error.what();
    } catch (...) {
            qDebug() << "RealSense D415:: Unkown error";
            //logger->e(getName() + ": Unkown error");
    }
    return false;
}

bool mt4sd::RealSenseD415Camera::disconnect()
{
    try {
        pipe.stop();
        return true;

    } catch (const std::runtime_error& error) {
        //logger->e(getName() + ": Error in disconnect, " + error.what());
        qDebug() << error.what();
    } catch (...) {
        //logger->e(getName() + ": Unkown error");
        qDebug() << "RealSense D415:: Unkown error";
    }

    return false;
}
