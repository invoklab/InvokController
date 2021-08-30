# Invok Controller

## What is this library?
Invok Controller library is a wrapper library based on [WiFi](https://github.com/arduino-libraries/WiFi), [ESP8266WiFi](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi), and [WebSockets](https://github.com/Links2004/arduinoWebSockets) library. This library is used for connecting development boards to the Controller app through various protocol.

## Disclaimer
This library is still a work in progress. There may be some breaking changes in the future, which might require you to replace, re-organize, and rearrange functions or variables included in this library. Use this library at your own risk.

## Supported Board
- ESP32 Development Board Family (WiFi)
- ESP8266 Development Board Family (WiFi)

## Basic Functionality
- Setting ESPs as Websocket Server
- Basic PING/PONG heartbeat routine through message (opcode 0x9 & 0xA not supported yet)
- Receive control data from Controller app

## Quickstart
- Download the Controller app from Google Play Store.
- Install the following library:
    - [WiFi](https://github.com/arduino-libraries/WiFi)
    - [ESP8266WiFi](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi)
    - [WebSockets](https://github.com/Links2004/arduinoWebSockets)
- Download/clone this repository, and put it into libraries folder of Arduino directory.
- Compile and upload example sketch.
- When connected to network, program will print __IP Address__, take note of this address.
- In Controller app home page, tap Wi-Fi icon on top right corner, this will route you to connection setup page.
- Input the IP Address printed on serial monitor to address field.
- Press __Connect__.
- Status icon on top right corner will turn green when connection is established. 
- Test connection by sending message. Server will respond or echo back the same message.

## Code Setup
Create a new arduino sketch, and include InvokController.h

`#include <InvokController.h>`

Instantiate Controller object as global variable before setup(), and specify controller type as argument.

`Controller myController = Controller("websocket");`

In setup(), initiate serial data transmission,

`Serial.begin(115200);`

and continue to call setters function to set wifi credentials.

```
myController.setSSID("YOUR_SSID");
myController.setSSIDPassword("YOUR_PASSWORD");
myController.begin();
myController.printIP();
```

Connected IP Address will be printed after printIP() function executes, this is the server address you need to connect from client (Controller app).

Inside loop(), do not forget to call,

`myController.loop();`


`delay()` function use is discouraged, because it blocks the program routine. It might cause the websocket connection to drop. Use `millis()` instead, and create if statement to execute routine every certain time period. 

## Examples
Two sample codes provided to demonstate basic functionality of this library, and the Controller app.

## Features
### Joystick
In Controller app, Joystick movement will generate 5 data, [x, y, r, theta, intensity].
- __x,y__ represent coordinate of the pad in cartesian form.
- __r,theta__ represent coordiate of the pad in polar form, where theta range is [0 - 360°].
- __intensity__ is the relative distance of pad from center circle to outer circle in percentage out of 100.

#### Getters
`ObjectName.getX()` -> Return x coordinate as double.
`ObjectName.getY()` -> Return y coordinate as double.

`ObjectName.getR()` -> Return range value as double.

`ObjectName.getTheta()` -> Return angle as double.

`ObjectName.getIntensity()` -> Return intensity  as double.

`ObjectName.getButtonState()` -> Return button state as boolean.

All of these datas are sent to the server via WiFi on selected protocol, parsed, and ready to be used.

There is a small deadzone in the middle of joystick to prevent unwanted control motion.