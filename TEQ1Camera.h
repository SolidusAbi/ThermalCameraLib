#ifndef TEQ1CAMERA_H
#define TEQ1CAMERA_H

#include <QObject>
#include "Camera.h"
#include <i3system/i3system_TE.h>

namespace mt4sd {
    class TEQ1Camera : public Camera
    {
        public:
            TEQ1Camera();
            ~TEQ1Camera();

            QImage * getDisplayFrame() override;
            bool connect() override;
            bool disconnect() override;
        private:
            i3::TE_B *pTE;
            unsigned short *pImgBuf;
            float *pRecvTemp;
            QImage *displayableFrame;

            void getDisplayFrame(unsigned short *frame, int size, unsigned char *display);
    };
}

#endif // TEQ1CAMERA_H
