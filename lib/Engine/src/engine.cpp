#include "engine.h"


engine::engine(hBridgePins* dcPins)
{
    _rpm = 0;
    _gearSelection = gearSelection::Neutral;
    _isRunning = false;
    _motorControl = new dcMotorControl(dcPins);
    _engineSounds = new sounds();
    _rpmLimit = 5500;
    _torqueMotorTable = rawMotorTable;
}

bool engine::isRunning()
{
    return _isRunning;
}

unsigned short engine::getRpm()
{
    return _rpm;
}

void engine::setGearSelection(gearSelection gearSelection)
{
    _gearSelection = gearSelection;
    if (gearSelection == gearSelection::Reverse)
        _motorControl->setDirection(0);
    else
        _motorControl->setDirection(1);
}

gearSelection engine::getGearSelection()
{
    return _gearSelection;
}

unsigned char engine::getFuelLevelPercent()
{
    // Todo: need to implement battery reader
    return 100;
}

void engine::startEngine(ignitionStartBehavior ignitionStartBehavior)
{
    if (ignitionStartBehavior == Failing)
    {
        _engineSounds->playEngineStartFailure();
        _isRunning = false;
        return;
    }
    
    if (ignitionStartBehavior == Successfully)
    {
        _engineSounds->playEngineStartSuccess();
        _isRunning = true;
        _rpm = 800;
    }
}

void engine::shutOffEngine()
{
    _isRunning = false;
    _rpm = 0;
    _gearSelection = gearSelection::Neutral;
    _motorControl->stop();
    _engineSounds->playEngineStop();
}

void engine::breakPedal(unsigned char brakePercent)
{
    
}

void engine::acceleratorPedal(unsigned char throttlePercent)
{
   // Need to emulate the engine load of Hemi Charger 500 engine
   // It will emulate torque curve from it
   // get time
    // to get rpm calculateEngineLoad(throtle, time)
    // with rpm in hands get value from torque table
    // from torque table, sends the value to dc engine
    short torqueCalculated = 100;
    _motorControl->setSpeed(torqueCalculated);
}
