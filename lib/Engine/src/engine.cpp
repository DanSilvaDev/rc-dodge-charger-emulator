#include "engine.h"
#include <esp32-hal.h>

#include "cmath"

engine::engine(hBridgePins* dcPins)
{
    _rpm = 0;
    _gearSelection = gearSelection::Neutral;
    _isRunning = false;
    _motorControl = new dcMotorControl(dcPins);
    _motorControl->setDirection(0);
    _engineSounds = new sounds();
    _rpmLimit = 5500;
    _idleRpm = 800;
    _lastUpdateTime = millis();
    _updateIntervalMillis = 50;
    // _torqueMotorTable = rawMotorTable;
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
        _rpm = _idleRpm;
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
    // for simplistic behavior it will just stop
    // Todo: add break factor to engine load calc
    _motorControl->stop();
    _engineSounds->playIdle();
    _rpm = _idleRpm;
}

void engine::acceleratorPedal(unsigned char throttlePercent)
{
    // Need to emulate the engine load of Hemi Charger 500 engine
    // It will emulate a torque curve from it
    // get time
    // to get rpm calculateEngineLoad(throtle, time)
    calculateEngineLoad(throttlePercent);
    if (_rpm <= _idleRpm)
    {
        _motorControl->stop();
        _engineSounds->playIdle();
        return;
    }
    // with rpm in hands get value from torque table
    // from torque table, sends the value to dc engine
    short torqueCalculated = calculateTorquePercent(_rpm);
    _motorControl->setSpeed(torqueCalculated);
}

double engine::calculateTorquePercent(unsigned short rpm)
{
    if (_gearSelection == gearSelection::Neutral || rpm == _idleRpm)
        return 0;

    // formula to emulate the Hemi engine torque curve in percentage
    double torquePerc = (((rpm * rpm) - 0.0000087832168) + (0.0659552447552 * rpm) - 23.2000000000051);
    if (torquePerc < 0)
        torquePerc = 0;
    if (torquePerc > 100)
        torquePerc = 100;

    return std::round(torquePerc);
}

void engine::calculateEngineLoad(unsigned char throttlePercent)
{
    if (!_isRunning)
        return;

    long currentTime = millis();
    // if less than desired interval ms do nothing
    if (currentTime - _lastUpdateTime < _updateIntervalMillis )
        return;

    // for simplistic simulation 30% to 50% throttle will make rpm steady
    if (throttlePercent >= 30 && throttlePercent <= 50)
    {
        return;
    }
    
    _lastUpdateTime = currentTime;

    // Trying to emulate the engine load based on throttle and gear selection,
    // this will also simulate some inertia when the throttle is released
    double alphaFactor = 0;
    double throttleInfluenceFactor = throttlePercent / 1000.0;
    switch (_gearSelection)
    {
        case gearSelection::Neutral:
            alphaFactor = 0.3 + throttleInfluenceFactor;
            break;
        case gearSelection::G1:
            alphaFactor = 0.12 + throttleInfluenceFactor;
        case gearSelection::G2:
            alphaFactor = 0.1 + throttleInfluenceFactor;
        case gearSelection::G3:
            alphaFactor = 0.08 + throttleInfluenceFactor;
        case gearSelection::G4:
            alphaFactor = 0.06 + throttleInfluenceFactor;
        case gearSelection::G5:
            alphaFactor = 0.04 + throttleInfluenceFactor;
        default:
            alphaFactor = 0.1 + throttleInfluenceFactor;
            break;
    }

    if (throttlePercent < 30)
    {
        alphaFactor = -alphaFactor;
        _engineSounds->playRevEngAtDecelerating();
    }
        

    double finalRpm = _rpm + (_rpm * alphaFactor);

    if (finalRpm > _rpmLimit)
        finalRpm = _rpmLimit;

    if (finalRpm < _idleRpm)
        finalRpm = _idleRpm;
    
    if (finalRpm > _rpm)
    {
        _engineSounds->playRevEngAtAccelerating();
    }
    
    _rpm = static_cast<int>(round(finalRpm));
}