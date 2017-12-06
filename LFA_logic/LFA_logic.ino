#include "Wire.h"
#include "sensorbar.h"

const byte LFAaddress = 0x3E;

SensorBar mySensorBar(LFAaddress);

#define idle_state 0
#define junction 1
#define follow 2
#define newpath 3


void setup() 
{
  Serial.begin(9600);
  Serial.println("Program started.");
  Serial.println();

  mySensorBar.clearBarStrobe();
  mySensorBar.clearInvertBits();
  uint8_t returnStatus = mySensorBar.begin();
  if (returnStatus)
  {
      Serial.println("LFA Comms OK"\n);
  }
  else
  {
      Serial.println("LFA Comms Alert"\n);
  }

}

void loop() 
{
  uint8_t nextState = state;
  switch (state) {
  case idle_state:
    //stopWheels();
    nextState = read_line;
    break;
  case read_line:
    if ((mySensorBar.getRaw() ==  0xFF) || (mySensorBar.getRaw() == 0xF8) || (mySensorBar.getRaw() == 0x1F)
    {
      nextState = junction;
    }
    else if (mySensorBar.getRaw() != 0x18)
    {
      stopWheels();
      nextState = errorCorrection;
    }
  case   

  }

}
