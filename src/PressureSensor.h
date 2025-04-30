#include "Arduino.h"
class PressureSensor 
{
  public:
    PressureSensor(int analogPin);
    ~PressureSensor();
    void updateKilogramReadin();
    float pressureSensorResistance = 0;
    
    float kilograms = 0.0;


  private: 
    float mapFloat(float x, float in_min, float in_max, float out_min, float out_max); 
    int analogData = 0;
    float voltageReadingon21MOResistor = 0.0;
    //Pressure sensor 322 is the lowest 337 590 016 is the highest 10kg to 0kg
    int aPin;

};

PressureSensor::PressureSensor(int analogPin) 
{
  aPin = analogPin;
}

PressureSensor::~PressureSensor() 
{
  // Destructor
}

void PressureSensor::updateKilogramReadin()
{
analogData = analogRead(aPin);
  if(analogData<=0)
  {
    analogData = 1;
  }
  voltageReadingon21MOResistor = analogData * (3.3 / 4095.0);
  pressureSensorResistance = ((3.3*330000)/voltageReadingon21MOResistor)-330000;
  if(pressureSensorResistance >= 75000)
  {
    pressureSensorResistance = 75000;
  }
  kilograms = mapFloat(pressureSensorResistance, 75000, 0, 0,10);
}



float PressureSensor::mapFloat(float x, float in_min, float in_max, float out_min, float out_max) 
{
  return (float)(x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
