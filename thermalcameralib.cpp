#include "thermalcameralib.h"
#include <iostream>

mt4sd::ThermalCameraLib::ThermalCameraLib(){}

mt4sd::ThermalCameraLib::ThermalCameraLib(mt4sd::Camera device)
{
    this->device = device;
    this->displayableFrame = new QImage(new uchar[this->getFrameSize()], this->getFrameWidth(), this->getFrameHeight(), QImage::Format::Format_Grayscale8);

    if (this->connect() == 0)
        this->connected = true;
    else
        this->connected = false;
}

mt4sd::ThermalCameraLib::~ThermalCameraLib(){
    if (this->dev_handle == nullptr)
        return;

    //send disconnect command
    unsigned char ctrl[16];
    libusb_control_transfer(dev_handle, 0x80, 0x33, 0x1, 0xbeef, ctrl, 0x10, 500);

    //release the claimed interface
    if (libusb_release_interface(dev_handle, 0))
    {
        libusb_close(dev_handle); //close the device we opened
        libusb_exit(ctx); //needs to be called to end the
    }
}

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
    if (this->dev_handle == nullptr)
    {
        libusb_free_device_list(usb_devs, 1); //free the list, unref the devices in it
        libusb_exit(this->ctx); //needs to be called to end the
        return -1;
    }
    libusb_free_device_list(usb_devs, 1); //free the list, unref the devices in it
    if (libusb_kernel_driver_active(this->dev_handle, 0) == 1)  //find out if kernel driver is attached
        libusb_detach_kernel_driver(this->dev_handle, 0);       //detach it

    r = libusb_claim_interface(this->dev_handle, 0); //claim interface 0 (the first) of device (mine had just 1)
    if(r < 0)
    {
        libusb_close(this->dev_handle); //close the device we opened
        libusb_exit(this->ctx); //needs to be called to end the
        return -1;
    }

    return 0;
}

QImage * mt4sd::ThermalCameraLib::getDisplayFrame()
{
    int len = this->readRawFrame(this->rawSize, this->rawFrame);
    if (len > 0){
        int offset = 0; //NO TOP LINES?! 4*384*2; //4 top + 4 bottom CDS lines for Q1 / zero for V1 (only 2x botton CDS lines)
        this->getShortFrame(this->rawFrame, this->frameSize, offset, this->frame);
        this->getDisplayFrame(frame, frameSize, this->displayableFrame->bits()); //convert to 8-bit and clip to min/max
    }

    return this->displayableFrame;
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
    uint16_t packets = static_cast<uint16_t>(size / 512);
    if(packets * 512 < size)
    {
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

void mt4sd::ThermalCameraLib::getShortFrame(unsigned char *raw, int imageSizePixels, int offsetBytes, unsigned short *frame)
{
    unsigned short val = 0;
    for(int i=0; i<imageSizePixels; i++)
    {
        int pos = offsetBytes + 2*i;
        val = static_cast<unsigned short>((raw[pos+1] << 8) | raw[pos]); //directly swap byte order
        /* min = val < min ? val : min;
        max = val > max ? val : max; */
        frame[i] = val;
    }
}

void mt4sd::ThermalCameraLib::getDisplayFrame(unsigned short *frame, int size, unsigned char *display)
{
    unsigned short min = 65535;
    unsigned short max = 0;
    //get min/max values -> AGC
    for(int i=0;i<size;i++){
        min = frame[i] < min ? frame[i] : min;
        max = frame[i] > max ? frame[i] : max;
    }
    //cout << "AGC: min = " << min << " - max = " << max << endl;
    //now scale ouput data
    //TBD: flip upside down!
    double invDelta = 1.0 / (static_cast<double>(max-min));
    for(int i=0;i<size;i++){
        display[i] = static_cast<unsigned char>((255.0 * (frame[i] - min)) * invDelta);
    }
}
