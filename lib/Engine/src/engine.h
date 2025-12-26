#ifndef ENGINE_H
#define ENGINE_H


enum IgnitionStartBehavior : unsigned short {
    Randomly = 0,
    Successfully = 1,
    Failing = 2
};

enum GearPosition : unsigned short {
    Reverse = 0,
    G1 = 1,
    G2 = 2,
    G3 = 3,
    G4 = 4,
    G5 = 5,
    Drive = 6,
    Neutral = 7,
    Parking = 8,
};

class engine
{
    private:
        bool _isRunning;
        unsigned int _rpm;
    public:
        engine();
        bool isRunning();
        unsigned int getRpm();
        GearPosition getGearPosition();
        unsigned short getFuelLevelPercent();
        void startEngine(IgnitionStartBehavior ignitionStartBehavior);
        void shutOffEngine();
        void acceleratorPedal(unsigned short throttlePercent);
        void breakPedal(unsigned short brakePercent);
        void setGearPosition(GearPosition gearPosition);
};


#endif //ENGINE_H