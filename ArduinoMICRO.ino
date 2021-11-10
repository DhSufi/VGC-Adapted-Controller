#include "SwitchJoystick.h"

// Create Joystick
SwitchJoystick_ Joystick;

// Set to true to test "Auto Send" mode or false to test "Manual Send" mode.
//const bool testAutoSendMode = true;
const bool testAutoSendMode = false;



uint32_t interval = 10;
unsigned long previousMillis = millis();


int buttonA = 2;
int buttonB = 1;
int buttonX = 3;
int buttonY = 0;
int buttonPLUS = 9;
int padUp = 0;
int padRight = 90;
int padDown = 180;
int padLeft = 270;
int center = -1;

int pinA = 2;
int pinB = 3;
int pinX = 4;
int pinY = 5;
int pinPLUS = 6;
int pinUp = 7;
int pinDown = 8;
int pinRight = 9;
int pinLeft = 10;


bool start = false;
int counter = 0;


void setup() {

  if (testAutoSendMode)
  {
    Joystick.begin();
  }
  else
  {
    Joystick.begin(false);
  }

  //pinMode(0, INPUT_PULLUP); TX0
  //pinMode(1, INPUT_PULLUP); RX1
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
//  pinMode(16, INPUT_PULLUP);
//  pinMode(14, INPUT_PULLUP);
//  pinMode(15, INPUT_PULLUP);

  Joystick.setLXAxis(128);
  Joystick.setLYAxis(128);
  Joystick.setRXAxis(128);
  Joystick.setRYAxis(128);
  Joystick.sendState();
}

void loop() {

  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    
    previousMillis = currentMillis;
      
    if (!digitalRead(pinA)){
      Joystick.pressButton(buttonA);
    } else {
      Joystick.releaseButton(buttonA);
    }

    if (!digitalRead(pinB)){
      Joystick.pressButton(buttonB);
    } else {
      Joystick.releaseButton(buttonB);
    }

    if (!digitalRead(pinY)){
      Joystick.pressButton(buttonY);
    } else {
      Joystick.releaseButton(buttonY);
    }

    if (!digitalRead(pinX)){
      Joystick.pressButton(buttonX);
    } else {
      Joystick.releaseButton(buttonX);
    }

    if (!digitalRead(pinPLUS)){
      Joystick.pressButton(buttonPLUS);
    } else {
      Joystick.releaseButton(buttonPLUS);
    }

    if (!digitalRead(pinUp)){
      Joystick.setHatSwitch(padUp);
    } 
    else if (!digitalRead(pinDown)) {
      Joystick.setHatSwitch(padDown);
    }
    else if (!digitalRead(pinRight)){
      Joystick.setHatSwitch(padRight);
    }
    else if (!digitalRead(pinLeft)){
      Joystick.setHatSwitch(padLeft);
    }
    else {
      Joystick.setHatSwitch(center);
    }
    
  Joystick.sendState();
  
  }
}
