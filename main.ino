#include "Adafruit_HT1632.h"

#define HT_DATA 3
#define HT_WR   4
#define HT_CS   5
int button_1 = 11;
int button_2 = 12;

//button values
int b_1 = 0;
int b_2 = 0;

//joystick values
int X = 0;  // variable to store the value read
int Y = 0;  // variable to store the value read

//menu variables
int menu_val = 0;
int menu_sel = 0;

// use this line for single matrix
Adafruit_HT1632LEDMatrix matrix = Adafruit_HT1632LEDMatrix(HT_DATA, HT_WR, HT_CS);

void setup() {
  pinMode(button_1, INPUT);
  pinMode(button_2, INPUT);
  Serial.begin(9600);
  matrix.begin(ADA_HT1632_COMMON_16NMOS);
  matrix.fillScreen();
  delay(500);
  matrix.clearScreen();
  matrix.setTextWrap(false);
}

void loop() {
  matrix.setRotation(0);
  matrix.clearScreen();
  matrix.setCursor(0, 0);
  b_1 = digitalRead(button_1);
  b_2 = digitalRead(button_2);
  X = analogRead(A0);  // read the A0 input pin
  Y = analogRead(A1);  // read the A1 input pin 
  if (X > 550) {
    menu_val++;
    if (menu_val > 1) {
      menu_val = 0;
    }
  }
  if (X < 450) {
    menu_val--;
    if (menu_val < 0) {
      menu_val = 1;
    }
  }


  matrix.writeScreen();
  delay(50);
}

void testcomponents() {
  int i = 0;
  while (i < 1) {
    matrix.setRotation(0);
    matrix.clearScreen();
    matrix.setCursor(0, 0);
  
    b_1 = digitalRead(button_1);
    b_2 = digitalRead(button_2);
    X = analogRead(A0);  // read the A0 input pin
    Y = analogRead(A1);  // read the A1 input pin 

    if (b_1 == LOW) {
      matrix.print("b1");
    }       
    else if ((X > 550) || (X < 450)) {
      matrix.print(X);
    }
    else {
      matrix.print("none");
    }

    matrix.print("\n");
  
    if (b_2 == LOW) {
      matrix.print("b2");
    }
    else if ((Y > 550) || (Y < 450)) {
      matrix.print(Y); 
    }
    else {
      matrix.print("none");
      }
    matrix.writeScreen();
    delay(50);
  }
}