#ifndef REALSENSED415CAMERA_H
#define REALSENSED415CAMERA_H

#include "Camera.h"

#include <librealsense2/rs.hpp>

namespace mt4sd {
    class RealSenseD415Camera : public Camera
    {
        public:
            RealSenseD415Camera();
            ~RealSenseD415Camera() override;

            QImage * getDisplayFrame() override;

        public slots:
            bool connect() override;
            bool disconnect() override;

        private:
            rs2::context ctx;
            rs2::pipeline pipe;
            rs2::pipeline_profile profile;
            rs2::config cfg;
            rs2::colorizer colorMap;

            rs2_stream alignTo;
            rs2::align align;

            rs2::decimation_filter dec;
            rs2::spatial_filter spat;
            rs2::temporal_filter temp;
            rs2::disparity_transform depth2disparity;
            rs2::disparity_transform disparity2depth;

            rs2_stream findStreamToAlign(const std::vector<rs2::stream_profile> &streams);
            void configureCamera();
            void getDisplayFrame(const uint16_t *frame, int size, unsigned char *display);
    };
}

#endif // REALSENSED415CAMERA_H
