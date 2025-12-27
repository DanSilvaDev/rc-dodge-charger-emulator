#ifndef SOUNDS_H
#define SOUNDS_H
#include <string>

class sounds {
public:
    sounds();

    std::string playIdle();
    std::string playFuelPumpStart();
    std::string playEngineStartSuccess();
    std::string playEngineStartFailure();
    std::string playEngineStop();
    std::string playRevEngAtAccelerating();
    std::string playRevEngAtDecelerating();
    std::string playNeutralRevUp(int rpm);
    std::string playNeutralRevDown(int rpm);

};


#endif //SOUNDS_H