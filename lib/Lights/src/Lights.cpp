#include "Lights.h"
#include "Arduino.h"


Lights::Lights(CarLightModel* lightModel, short blinkFrequencyMillis)
{
    _pCarLightModel = lightModel;
    _blinkFrequencyMillis = blinkFrequencyMillis;
    _lastMillis = 0;
    _blinkLastState = LOW;
}

// Todo: Pending to implement proper the intermediary stages. I don`t want to occupy all PWM ports for lights

void Lights::setHeadlightsOff()
{
    digitalWrite(_pCarLightModel->rightHeadLightPin, LOW);
    digitalWrite(_pCarLightModel->leftHeadLightPin, LOW);
}

void Lights::setParkingLightsOn()
{
    digitalWrite(_pCarLightModel->rightHeadLightPin, HIGH);
    digitalWrite(_pCarLightModel->leftHeadLightPin, HIGH);
    digitalWrite(_pCarLightModel->leftRearBreakLightPin, HIGH);
    digitalWrite(_pCarLightModel->rightRearBreakLightPin, HIGH);
}

void Lights::setParkingLightsOff()
{
    digitalWrite(_pCarLightModel->rightHeadLightPin, HIGH);
    digitalWrite(_pCarLightModel->leftHeadLightPin, HIGH);
    digitalWrite(_pCarLightModel->leftRearBreakLightPin, HIGH);
    digitalWrite(_pCarLightModel->rightRearBreakLightPin, HIGH);
}

void Lights::setHeadlightsLowBeam()
{
    digitalWrite(_pCarLightModel->rightHeadLightPin, HIGH);
    digitalWrite(_pCarLightModel->leftHeadLightPin, HIGH);
}

void Lights::setHeadlightHighBeam()
{
    digitalWrite(_pCarLightModel->rightHeadLightPin, HIGH);
    digitalWrite(_pCarLightModel->leftHeadLightPin, HIGH);
}

void Lights::setBreakLightLowBeam()
{
    digitalWrite(_pCarLightModel->leftRearBreakLightPin, HIGH);
    digitalWrite(_pCarLightModel->rightRearBreakLightPin, HIGH);
}

void Lights::setBreakLightHighBeam()
{
    digitalWrite(_pCarLightModel->leftRearBreakLightPin, HIGH);
    digitalWrite(_pCarLightModel->rightRearBreakLightPin, HIGH);
}

void Lights::setBreakLightsOff()
{
    digitalWrite(_pCarLightModel->leftRearBreakLightPin, LOW);
    digitalWrite(_pCarLightModel->rightRearBreakLightPin, LOW);
}

void Lights::setBlinkRightTurnIndicator(unsigned long currentMillis)
{
    blinkOnFrequency(_pCarLightModel->rightTurnLightPin, _blinkLastState, _lastMillis,
                                                  currentMillis, _blinkFrequencyMillis);
}

void Lights::setBlinkLeftTurnIndicator(unsigned long currentMillis)
{
    blinkOnFrequency(_pCarLightModel->leftTurnLightPin, _blinkLastState, _lastMillis,
                                                  currentMillis, _blinkFrequencyMillis);
}

void Lights::setBlinkTurnIndicatorOff()
{
    digitalWrite(_pCarLightModel->leftTurnLightPin, LOW);
    digitalWrite(_pCarLightModel->rightTurnLightPin, LOW);
}

void Lights::setBlinkEmergencyLights(unsigned long currentMillis)
{
    setBlinkLeftTurnIndicator(currentMillis);
    // just follows the last blink state set so they could be the same
    digitalWrite(_pCarLightModel->rightTurnLightPin, _blinkLastState);
}

void Lights::setReverseLightOn()
{
    digitalWrite(_pCarLightModel->reverseLightPin, HIGH);
}

void Lights::setReverseLightOff()
{
    digitalWrite(_pCarLightModel->reverseLightPin, LOW);
}

void Lights::setFogLightsOn()
{
    digitalWrite(_pCarLightModel->fogLightPin, HIGH);
}

void Lights::setFogLightsOff()
{
    digitalWrite(_pCarLightModel->fogLightPin, LOW);
}

void Lights::configurePins()
{
    setPinAsOutputIfValid(_pCarLightModel->rightHeadLightPin);
    setPinAsOutputIfValid(_pCarLightModel->leftHeadLightPin);
    setPinAsOutputIfValid(_pCarLightModel->rightRearBreakLightPin);
    setPinAsOutputIfValid(_pCarLightModel->leftRearBreakLightPin);
    setPinAsOutputIfValid(_pCarLightModel->rightTurnLightPin);
    setPinAsOutputIfValid(_pCarLightModel->leftTurnLightPin);
    setPinAsOutputIfValid(_pCarLightModel->fogLightPin);
    setPinAsOutputIfValid(_pCarLightModel->reverseLightPin);
    _lastMillis = millis();
}

void Lights::setPinAsOutputIfValid(char pinNumber)
{
    if (pinNumber < 1)
        return;

    pinMode(pinNumber, OUTPUT);
}

void Lights::blinkOnFrequency(char pinNumber, char & pinState, unsigned long & lastMillis, unsigned long currentMillis,
                              short frequencyDesired)
{
    unsigned long diffTime = currentMillis - lastMillis;
    // it could be zero when the overflow has already happened
    // to see: https://docs.arduino.cc/language-reference/en/functions/time/millis/
    if (diffTime >= frequencyDesired) // || diffTime == 1)
    {
        pinState = !pinState;
        digitalWrite(pinNumber, pinState);
        lastMillis = millis();
    }
}
