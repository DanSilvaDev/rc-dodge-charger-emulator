#include "Lights.h"
#include "Arduino.h"


Lights::Lights(char leftHeadLightPin, char rightHeadLightPin,
               char rightRearBreakLightPin, char leftRearBreakLightPin,
               char rightTurnLightPin, char leftTurnLightPin,
               char reverseLightPin, char fogLightPin, short blinkFrequencyMillis)
{
    this->leftHeadLightPin = leftHeadLightPin;
    this->rightHeadLightPin = rightHeadLightPin;
    this->leftRearBreakLightPin = leftRearBreakLightPin;
    this->rightRearBreakLightPin = rightRearBreakLightPin;
    this->rightTurnLightPin = rightTurnLightPin;
    this->leftTurnLightPin = leftTurnLightPin;
    this->reverseLightPin = reverseLightPin;
    this->fogLightPin = fogLightPin;
    this->blinkFrequencyMillis = blinkFrequencyMillis;

    this->configurePins();
}

// Todo: Pending to implement proper the intermediary stages. I don`t want to occupy all PWM ports for lights

void Lights::setHeadlightsOff()
{
    digitalWrite(this->rightHeadLightPin, LOW);
    digitalWrite(this->leftHeadLightPin, LOW);
}

void Lights::setParkingLightsOn()
{
    digitalWrite(this->rightHeadLightPin, HIGH);
    digitalWrite(this->leftHeadLightPin, HIGH);
    digitalWrite(this->leftRearBreakLightPin, HIGH);
    digitalWrite(this->rightRearBreakLightPin, HIGH);
}

void Lights::setParkingLightsOff()
{
    digitalWrite(this->rightHeadLightPin, HIGH);
    digitalWrite(this->leftHeadLightPin, HIGH);
    digitalWrite(this->leftRearBreakLightPin, HIGH);
    digitalWrite(this->rightRearBreakLightPin, HIGH);
}

void Lights::setHeadlightsLowBeam()
{
    digitalWrite(this->rightHeadLightPin, HIGH);
    digitalWrite(this->leftHeadLightPin, HIGH);
}

void Lights::setHeadlightHighBeam()
{
    digitalWrite(this->rightHeadLightPin, HIGH);
    digitalWrite(this->leftHeadLightPin, HIGH);
}

void Lights::setBreakLightLowBeam()
{
    digitalWrite(this->leftRearBreakLightPin, HIGH);
    digitalWrite(this->rightRearBreakLightPin, HIGH);
}

void Lights::setBreakLightHighBeam()
{
    digitalWrite(this->leftRearBreakLightPin, HIGH);
    digitalWrite(this->rightRearBreakLightPin, HIGH);
}

void Lights::setBreakLightsOff()
{
    digitalWrite(this->leftRearBreakLightPin, LOW);
    digitalWrite(this->rightRearBreakLightPin, LOW);
}

void Lights::setBlinkRightTurnIndicator(unsigned long currentMillis)
{
    this->blinkLastState = this->blinkOnFrequency(this->rightTurnLightPin, this->blinkLastState, this->lastMillis,
                                                  currentMillis, this->blinkFrequencyMillis);
    this->lastMillis = currentMillis;
}

void Lights::setBlinkLeftTurnIndicator(unsigned long currentMillis)
{
    this->blinkLastState = this->blinkOnFrequency(this->leftTurnLightPin, this->blinkLastState, this->lastMillis,
                                                  currentMillis, this->blinkFrequencyMillis);
    this->lastMillis = currentMillis;
}

void Lights::setBlinkTurnIndicatorOff()
{
    digitalWrite(this->leftTurnLightPin, LOW);
    digitalWrite(this->rightTurnLightPin, LOW);
}

void Lights::setBlinkEmergencyLights(unsigned long currentMillis)
{
    this->setBlinkLeftTurnIndicator(currentMillis);
    // just follows the last blink state set so they could be the same
    digitalWrite(this->rightTurnLightPin, this->blinkLastState);
}

void Lights::setReverseLightOn()
{
    digitalWrite(this->reverseLightPin, HIGH);
}

void Lights::setReverseLightOff()
{
    digitalWrite(this->reverseLightPin, LOW);
}

void Lights::setFogLightsOn()
{
    digitalWrite(this->fogLightPin, HIGH);
}

void Lights::setFogLightsOff()
{
    digitalWrite(this->fogLightPin, LOW);
}

void Lights::configurePins()
{
    this->setPinAsOutputIfValid(this->rightHeadLightPin);
    this->setPinAsOutputIfValid(this->leftHeadLightPin);
    this->setPinAsOutputIfValid(this->rightRearBreakLightPin);
    this->setPinAsOutputIfValid(this->leftRearBreakLightPin);
    this->setPinAsOutputIfValid(this->leftTurnLightPin);
    this->setPinAsOutputIfValid(this->rightTurnLightPin);
    this->setPinAsOutputIfValid(this->fogLightPin);
    this->setPinAsOutputIfValid(this->reverseLightPin);
    this->lastMillis = millis();
    this->blinkLastState = LOW;
}

void Lights::setPinAsOutputIfValid(char pinNumber)
{
    if (pinNumber < 0)
        return;

    pinMode(pinNumber, OUTPUT);
}

char Lights::blinkOnFrequency(char pinNumber, char lastState, unsigned long lastMilles, unsigned long currentMillis,
                              short frequencyDesired)
{
    long diffTime = currentMillis - lastMilles;
    char finalState = lastState;

    // it could be negative when the overflow has already happened
    // see: https://docs.arduino.cc/language-reference/en/functions/time/millis/
    if (diffTime >= frequencyDesired || diffTime < 0)
    {
        finalState = !lastState;
        digitalWrite(pinNumber, finalState);
    }
    return finalState;
}
