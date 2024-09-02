#include <Arduino.h>
#include <chassis.h>
#include <carDrive.h>

Chassis *motori = new Chassis();
CarDrive *car = new CarDrive(motori);

bool conected = false;
int conectionLost = 0;

void setup() {

  Serial.begin(9600);

    while (Serial.available() > 0) {
    Serial.read();  
  }
}

void loop() {


if (Serial.available() >= 6) {
    unsigned long x;
    byte mask1 = Serial.read();
    byte byte1 = Serial.read();
    byte byte2 = Serial.read();
    byte byte3 = Serial.read();
    byte byte4 = Serial.read();
    byte mask2 = Serial.read();

    if(mask1 == 0xAB && mask2 == 0xCD){
      x = ((unsigned long)byte1 << 24) | ((unsigned long)byte2 << 16) | ((unsigned long)byte3 << 8) | (unsigned long)byte4;
    }else{
      while (Serial.available() > 0) {
        Serial.read();  
      }  
    }

    if(conected){
      if(x == 0x11223344){
        conected = false;
        car->reeadMessage(0x00000000);
      }else{
        car->reeadMessage(x);
        Serial.write(0xAB);
        Serial.write(0x01);
        Serial.write(0x23);
        Serial.write(0x45);
        Serial.write(0x67);
        Serial.write(0xCD);
        conectionLost = 0;
      }
    }else{
      if(x == 0x11223344){
        Serial.write(0xAB);
        Serial.write(0x04);
        Serial.write(0x04);
        Serial.write(0x04);
        Serial.write(0x04);
        Serial.write(0xCD);
        conectionLost = 0;
        conected = true;
      }else{
        conectionLost++;
      }
    }

  }else{
    conectionLost++;
    while (Serial.available() > 0) {
      Serial.read();  
    } 
  }

  if(conectionLost > 15){
    conected = false;
    car->reeadMessage(0x00000000);
    Serial.write(0xAB);
    Serial.write(0x0F);
    Serial.write(0x0F);
    Serial.write(0x0F);
    Serial.write(0x0F);
    Serial.write(0xCD);
    conectionLost -=2;
  }

  car->controllCar();

  delay(30);
}
