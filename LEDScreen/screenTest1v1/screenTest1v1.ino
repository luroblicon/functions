#include <Wire.h>

#define ROWS  41
#define COLS  7
#define HT1635B_I2C_ADDRESS       0x68
#define HT1632B_CMD_RAM_W         0b10000000
#define HT1635B_CMD_BLINK         0b10000100
#define HT1635B_CMD_COM           0b10001000
#define HT1635B_CMD_OSC           0b10100000
#define HT1635B_CMD_SYSTEM_MODE   0b10000010
#define HT1635B_CMD_BRIGHTNESS    0b11000000

#define HT1635B_ROW_SIZE    43

uint8_t row_[HT1635B_ROW_SIZE];

void setup() {
  // begin
  Wire.begin();
  
  // Set N-Mos
  Wire.beginTransmission(HT1635B_I2C_ADDRESS);
  Wire.write(HT1635B_CMD_COM);
  Wire.write(0);
  Wire.endTransmission();
  
  //Blink
  Wire.beginTransmission(HT1635B_I2C_ADDRESS);
  Wire.write(HT1635B_CMD_BLINK);
  Wire.write(2);
  Wire.endTransmission();
  
  // RC master mode 0, use on chip OSC, OSC pin Hi-Z, Sync pin high
  Wire.beginTransmission(HT1635B_I2C_ADDRESS);
  Wire.write(HT1635B_CMD_OSC);
  Wire.write(4);
  Wire.endTransmission();
  
  // System enabled, LED on
  Wire.beginTransmission(HT1635B_I2C_ADDRESS);
  Wire.write(HT1635B_CMD_SYSTEM_MODE);
  Wire.write(3);
  Wire.endTransmission();
  
  //System Brghtness at 7;
  Wire.beginTransmission(HT1635B_I2C_ADDRESS);
  Wire.write(HT1635B_CMD_BRIGHTNESS);
  Wire.write(7);
  Wire.endTransmission();
  
  //Clear memory
  memset(row_, 0, 43);
  //Render Screen in two steps, memory of IC is less than 64
  Wire.beginTransmission(HT1635B_I2C_ADDRESS);
  Wire.write(HT1632B_CMD_RAM_W);
  Wire.write(0x00); //address for row 0
  for (size_t j = 0; j < 30; j++) { // draw row 0 -> row 29
    Wire.write(row_[j]);
  }
  Wire.endTransmission();

  Wire.beginTransmission(HT1635B_I2C_ADDRESS);
  Wire.write(HT1632B_CMD_RAM_W);
  Wire.write(0x3C); //address for row 30
  for (size_t j = 30; j < 44; j++) { // draw row 30 -> row 43
    Wire.write(row_[j]);
  }
  Wire.endTransmission();

  
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      setPixel(i, j);
    }
  }
  //Render
  Wire.beginTransmission(HT1635B_I2C_ADDRESS);
  Wire.write(HT1632B_CMD_RAM_W);
  Wire.write(0x00); //address for row 0
  for (size_t j = 0; j < 30; j++) { // draw row 0 -> row 29
    Wire.write(row_[j]);
  }
  Wire.endTransmission();

  Wire.beginTransmission(HT1635B_I2C_ADDRESS);
  Wire.write(HT1632B_CMD_RAM_W);
  Wire.write(0x3C); //address for row 30
  for (size_t j = 30; j < 44; j++) { // draw row 30 -> row 43
    Wire.write(row_[j]);
  }
  Wire.endTransmission();
  

 delay(1000);

}

uint8_t getYuint8_tLocation_(uint8_t y) {
  uint8_t firstBit = 0b10000000;
  uint8_t yBitLocationInuint8_t = y % 8;
  return (firstBit >> yBitLocationInuint8_t);
}

void setRowMemory(uint8_t index, uint8_t data) {
  row_[index] |= data;
}

void clearPixel(int x, int y) {
  clearRowMemory(x, getYuint8_tLocation_(y));
}

void clearRowMemory(uint8_t index, uint8_t data) {
  row_[index] &= ~(data);
}

void setPixel(int x, int y) {
  setRowMemory(x, getYuint8_tLocation_(y));
}
