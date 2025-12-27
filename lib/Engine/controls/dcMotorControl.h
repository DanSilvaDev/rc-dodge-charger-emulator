#ifndef DCMOTORCONTROL_H
#define DCMOTORCONTROL_H

#include "models/hBridgePins.h"


class dcMotorControl
{
    private:
        hBridgePins* _pins;
        void configOutputPin(int pinNumber);
    public:
        dcMotorControl(hBridgePins* dcPins);
        void setSpeed(unsigned short speed);
        void stop();
        /// 0 - Reverse, 1 - Forward
        void setDirection(bool direction);
};


#endif //DCMOTORCONTROL_H