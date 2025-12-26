#ifndef ENGINE_H
#define ENGINE_H
#include "models/gearSelection.h"
#include "models/ignitionStartBehavior.h"
#include "../controls/models/hBridgePins.h"
#include "../controls/dcMotorControl.h"
#include "../sounds/sounds.h"
#include "models/torqueMotorTable.h"

class engine
{
    private:
        bool _isRunning;
        unsigned int _rpm;
        gearSelection _gearSelection;
        dcMotorControl* _motorControl;
        sounds* _engineSounds;
        unsigned short _rpmLimit;
        torqueMotorTable* _torqueMotorTable;
        
        void calculateEngineLoad();
    public:
        engine(hBridgePins* dcPins);
        bool isRunning();
        unsigned short getRpm();
        gearSelection getGearSelection();
        unsigned char getFuelLevelPercent();
        void startEngine(ignitionStartBehavior ignitionStartBehavior);
        void shutOffEngine();
        void acceleratorPedal(unsigned char throttlePercent);
        void breakPedal(unsigned char brakePercent);
        void setGearSelection(gearSelection gearSelection);
};


#endif //ENGINE_H