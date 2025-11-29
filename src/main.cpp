#include <Arduino.h>
#include <Lights.h>

// Pin Consts
#define LEFT_HEAD_LIGHT 1
#define RIGHT_HEAD_LIGHT 2
#define LEFT_TAIL_LIGHT 3
#define RIGHT_TAIL_LIGHT 4
#define RIGHT_TURN_SIGNAL 5
#define LEFT_TURN_SIGNAL 6
#define TURN_SIGNAL_FREQ_MS 500

unsigned long currentMillis;
Lights* pLightsHandler;
CarLightModel carLightModel;
// Lights lightsHandler;

// put function declarations here:
//int myFunction(int, int);

void setup()
{
    currentMillis = millis();


    carLightModel = {
        .leftHeadLightPin = LEFT_HEAD_LIGHT,
        .rightHeadLightPin = RIGHT_HEAD_LIGHT,
        .leftRearBreakLightPin = LEFT_TAIL_LIGHT,
        .rightRearBreakLightPin = RIGHT_TAIL_LIGHT,
        .reverseLightPin = 0,
        .fogLightPin = 0,
        .rightTurnLightPin = RIGHT_TURN_SIGNAL,
        .leftTurnLightPin = LEFT_TURN_SIGNAL
    };

    pLightsHandler = new Lights(carLightModel, TURN_SIGNAL_FREQ_MS);

    pLightsHandler->setHeadlightHighBeam();
}

void loop()
{
    // put your main code here, to run repeatedly:
    currentMillis = millis();
    pLightsHandler->setBlinkRightTurnIndicator(currentMillis);
}

// put function definitions here:
// int myFunction(int x, int y) {
//   return x + y;
// }
