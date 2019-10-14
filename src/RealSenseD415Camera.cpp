#include "RealSenseD415Camera.h"

#include <QDebug>

// Importante, usar el ejemplo rs-measure como referencia! :D

mt4sd::RealSenseD415Camera::RealSenseD415Camera() :
    Camera(), ctx(), pipe(ctx), profile(), cfg(), colorMap(), alignTo(RS2_STREAM_DEPTH), align(alignTo),
    dec(), spat(), temp(), depth2disparity(), disparity2depth(false)
{
    configureCamera();
    if (this->connect()){
        frameWidth = 640;
        frameHeight = 480;
        //displayableFrame = new QImage(new uchar[getFrameSize()], getFrameWidth(), getFrameHeight(), QImage::Format::Format_Grayscale8);
        displayableFrame = new QImage(new uchar[getFrameSize()*3], getFrameWidth(), getFrameHeight(), QImage::Format::Format_RGB888);
    }
}

mt4sd::RealSenseD415Camera::~RealSenseD415Camera()
{
    // Will be disconnected automatically before being destroyed
}

QImage * mt4sd::RealSenseD415Camera::getDisplayFrame()
{
    //If it is too slow, you can increase the following parameter to decimate depth more (reducing quality)
    dec.set_option(RS2_OPTION_FILTER_MAGNITUDE, 1);

    //rs2::frameset frames = pipe.wait_for_frames();
    rs2::frameset data;
    if(pipe.poll_for_frames(&data))
    {
        data = data.apply_filter(align);

        // Decimation will reduce the resultion of the depth image,
        // closing small holes and speeding-up the algorithm
        data = data.apply_filter(dec);

        // To make sure far-away objects are filtered proportionally
        // we try to switch to disparity domain
        data = data.apply_filter(depth2disparity);

        // Apply spatial filtering
        data = data.apply_filter(spat);

        // Apply temporal filtering
        data = data.apply_filter(temp);

        // If we are in disparity domain, switch back to depth
        data = data.apply_filter(disparity2depth);

        //// Apply color map for visualization of depth
        data = data.apply_filter(colorMap);

        auto depth = data.get_depth_frame();
        auto color = data.get_color_frame();

        //const uint16_t *test2 = static_cast<const uint16_t *>(depth.get_data());
        const uchar *color_test2 = static_cast<const uchar *>(color.get_data());
        this->bgrToRgb(displayableFrame->bits(), color_test2, this->getFrameSize());

        //getDisplayFrame(test2, this->getFrameSize(), displayableFrame->bits());


//        auto colorized_depth = data.first(RS2_STREAM_DEPTH, RS2_FORMAT_RGB8);

//        colorized_depth.get_data();


//        auto depth = data.get_depth_frame();
//        qDebug() << depth.get_data_size();

//        rs2::frame  depth_texture;
//        depth_texture = colorMap.colorize(depth);

//        depth_texture.get_data();
//        const uint16_t *test2 = static_cast<const uint16_t *>(depth.get_data());
//        for (size_t i=0; i < 10; ++i){
//            //qDebug() << static_cast<uint16_t *>(test[0]);
//            //qDebug() << static_cast<char *[10]>(test)[0][0];
//            //qDebug() << QVariant::fromValue(test);
//            qDebug() << test2[i];
//        }
//        //data = reinterpret_cast<uchar>(depth.get_data());
//        qDebug() << "Parate aquí";

    }

    return displayableFrame;
}

bool mt4sd::RealSenseD415Camera::connect()
{
    try {
        profile = pipe.start(cfg);
        //alignTo = findStreamToAlign(profile.get_streams());
        align   = rs2::align(alignTo);

        //Set the device to High Accuracy preset
        rs2::depth_sensor sensor = profile.get_device().first<rs2::depth_sensor>();
        if (sensor && sensor.is<rs2::depth_stereo_sensor>())
            sensor.set_option(RS2_OPTION_VISUAL_PRESET, RS2_RS400_VISUAL_PRESET_HAND);

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

void mt4sd::RealSenseD415Camera::configureCamera()
{
    cfg = rs2::config();
    cfg.enable_stream(RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_BGR8, 30);
    cfg.enable_stream(RS2_STREAM_DEPTH, 640, 480, RS2_FORMAT_Z16, 30); //16-bit depth values
}

void mt4sd::RealSenseD415Camera::getDisplayFrame(const uint16_t *frame, int size, unsigned char *display)
{
    unsigned short min = 65535;
    unsigned short max = 0;
    //get min/max values -> AGC
    for(int i=0; i<size; i++)
    {
        min = frame[i] < min ? frame[i] : min;
        max = frame[i] > max ? frame[i] : max;
    }
    //cout << "AGC: min = " << min << " - max = " << max << endl;
    //now scale ouput data
    //TBD: flip upside down!
    double invDelta = 1.0 / (static_cast<double>(max-min));
    for(int i=0;i<size;i++)
    {
        display[i] = static_cast<unsigned char>((255.0 * (frame[i] - min)) * invDelta);
    }
}

void mt4sd::RealSenseD415Camera::bgrToRgb(uchar *rgb, const uchar *bgr, size_t frameSize){
    for(size_t pixel=0; pixel < frameSize; ++pixel)
        for (ssize_t channel=2; channel >= 0; --channel)
            rgb[pixel * 3 + 2 - static_cast<size_t>(channel)] = bgr[pixel * 3 + static_cast<size_t>(channel)];
}
