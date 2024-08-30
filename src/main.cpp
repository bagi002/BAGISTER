#include <Arduino.h>
#include <chassis.h>
#include <carDrive.h>


Chassis *motori = new Chassis();
CarDrive *car = new CarDrive(motori);

void setup() {

  delay(8000);
  
  motori->fowardLeft(100);
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
  motori->stopRight();

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

void loop() {
  
}
