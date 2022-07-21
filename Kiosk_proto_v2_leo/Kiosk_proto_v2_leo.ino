// Rotary Encoder code from https://lastminuteengineers.com/rotary-encoder-arduino-tutorial/
// LCD code from https://docs.arduino.cc/learn/electronics/lcd-displays
// LCD tips drawn from https://www.baldengineer.com/arduino-lcd-display-tips.html

#include "Wire.h"
#include "Adafruit_LiquidCrystal.h"
#include <KeyboardLayout.h>
#include <Keyboard.h>

// Connect via i2c, default address #0 (A0-A2 not jumpered)
Adafruit_LiquidCrystal lcd(0);

// not using backpack and connecting direct?
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
//const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Rotary Encoder Inputs
#define CLK 5  //also pin a
#define DT 6   //also pin b
#define SW 7  //also pin c

int counter = 0;
int currentStateCLK;
int lastStateCLK;
String currentDir =""; 
unsigned long lastButtonPress = 0;

char line0[17];
char line1[17];
char msg1[17];
char msg2[17];

void setup() {
  
  // Set encoder pins as inputs
  pinMode(CLK,INPUT);
  pinMode(DT,INPUT);
  pinMode(SW, INPUT_PULLUP);

  // Setup Serial Monitor
  Serial.begin(9600);
  Keyboard.begin();

  // Read the initial state of CLK
  lastStateCLK = digitalRead(CLK);

  // Print a message to the LCD.
  lcd.begin(16, 2);
  lcd.print("hello, world!");
}

void updateDisplay() {
   lcd.setCursor(0,0);
   lcd.print(line0);
   lcd.print(line1);
}

void loop() {
  
  // Read the current state of CLK
  currentStateCLK = digitalRead(CLK);

  // If last and current state of CLK are different, then pulse occurred
  // React to only 1 state change to avoid double count
  if (currentStateCLK != lastStateCLK  && currentStateCLK == 1) {

    // If the DT state is different than the CLK state then
    // the encoder is rotating CCW so decrement
    if (digitalRead(DT) != currentStateCLK) {
      currentDir ="CCW";
      Keyboard.write(KEY_LEFT_ARROW);
      counter --;
      if (counter < 0) {
      counter = 42;
    }
    } else {
      // Encoder is rotating CW so increment
      currentDir ="CW";
      counter ++;
      Keyboard.write(KEY_RIGHT_ARROW);
      if (counter > 42) {
      counter = 0;
    }
    }
    updateDisplay() ;
    lcd.setCursor(0,0) ; //sets cursor to first column first row
    sprintf(msg1, "Direction: %-5s", currentDir.c_str());
    lcd.print(msg1);
    //lcd.print("Direction:");
    //lcd.print(currentDir);
    lcd.setCursor(0,1); // cursor to first column, second row
    sprintf(msg2, "Counter: %-3d", counter);
    lcd.print(msg2);
    //lcd.print("Counter: ");
    //lcd.print(counter);
  }


  // Remember last CLK state
  lastStateCLK = currentStateCLK;

  // Read the button state
  int btnState = digitalRead(SW);

  //If we detect LOW signal, button is pressed
  if (btnState == LOW) { 
    //if 50ms have passed since last LOW pulse, it means that the
    //button has been pressed, released and pressed again
    if (millis() - lastButtonPress < 50) {
      lcd.setCursor(0,0) ; //sets cursor to first column first row
      lcd.print("Button pressed!!");
      lcd.setCursor(0,1) ; //sets cursor to first column second row
      lcd.print("                ");
      Keyboard.write(KEY_UP_ARROW);
    } 
      // Remember last button press event
      lastButtonPress = millis();
    }
    // Put in a slight delay to help debounce the reading
    delay(1);
}
