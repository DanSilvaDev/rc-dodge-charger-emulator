#include <Arduino.h>
#include <Lights/Handlers/SimpleLedLightHandler.h>
#include "lights_handlers"

unsigned long currentMillis;
CarLightsHandlers::SimpleLedLightHandler* handler;
short blinkFrequency = 500;

// put function declarations here:
//int myFunction(int, int);

void setup()
{
    currentMillis = millis();
    handler =
            new CarLightsHandlers::SimpleLedLightHandler(1, 2, 3,
                                                         4, 5, 6,
                                                         -1, -1, blinkFrequency);
    handler->setHeadlightHighBeam();
}

void loop()
{
    // put your main code here, to run repeatedly:
    currentMillis = millis();
    handler->setBlinkRightTurnIndicator(currentMillis);
}

// put function definitions here:
// int myFunction(int x, int y) {
//   return x + y;
// }
