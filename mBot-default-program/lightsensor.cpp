MePort lightSensor(8);

double lightStrength;

void setup()
{
  lightSensorDemo();
}


void lightSensorDemo() {
   lightStrength = lightSensor.aRead2();
   Serial.print("LightStrength: ");
   Serial.println(lightStrength);
}
