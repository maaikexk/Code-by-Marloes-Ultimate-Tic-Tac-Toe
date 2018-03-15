//PROGRAMMING END ASSIGMENT module 6: ultimate tic tac toe in arcede machine
// Maaike keurhorst Marloes ten Hage
// januari 2018
// lasercut design based on http://www.instructables.com/id/Mini-Pi-Powered-Arcade-Machine/
//============================================================================================================================================================================================
#include "FastLED.h"

//Disable/ enable AI player
const bool CPLAYER = true;
const bool CHECKWINNER = false;

//In which part of the game are you
int state = 0;

//Joystick constants
const int JSDOWN = 1;
const int JSRIGHT = 2;
const int JSUP = 3;
const int JSLEFT = 4;
const int JSNOCHOICE = 0;

//color constants
const int NOCOLOR = 0;
const int COLORRED = 1;
const int COLORAI = 2;    //AI player
const int COLORFIRSTLED = 3;
const int COLORHP = 4;    //HP player
const int COLORAICHOOSE = 5;    //AI Player chooses
const int COLORSEPARATOR = 6;

//The size of the 2 arrays (blocks and seporators)
const int NUMBLOCKLEDS = 81;
const int NUMSEPLEDS = 40;

//used to decected change in Joystick
int currentJSChoice = 0;
int prevJSChoice = 0;

//The grid the human player can play in
int currentHPGrid = 1;
int currentHPLed = 1;

bool newButtonPressed = false;

//Global variables for the incomming data from the AI player
int aiGrid = 0;
int aiLed = 0;
int aiNewGrid = 0;
//Leds:

// How many leds are in the strip?
#define NUM_LEDS1 150
#define NUM_LEDS2 30
#define NUM_SQUARE 9

// Data pin that led data will be written out over
#define DATA_PIN1 6
#define DATA_PIN2 7

// This is an array of leds.  One item for each led in your strip.
CRGB leds1[NUM_LEDS1];
CRGB leds2[NUM_LEDS2];

//0 = the grid number; 1 = the subgrid number; 2 = string number; 3 = the lednumber; 4 = the color (0 = off)
int blocks[81][5] = {{1, 1, 1, 149, 0}, {1, 2, 1, 104, 0}, {1, 3, 1, 100, 0}, {1, 4, 1, 148, 0}, {1, 5, 1, 105, 0}, {1, 6, 1, 99, 0}, {1, 7, 1, 147, 0}, {1, 8, 1, 106, 0}, {1, 9, 1, 98, 0},
  {2, 1, 1, 73, 0},  {2, 2, 1, 70, 0},  {2, 3, 1, 44, 0},  {2, 4, 1, 74, 0},  {2, 5, 1, 69, 0},  {2, 6, 1, 45, 0}, {2, 7, 1, 75, 0},  {2, 8, 1, 68, 0},  {2, 9, 1, 46, 0},
  {3, 1, 1, 40, 0},  {3, 2, 1, 13, 0},  {3, 3, 1, 10, 0},  {3, 4, 1, 39, 0},  {3, 5, 1, 14, 0},  {3, 6, 1, 9, 0},  {3, 7, 1, 38, 0},  {3, 8, 1, 15, 0},  {3, 9, 1, 8, 0},
  {4, 1, 1, 145, 0}, {4, 2, 1, 108, 0}, {4, 3, 1, 96, 0},  {4, 4, 1, 144, 0}, {4, 5, 1, 109, 0}, {4, 6, 1, 95, 0}, {4, 7, 1, 143, 0}, {4, 8, 1, 110, 0}, {4, 9, 1, 94, 0},
  {5, 1, 1, 77, 0},  {5, 2, 1, 66, 0},  {5, 3, 1, 48, 0},  {5, 4, 1, 78, 0},  {5, 5, 1, 65, 0},  {5, 6, 1, 49, 0}, {5, 7, 1, 79, 0},  {5, 8, 1, 64, 0},  {5, 9, 1, 50, 0},
  {6, 1, 1, 36, 0},  {6, 2, 1, 17, 0},  {6, 3, 1, 6, 0},   {6, 4, 1, 35, 0},  {6, 5, 1, 18, 0},  {6, 6, 1, 5, 0},  {6, 7, 1, 34, 0},  {6, 8, 1, 19, 0},  {6, 9, 1, 4, 0},
  {7, 1, 1, 141, 0}, {7, 2, 1, 112, 0}, {7, 3, 1, 92, 0},  {7, 4, 1, 140, 0}, {7, 5, 1, 113, 0}, {7, 6, 1, 91, 0}, {7, 7, 1, 139, 0}, {7, 8, 1, 114, 0}, {7, 9, 1, 90, 0},
  {8, 1, 1, 81, 0},  {8, 2, 1, 62, 0},  {8, 3, 1, 52, 0},  {8, 4, 1, 82, 0},  {8, 5, 1, 61, 0},  {8, 6, 1, 53, 0}, {8, 7, 1, 83, 0},  {8, 8, 1, 60, 0},  {8, 9, 1, 54, 0},
  {9, 1, 1, 32, 0},  {9, 2, 1, 21, 0},   {9, 3, 1, 2, 0},  {9, 4, 1, 31, 0},  {9, 5, 1, 22, 0},  {9, 6, 1, 1, 0},  {9, 7, 1, 30, 0},  {9, 8, 1, 23, 0},  {9, 9, 1, 0, 0}
};

