#include <Arduino.h>
#include <Lights.h>

// Pin Consts
#define LEFT_HEAD_LIGHT 1
#define RIGHT_HEAD_LIGHT 2
#define LEFT_TAIL_LIGHT 3
#define RIGHT_TAIL_LIGHT 4
#define RIGHT_TURN_SIGNAL 5
#define LEFT_TURN_SIGNAL 6

unsigned long currentMillis;
Lights * pLightsHandler;
short blinkFrequency = 500;

// put function declarations here:
//int myFunction(int, int);

void setup()
{
    currentMillis = millis();
    pLightsHandler = new Lights(LEFT_HEAD_LIGHT, RIGHT_HEAD_LIGHT, RIGHT_TAIL_LIGHT,
            LEFT_TAIL_LIGHT, RIGHT_TURN_SIGNAL, LEFT_TURN_SIGNAL,
            -1, -1, blinkFrequency);

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
