#ifndef THERMALCAMERALIB_H
#define THERMALCAMERALIB_H

#include "ThermalCameraLib_global.h"
#include <libusb-1.0/libusb.h>


namespace mt4sd{
   class THERMALCAMERALIB_EXPORT ThermalCameraLib
    {
    public:
        ThermalCameraLib();
        ThermalCameraLib(mt4sd::Camera device);

        int connect();

    private:
        mt4sd::Camera device;
        mt4sd::TE_Setting setting;
        libusb_device_handle *dev_handle; //a device handle
        libusb_context *ctx = nullptr;
        bool connected;

        int rawSize = 384*296*2; //raw frame size in bytes
        int frameSize = 384*288; //number of actual pixels


        int readRawFrame(int size, unsigned char *frame);
    };
}

#endif // THERMALCAMERALIB_H
