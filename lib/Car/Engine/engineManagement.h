//
// Created by rvezy on 11/8/2025.
//

#ifndef RCDODGECHARGEREMULATION_ENGINAMANAGEMENT_H
#define RCDODGECHARGEREMULATION_ENGINAMANAGEMENT_H
#include <Arduino.h>

enum IgnitionStartBehavior : short {
    Ramdonly = 0,
    Successfully = 1,
    Failing = 2
};

class EngineManagement {
private:
    int8_t rpm;
public:
    EngineManagement();
    bool isRunning;
    byte ignitionStage;
    byte fuelLevelPercent;
    void startEngine(IgnitionStartBehavior ignitionStartBehavior);
    void stopEngine();
    void acceleratorPedal(short throttlePercent);
    void breakPedal(short brakePercent);
    void setIgnitionLevelOne();
    void setIgnitionLevelTwo();
};

#endif //RCDODGECHARGEREMULATION_ENGINAMANAGEMENT_H