//0 = the string number; 1 = the led number; 2 = the adjecent grid to the left;  3 = the adjecent grid to the button; 4 = the adjecent grid to the right;
// 5 = the adjecent grid to the top; 6= the color (0 = off);
int seperators[40][7] =    {{2, 17, 6, 1, 0, 2, 0},  {2, 10, 6, 2, 0, 3, 0},  {2, 18, 6, 1, 0, 2, 0}, {2, 9, 6, 2, 0, 3, 0},  {2, 19, 6, 1, 0, 2, 0},  {2, 8, 6, 2, 0, 3, 0},
  {1, 146, 6, 1, 4, 0, 0}, {1, 107, 6, 1, 4, 0, 0}, {1, 97, 6, 1, 4, 0, 0}, {2, 20, 6, 1, 4, 5, 2}, {1, 76, 6, 0, 5, 0, 2},  {1, 67, 6, 0, 5, 0, 2},
  {1, 47, 6, 0, 5, 0, 2},  {2, 7, 6, 5, 6, 3, 2},   {1, 37, 6, 0, 6, 0, 3}, {1, 16, 6, 0, 6, 0, 3}, {1, 7, 6, 0, 6, 0, 3},   {2, 21, 6, 4, 0, 5, 0},
  {2, 6, 6, 5, 0, 6, 0},   {2, 22, 6, 4, 0, 5, 0},  {2, 5, 6, 5, 0, 6, 0},  {2, 23, 6, 4, 0, 5, 0}, {2, 4, 6, 5, 0, 6, 0}, {1, 142, 6, 0, 7, 0, 4}, {1, 111, 6, 0, 7, 0, 4},
  {1, 93, 6, 0, 7, 0, 4},  {2, 24, 6, 4, 7, 8, 5},  {1, 80, 6, 0, 8, 0, 5}, {1, 63, 6, 0, 8, 0, 5}, {1, 51, 6, 0, 8, 0, 5},  {2, 3, 6, 5, 8, 9, 6},
  {1, 33, 6, 0, 9, 0, 6},  {1, 20, 6, 0, 9, 0, 6},  {1, 3, 6, 0, 9, 0, 6},  {2, 25, 6, 7, 0, 8, 0}, {2, 2, 6, 8, 0, 9, 0},   {2, 26, 6, 7, 0, 8, 0},
  {2, 1, 6, 8, 0, 9, 0},   {2, 27, 6, 7, 0, 8, 0},  {2, 0, 6, 8, 0, 9, 0}
};

