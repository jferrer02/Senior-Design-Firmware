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

// use this line for single matrix
Adafruit_HT1632LEDMatrix matrix = Adafruit_HT1632LEDMatrix(HT_DATA, HT_WR, HT_CS);

//button values
int b_1 = 0;
int b_2 = 0;

//joystick values
int X = 0;  // variable to store the value read
int Y = 0;  // variable to store the value read

//matrix values of maze
int maze[maze_width][maze_length] = {
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1},
{1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1 ,1},
{1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1 ,1},
{1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1 ,1},
{1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1 ,1},
{1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 ,1},
{1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1},
{1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1 ,1},
{1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1 ,1},
{1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1 ,1},
{1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1 ,1},
{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 ,1},
{1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1 ,1},
{1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1 ,1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1 ,1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1 ,1},  
};

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
/*
void testcomponents();
void Game1();
void OutputArrows();
void Maze();
void displaymaze();
void moveDot();
void Maze();
bool checkvalid();
*/

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
  // adding a comment for the sake of merging
  int x = 10;
  int y = 8;
  int r = 0; //for while loop
  //taking code from stack overflow
  //https://stackoverflow.com/questions/12657962/how-do-i-generate-a-random-number-between-two-variables-that-i-have-stored
  int pointsdot_x = rand()%(23-0 + 1) + 0;
  int pointsdot_y = rand()%(15-0 + 1) + 0;
  int pointsdot_countdown = 30; // a countdown for the point dot to go away
  int points_counter = 0; //player's point, win if reaches certain amount and game gets harder as points are added
  int health_bar = 3; //player's health, lose if reaches 0

  int healthdot_x = rand()%(23-0 + 1) + 0;
  int healthdot_y = rand()%(15-0 + 1) + 0;
  int healthbar_countdown = 100;
  int health_max = 5;

  // arrow pointing to the right
  int right_point_y = rand()%(15-0 + 1) + 0;
  int ra_x[10] = {-3,-2,-1,-2,-3,-4,-3,-2,-3,-4};
  int ra_y[10] = {right_point_y+2,right_point_y+1,right_point_y,right_point_y-1,right_point_y-2,right_point_y+2,right_point_y+1,right_point_y,right_point_y-1,right_point_y-2};
  // arrow pointing to the left
  int left_point_y = rand()%(15-0 + 1) + 0;
  int la_x[10] = {26,25,24,25,26,27,26,25,26,27};
  int la_y[10] = {left_point_y+2,left_point_y+1,left_point_y,left_point_y-1,left_point_y-2,left_point_y+2,left_point_y+1,left_point_y,left_point_y-1,left_point_y-2};
  // arrow pointing up
  int up_point_x = rand()%(23-0 + 1) + 0;
  int ua_x[10] = {up_point_x-2,up_point_x-1,up_point_x,up_point_x+1,up_point_x+2,up_point_x-2,up_point_x-1,up_point_x,up_point_x+1,up_point_x+2};
  int ua_y[10] = {18,17,16,17,18,19,18,17,18,19};
  // arrow pointing down
  int down_point_x = rand()%(23-0 + 1) + 0;
  int da_x[10] = {down_point_x-2,down_point_x-1,down_point_x,down_point_x+1,down_point_x+2,down_point_x-2,down_point_x-1,down_point_x,down_point_x+1,down_point_x+2};
  int da_y[10] = {-3,-2,-1,-2,-3,-4,-3,-2,-3,-4};

  int zr = rand()%(100-0 + 1) + 0; //range of random values where arrow can start from
  int zl = rand()%(100-0 + 1) + 0; //range of random values where arrow can start from
  int zu = rand()%(100-0 + 1) + 0; //range of random values where arrow can start from
  int zd = rand()%(100-0 + 1) + 0; //range of random values where arrow can start from 
  int d = 100; //determines difficulty of game, the lower the value of d, the more difficult
  
  //print points
  matrix.setRotation(0);
  matrix.clearScreen();
  matrix.setCursor(0, 0); 
  matrix.print("Pts:\n");
  matrix.print(points_counter);
  matrix.writeScreen();
  delay(2000); 

  //print health
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
    if ((x == pointsdot_x) && (y == pointsdot_y)) {
      points_counter++;
      matrix.clearScreen();
      pointsdot_countdown = 30;
      //taking code from stack overflow
      //https://stackoverflow.com/questions/12657962/how-do-i-generate-a-random-number-between-two-variables-that-i-have-stored
      pointsdot_x = rand()%(23-0 + 1) + 0;
      pointsdot_y = rand()%(15-0 + 1) + 0;
    }
    else if (pointsdot_countdown > 0) {
      matrix.setPixel(pointsdot_x, pointsdot_y);
    } 
    else {
      pointsdot_countdown = 30;
      //taking code from stack overflow
      //https://stackoverflow.com/questions/12657962/how-do-i-generate-a-random-number-between-two-variables-that-i-have-stored
      pointsdot_x = rand()%(23-0 + 1) + 0;
      pointsdot_y = rand()%(15-0 + 1) + 0;
    }
    pointsdot_countdown--;


    if ((x == healthdot_x) && (y == healthdot_y)) {
      health_bar++;
      matrix.clearScreen();
      if (health_bar < health_max) {
        healthbar_countdown = 100;
        //taking code from stack overflow
        //https://stackoverflow.com/questions/12657962/how-do-i-generate-a-random-number-between-two-variables-that-i-have-stored
        healthdot_x = rand()%(23-0 + 1) + 0;
        healthdot_y = rand()%(15-0 + 1) + 0;
      }
    }
    else if (healthbar_countdown > 0) {
      matrix.setPixel(healthdot_x, healthdot_y);
    } 
    else {
      if (health_bar < health_max) {
        healthbar_countdown = 100;
        //taking code from stack overflow
        //https://stackoverflow.com/questions/12657962/how-do-i-generate-a-random-number-between-two-variables-that-i-have-stored
        healthdot_x = rand()%(23-0 + 1) + 0;
        healthdot_y = rand()%(15-0 + 1) + 0;
      }
    }
    healthbar_countdown--;
    
    // move dot with joystick and keep it within bounds 
    if (X > 650) {
      x++;
    }
    if (X < 350) {
      x--;
    }
    if (Y > 650) {
      y--;
    }
    if (Y < 350) {
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
    
    //~-~-~-~-~-~-~-~-~-Right Pointing Arrow~-~-~-~-~-~-~-~-~-
    OutputArrows(ra_x[0],ra_x[1],ra_x[2],ra_x[3],ra_x[4],ra_x[5],ra_x[6],ra_x[7],ra_x[8],ra_x[9],ra_y[0],ra_y[1],ra_y[2],ra_y[3],ra_y[4],ra_y[5],ra_y[6],ra_y[7],ra_y[8],ra_y[9]); //output right pointing arrow
    if ((x==ra_x[0] && y==ra_y[0]) || (x==ra_x[1] && y==ra_y[1]) || (x==ra_x[2] && y==ra_y[2]) || (x==ra_x[3] && y==ra_y[3]) || (x==ra_x[4] && y==ra_y[4]) || (x==ra_x[5] && y==ra_y[5]) || (x==ra_x[6] && y==ra_y[6]) || (x==ra_x[7] && y==ra_y[7]) || (x==ra_x[8] && y==ra_y[8]) || (x==ra_x[9] && y==ra_y[9])) {
      matrix.clearScreen();
      health_bar--;
      matrix.setRotation(0);
      matrix.print("Hlth\n");
      matrix.print(health_bar);
      matrix.writeScreen();
      delay(2000);
      matrix.clearScreen();
      pointsdot_countdown = 30;
      //taking code from stack overflow
      //https://stackoverflow.com/questions/12657962/how-do-i-generate-a-random-number-between-two-variables-that-i-have-stored
      pointsdot_x = rand()%(23-0 + 1) + 0;
      pointsdot_y = rand()%(15-0 + 1) + 0;
      /* reset x and y values of arrows, can use references in a function that also take in
      parameters for how far back the arrows can start (where there will be some randomness).
      The more health you have, the less far back the arrows can start and the game gets more
      difficult.
      */
      zr = rand()%(d-0 + 1) + 0;
      ra_x[0] = -4 - zr; // reset x location
      ra_x[1] = -3 - zr; // reset x location
      ra_x[2] = -2 - zr; // reset x location
      ra_x[3] = -3 - zr; // reset x location
      ra_x[4] = -4 - zr; // reset x location
      ra_x[5] = -5 - zr; // reset x location
      ra_x[6] = -4 - zr; // reset x location
      ra_x[7] = -3 - zr; // reset x location
      ra_x[8] = -4 - zr; // reset x location
      ra_x[9] = -5 - zr; // reset x location

      right_point_y = rand()%(15-0 + 1) + 0;  // new random y value
      ra_y[0] = right_point_y + 2;            // reset y location
      ra_y[1] = right_point_y + 1;            // reset y location
      ra_y[2] = right_point_y;                // reset y location
      ra_y[3] = right_point_y - 1;            // reset y location
      ra_y[4] = right_point_y - 2;            // reset y location
      ra_y[5] = right_point_y + 2;            // reset y location
      ra_y[6] = right_point_y + 1;            // reset y location
      ra_y[7] = right_point_y;                // reset y location
      ra_y[8] = right_point_y - 1;            // reset y location
      ra_y[9] = right_point_y - 2;            // reset y location
    }
    if (ra_x[2]==27) {
      zr = rand()%(d-0 + 1) + 0;
      ra_x[0] = -4 - zr; // reset x location
      ra_x[1] = -3 - zr; // reset x location
      ra_x[2] = -2 - zr; // reset x location
      ra_x[3] = -3 - zr; // reset x location
      ra_x[4] = -4 - zr; // reset x location
      ra_x[5] = -5 - zr; // reset x location
      ra_x[6] = -4 - zr; // reset x location
      ra_x[7] = -3 - zr; // reset x location
      ra_x[8] = -4 - zr; // reset x location
      ra_x[9] = -5 - zr; // reset x location

      right_point_y = rand()%(15-0 + 1) + 0;  // new random y value
      ra_y[0] = right_point_y + 2;            // reset y location
      ra_y[1] = right_point_y + 1;            // reset y location
      ra_y[2] = right_point_y;                // reset y location
      ra_y[3] = right_point_y - 1;            // reset y location
      ra_y[4] = right_point_y - 2;            // reset y location
      ra_y[5] = right_point_y + 2;            // reset y location
      ra_y[6] = right_point_y + 1;            // reset y location
      ra_y[7] = right_point_y;                // reset y location
      ra_y[8] = right_point_y - 1;            // reset y location
      ra_y[9] = right_point_y - 2;            // reset y location
    }
    ra_x[0] = ra_x[0] + 1; //increment arrow to the right
    ra_x[1] = ra_x[1] + 1; //increment arrow to the right
    ra_x[2] = ra_x[2] + 1; //increment arrow to the right
    ra_x[3] = ra_x[3] + 1; //increment arrow to the right
    ra_x[4] = ra_x[4] + 1; //increment arrow to the right
    ra_x[5] = ra_x[5] + 1; //increment arrow to the right
    ra_x[6] = ra_x[6] + 1; //increment arrow to the right
    ra_x[7] = ra_x[7] + 1; //increment arrow to the right
    ra_x[8] = ra_x[8] + 1; //increment arrow to the right
    ra_x[9] = ra_x[9] + 1; //increment arrow to the right

    
    //~-~-~-~-~-~-~-~-~-Left Pointing Arrow~-~-~-~-~-~-~-~-~-
    OutputArrows(la_x[0],la_x[1],la_x[2],la_x[3],la_x[4],la_x[5],la_x[6],la_x[7],la_x[8],la_x[9],la_y[0],la_y[1],la_y[2],la_y[3],la_y[4],la_y[5],la_y[6],la_y[7],la_y[8],la_y[9]); //output left pointing arrow
    if ((x==la_x[0] && y==la_y[0]) || (x==la_x[1] && y==la_y[1]) || (x==la_x[2] && y==la_y[2]) || (x==la_x[3] && y==la_y[3]) || (x==la_x[4] && y==la_y[4]) || (x==la_x[5] && y==la_y[5]) || (x==la_x[6] && y==la_y[6]) || (x==la_x[7] && y==la_y[7]) || (x==la_x[8] && y==la_y[8]) || (x==la_x[9] && y==la_y[9])) {
      matrix.clearScreen();
      health_bar--;
      matrix.setRotation(0);
      matrix.print("Hlth\n");
      matrix.print(health_bar);
      matrix.writeScreen();
      delay(2000);
      matrix.clearScreen();
      pointsdot_countdown = 30;
      //taking code from stack overflow
      //https://stackoverflow.com/questions/12657962/how-do-i-generate-a-random-number-between-two-variables-that-i-have-stored
      pointsdot_x = rand()%(23-0 + 1) + 0;
      pointsdot_y = rand()%(15-0 + 1) + 0;
      /* reset x and y values of arrows, can use references in a function that also take in
      parameters for how far back the arrows can start (where there will be some randomness).
      The more health you have, the less far back the arrows can start and the game gets more
      difficult. */
      
      /* 
      // arrow pointing to the left
      int left_point_y = rand()%(15-0 + 1) + 0;
      int la_x[10] = {26,25,24,25,26,27,26,25,26,27};
      int la_y[10] = {left_point_y+2,left_point_y+1,left_point_y,left_point_y-1,left_point_y-2,left_point_y+2,left_point_y+1,left_point_y,left_point_y-1,left_point_y-2};
      */
      zl = rand()%(d-0 + 1) + 0;
      la_x[0] = 27 + zl; // reset x location
      la_x[1] = 26 + zl; // reset x location
      la_x[2] = 25 + zl; // reset x location
      la_x[3] = 26 + zl; // reset x location
      la_x[4] = 27 + zl; // reset x location
      la_x[5] = 28 + zl; // reset x location
      la_x[6] = 27 + zl; // reset x location
      la_x[7] = 26 + zl; // reset x location
      la_x[8] = 27 + zl; // reset x location
      la_x[9] = 28 + zl; // reset x location

      left_point_y = rand()%(15-0 + 1) + 0;  // new random y value
      la_y[0] = left_point_y + 2;            // reset y location
      la_y[1] = left_point_y + 1;            // reset y location
      la_y[2] = left_point_y;                // reset y location
      la_y[3] = left_point_y - 1;            // reset y location
      la_y[4] = left_point_y - 2;            // reset y location
      la_y[5] = left_point_y + 2;            // reset y location
      la_y[6] = left_point_y + 1;            // reset y location
      la_y[7] = left_point_y;                // reset y location
      la_y[8] = left_point_y - 1;            // reset y location
      la_y[9] = left_point_y - 2;            // reset y location
    }
    if (la_x[2]==-4) {
      zl = rand()%(d-0 + 1) + 0;
      la_x[0] = 27 + zl; // reset x location
      la_x[1] = 26 + zl; // reset x location
      la_x[2] = 25 + zl; // reset x location
      la_x[3] = 26 + zl; // reset x location
      la_x[4] = 27 + zl; // reset x location
      la_x[5] = 28 + zl; // reset x location
      la_x[6] = 27 + zl; // reset x location
      la_x[7] = 26 + zl; // reset x location
      la_x[8] = 27 + zl; // reset x location
      la_x[9] = 28 + zl; // reset x location

      left_point_y = rand()%(15-0 + 1) + 0;  // new random y value
      la_y[0] = left_point_y + 2;            // reset y location
      la_y[1] = left_point_y + 1;            // reset y location
      la_y[2] = left_point_y;                // reset y location
      la_y[3] = left_point_y - 1;            // reset y location
      la_y[4] = left_point_y - 2;            // reset y location
      la_y[5] = left_point_y + 2;            // reset y location
      la_y[6] = left_point_y + 1;            // reset y location
      la_y[7] = left_point_y;                // reset y location
      la_y[8] = left_point_y - 1;            // reset y location
      la_y[9] = left_point_y - 2;            // reset y location
    }
    la_x[0] = la_x[0] - 1; //increment arrow to the left
    la_x[1] = la_x[1] - 1; //increment arrow to the left
    la_x[2] = la_x[2] - 1; //increment arrow to the left
    la_x[3] = la_x[3] - 1; //increment arrow to the left
    la_x[4] = la_x[4] - 1; //increment arrow to the left
    la_x[5] = la_x[5] - 1; //increment arrow to the left
    la_x[6] = la_x[6] - 1; //increment arrow to the left
    la_x[7] = la_x[7] - 1; //increment arrow to the left
    la_x[8] = la_x[8] - 1; //increment arrow to the left
    la_x[9] = la_x[9] - 1; //increment arrow to the left

    //~-~-~-~-~-~-~-~-~-Up Pointing Arrow~-~-~-~-~-~-~-~-~-
    OutputArrows(ua_x[0],ua_x[1],ua_x[2],ua_x[3],ua_x[4],ua_x[5],ua_x[6],ua_x[7],ua_x[8],ua_x[9],ua_y[0],ua_y[1],ua_y[2],ua_y[3],ua_y[4],ua_y[5],ua_y[6],ua_y[7],ua_y[8],ua_y[9]); //output up pointing arrow
    if ((x==ua_x[0] && y==ua_y[0]) || (x==ua_x[1] && y==ua_y[1]) || (x==ua_x[2] && y==ua_y[2]) || (x==ua_x[3] && y==ua_y[3]) || (x==ua_x[4] && y==ua_y[4]) || (x==ua_x[5] && y==ua_y[5]) || (x==ua_x[6] && y==ua_y[6]) || (x==ua_x[7] && y==ua_y[7]) || (x==ua_x[8] && y==ua_y[8]) || (x==ua_x[9] && y==ua_y[9])) {
      matrix.clearScreen();
      health_bar--;
      matrix.setRotation(0);
      matrix.print("Hlth\n");
      matrix.print(health_bar);
      matrix.writeScreen();
      delay(2000);
      matrix.clearScreen();
      pointsdot_countdown = 30;
      //taking code from stack overflow
      //https://stackoverflow.com/questions/12657962/how-do-i-generate-a-random-number-between-two-variables-that-i-have-stored
      pointsdot_x = rand()%(23-0 + 1) + 0;
      pointsdot_y = rand()%(15-0 + 1) + 0;
      /* reset x and y values of arrows, can use references in a function that also take in
      parameters for how far back the arrows can start (where there will be some randomness).
      The more health you have, the less far back the arrows can start and the game gets more
      difficult. */
      
      /* 
      // arrow pointing up
      int up_point_x = rand()%(23-0 + 1) + 0;
      int ua_x[10] = {up_point_x-2,up_point_x-1,up_point_x,up_point_x+1,up_point_x+2,up_point_x-2,up_point_x-1,up_point_x,up_point_x+1,up_point_x+2};
      int ua_y[10] = {18,17,16,17,18,19,18,17,18,19};
      */
      zu = rand()%(d-0 + 1) + 0;
      ua_y[0] = 18 + zu; // reset y location
      ua_y[1] = 17 + zu; // reset y location
      ua_y[2] = 16 + zu; // reset y location
      ua_y[3] = 17 + zu; // reset y location
      ua_y[4] = 18 + zu; // reset y location
      ua_y[5] = 19 + zu; // reset y location
      ua_y[6] = 18 + zu; // reset y location
      ua_y[7] = 17 + zu; // reset y location
      ua_y[8] = 18 + zu; // reset y location
      ua_y[9] = 19 + zu; // reset y location

      up_point_x = rand()%(23-0 + 1) + 0;  // new random y value
      ua_x[0] = up_point_x + 2;            // reset x location
      ua_x[1] = up_point_x + 1;            // reset x location
      ua_x[2] = up_point_x;                // reset x location
      ua_x[3] = up_point_x - 1;            // reset x location
      ua_x[4] = up_point_x - 2;            // reset x location
      ua_x[5] = up_point_x + 2;            // reset x location
      ua_x[6] = up_point_x + 1;            // reset x location
      ua_x[7] = up_point_x;                // reset x location
      ua_x[8] = up_point_x - 1;            // reset x location
      ua_x[9] = up_point_x - 2;            // reset x location
    }
    if (ua_y[2]==-4) {
      zu = rand()%(d-0 + 1) + 0;
      ua_y[0] = 18 + zu; // reset y location
      ua_y[1] = 17 + zu; // reset y location
      ua_y[2] = 16 + zu; // reset y location
      ua_y[3] = 17 + zu; // reset y location
      ua_y[4] = 18 + zu; // reset y location
      ua_y[5] = 19 + zu; // reset y location
      ua_y[6] = 18 + zu; // reset y location
      ua_y[7] = 17 + zu; // reset y location
      ua_y[8] = 18 + zu; // reset y location
      ua_y[9] = 19 + zu; // reset y location

      up_point_x = rand()%(23-0 + 1) + 0;  // new random y value
      ua_x[0] = up_point_x + 2;              // reset x location
      ua_x[1] = up_point_x + 1;              // reset x location
      ua_x[2] = up_point_x;                  // reset x location
      ua_x[3] = up_point_x - 1;              // reset x location
      ua_x[4] = up_point_x - 2;              // reset x location
      ua_x[5] = up_point_x + 2;              // reset x location
      ua_x[6] = up_point_x + 1;              // reset x location
      ua_x[7] = up_point_x;                  // reset x location
      ua_x[8] = up_point_x - 1;              // reset x location
      ua_x[9] = up_point_x - 2;              // reset x location
    }
    ua_y[0] = ua_y[0] - 1; //increment arrow up
    ua_y[1] = ua_y[1] - 1; //increment arrow up
    ua_y[2] = ua_y[2] - 1; //increment arrow up
    ua_y[3] = ua_y[3] - 1; //increment arrow up
    ua_y[4] = ua_y[4] - 1; //increment arrow up
    ua_y[5] = ua_y[5] - 1; //increment arrow up
    ua_y[6] = ua_y[6] - 1; //increment arrow up
    ua_y[7] = ua_y[7] - 1; //increment arrow up
    ua_y[8] = ua_y[8] - 1; //increment arrow up
    ua_y[9] = ua_y[9] - 1; //increment arrow up


    //~-~-~-~-~-~-~-~-~-Down Pointing Arrow~-~-~-~-~-~-~-~-~-
    OutputArrows(da_x[0],da_x[1],da_x[2],da_x[3],da_x[4],da_x[5],da_x[6],da_x[7],da_x[8],da_x[9],da_y[0],da_y[1],da_y[2],da_y[3],da_y[4],da_y[5],da_y[6],da_y[7],da_y[8],da_y[9]); //output down pointing arrow
    if ((x==da_x[0] && y==da_y[0]) || (x==da_x[1] && y==da_y[1]) || (x==da_x[2] && y==da_y[2]) || (x==da_x[3] && y==da_y[3]) || (x==da_x[4] && y==da_y[4]) || (x==da_x[5] && y==da_y[5]) || (x==da_x[6] && y==da_y[6]) || (x==da_x[7] && y==da_y[7]) || (x==da_x[8] && y==da_y[8]) || (x==da_x[9] && y==da_y[9])) {
      matrix.clearScreen();
      health_bar--;
      matrix.setRotation(0);
      matrix.print("Hlth\n");
      matrix.print(health_bar);
      matrix.writeScreen();
      delay(2000);
      matrix.clearScreen();
      pointsdot_countdown = 30;
      //taking code from stack overflow
      //https://stackoverflow.com/questions/12657962/how-do-i-generate-a-random-number-between-two-variables-that-i-have-stored
      pointsdot_x = rand()%(23-0 + 1) + 0;
      pointsdot_y = rand()%(15-0 + 1) + 0;
      /* reset x and y values of arrows, can use references in a function that also take in
      parameters for how far back the arrows can start (where there will be some randomness).
      The more health you have, the less far back the arrows can start and the game gets more
      difficult. */
      
      /* 
      // arrow pointing down
      int down_point_x = rand()%(23-0 + 1) + 0;
      int da_x[10] = {down_point_x-2,down_point_x-1,down_point_x,down_point_x+1,down_point_x+2,down_point_x-2,down_point_x-1,down_point_x,down_point_x+1,down_point_x+2};
      int da_y[10] = {-3,-2,-1,-2,-3,-4,-3,-2,-3,-4};
      */
      zd = rand()%(d-0 + 1) + 0;
      da_y[0] = -3 - zd; // reset y location
      da_y[1] = -2 - zd; // reset y location
      da_y[2] = -1 - zd; // reset y location
      da_y[3] = -2 - zd; // reset y location
      da_y[4] = -3 - zd; // reset y location
      da_y[5] = -4 - zd; // reset y location
      da_y[6] = -3 - zd; // reset y location
      da_y[7] = -2 - zd; // reset y location
      da_y[8] = -3 - zd; // reset y location
      da_y[9] = -4 - zd; // reset y location

      down_point_x = rand()%(23-0 + 1) + 0;  // new random y value
      da_x[0] = down_point_x + 2;            // reset x location
      da_x[1] = down_point_x + 1;            // reset x location
      da_x[2] = down_point_x;                // reset x location
      da_x[3] = down_point_x - 1;            // reset x location
      da_x[4] = down_point_x - 2;            // reset x location
      da_x[5] = down_point_x + 2;            // reset x location
      da_x[6] = down_point_x + 1;            // reset x location
      da_x[7] = down_point_x;                // reset x location
      da_x[8] = down_point_x - 1;            // reset x location
      da_x[9] = down_point_x - 2;            // reset x location
    }
    if (da_y[2]==19) {
      zd = rand()%(d-0 + 1) + 0;
      da_y[0] = -3 - zd; // reset y location
      da_y[1] = -2 - zd; // reset y location
      da_y[2] = -1 - zd; // reset y location
      da_y[3] = -2 - zd; // reset y location
      da_y[4] = -3 - zd; // reset y location
      da_y[5] = -4 - zd; // reset y location
      da_y[6] = -3 - zd; // reset y location
      da_y[7] = -2 - zd; // reset y location
      da_y[8] = -3 - zd; // reset y location
      da_y[9] = -4 - zd; // reset y location

      down_point_x = rand()%(23-0 + 1) + 0;  // new random y value
      da_x[0] = down_point_x + 2;              // reset x location
      da_x[1] = down_point_x + 1;              // reset x location
      da_x[2] = down_point_x;                  // reset x location
      da_x[3] = down_point_x - 1;              // reset x location
      da_x[4] = down_point_x - 2;              // reset x location
      da_x[5] = down_point_x + 2;              // reset x location
      da_x[6] = down_point_x + 1;              // reset x location
      da_x[7] = down_point_x;                  // reset x location
      da_x[8] = down_point_x - 1;              // reset x location
      da_x[9] = down_point_x - 2;              // reset x location
    }
    da_y[0] = da_y[0] + 1; //increment arrow down
    da_y[1] = da_y[1] + 1; //increment arrow down
    da_y[2] = da_y[2] + 1; //increment arrow down
    da_y[3] = da_y[3] + 1; //increment arrow down
    da_y[4] = da_y[4] + 1; //increment arrow down
    da_y[5] = da_y[5] + 1; //increment arrow down
    da_y[6] = da_y[6] + 1; //increment arrow down
    da_y[7] = da_y[7] + 1; //increment arrow down
    da_y[8] = da_y[8] + 1; //increment arrow down
    da_y[9] = da_y[9] + 1; //increment arrow down
    
    // determine difficulty of game
    d = 100 - points_counter*points_counter - 18;

    if (health_bar==0) {
      matrix.setRotation(0);
      matrix.clearScreen();
      matrix.setCursor(0, 0); 
      matrix.print("Game\nOver");
      matrix.writeScreen();
      delay(5000);
      break;
    }

    if (points_counter==10) {
      matrix.setRotation(0);
      matrix.clearScreen();
      matrix.setCursor(0, 0); 
      matrix.print("You\nWin!");
      matrix.writeScreen();
      delay(5000);
      break;  
    }
    
    matrix.writeScreen();
    if (b_1 == LOW) {
      break;
    }
    delay(50); 
  }  
}

