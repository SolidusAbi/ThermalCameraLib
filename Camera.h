#ifndef CAMERA_H
#define CAMERA_H

#include <QImage>

namespace mt4sd {
    class Camera {
        public:
            Camera (int frameWidth, int frameHeight);
            virtual ~Camera ();
            virtual QImage *getDisplayFrame() = 0;

            virtual bool connect() = 0;
            virtual bool disconnect() = 0;

            inline int getFrameWidth(){ return frameWidth; }
            inline int getFrameHeight(){ return frameHeight; }
            inline int getFrameSize(){ return getFrameWidth()*getFrameHeight(); }
        private:
            int frameWidth;
            int frameHeight;
    };
}

#endif // CAMERA_H