void setup() {
  Serial.begin(9600);
  // sanity check delay - allows reprogramming if accidently blowing power w/leds
  delay(2000);

  //initialize the 2 leds strips
  FastLED.addLeds<WS2812, DATA_PIN1, RGB>(leds1, NUM_LEDS1);
  FastLED.addLeds<WS2812, DATA_PIN2, RGB>(leds2, NUM_LEDS2);
  // FastLED.addLeds<WS2812, DATA_PIN, RGB>(left_upper, 3);

  FastLED.setBrightness(100);
  FastLED.clear();

  pinMode(2, INPUT_PULLUP); //down
  pinMode(3, INPUT_PULLUP); //right
  pinMode(4, INPUT_PULLUP); // up
  pinMode(5, INPUT_PULLUP); //left
  pinMode(8, INPUT_PULLUP); //Button

  //show first grid als default grid
  setColorSeperator(1, COLORRED);
}

void loop() {
  switch (state) {
    //Human player chooses grid & is displayed
    case 0:
      state = procesState0();
      break;
    // Human player chooses led en displayed it
    case 1:
      state = procesState1();
      break;
    //check if the grid is full
    case 2:
      state = procesState2();
      break;
    //Ai player turn
    case 3:
      state = procesState3();
      break;
  }


  //Set the LEDS-tables
  fillLeds();
  FastLED.show();

}

//Human player chooses a grid and sets first LED in the chosen grid;
int procesState0() {
  // Serial.println("IN state 0");
  int newState = 0;
  int newGrid;
  int localHPGrid = currentHPGrid;
  currentJSChoice = joyStickChoose();

  //check if there is a new movement of the joystick
  if (currentJSChoice != prevJSChoice && currentJSChoice != JSNOCHOICE) {
    newButtonPressed = false;
    //loop through the 9 grids and check if it is valid grid to choose;
    for (int i = 0; i < 9; i++) {
      newGrid = getNextGrid(currentJSChoice, localHPGrid);
      if (!isGridFull(newGrid)) {
        break;
      } else {
        localHPGrid = newGrid;
      };
    }
    if (newGrid != currentHPGrid) {
      setColorSeperator(newGrid, COLORRED);
      currentHPGrid = newGrid;
    }
  }
  prevJSChoice = currentJSChoice;
  //go to next state and set the first led in the chosen grid
  if (buttonPressed()) {
    currentHPLed = setFirstLed(currentHPGrid, COLORFIRSTLED);
    newState = 1;
  }
  return newState;
}

//Human player LED choose
int procesState1() {
  int newState = 1;
  int newLed;
  int localHPLed = currentHPLed;
  currentJSChoice = joyStickChoose();

  //detect movement of the joystick
  if (currentJSChoice != prevJSChoice && currentJSChoice != JSNOCHOICE) {
    newButtonPressed = false; //New button may be pressed
    //loop through the 9 leds in the grid and see if it is valid LED
    for (int i = 0; i < 9; i++) {
      newLed = getNextGrid(currentJSChoice, localHPLed);

      if (getBlockValue(currentHPGrid, newLed, 3) == NOCOLOR) {
        break;
      } else {
        localHPLed = newLed;
      }
    }

    //if gone to next LED turn off prev and turn on new LED
    setBlockValue(currentHPGrid, currentHPLed, 3, NOCOLOR);
    setBlockValue(currentHPGrid, newLed, 3, COLORFIRSTLED);
    currentHPLed = newLed;
  }

  prevJSChoice = currentJSChoice;

  if (buttonPressed()) {
    //HP Made a choice
    setBlockValue(currentHPGrid, currentHPLed, 3, COLORHP);
    checkWinner();
    //Set grey leds for gridchoise AI
    setColorSeperator(currentHPLed, COLORAICHOOSE);

    //tell AI which move is done
    Serial.print(currentHPGrid);
    Serial.println(currentHPLed);
    newState = 2;
    //newState = 3;

  }
  return newState;
}

