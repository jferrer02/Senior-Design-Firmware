#include <iostream>
using namespace std;
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

void testcomponents();
void Game1();
void OutputArrows();

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
  if (b_1 == LOW) {
    menu_sel = 1;
  }
  else {
    menu_sel = 0;
  }
  matrix.print("Menu\n"); //print menu at top of screen
  if (menu_val == 0) {
    matrix.print("Comp");
    if (menu_sel == 1) {
      matrix.clearScreen();
      matrix.setCursor(0, 0);
      matrix.print("Test\nComp");
      matrix.writeScreen();
      delay(5000);
      testcomponents();
    }
  }
  if (menu_val == 1) {
    matrix.print("Game");
    if (menu_sel == 1) {
      matrix.clearScreen();
      matrix.setCursor(0, 0);
      matrix.print("Play\nGame");
      matrix.writeScreen();
      delay(5000);
      Game1();
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

void Game1() {
  int x = 10;
  int y = 8;
  int r = 0; //for while loop
  //taking code from stack overflow
  //https://stackoverflow.com/questions/12657962/how-do-i-generate-a-random-number-between-two-variables-that-i-have-stored
  int healthdot_x = rand()%(23-0 + 1) + 0;
  int healthdot_y = rand()%(15-0 + 1) + 0;
  int healthdot_countdown = 100; // a countdown for the health dot to go away
  int health_bar = 1; //players health, lose if reaches 0
  // arrow pointing to the right
  int right_point_y = rand()%(13-2 + 1) + 0;
  int ra_x[5] = {-2,-1,0,-1,-2};
  int ra_y[5] = {right_point_y+2,right_point_y+1,right_point_y,right_point_y-1,right_point_y-2};
  // arrow pointing to the left
  int left_point_y = rand()%(13-2 + 1) + 0;
  int la_x[5] = {25,24,23,24,25};
  int la_y[5] = {left_point_y+2,left_point_y+1,left_point_y,left_point_y-1,left_point_y-2};
  // arrow pointing up
  int up_point_x = rand()%(21-2 + 1) + 0;
  int ua_x[5] = {up_point-2,up_point-1,up_point_x,up_point+1,up_point+2};
  int ua_y[5] = {17,16,15,16,17};
  // arrow pointing down
  int down_point_x = rand()%(21-2 + 1) + 0;
  int da_x[5] = {down_point-2,down_point-1,down_point_x,down_point+1,down_point+2};
  int da_y[5] = {-2,-1,0,-1,-2};
  matrix.setRotation(0);
  matrix.clearScreen();
  matrix.setCursor(0, 0); 
  matrix.print("Hlth\n");
  matrix.print(health_bar);
  matrix.writeScreen();
  delay(2000);  
  while (r < 1) {
    b_1 = digitalRead(button_1);
    b_2 = digitalRead(button_2);
    X = analogRead(A0);  // read the A0 input pin
    Y = analogRead(A1);  // read the A1 input pin
    matrix.setRotation(0);
    matrix.clearScreen();
    matrix.setCursor(0, 0);  
    if ((x == healthdot_x) && (y == healthdot_y)) {
      health_bar++;
      matrix.setRotation(0);
      matrix.print("Hlth\n");
      matrix.print(health_bar);
      matrix.writeScreen();
      delay(2000);
      matrix.clearScreen();
      healthdot_countdown = 100;
      //taking code from stack overflow
      //https://stackoverflow.com/questions/12657962/how-do-i-generate-a-random-number-between-two-variables-that-i-have-stored
      healthdot_x = rand()%(23-0 + 1) + 0;
      healthdot_y = rand()%(15-0 + 1) + 0;
    }
    else if (healthdot_countdown > 0) {
      matrix.setPixel(healthdot_x, healthdot_y);
    } 
    else {
      healthdot_countdown = 100;
      //taking code from stack overflow
      //https://stackoverflow.com/questions/12657962/how-do-i-generate-a-random-number-between-two-variables-that-i-have-stored
      healthdot_x = rand()%(23-0 + 1) + 0;
      healthdot_y = rand()%(15-0 + 1) + 0;
    }
    healthdot_countdown--;
    // 
    if (X > 550) {
      x++;
    }
    if (X < 450) {
      x--;
    }
    if (Y > 550) {
      y--;
    }
    if (Y < 450) {
      y++;
    }
    if (x == -1) {
      x = 0;
    }    
    if (y == -1) {
      y = 0;
    }
    if (x == 24) {
      x = 23;
    }   
    if (y == 16) {
      y = 15;
    } 
    matrix.setPixel(x, y);

    //right pointing arrow
    OutputArrows(ra_x[0],ra_x[1],ra_x[2],ra_x[3],ra_x[4],ra_y[0],ra_y[1],ra_y[2],ra_y[3],ra_y[4]);
    if ((x==ra_x[0] && y==ra_y[0]) || (x==ra_x[1] && y==ra_y[1]) || (x==ra_x[2] && y==ra_y[2]) || (x==ra_x[3] && y==ra_y[3]) || (x==ra_x[4] && y==ra_y[4])) {
      health_bar--;
      matrix.setRotation(0);
      matrix.print("Hlth\n");
      matrix.print(health_bar);
      matrix.writeScreen();
      delay(2000);
      matrix.clearScreen();
      healthdot_countdown = 100;
      //taking code from stack overflow
      //https://stackoverflow.com/questions/12657962/how-do-i-generate-a-random-number-between-two-variables-that-i-have-stored
      healthdot_x = rand()%(23-0 + 1) + 0;
      healthdot_y = rand()%(15-0 + 1) + 0;
      /* reset x and y values of arrows, can use references in a function that also take in
      parameters for how far back the arrows can start (where there will be some randomness).
      The more health you have, the less far back the arrows can start and the game gets more
      difficult.
      */
    }
    ra_x[0] = ra_x[0] + 1; //increment arrow
    ra_x[1] = ra_x[1] + 1; //increment arrow
    ra_x[2] = ra_x[2] + 1; //increment arrow
    ra_x[3] = ra_x[3] + 1; //increment arrow
    ra_x[4] = ra_x[4] + 1; //increment arrow



    matrix.writeScreen();
    if (b_1 == LOW) {
      break;
    }
    delay(50); 
  }  
}

OutputArrows(x0,x1,x2,x3,x4,y0,y1,y2,y3,y4) {
  matrix.setPixels(x0,y0);
  matrix.setPixels(x1,y1);
  matrix.setPixels(x2,y2);
  matrix.setPixels(x3,y3);
  matrix.setPixels(x4,y4);
}