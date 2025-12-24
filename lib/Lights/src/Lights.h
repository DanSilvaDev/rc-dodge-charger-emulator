#ifndef LIGHTS_H
#define LIGHTS_H

#include <../Handlers/Interfaces/ILightsHandler.h>
#include <../Models/CarLightModel.h>


class Lights : public ILightsHandler
{
    public:
        explicit Lights(CarLightModel* lightModel,
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
        void configurePins();

    private:
        // Properties
        CarLightModel* _pCarLightModel;
        unsigned long _lastMillis;
        char _blinkLastState;
        short _blinkFrequencyMillis;
        //Methods
        static void setPinAsOutputIfValid(char pinNumber);

        /// This function checks if it has passed enough time based on the frequency desired to set the PIN high or Low
        /// this is a non-thread blocking function
        /// @param pinNumber the Pin to have the state set
        /// @param pinState the last state know of the PIN
        /// @param lastMillis the last millis registered
        /// @param currentMillis the current millis at the time of the calling this function
        /// @param frequencyDesired the frequency desired for the blink to happen in millis seconds
        static void blinkOnFrequency(char pinNumber, char & pinState, unsigned long & lastMillis,
                                            unsigned long currentMillis,
                                            short frequencyDesired);
};

#endif // LIGHTS_H
