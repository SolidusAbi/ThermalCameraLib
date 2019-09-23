#ifndef THERMALCAMERALIB_H
#define THERMALCAMERALIB_H

#include "ThermalCameraLib_global.h"

namespace mt4sd{
   class THERMALCAMERALIB_EXPORT ThermalCameraLib
    {
    public:
        ThermalCameraLib();
        ThermalCameraLib(mt4sd::Camera device);


    private:
        mt4sd::Camera device;
        mt4sd::TE_Setting setting;
    };
}

#endif // THERMALCAMERALIB_H
