#ifndef CHASSIS_H
#define CHASSIS_H

    class Chassis{
        private:
            int ELS, FLS, BLS;
            int ERS, FRS, BRS;
        public:

            Chassis();
            Chassis(int, int, int, int, int, int);
            void fowardLeft(int);
            void fowardRight(int);
            void backRight(int);
            void backLeft(int);
            void stopLeft();
            void stopRight();
            void stopCar();
            void fowardCar(int);
            void backCar(int);
            void changeSpeedL(int);
            void changeSpeedR(int);

    };

#endif 