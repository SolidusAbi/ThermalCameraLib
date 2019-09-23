#include "thermalcameralib.h"

mt4sd::ThermalCameraLib::ThermalCameraLib()
{
}


mt4sd::ThermalCameraLib::ThermalCameraLib(mt4sd::Camera device)
{
    this->device = device;
}
