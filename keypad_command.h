/*4x4 Matrix Keypad connected to Arduino
 This code prints the key pressed on the keypad to the serial port*/

#include <Keypad.h>


Keypad* myKeypad = NULL;

void keypad_command(){
  if(myKeypad != NULL) {
    Serial.print("ERR\r\n");
    return;
  }

  const byte numRows=4; //number of rows on the keypad
  const byte numCols=4; //number of columns on the keypad

  //keymap defines the key pressed according to the row and columns just as appears on the keypad
  char* keymap = new char[numRows*numCols];
  keymap[numRows*0+0] = '1'; 
  keymap[numRows*0+1] = '2';
  keymap[numRows*0+2] = '3';
  keymap[numRows*0+3] = 'A';

  keymap[numRows*1+0] = '4'; 
  keymap[numRows*1+1] = '5';
  keymap[numRows*1+2] = '6';
  keymap[numRows*1+3] = 'B';

  keymap[numRows*2+0] = '7'; 
  keymap[numRows*2+1] = '8';
  keymap[numRows*2+2] = '9';
  keymap[numRows*2+3] = 'C';

  keymap[numRows*3+0] = '*'; 
  keymap[numRows*3+1] = '0';
  keymap[numRows*3+2] = '#';
  keymap[numRows*3+3] = 'D';

  // keymap = {
  //   {'1', '2', '3', 'A'}, 
  //   {'4', '5', '6', 'B'}, 
  //   {'7', '8', '9', 'C'},
  //   {'*', '0', '#', 'D'}
  // };

  //Code that shows the the keypad connections to the arduino terminals
  byte* rowPins = new byte[numRows];
  rowPins[0] = 12;
  rowPins[1] = 11;
  rowPins[2] = 10;
  rowPins[3] = 9; 

  // rowPins = {12,11,10,9}; //Rows 0 to 3
  byte* colPins = new byte[numCols];
  colPins[0] = 8;
  colPins[1] = 7;
  colPins[2] = 6;
  colPins[3] = 5;

  // colPins= {8,7,6,5}; //Columns 0 to 3

  //initializes an instance of the Keypad class
  myKeypad = new Keypad(keymap, rowPins, colPins, numRows, numCols);
  Serial.print("ACK\r\n");
}

void keypad_loop() {
  if(myKeypad == NULL) {
    return;
  }
  char keypressed = myKeypad->getKey();
  if (keypressed != NO_KEY) {
    Serial.print("KP ");
    Serial.write(keypressed);
    Serial.print("\r\n");
  }
}
