#ifndef THERMALCAMERALIB_H
#define THERMALCAMERALIB_H

#include "ThermalCameraLib_global.h"
#include <QImage>
#include <libusb-1.0/libusb.h>


namespace mt4sd{
   class THERMALCAMERALIB_EXPORT ThermalCameraLib
    {
    public:
        ThermalCameraLib();
        ThermalCameraLib(mt4sd::Camera device);

        ~ThermalCameraLib();

        int connect();

        QImage * getDisplayFrame();

        inline bool isConnected(){ return connected; }
        inline int getFrameWidth(){ return frameWidth; }
        inline int getFrameHeight(){ return frameHeight; }
        inline int getFrameSize(){ return frameSize; }
    private:
        mt4sd::Camera device;
        mt4sd::TE_Setting setting;
        libusb_device_handle *dev_handle; //a device handle
        libusb_context *ctx = nullptr;
        bool connected;

        int rawSize = 384*296*2; //raw frame size in bytes
        int frameWidth = 384;
        int frameHeight = 288;
        int frameSize = frameWidth*frameHeight; //number of actual pixels

        unsigned char *rawFrame = new unsigned char[rawSize];
        unsigned short *frame = new unsigned short[frameSize];
        QImage *displayableFrame;

        int readRawFrame(int size, unsigned char *frame);
        void getShortFrame(unsigned char *raw, int imageSizePixels, int offsetBytes, unsigned short *frame);
        void getDisplayFrame(unsigned short *frame, int size, unsigned char *display);
    };
}

#endif // THERMALCAMERALIB_H
