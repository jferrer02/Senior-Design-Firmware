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

//menu options

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
  
  //menu function
  
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
  
  /*
  matrix.print("New \n" "test"); 
  matrix.writeScreen(); 
  delay(4000);
  for(uint8_t i=0; i<4; i++) {
    matrix.setRotation(0);
    matrix.clearScreen();
    matrix.setCursor(0, 0);
    matrix.print("Test");
    matrix.writeScreen();
    delay(1000);
    for (uint8_t y=0; y<matrix.height(); y++) {
      for (uint8_t x=0; x< matrix.width(); x++) {
        matrix.setPixel(x, y);
        matrix.writeScreen();
      }
    }
    // blink!
    matrix.blink(false);
    delay(2000);
    matrix.blink(false);
    // Adjust the brightness down
    for (int8_t i=15; i>=0; i--) {
      matrix.setBrightness(i);
      delay(100);
    }
    // then back up
    for (uint8_t i=0; i<16; i++) {
      matrix.setBrightness(i);
      delay(100);
    }

    for (uint8_t y=0; y<matrix.height(); y++) {
      for (uint8_t x=0; x< matrix.width(); x++) {
        matrix.clrPixel(x, y);
        matrix.writeScreen();
      
      }
      
    }
  }
  */
}
