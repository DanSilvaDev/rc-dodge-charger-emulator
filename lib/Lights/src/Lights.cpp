#include "Lights.h"
#include "Arduino.h"


Lights::Lights(CarLightModel& lightModel, short blinkFrequencyMillis)
{
    _pCarLightModel = &lightModel;
    _blinkFrequencyMillis = blinkFrequencyMillis;
    _lastMillis = millis();
    _blinkLastState = LOW;
    configurePins();
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
    _blinkLastState = blinkOnFrequency(_pCarLightModel->rightTurnLightPin, _blinkLastState, _lastMillis,
                                                  currentMillis, _blinkFrequencyMillis);
    _lastMillis = currentMillis;
}

void Lights::setBlinkLeftTurnIndicator(unsigned long currentMillis)
{
    _blinkLastState = blinkOnFrequency(_pCarLightModel->leftTurnLightPin, _blinkLastState, _lastMillis,
                                                  currentMillis, _blinkFrequencyMillis);
    _lastMillis = currentMillis;
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
    setPinAsOutputIfValid(_pCarLightModel->leftTurnLightPin);
    setPinAsOutputIfValid(_pCarLightModel->rightTurnLightPin);
    setPinAsOutputIfValid(_pCarLightModel->fogLightPin);
    setPinAsOutputIfValid(_pCarLightModel->reverseLightPin);
    _lastMillis = millis();
    _blinkLastState = LOW;
}

void Lights::setPinAsOutputIfValid(char pinNumber)
{
    if (pinNumber < 1)
        return;

    pinMode(pinNumber, OUTPUT);
}

char Lights::blinkOnFrequency(char pinNumber, char lastState, unsigned long lastMilles, unsigned long currentMillis,
                              short frequencyDesired)
{
    unsigned long diffTime = currentMillis - lastMilles;
    char finalState = lastState;

    // it could be zero when the overflow has already happened
    // to see: https://docs.arduino.cc/language-reference/en/functions/time/millis/
    if (diffTime >= frequencyDesired || diffTime == 0)
    {
        finalState = !lastState;
        digitalWrite(pinNumber, finalState);
    }
    return finalState;
}
