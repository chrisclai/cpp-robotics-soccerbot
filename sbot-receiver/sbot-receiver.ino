// BANSHEE UAV Robotics
// Custom Pro Micro Receiver Code
// Christopher Lai
// soccer bot edition
// LAST UPDATED: 4/29/2022

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00501";
const uint8_t  channel = 122;

const int motorFR1 = 0;
const int motorFR2 = 1;
const int motorBR1 = 2;
const int motorBR2 = 3;
const int motorFL1 = 9;
const int motorFL2 = 6;
const int motorBL1 = 4;
const int motorBL2 = 5;

void setup() {
  //Set Up Serial Comms - Debug
  Serial.begin(9600);

  //Set up Radio
  radio.begin();
  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_LOW,0);
  radio.setChannel(channel);
  Serial.println("Starting Radio"); 

  //to recieve
  radio.startListening();

  //stop
  stopMoving();
}
void loop() {
  
  if (radio.available()) {
    byte packet[] = {0,0,0,0,0,0};
    radio.read(&packet, sizeof(packet));

    // Will delay code, only use if necessary
    debug(packet);

    // Controller Modes
    if (packet[1] > 160) // LYstick Up
    {
      moveForward();
    }
    else if (packet[1] < 100) // LYstick Down
    {
      moveBackward();
    }
    else if (packet[0] > 160) // LXstick Up
    {
      moveSidewaysRight();
    }
    else if (packet[0] < 100) // LXStick Down
    {
      moveSidewaysLeft();
    }
    else if (packet[2] < 100 & packet[3] > 160) {
      moveLeftForward();
    }
    else if (packet[2] > 160 & packet[3] > 160) {
      moveRightForward();
    }
    else if (packet[2] < 100 & packet[3] < 100) {
      moveLeftBackward();
    }
    else if (packet[2] > 160 & packet[3] < 100) {
      moveRightBackward();
    }
    else if (packet[2] < 100) {
      rotateLeft();
    }
    else if (packet[2] > 150) {
      rotateRight();
    }
    else
    {
      stopMoving();
    }
    
    delay(50);
    
  }
  else {
    Serial.println("NO CONNECTION");
    stopMoving();
  }
}

