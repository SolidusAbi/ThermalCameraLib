#ifndef CAMERA_H
#define CAMERA_H

#include "ThermalCameraLib_global.h"
#include <QImage>

namespace mt4sd {
    class THERMALCAMERALIB_EXPORT Camera : public QObject
    {
        Q_OBJECT

        public:
            Camera();
            virtual ~Camera();
            virtual QImage *getDisplayFrame() = 0;

            inline int getFrameWidth(){ return frameWidth; }
            inline int getFrameHeight(){ return frameHeight; }
            inline int getFrameSize(){ return getFrameWidth()*getFrameHeight(); }

        public slots:
            virtual bool connect() = 0;
            virtual bool disconnect() = 0;

        protected:
            int frameWidth;
            int frameHeight;
            QImage *displayableFame;
    };
}

#endif // CAMERA_H
