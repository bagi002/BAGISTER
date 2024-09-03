#include <chassis.h>
#include <carDrive.h>
#include <Arduino.h>

CarDrive::CarDrive(Chassis* motori){
    sirenPin = 3;
    this->motori = motori;
    status = true;
    left = STOPCAR;
    right = STOPCAR;
    message = 0x00000000;
    pinMode(sirenPin, OUTPUT);
    command = new ControlWord(STOP, 0);
}

bool CarDrive::reeadMessage(unsigned long message){
    unsigned char fowardB, backB, leftB, rightB;
    fowardB = (char)((message >> 24) & 0xFF);
    backB = (char)((message >> 16) & 0xFF);
    leftB = (char)((message >> 8) & 0xFF);
    rightB = (char)(message & 0xFF);



    Direction x = STOP;
    int speed = 0;

    if(fowardB){
        speed = fowardB;
        if(rightB){
            x = FOWARDRIGHT;
        }else if(leftB){
            x = FOWARDLEFT;
        }else{
            x = FOWARD;
        }
    }
    if(backB){
        speed = backB;
        if(rightB){
            x = BACKRIGHT;
        }else if(leftB){
            x = BACKLEFT;
        }else{
            x = BACK;
        }       
    }
    if(rightB){
        x = RIGHT;
        speed = rightB;
    }
    if(leftB){
        speed = leftB;
        x = LEFT;
    }

    command->direction = x;
    command->speed = speed;
    
    return true;
}

void CarDrive::fowardCar(int x){
    if(left != FOWARDCAR && right != FOWARDCAR){
        motori->fowardCar(x);
        left = FOWARDCAR;
        right = FOWARDCAR;
        return;
    }
    if(left == FOWARDCAR && right == FOWARDCAR){
        motori->changeSpeedL(x);
        motori->changeSpeedR(x);
        return;
    }
    if(left == FOWARDCAR && right != FOWARDCAR){
        motori->fowardRight(x);
        motori->changeSpeedL(x);
        right = FOWARDCAR;
        return;
    }
    if(left != FOWARDCAR && right == FOWARDCAR){
        motori->fowardLeft(x);
        motori->changeSpeedR(x);
        left = FOWARDCAR;
        return;
    }
}

void CarDrive::backCar(int x){
    if(left != BACKCAR && right != BACKCAR){
        motori->backCar(x);
        left = BACKCAR;
        right = BACKCAR;
        return;
    }
    if(left == BACKCAR && right == BACKCAR){
        motori->changeSpeedL(x);
        motori->changeSpeedR(x);
        return;
    }
    if(left == BACKCAR && right != BACKCAR){
        motori->backRight(x);
        motori->changeSpeedL(x);
        right = BACKCAR;
        return;
    }
    if(left != BACKCAR && right == BACKCAR){
        motori->backLeft(x);
        motori->changeSpeedR(x);
        left = BACKCAR;
        return;
    }
}

void CarDrive::rotateInPlace(bool rotate){
    if(rotate){
        right = STOPCAR;
        left = FOWARDCAR;
        motori->stopCar();
        motori->fowardLeft(210);
    }else{
        left = STOPCAR;
        right = FOWARDCAR;
        motori->stopCar();
        motori->fowardRight(210);
    }
}

void CarDrive::stopCar(){
    motori->changeSpeedL(50);
    motori->changeSpeedR(50); 
    delay(50);
    motori->stopCar();
    left = STOPCAR;
    right = STOPCAR;
}

void CarDrive::siren(int time){
    digitalWrite(sirenPin, HIGH);
    delay(time);
    digitalWrite(sirenPin, LOW);
}

// Potrebno sto prije refaktorisati funkciju da se ucini vise upotrebljivom
void CarDrive::rollCar(int speed, bool rotate){
    if(rotate){
        if(left == FOWARDCAR && right == FOWARDCAR){
            motori->changeSpeedL(speed);
            motori->changeSpeedR(80);
        }else{
            motori->fowardCar(255);
            delay(5);
            motori->fowardLeft(speed);
            motori->fowardRight(80);
        }
    }else{
        if(left == FOWARDCAR && right == FOWARDCAR){
            motori->changeSpeedR(speed);
            motori->changeSpeedL(80);
        }else{

            motori->fowardCar(255);
            delay(5);
            motori->fowardLeft(80);
            motori->fowardRight(speed);
        }
    }
}

void CarDrive::controllCar(){
    int x = command->speed;
    switch (command->direction)
    {
    case STOP:
        stopCar();
        break;
    case FOWARD:
        fowardCar(x);
        break;
    case BACK:
        backCar(x);
        break;
    case LEFT:
        rotateInPlace(false);
        break;
    case RIGHT:
        rotateInPlace(true);
        break;
    case FOWARDLEFT:
        rollCar(x, false);
        break;
    case FOWARDRIGHT:
        rollCar(x, true);
        break;
    default:
        break;
    }
}