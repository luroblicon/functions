#pragma once
//7-bit Address + W/R direction bit = 0x48/d72/b
//
#include "ADS7830.h"



ADS7830 Sensors(false,false);
int readSensor(String sensorChan);
int data;
int commandByte_;
int devAddress_;
bool printFlag;

void setup(){
  Particle.function("SensorData",readSensor);
  Particle.variable("CommandByte",commandByte_);
  Particle.variable("DevideAdd", devAddress_);
  Sensors.begin();
  Sensors.setCommand(3);
  Serial.begin(9600);
  Serial.print(0);
}

void loop(){
  devAddress_ = Sensors.deviceAddress();
  commandByte_ = Sensors.currentMode();

  if(printFlag){
    Serial.println(data);
    printFlag = 0;
  }
}

int readSensor(String sensorChan){
  int _sensorChan = sensorChan.toInt();
  data = Sensors.readChan(_sensorChan);
  printFlag = 1;
  return 1;
}
/*
int changeAddress(String address){
  I2CAdd = address.toInt();// = address.toInt();
  return I2CAdd;  
}
*/
//particle compile --target 0.8.0-rc.11 p1 ADC_Read.ino --saveTo ADC_Read.bin
//particle flash 3f004c000251353532373238 ADC_Read.bin

/*
#define Addr 0x48

int data = 0;
void setup()
{
  // Set variable
  Particle.variable("i2cdevice", "ADS7830");
  Particle.variable("data", data);
  // Initialise I2C communication as Master
  Wire.begin();
  // Initialise serial communication, set baud rate = 9600
  Serial.begin(9600);
  delay(300);
}

void loop()
{
  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Differential inputs, channel-0, channel-1 selected
  Wire.write(140);
  // Stop I2C transmission
  Wire.endTransmission();

  // Request 1 byte of data
  Wire.requestFrom(Addr, 1);

  // Read 1 byte of data
  if (Wire.available() == 1)
  {
    data = Wire.read();
  }

  // Output data to dashboard
  Particle.publish("Digital value of analog input  : ", String(data));
  delay(1000);
}
*/