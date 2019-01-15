#pragma once
//7-bit Address + W/R direction bit = 0x48/d72/b
//
int I2CAdd = 0b1001000;

int data = 0;
int changeAddress(String address);

void setup(){
  Particle.variable("Data",data);
  Particle.variable("Address",I2CAdd);
  Particle.function("I2C",changeAddress);
  Wire.begin();
  Serial.begin(9600);
  delay(100);
}

void loop(){
  Wire.write(I2CAdd);//Write-Addressing byte
  //Wire.write(0x8C);//Command byte
  //Wire.write(0x91);//ADC converting mode
  //data = Wire.read();
  Wire.write(I2CAdd+1);

  Wire.requestFrom(I2CAdd,1);


 /*
  Wire.requestFrom(0x49, 1);
    // Request 1 byte of data
  // Read 1 byte of data
  if(Wire.available()== 1)
    data = Wire.read();
 */
}

int changeAddress(String address){
  I2CAdd = address.toInt();// = address.toInt();
  return I2CAdd;  
}

//particle compile --target 0.8.0-rc.11 p1 ADC_Read.ino --saveTo ADC_Read.bin
//particle flash 3f004c000251353532373238 ADC_Read.bin