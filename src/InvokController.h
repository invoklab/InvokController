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
  #include <WiFi.h>
#else 
  #include <ESP8266WiFi.h>
#endif

#include <WebSocketsServer.h>
#include <Joystick.h>
#include <ColorPicker.h>
#include <ButtonArray.h>
#include <Slider.h>
#include <string>
#include <vector>

#define NUM_OF_DATA 15

using namespace std;
class Controller{
  private:
    string SSID = "";
    string password = "";
    string hostname = "ESPServer";
    int websocketPort = 80;
    string connectionType = "";
    string response = "";
    string rawData = "";
    string message="";
    IPAddress localIP;
    bool _isConnected = false;
    vector<string> parsedDataVector{};
    string command = "";
    bool dataArrived = false;

  public:
    // ---------- Constructor ---------- 
    Controller();
    Controller(string connectionType);

    void begin();
    void loop();

    // ---------- Setters ----------
    void setSSID(string SSID);
    void setSSIDPassword(string password);
    void setWifiHostname(string hostname);
    void setWebsocketPort(int port);
    void setAuthorisation(string user, string pass);
    void setMessage(string data);
    void setDataArrived(bool state);

    // ---------- Getters ----------
    bool isConnected();
    string getMessage();
    bool isDataArrived();
    
    void printIP();

    // ---------- Callback ----------
    void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length);
    void onMessageCallback(uint8_t num, string message);

    vector<string> parsecpp(string data, string delim);
    IPAddress getLocalIP();

    // ---------- Object -----------
    WebSocketsServer websocket = WebSocketsServer(80);
    Joystick joystick;
    ColorPicker colorPicker;
    ButtonArray buttonArray;
    Slider slider;

    
};

#endif