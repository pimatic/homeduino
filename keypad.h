/*4x4 Matrix Keypad connected to Arduino
 This code prints the key pressed on the keypad to the serial port*/

#include <Keypad.h>

const byte numRows=4; //number of rows on the keypad
const byte numCols=4; //number of columns on the keypad

//keymap defines the key pressed according to the row and columns just as appears on the keypad
char keymap[numRows][numCols]= 
{
  {'1', '2', '3', 'A'}, 
  {'4', '5', '6', 'B'}, 
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

//Code that shows the the keypad connections to the arduino terminals
byte rowPins[numRows] = {12,11,10,9}; //Rows 0 to 3
byte colPins[numCols]= {8,7,6,5}; //Columns 0 to 3

//initializes an instance of the Keypad class
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);


void keypad_setup() {

}

void keypad_loop() {
  char keypressed = myKeypad.getKey();
  if (keypressed != NO_KEY) {
    Serial.print("KP ");
    Serial.write(keypressed);
    Serial.write('\n');
  }
}
