/*
* Soccerbot Transmitter Controller
* Christopher Lai
* Last Updated: 4/29/2022
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00501";
const uint8_t  channel = 122;

int lowmap = 10;
int highmap = 250;

// Define the digital inputs
#define lBTN 4  // Joystick button 1
#define rBTN 3  // Joystick button 2

byte packet[] = {0,0,0,0,0,0};

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW,0);
  radio.setChannel(channel);
  radio.stopListening();
  Serial.println("Sending");
  
  //Set Up Controls
  pinMode(lBTN, INPUT_PULLUP);
  pinMode(rBTN, INPUT_PULLUP);
}

void loop() {

  int tempx = 0;
  int tempy = 0;
  
  // Read all analog inputs and map them to one Byte value
  //Gather Left Stick Values
  tempx = map(analogRead(A1),0,1023,highmap,lowmap);
  tempy = map(analogRead(A0),0,1023,highmap,lowmap);
  packet[0] = tempx;
  packet[1] = tempy;
  //Gather Right Stick Values
  tempx = map(analogRead(A3),0,1023,highmap,lowmap);
  tempy = map(analogRead(A2),0,1023,highmap,lowmap);
  packet[2] = tempx;
  packet[3] = tempy; 
  
  // Read all digital inputs
  packet[4] = digitalRead(lBTN);
  packet[5] = digitalRead(rBTN);

  // Send the whole data from the structure to the receiver
  radio.write(&packet, sizeof(packet));

  //debug();
  
  delay(5);
}

void debug() {
      //THIS IS FOR DEBUG
      int RecLarge= packet[0];
      Serial.print("LX: ");
      Serial.print(RecLarge);
      RecLarge= packet[1];
      Serial.print("; LY: ");
      Serial.print(RecLarge);
      Serial.print("; LB: ");
      Serial.print(packet[4]);
      RecLarge= packet[2];
      Serial.print("; RX: ");
      Serial.print(RecLarge); 
      RecLarge= packet[3];
      Serial.print("; RY: ");
      Serial.print(RecLarge);
      Serial.print("; RB: ");
      Serial.print(packet[5]);
      Serial.println();
      delay(5);
}
