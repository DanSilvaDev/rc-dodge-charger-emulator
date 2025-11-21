#ifndef LIGHTS_H
#define LIGHTS_H

#include <../Handlers/Interfaces/ILightsHandler.h>

// class ILightsHandler
// {
// public:
//     virtual ~ILightsHandler() = default;
//     virtual void setHeadlightsOff() = 0;
//     virtual void setParkingLightsOn() = 0;
//     virtual void setParkingLightsOff() = 0;
//     virtual void setHeadlightsLowBeam() = 0;
//     virtual void setHeadlightHighBeam() = 0;
//     virtual void setBreakLightLowBeam() = 0;
//     virtual void setBreakLightHighBeam() = 0;
//     virtual void setBreakLightsOff() = 0;
//     virtual void setBlinkRightTurnIndicator(unsigned long currentMillis) = 0;
//     virtual void setBlinkLeftTurnIndicator(unsigned long currentMillis) = 0;
//     virtual void setBlinkTurnIndicatorOff() = 0;
//     virtual void setBlinkEmergencyLights(unsigned long currentMillis) = 0;
//     virtual void setReverseLightOn() = 0;
//     virtual void setReverseLightOff() = 0;
//     virtual void setFogLightsOn() = 0;
//     virtual void setFogLightsOff() = 0;
// };

class Lights : public ILightsHandler
{
public:
    Lights(
        char leftHeadLightPin,
        char rightHeadLightPin,
        char rightRearBreakLightPin,
        char leftRearBreakLightPin,
        char rightTurnLightPin,
        char leftTurnLightPin,
        char reverseLightPin = -1,
        char fogLightPin = -1,
        short blinkFrequencyMillis = 500);

    void setHeadlightsOff() override;
    void setParkingLightsOn() override;
    void setParkingLightsOff() override;
    void setHeadlightsLowBeam() override;
    void setHeadlightHighBeam() override;
    void setBreakLightLowBeam() override;
    void setBreakLightHighBeam() override;
    void setBreakLightsOff() override;
    void setBlinkRightTurnIndicator(unsigned long currentMillis) override;
    void setBlinkLeftTurnIndicator(unsigned long currentMillis) override;
    void setBlinkTurnIndicatorOff() override;
    void setBlinkEmergencyLights(unsigned long currentMillis) override;
    void setReverseLightOn() override;
    void setReverseLightOff() override;
    void setFogLightsOn() override;
    void setFogLightsOff() override;

private:
    inline void configurePins();
    static inline void setPinAsOutputIfValid(char pinNumber);

    /// This function checks if has passed enough time based on the frequency desired to set the PIN high or Low
    /// @param pinNumber the Pin to be set HIGH or Low
    /// @param lastState the last state know of the PIN
    /// @param lastMillis the last millis registered
    /// @param currentMillis the current millis at the time of the calling this function
    /// @param frequencyDesired the frequency desired for the blink to happen in millis seconds
    /// @return The state that should be at the moment, could be High or Low
    static inline char blinkOnFrequency(char pinNumber, char lastState, unsigned long lastMillis,
                                        unsigned long currentMillis,
                                        short frequencyDesired);
    char leftHeadLightPin;
    char rightHeadLightPin;
    char rightRearBreakLightPin;
    char leftRearBreakLightPin;
    char reverseLightPin;
    char fogLightPin;
    char rightTurnLightPin;
    char leftTurnLightPin;
    unsigned long lastMillis;
    char blinkLastState;
    short blinkFrequencyMillis;
};

#endif // LIGHTS_H
