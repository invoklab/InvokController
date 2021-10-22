# Invok Controller

## What is this library?

Invok Controller library is a wrapper library based on [WiFi](https://github.com/arduino-libraries/WiFi), [ESP8266WiFi](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi), and [WebSockets](https://github.com/Links2004/arduinoWebSockets) library. This library is used for connecting development boards to the [Controller](https://play.google.com/store/apps/details?id=com.invokcontroller.app) app. Controller App is now available on Google Play.

## Disclaimer

This library is still a work in progress. There may be some breaking changes in the future, which might require you to replace, re-organize, and rearrange functions or variables included in this library. Use this library at your own risk.

## Supported Development Board

- ESP32 Development Board Family (WiFi)
- ESP8266 Development Board Family (WiFi)

## Basic Functionality

- Setting ESPs as Websocket Server
- Basic PING/PONG heartbeat routine through message (opcode 0x9 & 0xA not supported yet)
- Receive control data from Controller app

## Quickstart

- Download the [Controller](https://play.google.com/store/apps/details?id=com.invokcontroller.app) app from Google Play Store.
- Install the following library:
    - [WiFi](https://github.com/arduino-libraries/WiFi)
    - [ESPmDNS] (https://github.com/espressif/arduino-esp32/tree/master/libraries/ESPmDNS)
    - [ESP8266WiFi](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi)
    - [ESP8266mDNS] (https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266mDNS)
    - [WebSockets](https://github.com/Links2004/arduinoWebSockets)
    - [WiFiManager] (https://github.com/tzapu/WiFiManager)
- Download/clone this repository, and put it into libraries folder of Arduino directory. Ensure you have downloaded the latest version.
- Compile and upload example sketch.
- With WiFiManager, you can now setup WiFi without hardcoding SSID and password. After uploading the firmware, connect to ESP Wifi, SSID should be something like ESP_XXXX.
- You will then be directed to configuration portal, if you are not redirected automatically, access the portal with this address (1.1.1.1). Internal LED will turn on when in wifi configuration mode.
- Choose SSID you want to connect to, and input the password.
- When connected to network, program will print __IP Address__ on Serial Monitor, take note of this address.
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

Sample sketch are provided to demo the functionality of the App.

## Features

### Joystick

In Controller app, Joystick movement will generate 5 data, [x, y, r, theta, intensity].

- __x,y__ represent coordinate of the pad in cartesian form.
- __r,theta__ represent coordiate of the pad in polar form, where theta range is [0 - 360°].
- __intensity__ is the relative distance of pad from center circle to outer circle in percentage out of 100.

#### Getters

`ControllerName.joystick.getX()` -> Return x coordinate as __double__.

`ControllerName.joystick.getY()` -> Return y coordinate as __double__.

`ControllerName.joystick.getR()` -> Return range value as __double__.

`ControllerName.joystick.getTheta()` -> Return angle as __double__.

`ControllerName.joystick.getIntensity()` -> Return intensity  as __double__.

`ControllerName.joystick.getButtonState()` -> Return button state as __bool__.

All of these datas are sent to the server via WiFi on selected protocol, parsed, and ready to be used.

There is a small deadzone in the middle of joystick to prevent unwanted control motion.

### Color Picker

Pick any color on color wheel. There are two modes available:

- Update -> when pressed, app will send color info to the board.
- Continuous -> triggered by long-press the update button, will continously send color data as user pick colors

#### Getters

`ControllerName.colorPicker.getR()` -> Return Red component of RGB color space as __int__.

`ControllerName.colorPicker.getG()` -> Return Green component of RGB color space as __int__.

`ControllerName.colorPicker.getB()` -> Return Blue component of RGB color space as __int__.

`ControllerName.colorPicker.getH()` -> Return Hue component of HSV color space as __double__.

`ControllerName.colorPicker.getS()` -> Return Saturation component of HSV color space as __double__.

`ControllerName.colorPicker.getV()` -> Return Value component of HSV color space as __double__.

### Button Array

Set state of button individually or all button at once. App will send 12 button states as string. The data will then be parsed and processed, and then user can get state of each button pressed in boolean.

#### Getters

`ControllerName.buttonArray.getButtonArrayState(int button)` -> Return button state as __bool__.
User need to specify which button state to get by passing number 0-11 (correspond to button 1 - 12) as parameter to getter function.

### Sliders

Set state of slider individually or all sliders at once with master slider. App will send 6 slider value as string. The data will then be parsed and processed, and then user can get value of each slider in double with single precision (xx.x).

#### Getters

`ControllerName.slider.getSliderData(int slider)` -> Return slider value as __double__.
User need to specify which slider to get by passing number 0-5 (correspond to slider 1 - 6) as parameter to getter function.

### Serial Monitor

Controller serial monitor act just like Arduino serial monitor. It can send, receive and print data between ESP device and Controller app.

#### Getters

`ControllerName.print(std::string stringToPrint)` -> will print 'stringToPrint' in Controller app.
`ControllerName.getIncomingCommand()` -> Return a __std::string__ received from Controller app.
`ControllerName.setIncomingCommand(std::string command)` -> Setter function to set the command when it is received from the app. This setter can also be used to flush the buffer by passing empty string as parameter ("").

