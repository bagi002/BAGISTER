#include <chassis.h>

#ifndef CARDRIVE_H
#define CARDRIVE_H

enum MotorStatus{
    STOPCAR, FOWARDCAR, BACKCAR
};

enum Direction{
    FOWARD, BACK, LEFT, RIGHT,
    FOWARDLEFT, FOWARDRIGHT,
    BACKLEFT, BACKRIGHT,
    STOP
};

struct ControlWord{
    Direction direction = STOP;
    int speed = 0;
    bool timeDependet = false;
    int angle = 0;

    ControlWord(Direction a, int b, bool c = false, int d = 0){
        direction = a;
        speed = b;
        timeDependet = c;
        angle = d;
    };
};

class CarDrive{
    private:
        Chassis* motori;
        unsigned long message;
        bool status;
        MotorStatus left;
        MotorStatus right;
        ControlWord* command;
        int sirenPin;
    public:
        CarDrive(Chassis*);
        bool reeadMessage(unsigned long);
        void controllCar();
        void fowardCar(int);
        void backCar(int);
        void rotateInPlace(bool);
        void rotateInPlace(bool, int);
        void rollCar(int, bool);
        void stopCar();
        void siren(int);
};

#endif