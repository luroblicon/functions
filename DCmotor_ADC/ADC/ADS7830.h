//#ifndef ADS7830_h
//#define ADS7830_h
//#endif 
#include "Particle.h"

class ADS7830
{
public:
  ADS7830(bool A1_, bool A0_);//A1 and A0 are the bits from the address that allow for the hardware setup of the device address
  void begin();
  void setCommand(int commandMode);
  int readChan(int chanNum);
  int deviceAddress();
  int currentMode();


private:
  int _commandMode; // 0,1,2,3 See CommandMode
  int _commandByte;
  int _chanNum;
  int _readData;
  int _devAddress;
};