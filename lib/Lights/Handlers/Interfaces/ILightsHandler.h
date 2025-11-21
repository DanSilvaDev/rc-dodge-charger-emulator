#ifndef ILIGHTSHANDLER_H
#define ILIGHTSHANDLER_H

   class ILightsHandler
    {
        public:
            virtual ~ILightsHandler() = default;
            virtual void setHeadlightsOff() = 0;
            virtual void setParkingLightsOn() = 0;
            virtual void setParkingLightsOff() = 0;
            virtual void setHeadlightsLowBeam() = 0;
            virtual void setHeadlightHighBeam() = 0;
            virtual void setBreakLightLowBeam() = 0;
            virtual void setBreakLightHighBeam() = 0;
            virtual void setBreakLightsOff() = 0;
            virtual void setBlinkRightTurnIndicator(unsigned long currentMillis) = 0;
            virtual void setBlinkLeftTurnIndicator(unsigned long currentMillis) = 0;
            virtual void setBlinkTurnIndicatorOff() = 0;
            virtual void setBlinkEmergencyLights(unsigned long currentMillis) = 0;
            virtual void setReverseLightOn() = 0;
            virtual void setReverseLightOff() = 0;
            virtual void setFogLightsOn() = 0;
            virtual void setFogLightsOff() = 0;
    };

#endif