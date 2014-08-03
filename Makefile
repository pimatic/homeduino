# Uses Arduino.mk https://github.com/sudar/Arduino-Makefile
BOARD_TAG    = nano328
ARDUINO_LIBS = SerialCommand RFControl Keypad
USER_LIB_PATH = ./libraries

include /usr/share/arduino/Arduino.mk
