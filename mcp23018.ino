#include <Wire.h>
#include "MCP23018.h"

MCP23018 pex(0x7);

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  Wire.begin();
  delay(500);
  pex.begin();
  pex.SetPorts(0xff,0xff);
  randomSeed(analogRead(0));
}

int dely=10;
uint8_t state;
uint8_t randNum;
uint8_t randOut;
int count=3;
bool up;
bool down;

void loop() {
  randOut=random(255);
  for (int x=0; x < count; x++) {
    randNum=random(255);
    randOut=(randOut | randNum);
  }
  pex.SetPortB(randOut);
  state=pex.GetPortA();

  if ((state & B00000001) == B00000000) {
    if (up) {
      count++;
      Serial.print(count);
      Serial.print("UP\n");
      up = false;
    }
  } else {
    up = true;
  }
  if ((state & B00000010) == B00000000) {
    if (down) {
      count--;
      Serial.print(count);
      Serial.print("DOWN\n");
      down=false;
    }
  } else {
    down=true;
  }
  if (count == 0) {
    count=1;
  }
  delay(20);
}

void poop() {
  digitalWrite(13, HIGH); // turn the LED on (HIGH is the voltage level)
  pex.SetPortB(B11111110);
  delay(dely);              // wait for a second
  pex.SetPortB(B11111101);
  delay(dely);
  pex.SetPortB(B11111011);
  delay(dely);
  pex.SetPortB(B11110111);
  delay(dely);
  pex.SetPortB(B11101111);
  delay(dely);
  pex.SetPortB(B11011111);
  delay(dely);
  pex.SetPortB(B10111111);
  delay(dely);
  pex.SetPortB(B01111111);
  delay(dely);
    pex.SetPortB(B01111111);
  delay(dely);
    pex.SetPortB(B10111111);
  delay(dely);
    pex.SetPortB(B11011111);
  delay(dely);
    pex.SetPortB(B11101111);
  delay(dely);
    pex.SetPortB(B11110111);
  delay(dely);
    pex.SetPortB(B11111011);
  delay(dely);
    pex.SetPortB(B11111101);
  delay(dely);
    pex.SetPortB(B11111110);
  delay(dely); 
//  dely++;
  state=pex.GetPortA();
  //Serial.print(state);
  //Serial.print("\n");
  if ((state & B00000001) == B00000000) {
    dely = dely + 1;
    Serial.print("UP\n");
  }
  if ((state & B00000010) == B00000000) {
    dely = dely - 1;
    Serial.print("DOWN\n");
  }
  if (dely == 0) {
    dely=1;
  }
  Serial.print(dely);
  Serial.print("\n");
}
