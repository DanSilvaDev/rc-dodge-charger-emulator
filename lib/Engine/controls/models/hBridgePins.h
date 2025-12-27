#ifndef HBRIDGEPINS_H
#define HBRIDGEPINS_H

/// Pins to match L298 H bridge 
struct hBridgePins
{
  unsigned char enableA;
  unsigned char enableB;
  unsigned char in1;
  unsigned char in2;
  unsigned char in3;
  unsigned char in4;
  
  // PWM Properties
  unsigned int pwmFrequency;
  unsigned short resolution;
  unsigned char pwmChannel;
  unsigned short dutyCycle;
};

#endif //HBRIDGEPINS_H