// check if grid is full
int procesState2() {
  int newState = 2;
  String winningField;
  if (Serial.available() > 0) {
    winningField = Serial.readString();
    //Serial.println(aiInput);

    if (winningField.length() == 2) {
      //  Serial.println("hoi ik ben hier");
      int player = winningField.charAt(1) - 48;
      int grid = winningField.charAt(0) - 48;
      setWinningField(grid, player);

      if (player == 1) {
        newState = 3;
      } else {
        newState = 1;
      }
      if (grid != 0) {
        if (currentHPGrid == grid) {
          if (player == 1) {
            newState = 3;
          } else {
            newState = 0;
          }
        }
      }

    }
  }
  // Serial.println(newState);
  // Serial.println(winningField);
  return newState;
}


// Ai player output and color the led
int procesState3() {
  Serial.println("00");
  int newState = 3;
  String aiInput;
  //String winningField;

  //so that you can play without ai
  if (CPLAYER == false) {
    return playArduino();
  }
  //AI input
  int i = 0;
  while (i == 0) {
    if (Serial.available() > 0) {
      aiInput = Serial.readString();

      // Serial.println("00");

      if (aiInput.length() == 2) {
        Serial.println(aiInput);
        newState = 2;
        i = 1;
        aiGrid = aiInput.charAt(0) - 48;
        aiLed = aiInput.charAt(1) - 48;
        aiNewGrid = aiInput.charAt(1) - 48;

        //Computer playes
        setBlockValue(aiGrid, aiLed, 3, COLORAI);
        checkWinner();

        //New grid for HP
        currentHPGrid = aiNewGrid;
        setColorSeperator(currentHPGrid, COLORRED);
        currentHPLed = setFirstLed(currentHPGrid, COLORFIRSTLED);
        newState = 2;
        //newState = 1;
      }
    }
    //Grid full, state 0; HP chooses grid
    if (isGridFull(currentHPGrid) ) {
      newState = 0;
    }
  }

  return newState;
}

//Detects the movement of the joyStick
int joyStickChoose() {
  int buttonState2 = digitalRead(2);
  int buttonState3 = digitalRead(3);
  int buttonState4 = digitalRead(4);
  int buttonState5 = digitalRead(5);

  if (buttonState2 == LOW && buttonState3 == HIGH && buttonState4 == HIGH && buttonState5 == HIGH) {
    return JSDOWN;
  }
  if (buttonState2 == HIGH && buttonState3 == LOW && buttonState4 == HIGH && buttonState5 == HIGH) {
    return JSRIGHT;
  }
  if (buttonState2 == HIGH && buttonState3 == HIGH && buttonState4 == LOW && buttonState5 == HIGH) {
    return JSUP;
  }
  if (buttonState2 == HIGH && buttonState3 == HIGH && buttonState4 == HIGH && buttonState5 == LOW) {
    return JSLEFT;
  }
  return JSNOCHOICE;
}

//check if a Grid full is
bool isGridFull(int grid) {

  for (int i = 0; i < NUMBLOCKLEDS; i++) {

    if (blocks[i][0] == grid) {
      for (int j = 1; j < 10; j++) {
        if (getBlockValue(blocks[i][0], j, 3) == NOCOLOR) {
          return false;
        }
      }
    }
  }
  return true;
}


//get the value out of the block array
// fieldnum 1 = stringnr
// fieldnum 2 = lednr
// fieldnum 3 = color
int getBlockValue(int gridId, int ledId, int fieldNum) {
  for (int i = 0; i < 81; i++) {
    if (blocks[i][0] == gridId && blocks[i][1] == ledId) {
      return blocks[i][fieldNum + 1];
    }
  }
}

//choose the next grid depending on the current grid and the movement of the joystick
int getNextGrid(int choice, int current) {
  int newGrid = 0;

  switch (choice) {
    case JSRIGHT:
      if (current == 9) {
        newGrid = 1;
      } else {
        newGrid = current + 1;
      }
      break;
    case JSLEFT:
      if (current == 1) {
        newGrid = 9;
      } else {
        newGrid = current - 1;
      }
      break;
    case JSDOWN:
      newGrid = current + 3;
      switch (newGrid) {
        case 10:
          newGrid = 2;
          break;
        case 11:
          newGrid = 3;
          break;
        case 12:
          newGrid = 1;
          break;
      }
      break;
    case JSUP:

      newGrid = current - 3;
      if (newGrid < 1) {
        newGrid = newGrid + 11;
      }
      break;
  }

  return newGrid;
}