void OutputArrows(int x0,int x1,int x2,int x3,int x4,int x5,int x6,int x7,int x8,int x9,int y0,int y1,int y2,int y3,int y4,int y5,int y6,int y7,int y8,int y9) {
  matrix.setPixel(x0,y0);
  matrix.setPixel(x1,y1);
  matrix.setPixel(x2,y2);
  matrix.setPixel(x3,y3);
  matrix.setPixel(x4,y4);
  matrix.setPixel(x5,y5);
  matrix.setPixel(x6,y6);
  matrix.setPixel(x7,y7);
  matrix.setPixel(x8,y8);
  matrix.setPixel(x9,y9);
}

void Maze() {
  int r = 0;
  while (r < 1) {
    matrix.writeScreen();
    displaymaze();
    moveDot();
    delay(100);
    if(x == 21 and y == 15) {
      matrix.clearScreen();
      matrix.setCursor(1, 1);
      matrix.setRotation(0);
      matrix.print("You Win!");
      matrix.writeScreen();
      delay(5000);
      x = 1;
      y = 1;
      matrix.clearScreen();    
  }
  }
}

void moveDot() {

  int r = 0; //for while loop
  //while (r < 1) {
    X = analogRead(A0);  // read the A0 input pin
    Y = analogRead(A1);  // read the A1 input pin
    //Read input from joystick and check if position ahead is a wall
    //Move only if it isn't a wall
    //Right 
    if (X > 750 && abs(Y) < 650 && checkvalid(x+1,y) ) {
      //x--;
      x++;
    }
    //Left
    else if (X < 250 && abs(Y) < 650 && checkvalid(x-1,y) ) {
      //x++;
      x--;
    }
    //Up
    else if (Y > 750 && abs(X) < 650 && checkvalid(x,y-1) ) {
      //y++;
      y--;
    }
    //Down
    else if (Y < 250 && abs(X) < 650 && checkvalid(x,y+1) ) {
      //y--;
      y++;
    }
    //Out of bound check
    if (x <= 0) {
      x = 0;
    }    
    if (y <= 0) {
      y = 0;
    }
    if (x >= 24) {
      x = 23;
    }   
    if (y >= 16) {
      y = 15;
    } 
    matrix.setPixel(x, y);
    
    matrix.writeScreen();
    matrix.clrPixel(x, y);
    
  //}
}

