#include <Arduino.h>
#include <Lights.h>

// Pin Consts
#define LEFT_HEAD_LIGHT 1
#define RIGHT_HEAD_LIGHT 2
#define LEFT_TAIL_LIGHT 3
#define RIGHT_TAIL_LIGHT 4
#define RIGHT_TURN_SIGNAL 25
#define LEFT_TURN_SIGNAL 26
#define TURN_SIGNAL_FREQ_MS 500

unsigned long currentMillis;
unsigned long lastMillis;
unsigned short testCommand;
CarLightModel carLightModel = {
    .leftHeadLightPin = 0,
    .rightHeadLightPin = 0,
    .leftRearBreakLightPin = 0,
    .rightRearBreakLightPin = 0,
    .reverseLightPin = 0,
    .fogLightPin = 0,
    .rightTurnLightPin = RIGHT_TURN_SIGNAL,
    .leftTurnLightPin = LEFT_TURN_SIGNAL
};
Lights lightsHandler = Lights(&carLightModel, TURN_SIGNAL_FREQ_MS);
// Lights lightsHandler;

// put function declarations here:
//int myFunction(int, int);

void setup()
{
    Serial.begin(9600);
    // while (!Serial);
    // Serial.print("Connected to Serial");
    lastMillis = currentMillis = millis();
    testCommand = 0;
    Serial.println("Test Access to Lights:");
    Serial.println(carLightModel.rightTurnLightPin, DEC);
    Serial.println(carLightModel.leftTurnLightPin, DEC);
    // currentMillis = millis();
    //
    // carLightModel = {
    //     .leftHeadLightPin = LEFT_HEAD_LIGHT,
    //     .rightHeadLightPin = RIGHT_HEAD_LIGHT,
    //     .leftRearBreakLightPin = LEFT_TAIL_LIGHT,
    //     .rightRearBreakLightPin = RIGHT_TAIL_LIGHT,
    //     .reverseLightPin = 0,
    //     .fogLightPin = 0,
    //     .rightTurnLightPin = RIGHT_TURN_SIGNAL,
    //     .leftTurnLightPin = LEFT_TURN_SIGNAL
    // };
    //
    // pLightsHandler = new Lights(&carLightModel, TURN_SIGNAL_FREQ_MS);
    lightsHandler.configurePins();
    Serial.println("Lights handler initialized");
    
    // pLightsHandler->setHeadlightHighBeam();
}

void loop()
{
    // put your main code here, to run repeatedly:
    currentMillis = millis();
    const unsigned long diff = currentMillis - lastMillis;

    // change the command every 5 seconds
    if (diff >= 5000)
    {
        lightsHandler.setBlinkTurnIndicatorOff();
        lastMillis = millis();
        testCommand++;
        if (testCommand > 2)
            testCommand = 0;
        Serial.print("Command changed to: ");
        Serial.println(testCommand);
    }
    
    switch (testCommand)
    {
        case 0:
            lightsHandler.setBlinkLeftTurnIndicator(currentMillis);
            break;
        case 1:
            lightsHandler.setBlinkRightTurnIndicator(currentMillis);
            break;
        default:
            lightsHandler.setBlinkEmergencyLights(currentMillis);
            break;
    }
}

// put function definitions here:
// int myFunction(int x, int y) {
//   return x + y;
// }
