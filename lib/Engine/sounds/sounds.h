#ifndef SOUNDS_H
#define SOUNDS_H
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


#endif //SOUNDS_H