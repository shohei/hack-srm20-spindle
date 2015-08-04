/*
   SRM-20 metal milling control
 Shohei Aoki
 23, Jul 2015
 */

#include <SPI.h>
#include <SRM20SPIRemote.h>

SRM20SPIRemote srm20;
boolean isEngaged;

int sPin;

void setup()
{
  Serial.begin(9600);
  srm20.begin(9,6);
  sPin = 8; // 8 is free; 13 is used in SPI
  pinMode(sPin,OUTPUT);
  isEngaged = false;
}

void loop()
{
  unsigned long system,remote;

  if(srm20.isReady()){
    srm20.getStatus(system,remote);
    if(system & 0x00010000) {
      if(!isEngaged){
        isEngaged = true;
        Serial.println("!!! #-WARNING-#: SPINDLE ENGAGED !!!\n");
        turnOnSpindle(sPin); 
      }   
    } 
    else {
      if(isEngaged){
        isEngaged = false;
        Serial.println("DISENGAGED\n");      
        turnOffSpindle(sPin); 
      }
    }
  }
  delay(300);
}

void turnOnSpindle(int _sPin){
  digitalWrite(_sPin,HIGH); 
}

void turnOffSpindle(int _sPin){
  digitalWrite(_sPin,LOW);   
}

