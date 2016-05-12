#include <Servo.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include "mCore.h"
MeRGBLed rgb;
MeUltrasonic ultr(PORT_3);
MeLineFollower line(PORT_2);
MeLEDMatrix ledMx;
MeIR ir;
MeBuzzer buzzer;
MeTemperature ts;
Me7SegmentDisplay seg;

MeDCMotor MotorL(M1);
MeDCMotor MotorR(M2);
MePort generalDevice;
Servo servo;

int moveSpeed = 200;
int minSpeed = 48;
int factor = 23;

#define NTD1 294
#define NTD2 330
#define NTD3 350
#define NTD4 393
#define NTD5 441
#define NTD6 495
#define NTD7 556
#define NTDL1 147
#define NTDL2 165
#define NTDL3 175
#define NTDL4 196
#define NTDL5 221
#define NTDL6 248
#define NTDL7 278
#define NTDH1 589
#define NTDH2 661
#define NTDH3 700
#define NTDH4 786
#define NTDH5 882
#define NTDH6 990
#define NTDH7 112


#define RUN_F 0x01
#define RUN_B 0x01<<1
#define RUN_L 0x01<<2
#define RUN_R 0x01<<3
#define STOP 0

int analogs[8]={A0,A1,A2,A3,A4,A5,A6,A7};

boolean isAvailable = false;
int len = 52;
char buffer[52];
char bufferBt[52];
byte index = 0;
byte dataLen;
byte modulesLen=0;
boolean isStart = false;
char serialRead;
String mVersion = "1.2.103";
float angleServo = 90.0;
unsigned char prevc=0;
boolean buttonPressed = false;
double lastTime = 0.0;
double currentTime = 0.0;
int LineFollowFlag=0;

#define VERSION 0
#define ULTRASONIC_SENSOR 1
#define TEMPERATURE_SENSOR 2
#define LIGHT_SENSOR 3
#define POTENTIONMETER 4
#define JOYSTICK 5
#define GYRO 6
#define SOUND_SENSOR 7
#define RGBLED 8
#define SEVSEG 9
#define MOTOR 10
#define SERVO 11
#define ENCODER 12
#define IR 13
#define IRREMOTE 14
#define PIRMOTION 15
#define INFRARED 16
#define LINEFOLLOWER 17
#define IRREMOTECODE 18
#define SHUTTER 20
#define LIMITSWITCH 21
#define BUTTON 22
#define DIGITAL 30
#define ANALOG 31
#define PWM 32
#define SERVO_PIN 33
#define TONE 34
#define BUTTON_INNER 35
#define LEDMATRIX 41
#define TIMER 50

#define GET 1
#define RUN 2
#define RESET 4
#define START 5


void setup()
{
  Serial.begin(115200);
  Serial.println("Game On JDriven!");
  Stop();
  disco();
  delay(1000);
}

void  disco()
{
  rgb.setNumber(16);
  rgb.clear();
  rgb.setColor(10, 0, 0);
  buzzer.tone(NTD1, 300); 
  delay(30);
  rgb.setColor(0, 10, 0);
  buzzer.tone(NTD2, 300);
  delay(30);
  rgb.setColor(0, 0, 10);
  buzzer.tone(NTD3, 300);
  delay(30);
  rgb.clear();

  buzzer.noTone();
}
       
void loop()
{

  // motor control
  motorDemo();

  // distance sensor
  distanceDemo();

  // line follow sensor
  lineFollowDemo();
  
}


void motorDemo() 
{
  Serial.print("Move Speed: ");
  Serial.println(moveSpeed);
  
  Serial.println("Forward!");
  Forward();
  delay(1000);
  
  Serial.println("Backward!");
  Backward();
  delay(1000);
  
  Serial.println("TurnLeft!");
  TurnLeft();
  delay(1000);
  
  Serial.println("TurnRight!");
  TurnRight();
  delay(1000);

  Serial.println("ChangeSpeed to 100 and Forward");
  ChangeSpeed(100);
  Forward();
  delay(1000);

  Serial.println("ChangeSpeed to 250 and Forward");
  ChangeSpeed(250);
  Forward();
  delay(1000);
}

void Forward()
{
  MotorL.run(-moveSpeed);
  MotorR.run(moveSpeed);
}
void Backward()
{
  MotorL.run(moveSpeed); 
  MotorR.run(-moveSpeed);
}
void TurnLeft()
{
  MotorL.run(-moveSpeed/10);
  MotorR.run(moveSpeed);
}
void TurnRight()
{
  MotorL.run(-moveSpeed);
  MotorR.run(moveSpeed/10);
}
void Stop()
{
  rgb.clear();
  MotorL.run(0);
  MotorR.run(0);
}

void ChangeSpeed(int spd)
{
  buzzer.tone(NTD5, 300); 
  moveSpeed = spd;
}


void distanceDemo()
{
  uint8_t d = ultr.distanceCm(50);
  Serial.print("Distance: ");
  Serial.println(d);
  delay(500);
}

void lineFollowDemo()
{
  uint8_t val = line.readSensors();

  bool leftIn = false;
  bool rightIn = false;
  
  switch (val)
  {
    case S1_IN_S2_IN:
      leftIn = true;
      rightIn = true;
      break;

    case S1_IN_S2_OUT:
      leftIn  = true;
      rightIn = false;
      break;

    case S1_OUT_S2_IN:
      leftIn = false;
      rightIn = true;
      break;

    case S1_OUT_S2_OUT:
      leftIn = false;
      rightIn = false;
      break;
  }
  Serial.print("LeftIn: ");
  Serial.println(leftIn);
  Serial.print("RightIn: ");
  Serial.println(rightIn);
  
  delay(500);
}


