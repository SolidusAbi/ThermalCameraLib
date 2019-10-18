#ifndef DEBUGCAMERA_H
#define DEBUGCAMERA_H

#include "Camera.h"

namespace mt4sd {
    class THERMALCAMERALIB_EXPORT DebugCamera : public Camera
    {
        public:
            DebugCamera();
            ~DebugCamera() override;

            QImage * getDisplayFrame() override;

        public slots:
            bool connect() override;
            bool disconnect() override;

        private:
            double *imgBuff;
    };
}

#endif // DEBUGCAMERA_H
