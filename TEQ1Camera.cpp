#include "TEQ1Camera.h"

mt4sd::TEQ1Camera::TEQ1Camera():
    Camera(384, 288)
{
    pImgBuf = new unsigned short[getFrameSize()];
    displayableFrame = new QImage(new uchar[getFrameSize()], getFrameWidth(), getFrameHeight(), QImage::Format::Format_Grayscale8);
    this->connect();
}

mt4sd::TEQ1Camera::~TEQ1Camera(){
    delete pImgBuf;
    delete displayableFrame;
    this->disconnect();
}

QImage * mt4sd::TEQ1Camera::getDisplayFrame()
{
    this->pTE->RecvImage(this->pImgBuf);
    getDisplayFrame(this->pImgBuf, this->getFrameSize(), displayableFrame->bits());
    return displayableFrame;
}

bool mt4sd::TEQ1Camera::connect()
{
    i3::SCANINFO *pScan = new i3::SCANINFO[MAX_USB_NUM];
    int hnd_dev = -1;

    i3::ScanTE(pScan);
    for (int i = 0; (i < MAX_USB_NUM) && (hnd_dev == -1); i++) {
        if (pScan[i].bDevCon)
            hnd_dev = i;
    }
    delete[] pScan;

    bool isConnected = (hnd_dev >= 0) && (this->pTE = i3::OpenTE_B(I3_TE_Q1, hnd_dev)) && (this->pTE->ReadFlashData() == 1);

    return isConnected;
}


bool mt4sd::TEQ1Camera::disconnect()
{
    if (pTE != nullptr)
        return false;

    pTE->CloseTE();
    return true;
}

void mt4sd::TEQ1Camera::getDisplayFrame(unsigned short *frame, int size, unsigned char *display)
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
