#include "ADS7830.h"
//A1 and A0 are the bits from the address 
//that allow for the hardware setup of the device address
ADS7830::ADS7830(bool A1_, bool A0_){
  _devAddress = 0b1001000;
  if(A1_ && A0_){
    _devAddress |= (1 << 2);//A1 set to 1
    _devAddress |= (1 << 1);//A0 set to 1  
  }
  else if(A1_){
      _devAddress |= (1 << 2);
  }
  else if (A0_){
      _devAddress |= (1 << 1);
  }
}
void ADS7830::begin(){
  _commandByte |= (1 << 7);  
  Wire.begin();
}

int ADS7830::deviceAddress(){
      return _devAddress;
}

int ADS7830::currentMode(){
  return _commandByte;    
}

//PowerDown = 0,//Power Down between A/D Conversions
//ADon = 1, //Internal Reference OFF and A/D Converter ON
//IRon = 2, //Internal Reference ON and A/D Converter OFF
//IRADon = 3, //Internal Reference ON and A/D Converter ON
 
void ADS7830::setCommand(int commandMode){
    _commandMode = commandMode; 
    switch(_commandMode)
    {
        case 0:
          _commandByte = (_commandByte & (~(1 << 3)) & (~(1 << 2)));
          break;
        
        case 1:
          _commandByte = (_commandByte & (~(1 <<3)) | (1 << 2));
          break;

        case 2:
          _commandByte = (_commandByte | (1 << 3) & (~(1 << 2)));
          break;

        case 3:
          _commandByte = (_commandByte | (1<<3) | (1 << 2));
          break;
    }
} 

int ADS7830::readChan(int chanNum){
  _chanNum = chanNum;
  _commandByte = (_commandByte & (~(1 << 6)) & (~(1 << 5)) & (~(1 << 4))); 
  
  switch (_chanNum)
  {
    case 0:
      _commandByte = (_commandByte & (~(1 << 6)) & (~(1 << 5)) & (~(1 << 4)));
      break;
      
    case 1:
      _commandByte = (_commandByte | (1 << 6) & (~(1 << 5)) & (~(1 << 4)));
      break;
      
    case 2:
      _commandByte = (_commandByte & (~(1 << 6)) & (~(1 << 5)) | (1 << 4));
      break;
      
    case 3:
      _commandByte = (_commandByte | (1 << 6) & (~(1 << 5)) | (1 << 4));
      break;
      
    case 4:
      _commandByte = (_commandByte & (~(1 << 6)) | (1 << 5) & (~(1 << 4)));
      break;

    case 5:
      _commandByte = (_commandByte | (1 << 6) | (1 << 5) & (~(1 << 4)));
      break;

    case 6:
      _commandByte = (_commandByte & (~(1 << 6)) | (1 << 5) | (1 << 4));
      break;

    case 7:
      _commandByte = (_commandByte | (1 << 6) | (1 << 5) | (1 << 4));
      break;
    }
  Wire.beginTransmission(_devAddress);
  Wire.write(_commandByte);
  // Stop I2C transmission
  Wire.endTransmission();
  Wire.requestFrom(_devAddress, 1);
  if (Wire.available() == 1)
    _readData = Wire.read();
  delay(100);
  return _readData;
}