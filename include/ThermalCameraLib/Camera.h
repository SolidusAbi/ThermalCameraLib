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
            inline size_t getFrameSize(){ return static_cast<size_t>(getFrameWidth()*getFrameHeight()); }

        public slots:
            virtual bool connect() = 0;
            virtual bool disconnect() = 0;
            bool save(const char *filename); //Aquí no debería ir

        protected:
            int frameWidth;
            int frameHeight;
            QImage *displayableFrame;
    };
}

#endif // CAMERA_H
