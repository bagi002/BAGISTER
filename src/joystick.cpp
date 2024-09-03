#include <Arduino.h>
#include <BluetoothSerial.h>


const int xOsa = 34;
const int yOsa = 35;
const int indikator = 2;
int losihKonekcija = 0;

BluetoothSerial SerialBT;
bool conectedStatus = false;

void clearBafer(){
  while(SerialBT.available()){
    SerialBT.read();
  }
}

void setup() {
  SerialBT.begin("Dzojtik", true);
  //SerialBT.setPin("1234");
  SerialBT.connect("JDY-31-SPP");     // Use Name

  pinMode(indikator, OUTPUT);
  pinMode(xOsa, INPUT);
  pinMode(yOsa, INPUT);

  Serial.begin(115200);
}

void loop() {
  //New version code with two-way comunication


//Dio koda zasluzan da kada ne postoji komunikacija ponovo uspostavi istu takosto salje signal za pocetak komunkacije
//i ceka odgovor sve dok ne dobije potvrdu uspjesne dvosmjerne komuniakcije sa vozilom u slucaju nepotpunih pogresnih i
//i losih komunikacija cisti dolazni bafer da omuguci uspostavu ponovne komunikacije.
  while(!conectedStatus){
    SerialBT.write(0xAB);
    SerialBT.write(0x11);
    SerialBT.write(0x22);
    SerialBT.write(0x33);
    SerialBT.write(0x44);    
    SerialBT.write(0xCD);
    Serial.println("Povezivanje....");

    delay(250);

    if(SerialBT.available() >= 6){
      if(SerialBT.read() == 0xAB){
        if(SerialBT.read() == 0x04 && SerialBT.read() == 0x04 && SerialBT.read() == 0x04 && SerialBT.read() == 0x04){
          if(SerialBT.read() == 0xCD){
            conectedStatus = true;
            digitalWrite(indikator, HIGH);
            Serial.println("Konekcija uspjesno obavljena");
          }else{
            clearBafer();
          }
        } 
      }else{
        clearBafer();
      }
    }else{
      clearBafer();
    }
  }

//Dio koda odgovoran za komunikaciju sa vozilom kada je komunikacija uspostavljena te za prijam potvrde slanja poruke autu
//Takodje moze primiti zahtjev auta za ponovnom komunikacijom ali idetektovati neuspjeh u slanju poruke ili drusgu vrstu smetnji
//sto pomaze u detektciji losih konekcija

  while(conectedStatus){
    int x = analogRead(xOsa) - 2047;
    int y = analogRead(yOsa) - 2047;

    char bit1 = 0x00;
    char bit2 = 0x00;
    char bit3 = 0x00;
    char bit4 = 0x00;

    if(x > 800){
      bit1 = ((x*1.0 - 400)/(2050 - 400)) * 205 + 50;
    }else if(x < -800){
      bit2 = (((-x)*1.0 - 400)/(2050 - 400)) * 205 + 50; 
    }
    if(y > 800){
      bit4 = ((y*1.0 - 800)/(2050 - 800)) * 155 + 99;
    }else if(y < -800){
      bit3 = (((-y)*1.0 - 800)/(2050 - 800)) * 155 + 99; 
    }
    SerialBT.write(0xAB);
    SerialBT.write(bit1);
    SerialBT.write(bit2);
    SerialBT.write(bit3);
    SerialBT.write(bit4);    
    SerialBT.write(0xCD);

    delay(100);

    if(SerialBT.available() >= 6){
      if(SerialBT.read() == 0xAB){
        char a1 = SerialBT.read();
        char a2 = SerialBT.read();
        char a3 = SerialBT.read();
        char a4 = SerialBT.read();
        SerialBT.read();

        if(a1 == 0x01 && a2 == 0x23 && a3 == 0x45 && a4 == 0x67){
          losihKonekcija = 0;
          Serial.println("Komanda uspjesno primljena");
        }else if(a1 == 0x0F && a2 == 0x0F && a3 == 0x0F && a4 == 0x0F){
          losihKonekcija += 10;
          Serial.println("zahtjev za rekonektovanje primljen");
        }else{
          losihKonekcija++;
          clearBafer();
        }
      }else{
        clearBafer();
        losihKonekcija++;
      }
    }else{
      clearBafer();
      losihKonekcija++;
    }

    //Ako vise puta zaredom nemoze da se uspostavi pravilna komunikacija proglasava se prekid komunikacije i 
    //dzojstik inicira ponovno povezivanje i restartovanje komunikacija a u slucaju tezek narusavanja ponovlja se i fizicko povezivanje
    if(losihKonekcija > 6){
      conectedStatus = false;
      digitalWrite(indikator, LOW);
      if(SerialBT.isClosed()){
              SerialBT.disconnect();
      SerialBT.connect("JDY-31-SPP");
      }
    }

  }
}

