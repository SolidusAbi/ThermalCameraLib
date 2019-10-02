#ifndef REALSENSED415CAMERA_H
#define REALSENSED415CAMERA_H

#include "Camera.h"

#include <librealsense2/rs.hpp>

namespace mt4sd {
    class RealSenseD415Camera : public Camera
    {
        public:
            RealSenseD415Camera();
            ~RealSenseD415Camera();

        public slots:
            bool connect() override;
            bool disconnect() override;

        private:
            rs2::pipeline pipe;
            rs2::config cfg;
            rs2::pipeline_profile profile;
            rs2_stream alignTo;
            rs2::align align;
            rs2::colorizer colorMap;

            rs2_stream findStreamToAlign(const std::vector<rs2::stream_profile> &streams);
    };
}

#endif // REALSENSED415CAMERA_H
