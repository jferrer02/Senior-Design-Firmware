#include "Adafruit_HT1632.h"
#define HT_DATA 3
#define HT_WR   4
#define HT_CS   5
#define maze_length 24
#define maze_width 16
int button_1 = 11;
int button_2 = 12;

int x=1;
int y=1;
int maze_animation_counter = 1;

// use this line for single matrix
Adafruit_HT1632LEDMatrix matrix = Adafruit_HT1632LEDMatrix(HT_DATA, HT_WR, HT_CS);

//button values
int b_1 = 0;
int b_2 = 0;

//joystick values
int X = 0;  // variable to store the value read
int Y = 0;  // variable to store the value read

//menu variables
int menu_val = 0;
int menu_sel = 0;

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
  if (maze_animation_counter == 1) {
    matrix.print("   G\nr");
    matrix.writeScreen();
  }

  if (maze_animation_counter == 2) {
    matrix.print("  Ga\ner");
    matrix.writeScreen();
  }
  if (maze_animation_counter == 3) {
    matrix.print(" Gam\nver");
    matrix.writeScreen();
  }
  if (maze_animation_counter == 4) {
    matrix.print("Game\nOver");
    matrix.writeScreen();
    delay(3000);
  }
  maze_animation_counter++;
  delay(300);
}