//decide which seperator lines should be on depeding the grid and color
void setColorSeperator(int grid, int color) {
  //Set the color of grid-seperator
  for (int i = 0; i < NUMSEPLEDS; i++) {
    // Default uit
    seperators[i][2] = COLORSEPARATOR; //CRGB::Black;

    for (int j = 3; j < 7; j++) {

      //Huidig grid?
      if (seperators[i][j] == grid) {
        seperators[i][2] = color; //color;
        break;
      }
    }

  }
}

//Fill all the leds with the right color;
void fillLeds() {
  int stringNr;
  int ledNr;
  int kleurNr;

  //Set led-table for blocks

  for (int i = 0; i < NUMBLOCKLEDS; i++) {
    stringNr = blocks[i][2];
    ledNr = blocks[i][3];
    kleurNr =  blocks[i][4];
    if (stringNr == 1) { //String 1
      switch (kleurNr) {
        case NOCOLOR:
          leds1[ledNr] = CRGB::Black;
          break;
        case COLORRED:
          leds1[ledNr] = CRGB::Blue;
          break;
        case COLORAI:
          leds1[ledNr] = CRGB::Red;
          break;
        case COLORHP:
          leds1[ledNr] = CRGB::Green;
          break;
        case COLORFIRSTLED:
          leds1[ledNr] = CRGB::White;
          break;
        case COLORAICHOOSE:
          leds1[ledNr] = CRGB::Grey;
          break;
      }

    }
    //Set led-table for seperators
    for (int i = 0; i < NUMSEPLEDS; i++) {
      stringNr = seperators[i][0];
      ledNr = seperators[i][1];
      kleurNr =  seperators[i][2];
      if (stringNr == 1) { //String 1
        switch (kleurNr) {
          case NOCOLOR:
            leds1[ledNr] = CRGB::Black;
            break;
          case COLORRED:
            leds1[ledNr] = CRGB::Blue;
            break;
          case COLORAI:
            leds1[ledNr] = CRGB::Red;
            break;
          case COLORHP:
            leds1[ledNr] = CRGB::Green;
            break;
          case COLORFIRSTLED:
            leds1[ledNr] = CRGB::White;
            break;
          case COLORAICHOOSE:
            leds1[ledNr] = CRGB(0, 255, 143);
            break;
          case COLORSEPARATOR:
            leds1[ledNr] =  CRGB(71, 71, 71);
            break;
        }

      } else {      //String 2
        switch (kleurNr) {
          case NOCOLOR:
            leds2[ledNr] = CRGB::Black;
            break;
          case COLORRED:
            leds2[ledNr] = CRGB::Blue;
            break;
          case COLORAI:
            leds2[ledNr] = CRGB::Red;
            break;
          case COLORHP:
            leds2[ledNr] = CRGB::Green;
            break;
          case COLORFIRSTLED:
            leds2[ledNr] = CRGB::White;
            break;
          case COLORAICHOOSE:
            leds2[ledNr] = CRGB(0, 255, 143);
            break;
          case COLORSEPARATOR:
            leds2[ledNr] =  CRGB(71, 71, 71);
            break;
        }
      }

    }
  }
}

//if the button is pressed return true
bool buttonPressed() {
  int button;

  button = digitalRead(8);

  if (button == HIGH && newButtonPressed == false ) {
    // Reset pin 8 (Button)
    pinMode(8, OUTPUT); //Button
    digitalWrite(8, LOW);
    pinMode(8, INPUT_PULLUP); //Button
    newButtonPressed = true;
    return true;
  }

  return false;
}

//indicates the first led in the grid you have chosen
int  setFirstLed(int grid, int color) {
  for (int i = 1; i < 10; i++) {

    if (getBlockValue(grid, i, 3) == NOCOLOR) {
      setBlockValue(grid, i, 3, color);
      return i;
    }
  }
}


