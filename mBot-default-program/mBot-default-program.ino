#include <Servo.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include "mCore.h"

MeRGBLed rgb;
MeUltrasonic ultr(PORT_3);
MeLineFollower line(PORT_2);
MeBuzzer buzzer;
MeDCMotor MotorL(M1);
MeDCMotor MotorR(M2);
MePort generalDevice;

int defaultSpeed = 200;
int minSpeed = 48;
int maxSpeed = 250;

int moveSpeed = defaultSpeed;

int motorSpeedUnit = 25;

void setup()
{
  Serial.begin(115200);
  Serial.println("Game On Team Gerard!");
  delay(1000);
}

void loop()
{
    // are we there yet?
  bool handled = hasSunImploded();

  // - wall too close
  if (!handled) {
      handled = handleWallClose();
  }
  //  - change in feet sensors
  handled = handleFeetSensors();

  if (!handled) {
    stillGoForward();
  }

}

boolean hasSunImploded() {
    // read light sensor
    return false; //(lightSensor detected dark)
}

boolean handleWallClose() {
  uint8_t d = ultr.distanceCm(50);
  if (d < 30) {
    go(10, 2, 100);
    halt();
    return true;
  }
  return false;
}

boolean stillGoForward() {
    go(10, 10, 100);
    halt();
    return true;
}

void go(int motorLeftSpeed, int motorRightSpeed, int runMotorFor) {
  rgb.clear();
  MotorL.run(motorSpeedUnit * motorLeftSpeed);
  MotorR.run(motorSpeedUnit * motorRightSpeed);
  delay(runMotorFor);
}

void halt()
{
  rgb.clear();
  MotorL.run(0);
  MotorR.run(0);
}
