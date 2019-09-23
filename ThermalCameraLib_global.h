#ifndef THERMALCAMERALIB_GLOBAL_H
#define THERMALCAMERALIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(THERMALCAMERALIB_LIBRARY)
#  define THERMALCAMERALIB_EXPORT Q_DECL_EXPORT
#else
#  define THERMALCAMERALIB_EXPORT Q_DECL_IMPORT
#endif

namespace mt4sd
{
    enum Camera
    {
        I3_TE_Q1 = 1,
        DEFAULT
    };

    typedef struct TE_Setting{
        unsigned short colorMap;/**< Display colormap. */
        unsigned short brightness;/**< Brighness of image. */
        unsigned short contrast;/**< Contrast of image. */
        bool AGC;/**< Apply AGC or not. */
        bool AIE;/**< Apply AIE or not. */
        unsigned short AIE_Factor;/**< AIE factor to apply in AIE algorithm. */
        bool alarm;/**< Apply alarm or not. */
        unsigned short alarmTemp;/**< Limit temperature when alarm is on. */
        bool traceHot;/**< Trace hottest point or not. */
        bool traceCold;/**< Trace coldest point or not. */
        bool center;/**< Display center temperature or not. */
        unsigned short frameRate;
        unsigned short shutterMode;
        unsigned short shutterTime;
        unsigned short shutterTemp;
        unsigned short exportable;
    }TE_SETTING;

}

#endif // THERMALCAMERALIB_GLOBAL_H
