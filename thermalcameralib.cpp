#include "thermalcameralib.h"

mt4sd::ThermalCameraLib::ThermalCameraLib(){}

mt4sd::ThermalCameraLib::ThermalCameraLib(mt4sd::Camera device)
{
    this->device = device;

    if (this->connect() != 0)
        this->connected = true;
    else
        this->connected = false;

}

mt4sd::ThermalCameraLib::~ThermalCameraLib(){}

int mt4sd::ThermalCameraLib::connect(){

    ssize_t n_usb_devices;
    int r = libusb_init(&this->ctx);

    if (r < 0)
    {
        //Log error!!!
        return -1;
    }

    libusb_device **usb_devs;
    n_usb_devices = libusb_get_device_list(this->ctx, &usb_devs);
    if (n_usb_devices < 0)
    {
        //Log error!!!
        return -1;
    }

    //TE-Q1 vID=0x0547(1351) pID=0x0080(128)
    this->dev_handle = libusb_open_device_with_vid_pid(ctx, 1351, 128);
    if (dev_handle == nullptr)
    {
        libusb_free_device_list(usb_devs, 1); //free the list, unref the devices in it
        libusb_exit(this->ctx); //needs to be called to end the
        return -1;
    }

    libusb_free_device_list(usb_devs, 1); //free the list, unref the devices in it
    if (libusb_kernel_driver_active(dev_handle, 0) == 0)
        libusb_detach_kernel_driver(dev_handle, 0);

    r = libusb_claim_interface(dev_handle, 0); //claim interface 0 (the first) of device (mine had just 1)
    if(r < 0) {
        libusb_close(dev_handle); //close the device we opened
        libusb_exit(this->ctx); //needs to be called to end the
        return -1;
    }

    return 0;
}

/**
 * Each request starts with a 8 byte long Setup Packet which has a specific format (https://www.beyondlogic.org/usbnutshell/usb6.shtml)
 * @brief mt4sd::ThermalCameraLib::readRawFrame
 * @param rawSize
 * @param rawFrame
 * @return
 */
int mt4sd::ThermalCameraLib::readRawFrame(int size, unsigned char *frame)
{
    //C#: byte[] byte1 = device.ControlTransferIn(0x80, 0x86, 0x1bc, 0xbeef, 0x10); //possibly 0x80 instead of 0xc0?!
    //0x1bc = 444 = 384*296*2/512 -> number of packets
    //for the V1 this is 640*482*2/512 = 1205 = 0x4B5
    uint16_t packets = (uint16_t)(size / 512);
    if(packets * 512 < size){
        packets++; //increase number of pakets to receive full frame
        size = packets * 512; //adapt size too!
    }
    unsigned char ctrl[16];
    int ret = libusb_control_transfer(this->dev_handle, 0x80, 0x86, packets, 0xbeef, ctrl, 0x10, 500);
    //C#: device.ReadExactPipe(0x86, 0x37800); //0x37800 = 384*296*2 bytes
    int len = 0; //actual length of returned data
    ret = libusb_bulk_transfer(this->dev_handle, 0x86, frame, size, &len, 500);
    //cout << "Read " << len << " bytes from pipe" << endl;

    return len;
}
