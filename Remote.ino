// Source Code untuk Transmitter (Remote Control)
// Courtesy of http://forum.arduino.cc/index.php?topic=138663.0

//Library SPI dan RF 24
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

//Pendefinisan Variabel
int msg[2]; //Array Pesan
RF24 radio(9,10); //Pin untuk Radio
const uint64_t pipe = 0xE8E8F0F0E1LL; //Pipe Radio
int SW1 = 7; //Switch 1
int SW2 = 4; //Switch 2
int sentSignal=0; //Sinyal kirim
 
void setup(void){
  Serial.begin(9600); //Setup Serial
  radio.begin(); //Setup Radio
  radio.openWritingPipe(pipe);
}
 
void loop(void){
//Inisialisasi variabel
  msg[0]=0;
  msg[1]=0;
  sentSignal=0;
  //Pembacaan Switch 1
  if (digitalRead(SW1) == HIGH) {
    msg[0] = 111;
    Serial.println("SW1");
    sentSignal=1;
  }
  //Pembacaan Switch 2
  if (digitalRead(SW2) == HIGH) {
    msg[1] = 111;
    Serial.println("SW2");
    sentSignal=1;
  }
  //Pembacaan Sinyal
  if (sentSignal==1){
    radio.write(msg, 4);
  }
  Serial.println("_______");
}
