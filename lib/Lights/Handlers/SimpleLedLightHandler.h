#ifndef RCDODGECHARGEREMULATION_SIMPLELEDLIGHTHANDLER_H
#define RCDODGECHARGEREMULATION_SIMPLELEDLIGHTHANDLER_H

#include "Interfaces/ILightsHandler.h"

namespace CarLightsHandlers
{
    class SimpleLedLightHandler : public CarLightsHandlersInterfaces::ILightsHandler
    {
        public:
            inline SimpleLedLightHandler(
                char leftHeadLightPin,
                char rightHeadLightPin,
                char rightRearBreakLightPin,
                char leftRearBreakLightPin,
                char rightTurnLightPin,
                char leftTurnLightPin,
                char reverseLightPin = -1,
                char fogLightPin = -1,
                short blinkFrequencyMillis = 500
            );

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
            static inline char blinkOnFrequency(char pinNumber, char lastState, unsigned long lastMillis, unsigned long currentMillis,
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
} // CarLightsHandlers

#endif //RCDODGECHARGEREMULATION_SIMPLELEDLIGHTHANDLER_H
