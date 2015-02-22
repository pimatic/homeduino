homeduino
=========

Arduino library for home automation. The Library can be used on a Arduino compatible board for home automation task via serial connection and in combination with [pimatic](https://github.com/pimatic/pimatic) and the [pimatic-homeduino](https://github.com/pimatic/pimatic-homeduino) plugin.


Flashing
--------

You can eithter import all libraries in `libraries` into your Arduino IDE and open the `homeduino.ino` sketch or you can compile and flash using the `Makefile` (recommended).

The Makefile uses [Arduino.mk](https://github.com/sudar/Arduino-Makefile). Because the arduino-mk version that comes with raspbian on the raspberry pi is to old, 
arduino-mk comes bundled as git submpodule with this repository.

```bash
sudo apt-get install arduino-core avr-libc avrdude binutils-avr gcc-avr libconfig-yaml-perl libftdi1 libyaml-perl screen python-serial
```

Then clone the homeduino repository with all submodules:

```bash
git clone --recursive https://github.com/pimatic/homeduino.git
```

Edit the `Makefile` to use the right `BOARD_TAG` and `MONITOR_PORT`. You can list all available `BOARD_TAG`s with: `make show_boards`.

You can now compile it by running `make` or compile and upload it with:

```bash
make upload
```

Serial communication
------------------------

You can use the serial monitor of the arduino IDE or the `screen` command.

Run 

```bash
make monitor
```

Type in your message and press `Ctrl+Return`. You can exit it with `Ctrl+a` and then `k`. Keep in mind that it does not echo what you type.

Commands
--------

All commands send to homeduino are accepted with `ACK` or rejected with `ERR`. homeduino prints an `ready` message on serial port open if it is ready to receive commands.

### PING

```
PING message
```

Sends back a string, can be used to check if the connection is working.

Example: `PING hello`


### RF

#### receive

```
RF receive interrupt_pin
```

Starts receiving 433 mhz RF signals on interrupt pin `interrupt_pin` using [RFControl](https://github.com/pimatic/RFControl). `interrupt_pin` can be `0` or `1`.

Example: `RF receive 0`

When an RF signal is received it prints a message to the serial port: 

```
RF receive 453 1992 88 9228 0 0 0 0 01020102020201020101010101010102010101010202010202020202010102010102020203
```

#### send

```
RF send digital_pin repeats b0 b1 b2 b3 b4 b5 b6 b7 pulse_sequence
```

Send an rf signal by its buckets and pulse sequence using [RFControl](https://github.com/pimatic/RFControl).

Example: `RF send 4 3 453 1992 88 9228 0 0 0 0 01020102020201020101010101010102010101010202010202020202010102010102020203`


### DHT

```
DHT type digital_pin
```

Reads a DHT temperature sensor of `type` on pin `pin` using [DHTlib](http://playground.arduino.cc//Main/DHTLib).

Example: `DHT 22 3`

Responds with: `ACK temperature humidity` or one of `ERR checksum_error`, `ERR timeout_error`, `ERR unknown_error`.

### DST

```
DST onewire_pin sensor_number precision 
```
`onewire_pin` can be any free pin (normally 5 to 12).  
`sensor_number` is 0, 1, 2...  
`precision` can be 9 to 12 (9 is lower precision, 12 is high precision 0.06ºC and slower). 9 is better if you have many sensors or do not need much accuracy.

Example: `DST 5 0 9` ask temperature for the sensor number 0 at onewire bus connected to pin 5 with precision 9. 

Responds with `ACK temperature sensor_number sensors_address `. 
Reads a DST temperature sensor in ºC and say also the sensor number and the sensor address . 

Note.-Convert Celsius to Fahrenheit can be done in pimatic once received the data: 
"processing": "($ value * 9/5) +32"

### DR, DW, AR, AW, PM

*  digital read: `DR pin`
*  digital write: `DW pin`
*  analog read: `AR pin`
*  analog write: `AW pin`
*  pin mode: `PM mode`

Example: `DR 4`

Resonds with `ACK` or `ACK value`. 


