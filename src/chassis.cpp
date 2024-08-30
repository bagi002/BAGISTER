#include <chassis.h>
#include <Arduino.h>

Chassis::Chassis(){
    ELS = 9;
    FLS = 4;
    BLS = 5;
    ERS = 10;
    FRS = 6;
    BRS = 7;

    pinMode(ELS, OUTPUT);
    pinMode(ERS, OUTPUT);

    pinMode(FLS, OUTPUT);
    pinMode(BLS, OUTPUT);
    pinMode(FRS, OUTPUT);
    pinMode(BRS, OUTPUT);
}

void Chassis::fowardLeft(int speed = 255){

    digitalWrite(FLS, HIGH);
    digitalWrite(BLS, LOW);

    analogWrite(ELS, 255);
    delay(20);
    analogWrite(ELS, speed);
}

void Chassis::backLeft(int speed = 255){

    digitalWrite(FLS, LOW);
    digitalWrite(BLS, HIGH);

    analogWrite(ELS, 255);
    delay(20);
    analogWrite(ELS, speed);
}

void Chassis::fowardRight(int speed = 255){

    digitalWrite(FRS, HIGH);
    digitalWrite(BRS, LOW);

    analogWrite(ERS, 255);
    delay(20);
    analogWrite(ERS, speed);
}

void Chassis::backRight(int speed = 255){

    digitalWrite(FRS, LOW);
    digitalWrite(BRS, HIGH);

    analogWrite(ERS, 255);
    delay(20);
    analogWrite(ERS, speed);
}

void Chassis::stopLeft(){
    digitalWrite(FLS, LOW);
    digitalWrite(BLS, LOW);
    analogWrite(ELS, 0);
}

void Chassis::stopRight(){
    digitalWrite(FRS, LOW);
    digitalWrite(BRS, LOW);
    analogWrite(ERS, 0);
}

void Chassis::stopCar(){
    stopLeft();
    stopRight();
}

void Chassis::fowardCar(int speed){
    fowardLeft(100);
    delay(20);
    fowardRight(240);
    fowardLeft(200);
    delay(10);
    fowardRight(speed);
    fowardLeft(speed);
}

void Chassis::backCar(int speed){
    backLeft(100);
    delay(20);
    backRight(240);
    backLeft(200);
    delay(10);
    backRight(speed);
    backLeft(speed);
}

void  Chassis::changeSpeedL(int speed){
    analogWrite(ELS, speed);
}

void Chassis::changeSpeedR(int speed){
    analogWrite(ERS, speed);
}