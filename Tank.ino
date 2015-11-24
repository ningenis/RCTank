// Source Code untuk Receiver (Tank)
// Courtesy of http://forum.arduino.cc/index.php?topic=138663.0

//Library SPI dan RF 24
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

//Pendefinisan Variabel
int msg[2]; //Array Pesan
RF24 radio(9,10); //Pin untuk Radio
const uint64_t pipe = 0xE8E8F0F0E1LL; //Pipe Radio
int Motor1 = 3; //Motor 1
int Motor2 = 5; //Motor 2

void setup(void){
  Serial.begin(9600); //Setup Serial
  radio.begin(); //Setup Radio
  radio.openReadingPipe(1,pipe);
  radio.startListening();
  pinMode(Motor1, OUTPUT); //Setup Pin untuk Motor
  pinMode(Motor2, OUTPUT);
}
 
void loop(void){
  //Pengecekan sinyal dari transmitter
  if (radio.available()){
    //Inisialisasi variabel pengecekan
    bool done = false;   
    while (!done){
      done = radio.read(msg, 4); //Baca pesan dari transmitter     
      Serial.println(msg[0]); //Salin pesan ke serial    
      Serial.println(msg[1]);
      Serial.println("__________");
      //Pembacaan pesan untuk motor 1    
      if (msg[0] == 111){
        delay(10);
        digitalWrite(Motor1, HIGH);
      } else {
        digitalWrite(Motor1, LOW);
      }
      //Pembacaan pesan untuk motor 2 
      if (msg[1] == 111){
        delay(10);
        digitalWrite(Motor2, HIGH);
      } else {
        digitalWrite(Motor2, LOW);
      }
      delay(10);
    }
  }
  else{
    Serial.println("No radio available");
  }
}
