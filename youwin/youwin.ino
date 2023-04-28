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
int maze_animation_counter = 0;

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
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},  
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
/*
void Game1() {
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
*/
void displaymaze() {    
  for (int y = 0; y < maze_width; y++)  {
    for (int x = 0; x < maze_length; x++) {
        if (maze[y][x] == 1) {
          matrix.setPixel(x, y);
      }
    }        
  }
}
void loop() {
  matrix.setRotation(0);
  matrix.clearScreen();
  matrix.setCursor(0, 0);
  displaymaze();
/*
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
  */
  matrix.writeScreen();
  delay(150);
  if (maze_animation_counter == 1) {
    int maze[maze_width][maze_length] = {
    {0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0},
    {1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},  
    };  
  }
  if (maze_animation_counter == 2) {
    int maze[maze_width][maze_length] = {

  }
  if (maze_animation_counter == 3) {
    int maze[maze_width][maze_length] = {

  }
  if (maze_animation_counter == 4) {
    int maze[maze_width][maze_length] = {

  }
  if (maze_animation_counter == 5) {
    int maze[maze_width][maze_length] = {

  }
  if (maze_animation_counter == 6) {
    int maze[maze_width][maze_length] = {

  }
  if (maze_animation_counter == 7) {
    int maze[maze_width][maze_length] = {

  }
  maze_animation_counter++;
}
