#ifndef COMPASS_H_INCLUDED
#define COMPASS_H_INCLUDED

#include <QMC5883LCompass.h>

class Compass {
    
    private:
        QMC5883LCompass comp;

    public:

        void init();
        
        // Calibrates the compass automatically by sending rotate command to arduino
        void autoCalibrate();
        
        /* Get angle (0 - 359) where:
                0: North
                90: East
                180: South
                270: West
        */
        int getAzimuth();
};

#endif