void moveForward() {
  digitalWrite(motorFL1, 1); // Left Front Wheel Forward
  digitalWrite(motorFL2, 0);
  digitalWrite(motorBL1, 1); // Left Back Wheel Forward
  digitalWrite(motorBL2, 0);
  digitalWrite(motorFR1, 1); // Right Front Wheel Forward
  digitalWrite(motorFR2, 0);
  digitalWrite(motorBR1, 1); // Right Back Wheel Forward
  digitalWrite(motorBR2, 0);
}
void moveBackward() {
  digitalWrite(motorFL1, 0); // Left Front Wheel Backward
  digitalWrite(motorFL2, 1);
  digitalWrite(motorBL1, 0); // Left Back Wheel Backward
  digitalWrite(motorBL2, 1);
  digitalWrite(motorFR1, 0); // Right Front Wheel Backward
  digitalWrite(motorFR2, 1);
  digitalWrite(motorBR1, 0); // Right Back Wheel Backward
  digitalWrite(motorBR2, 1);
}
void moveSidewaysRight() {
  digitalWrite(motorFL1, 1); // Left Front Wheel Forward
  digitalWrite(motorFL2, 0);
  digitalWrite(motorBL1, 0); // Left Back Wheel Backward
  digitalWrite(motorBL2, 1);
  digitalWrite(motorFR1, 0); // Right Front Wheel Backward
  digitalWrite(motorFR2, 1);
  digitalWrite(motorBR1, 1); // Right Back Wheel Forward
  digitalWrite(motorBR2, 0);
}
void moveSidewaysLeft() {
  digitalWrite(motorFL1, 0); // Left Front Wheel Backward
  digitalWrite(motorFL2, 1);
  digitalWrite(motorBL1, 1); // Left Back Wheel Forward
  digitalWrite(motorBL2, 0);
  digitalWrite(motorFR1, 1); // Right Front Wheel Forward
  digitalWrite(motorFR2, 0);
  digitalWrite(motorBR1, 0); // Right Back Wheel Backward
  digitalWrite(motorBR2, 1);
}
void rotateLeft() {
  digitalWrite(motorFL1, 0); // Left Front Wheel Backward
  digitalWrite(motorFL2, 1);
  digitalWrite(motorBL1, 0); // Left Back Wheel Backward
  digitalWrite(motorBL2, 1);
  digitalWrite(motorFR1, 1); // Right Front Wheel Forward
  digitalWrite(motorFR2, 0);
  digitalWrite(motorBR1, 1); // Right Back Wheel Forward
  digitalWrite(motorBR2, 0);
}
void rotateRight() {
  digitalWrite(motorFL1, 1); // Left Front Wheel Forward
  digitalWrite(motorFL2, 0);
  digitalWrite(motorBL1, 1); // Left Back Wheel Forward
  digitalWrite(motorBL2, 0);
  digitalWrite(motorFR1, 0); // Right Front Wheel Backward
  digitalWrite(motorFR2, 1);
  digitalWrite(motorBR1, 0); // Right Back Wheel Backward
  digitalWrite(motorBR2, 1);
}
void moveRightForward() {
  digitalWrite(motorFL1, 1); // Left Front Wheel Forward
  digitalWrite(motorFL2, 0);
  digitalWrite(motorBL1, 0); // Left Back Wheel STOP
  digitalWrite(motorBL2, 0);
  digitalWrite(motorFR1, 0); // Right Front Wheel STOP
  digitalWrite(motorFR2, 0);
  digitalWrite(motorBR1, 1); // Right Back Wheel Forward
  digitalWrite(motorBR2, 0);
}
void moveRightBackward() {
  digitalWrite(motorFL1, 0); // Left Front Wheel STOP
  digitalWrite(motorFL2, 0);
  digitalWrite(motorBL1, 0); // Left Back Wheel Backward
  digitalWrite(motorBL2, 1);
  digitalWrite(motorFR1, 0); // Right Front Wheel Backward
  digitalWrite(motorFR2, 1);
  digitalWrite(motorBR1, 0); // Right Back Wheel STOP
  digitalWrite(motorBR2, 0);
}
void moveLeftForward() {
  digitalWrite(motorFL1, 0); // Left Front Wheel STOP
  digitalWrite(motorFL2, 0);
  digitalWrite(motorBL1, 1); // Left Back Wheel Forward
  digitalWrite(motorBL2, 0);
  digitalWrite(motorFR1, 1); // Right Front Wheel Forward
  digitalWrite(motorFR2, 0);
  digitalWrite(motorBR1, 0); // Right Back Wheel STOP
  digitalWrite(motorBR2, 0);
}
void moveLeftBackward() {
  digitalWrite(motorFL1, 0); // Left Front Wheel Backward
  digitalWrite(motorFL2, 1);
  digitalWrite(motorBL1, 0); // Left Back Wheel STOP
  digitalWrite(motorBL2, 0);
  digitalWrite(motorFR1, 0); // Right Front Wheel STOP
  digitalWrite(motorFR2, 0);
  digitalWrite(motorBR1, 0); // Right Back Wheel Backward
  digitalWrite(motorBR2, 1);
}
void stopMoving() {
  digitalWrite(motorFL1, 0); // Left Front Wheel STOP
  digitalWrite(motorFL2, 0);
  digitalWrite(motorBL1, 0); // Left Back Wheel STOP
  digitalWrite(motorBL2, 0);
  digitalWrite(motorFR1, 0); // Right Front Wheel STOP
  digitalWrite(motorFR2, 0);
  digitalWrite(motorBR1, 0); // Right Back Wheel STOP
  digitalWrite(motorBR2, 0);
}

void debug(byte packet[]) {
      //THIS IS FOR DEBUG
      Serial.print("LX: ");
      Serial.print(packet[0]);
      Serial.print("; LY: ");
      Serial.print(packet[1]);
      Serial.print("; LB: ");
      Serial.print(packet[4]);
      Serial.print("; RX: ");
      Serial.print(packet[2]); 
      Serial.print("; RY: ");
      Serial.print(packet[3]);
      Serial.print("; RB: ");
      Serial.print(packet[5]);
      Serial.println();
      //delay(5);
}
