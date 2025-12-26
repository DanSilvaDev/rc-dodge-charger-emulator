//
// Created by rvezy on 11/7/2025.
//

#ifndef RCDODGECHARGEREMULATION_SOUNDS_H
#define RCDODGECHARGEREMULATION_SOUNDS_H
#include <string>

class EngineSounds {
public:
    EngineSounds();

    std::string getIdle();
    std::string getFuelPumpStart();
    std::string getEngineStartSuccess();
    std::string getEngineStartFailure();
    std::string getEngineStop();
    std::string getRevEngAtAccelerating(int rpm);
    std::string getRevEngAtDecelerating(int rpm);
    std::string getNeutralRevUp(int rpm);
    std::string getNeutralRevDown(int rpm);

};


#endif //RCDODGECHARGEREMULATION_SOUNDS_H