#ifdef __IN_ECLIPSE__
//This is a automatic generated file
//Please do not modify this file
//If you touch this file your change will be overwritten during the next build
//This file has been generated on 2016-11-09 18:57:43

#include "Arduino.h"
#include "Arduino.h"
#include "Wire.h"
void setup();
void loop();
void ds1307StartClock(byte deviceAddress);
unsigned int reverseByte(unsigned int sorted, int nbBits);
void tcn75aPrintTemperature();
void ds1307PrintTime();
void setRegisterIndex(byte pointer, byte deviceAddress);
void setRegisterData(byte pointer, byte deviceAddress, byte data);
int interpretData(byte data,byte cache);
int convertDatatoNum(byte data);
byte convertNumtoData(unsigned int num);
int charToDec(char c);
void serialEvent();
void setups();
void prints();
void setupThermo();
void setupHorloge();

#include "MEGAmaison.ino"


#endif