void displaymaze() {    
  for (int y = 0; y < maze_width; y++)  {
    for (int x = 0; x < maze_length; x++) {
        if (maze[y][x] == 1) {
          matrix.setPixel(x, y);
      }
    }        
  }
}

bool checkvalid(int x, int y) {
  Serial.print("Checking position: ");
  Serial.print(x);
  Serial.print(",");
  Serial.println(y);
    
  if(maze[y][x] == 1) {
    Serial.println("Is a wall"); 
    return false;
  }
  Serial.println("Open path");
  return true;  
}

void loop() {
  matrix.setRotation(0);
  matrix.clearScreen();
  matrix.setCursor(0, 0);
  b_1 = digitalRead(button_1);
  b_2 = digitalRead(button_2);
  X = analogRead(A0);  // read the A0 input pin
  Y = analogRead(A1);  // read the A1 input pin 
  if (X > 700) {
    menu_val++;
    if (menu_val > 2) {
      menu_val = 2;
    }
  }
  
  if (X < 300) {
    menu_val--;
    if (menu_val < 0) {
      menu_val = 0;
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
  if (menu_val == 2) {
    matrix.print("Maze");
    if (menu_sel == 1) {
      matrix.clearScreen();
      matrix.setCursor(0, 0);
      matrix.print("Maze\nGame");
      matrix.writeScreen();
      delay(5000);
      Maze();
    }
  }
  matrix.writeScreen();
  delay(250);
}
