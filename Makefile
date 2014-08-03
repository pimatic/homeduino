# Uses Arduino.mk https://github.com/sudar/Arduino-Makefile
BOARD_TAG    = nano328
ARDUINO_LIBS = SerialCommand RFControl Keypad DHTlib
USER_LIB_PATH = ./libraries
MONITOR_PORT  = /dev/ttyUSB0

include /usr/share/arduino/Arduino.mk
