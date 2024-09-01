#include <Arduino.h>
#include <BluetoothSerial.h>

const int xOsa = 34;
const int yOsa = 35;
const int indikator = 2;

BluetoothSerial SerialBT;

void setup() {
  bool conectedStatus = false;
  SerialBT.begin("Dzojtik", true);
  //SerialBT.setPin("1234");
  SerialBT.connect("JDY-31-SPP");     // Use Name

  delay(250);
  SerialBT.write(0x12);
  SerialBT.write(0x34);
  SerialBT.write(0x56);
  SerialBT.write(0x78);

  pinMode(indikator, OUTPUT);

  delay(150);

  if(SerialBT.available()){
    if(SerialBT.read() == 0xAB){
      conectedStatus = true;
      digitalWrite(indikator, HIGH);
    }
  }

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

  if(x > 800){
    bit1 = ((x*1.0 - 800)/(2050 - 800)) * 155 + 99;
  }else if(x < -800){
    bit2 = (((-x)*1.0 - 800)/(2050 - 800)) * 155 + 99; 
  }else{
  
  }

    if(y > 800){
    bit4 = ((y*1.0 - 800)/(2050 - 800)) * 155 + 99;
  }else if(y < -800){
    bit3 = (((-y)*1.0 - 800)/(2050 - 800)) * 155 + 99; 
  }else{
  
  }
    SerialBT.write(0xAB);
    SerialBT.write(bit1);
    SerialBT.write(bit2);
    SerialBT.write(bit3);
    SerialBT.write(bit4);    
    SerialBT.write(0xCD);

  delay(100);
}

