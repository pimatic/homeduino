# Uses Arduino.mk https://github.com/sudar/Arduino-Makefile
BOARD_TAG    = nano328
ARDUINO_LIBS = SerialCommand RFControl Keypad DHTlib
USER_LIB_PATH := $(realpath ./libraries)
MONITOR_PORT  = /dev/ttyUSB0

ARDMK_DIR := $(realpath ./arduino-mk)
include $(ARDMK_DIR)/Arduino.mk
