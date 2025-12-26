#ifndef HBRIDGEPINS_H
#define HBRIDGEPINS_H

/// Pins to match L298 H bridge 
struct hBridgePins
{
  unsigned short enableA;
  unsigned short enableB;
  unsigned short in1;
  unsigned short in2;
  unsigned short in3;
  unsigned short in4;
};

#endif //HBRIDGEPINS_H