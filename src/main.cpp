#include <Arduino.h>
#include <chassis.h>
#include <carDrive.h>

void test1(){
  /*motori->fowardLeft(100);
  delay(20);
  motori->fowardRight(200);
  motori->fowardLeft(200);
  delay(2000);
  motori->fowardLeft(35);
  motori->fowardRight(255);
  delay(3200);
  motori->fowardLeft(200);
  motori->fowardRight(200);
  delay(800);
  motori->stopLeft();
  motori->stopRight();*/
}

void test2(){
    /*car->fowardCar(250);
  delay(1000);
  car->fowardCar(120);
  delay(1500);
  car->stopCar();

  delay(1000);
  car->backCar(255);
  delay(2000);
  car->rotateInPlace(false);
  delay(1200);
  car->fowardCar(250);
  delay(1000);
  car->stopCar();*/
}

void test3(){
    /*car->fowardCar(250);
  delay(1000);
  car->fowardCar(120);
  delay(1500);
  car->stopCar();

  delay(1000);
  car->backCar(255);
  delay(2000);
  car->rotateInPlace(false);
  delay(1200);
  car->fowardCar(250);
  delay(1000);
  car->stopCar();*/
}

void test4(){
/*car->fowardCar(250);
  delay(1000);
  car->fowardCar(100);
  delay(2500);
  car->stopCar();
  car->siren(500);
  delay(1000);
  car->backCar(250);
  delay(1000);
  car->stopCar();
  delay(500);
  car->rollCar(250, false);
  delay(4000);
  car->stopCar();*/
}

void test5(){
    /*car->reeadMessage(0xFF000000);
  car->controllCar();
  delay(1800);
  car->reeadMessage(0x00000000);
  car->controllCar();
  delay(1000);
  car->reeadMessage(0x0000FF00);
  car->controllCar();
  delay(500);
  car->reeadMessage(0xFF000000);
  car->controllCar();
  delay(500);
  car->reeadMessage(0xFF00FF00);
  car->controllCar();
  delay(1500);
  car->reeadMessage(0xFF000000);
  car->controllCar();
  delay(800);
  car->reeadMessage(0x00000000);
  car->controllCar();*/
}

Chassis *motori = new Chassis();
CarDrive *car = new CarDrive(motori);

void setup() {

  Serial.begin(9600);

    while (Serial.available() > 0) {
    Serial.read();  
  }

  while(true){
    if(Serial.available() > 0){
      if(Serial.read() == 0x12){
        delay(5);
        if(Serial.read() == 0x34){
          delay(5);
          if(Serial.read() == 0x56){
            if(Serial.read() == 0x78){
              break;
            }
          }
        }
      }
    }
  }

  while (Serial.available() > 0) {
    Serial.read();  
  }  

  Serial.write(0xAB);
}

void loop() {


if (Serial.available() >= 6) {
    byte mask1 = Serial.read();
    byte byte1 = Serial.read();
    byte byte2 = Serial.read();
    byte byte3 = Serial.read();
    byte byte4 = Serial.read();
    byte mask2 = Serial.read();

    if(mask1 == 0xAB && mask2 == 0xCD){
      unsigned long x = ((unsigned long)byte1 << 24) | ((unsigned long)byte2 << 16) | ((unsigned long)byte3 << 8) | (unsigned long)byte4;

      car->reeadMessage(x);
      car->controllCar();
    }else{
      while (Serial.available() > 0) {
      Serial.read();  
  }  
    }
  }
}