//when a field is won set all the leds of that grid to the players color
int  setWinningField(int grid, int player) {
  int color;
  if (player == 1) {
    color = COLORHP;
  } else if (player == 2) {
    color = COLORAI;
  } else {
    return 0;
  }
  for (int i = 1; i < 10; i++) {
    setBlockValue(grid, i, 3, color);
  }
}


// change the value of the block array with:
// fieldnum 1 = stringnr
// fieldnum 2 = lednr
// fieldnum 3 = color
void setBlockValue(int gridId, int ledId, int fieldNum, int newValue) {

  for (int i = 0; i < 81; i++) {
    if (blocks[i][0] == gridId && blocks[i][1] == ledId) {
      blocks[i][fieldNum + 1] = newValue;
      break;
    }
  }
}

//if you want to play against a random player
int playArduino() {

  //Play Arduino
  int newState;
  int newGrid = currentHPLed;

  for (int i = 1; i < 10; i++) {
    //Find new block for computer
    if (!isGridFull(newGrid)) {
      break;
    } else {
      newGrid = getNextGrid(JSRIGHT, newGrid);
    }
  }

  //Find new lednr
  int newLed;
  newLed = random(1, 10);
  for (int i = 1; i < 10; i++) {
    if (getBlockValue(newGrid, newLed, 3) == NOCOLOR) {
      break;
    } else {
      newLed = getNextGrid(JSRIGHT, newLed);
    }
  }
  //Computer plays
  setBlockValue(newGrid, newLed, 3, COLORAI);
  checkWinner();

  //New block for HP
  newGrid = newLed;
  for (int i = 1; i < 10; i++) {
    //Find new block for HP
    if (!isGridFull(newGrid)) {
      break;
    } else {
      newGrid = getNextGrid(JSRIGHT, newGrid);
    }
  }
  //Let HP play with new Grid
  currentHPGrid = newGrid;
  setColorSeperator(currentHPGrid, COLORRED);
  currentHPLed = setFirstLed(currentHPGrid, COLORFIRSTLED);

  newState = 1;
  return newState;
}

void checkWinner() {
  //Check if we have a winner);
  if (CHECKWINNER == false) {
    return;
  }

  int l1;
  int l2;
  int l3;
  int l4;
  int l5;
  int l6;
  int l7;
  int l8;
  int l9;
  for (int i = 1; i < 10; i++) {
    l1 = getBlockValue(i, 1, 3);
    l2 = getBlockValue(i, 2, 3);
    l3 = getBlockValue(i, 3, 3);
    l4 = getBlockValue(i, 4, 3);
    l5 = getBlockValue(i, 5, 3);
    l6 = getBlockValue(i, 6, 3);
    l7 = getBlockValue(i, 7, 3);
    l8 = getBlockValue(i, 8, 3);
    l9 = getBlockValue(i, 9, 3);
    if ( l1 == l2 && l2 == l3 && l1 != NOCOLOR) {
      setWinner(i, l1);
      break;
    }
    if         ( l4 == l5 && l5 == l6 && l4  != NOCOLOR) {
      setWinner(i, l4);
      break;

    }
    if         ( l7 == l8 && l8 == l9 && l7 != NOCOLOR ) {
      setWinner(i, l7);
      break;

    }
    if         ( l1 == l4 && l4 == l7 && l1  != NOCOLOR ) {
      setWinner(i, l1);
      break;

    }
    if         ( l2 == l2 && l2 == l8 && l2 != NOCOLOR ) {
      setWinner(i, l2);
      break;

    }
    if         ( l3 == l6 && l6 == l9 && l3 != NOCOLOR ) {
      setWinner(i, l3);
      break;
    }
    if         ( l1 == l5 && l5 == l9 && l1  != NOCOLOR ) {
      setWinner(i, l1);
      break;

    }
    if    ( l3 == l5 && l7 == l9 && l3 != NOCOLOR ) {
      setWinner(i, l3);
      break;
    }
  }
}
// this is needed for the random player
void setWinner(int grid, int color) {
  for (int i = 1; i < 10; i++) {
    setBlockValue(grid, i, 3, color);
  }
}

