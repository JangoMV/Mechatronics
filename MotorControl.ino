#include <Servo.h>

Servo LeftMotor;
Servo RightMotor;

const int LeftMotorSpeedPin = 5;
const int RightMotorSpeedPin = 6;
const int LeftMotorDirPin = 4;
const int RightMotorDirPin = 7;

volatile signed int Count1 = 0;
volatile signed int Count2 = 0;

unsigned long previousMillis = 0;

int EncoderInterval = 1000;
int EncoderSlots = 100;
int GearRatio = 30;
long LeftMotorSpeed = 0;
long RightMotorSpeed = 0;
float LeftWheelRPM = 0.0;
float RightWheelRPM = 0.0;
float LeftWheelRevs = 0.0;
float RightWheelRevs = 0.0;

void setup() 
{
  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(4),EncoderRead1,RISING);
  attachInterrupt(digitalPinToInterrupt(7),EncoderRead2,RISING);

  LeftMotor.attach(LeftMotorSpeedPin,1000,2000);
  RightMotor.attach(RightMotorSpeedPin,1000,2000);

  driveForward (90, 90);

}

void loop() {
  unsigned long currentMillis = millis();

  if((currentMillis - previousMillis) > EncoderInterval)
  {
    LeftMotorSpeed = Count1;
    RightMotorSpeed = Count2;
    LeftWheelRPM = (LeftMotorSpeed * 60.0)/(EncoderSlots * GearRatio);
    RightWheelRPM = (RightMotorSpeed * 60.0)/(EncoderSlots * GearRatio);
    LeftWheelRevs = (LeftWheelRevs + LeftWheelRPM/60.0);
    RightWheelRevs = (RightWheelRevs + RightWheelRPM/60.0);

    Count1 = 0;
    Count2 = 0;

    previousMillis = currentMillis;
  }

}

void driveForward (char a,char b)
  {
    analogWrite (LeftMotorSpeedPin,a);
    digitalWrite (LeftMotorDirPin, HIGH);
    analogWrite (RightMotorSpeedPin,b);
    digitalWrite (RightMotorDirPin,HIGH);
  }
void driveReverse (char a,char b)          //Move backward
  {
    analogWrite (LeftMotorSpeedPin,a);
    digitalWrite(LeftMotorDirPin,LOW);   
    analogWrite (RightMotorSpeedPin,b);    
    digitalWrite(RightMotorDirPin,LOW);
  }
void turnLeft (char a,char b)             //Turn Left
  {
    analogWrite (LeftMotorSpeedPin,a);
    digitalWrite(LeftMotorDirPin,LOW);    
    analogWrite (RightMotorSpeedPin,b);    
    digitalWrite(RightMotorDirPin,HIGH);
  }
void turnRight (char a,char b)             //Turn Right
  {
    analogWrite (LeftMotorSpeedPin,a);
    digitalWrite(LeftMotorDirPin,HIGH);    
    analogWrite (RightMotorSpeedPin,b);    
    digitalWrite(RightMotorDirPin,LOW);
  }
void EncoderRead1()
  {                                                                   //Function to read the encoder 1 state once the interrupt occurs
    if (digitalRead(18)==HIGH && digitalRead(19)==LOW)                //Based on the forward square waves generated by the encoder. See diagram
    {           
      Count1++;
    }
    else{                                                             //If wheel is not going forward, reduce count
      Count1--;
    }   
  }
void EncoderRead2()
  {                                                                   //Function to read the encoder 2 state once the interrupt occurs
    if (digitalRead(21)==HIGH && digitalRead(20)==LOW)                //Based on the forward square waves generated by the encoder. See diagram
    {
      Count2++;
    }
    else{                                                             //If wheel is not going forward, reduce count
      Count2--;
    }  
  }
