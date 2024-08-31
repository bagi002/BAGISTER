#include <Arduino.h>
#include <BluetoothSerial.h>

const int xOsa = 34;
const int yOsa = 35;

BluetoothSerial SerialBT;

void setup() {
  SerialBT.begin("Dzojtik", true);
  //SerialBT.setPin("1234");
  SerialBT.connect("JDY-31-SPP");     // Use Name


  Serial.begin(115200);
  pinMode(xOsa, INPUT);
  pinMode(yOsa, INPUT);
}

void loop() {
  int x = analogRead(xOsa) - 2047;
  int y = analogRead(yOsa) - 2047;

  char bit1 = 0x00;
  char bit2 = 0x00;
  char bit3 = 0x00;
  char bit4 = 0x00;

  if(x > 1500){
    bit1 = 0xFF;
  }else if(x < -1500){
    bit2 = 0xFF; 
  }else{
  
  }

    if(y > 1500){
    bit4 = 0xFF;
  }else if(y < -1500){
    bit3 = 0xFF; 
  }else{
  
  }

    SerialBT.write(bit1);
    SerialBT.write(bit2);
    SerialBT.write(bit3);
    SerialBT.write(bit4);    

  delay(100);
}

