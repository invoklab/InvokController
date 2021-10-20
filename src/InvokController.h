/*
  InvokController.h - Wrapper library based on:
  - WiFi.h
  - ESP8266WiFi.h
  - WebSocketsServer.h
  Controller library with WiFi and websocket functionality,
  to be used for connecting and processing data from Controller app.
  Created by Thoby L. Noorhalim.
  26 August 2021.
*/

#ifndef INVOKCONTROLLER_H
#define INVOKCONTROLLER_H

#ifdef ESP32
  #define LED_ON 0x1
  #define LED_OFF 0x0
  #include <WiFi.h>
  #include <ESPmDNS.h>
  #define LED_BUILTIN 2
#endif

#ifdef ESP8266
  #define LED_ON 0x0
  #define LED_OFF 0x1
  #include <ESP8266WiFi.h>
  #include <ESP8266mDNS.h> 
#endif

#include <WebSocketsServer.h>
#include <WiFiManager.h>
#include <Joystick.h>
#include <ColorPicker.h>
#include <ButtonArray.h>
#include <Slider.h>
#include <string>
#include <vector>

#define NUM_OF_DATA 15

class Controller{
  private:
    std::string SSID = "";
    std::string password = "";
    int websocketPort = 80;
    std::string connectionType = "";
    std::string response = "";
    std::string rawData = "";
    std::string message="";
    IPAddress localIP;
    bool _isConnected = false;
    std::vector<std::string> parsedDataVector{};
    std::string command = "";
    bool dataArrived = false;
    std::string printString = "";
    uint8_t connectedIndex = 0;
    std::string incomingCommand = "";
    std::string hostname = "Invok Controller";

  public:
    // ---------- Constructor ---------- 
    Controller();
    Controller(std::string connectionType);

    void begin();
    void loop();

    // ---------- Setters ----------
    void setSSID(std::string SSID);
    void setSSIDPassword(std::string password);
    void setWifiHostname(std::string hostname);
    void setWebsocketPort(int port);
    void setAuthorisation(std::string user, std::string pass);
    void setMessage(std::string data);
    void setDataArrived(bool state);
    void print(std::string toPrint); // For serial monitor printing
    void setIncomingCommand(std::string command);
    void setHostname(std::string name);

    // ---------- Getters ----------
    bool isConnected();
    std::string getMessage();
    bool isDataArrived();
    std::string getIncomingCommand();
    void printIP();
    std::string getHostname();

    // Functions
    void mdnsBegin();

    // ---------- Callback ----------
    void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length);
    void onMessageCallback(uint8_t num, std::string message);

    std::vector<std::string> parsecpp(std::string data, std::string delim);
    IPAddress getLocalIP();

    // ---------- Object -----------
    WebSocketsServer websocket = WebSocketsServer(80);
    Joystick joystick;
    ColorPicker colorPicker;
    ButtonArray buttonArray;
    Slider slider;
    WiFiManager wm;

    // Timer
    double startTime;
};

#endif