#include "Adafruit_HT1632.h"
#define HT_DATA 3
#define HT_WR   4
#define HT_CS   5
#define maze_length 24
#define maze_width 16

//joystick values
int X = 0;  // variable to store the value read
int Y = 0;  // variable to store the value read
//Startign values for player
int x = 1;
int y = 1;

Adafruit_HT1632LEDMatrix matrix = Adafruit_HT1632LEDMatrix(HT_DATA, HT_WR, HT_CS);

int maze[maze_width][maze_length] = {
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
{1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1},
{1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1},
{1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1},
{1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
{1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1},
{1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
{1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1},
{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
{1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1},
{1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 
};

//start_row, start_col = 1,1
//end_row, end_col = .

void setup() {
  // put your setup code here, to run once:
  matrix.begin(ADA_HT1632_COMMON_16NMOS);
}

void displaymaze() {
  for (int y = 0; y < maze_width; y++) {
    for (int x = 0; x < maze_length; x++) {
      if (maze[y][x] == 1) {
        matrix.setPixel(x, y);
      }
    }        
  }
}

void loop() {
  // put your main code here, to run repeatedly
  matrix.writeScreen();
  displaymaze();
  moveDot();
  delay(50);  
}

bool checkvalid(int x, int y) {
  if(maze[x][y] == 1) {
    return false;
  }
  return true;  
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