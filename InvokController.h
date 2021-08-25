#ifndef INVOKCONTROLLER_H
#define INVOKCONTROLLER_H

#ifdef ESP32
  #include <WiFi.h>
#else 
  #include <ESP8266WiFi.h>
#endif

#include <WebSocketsServer.h>
#include <Joystick.h>
#include <string>
#include <vector>

#define NUM_OF_DATA 10

using namespace std;

class Controller{
  private:
    string SSID = "";
    string password = "";
    string hostname = "ESP";
    int websocketPort = 80;
    string connectionType = "";
    string response = "";
    string rawData = "";
    IPAddress localIP;
    

  public:
    Controller();
    Controller(string connectionType);
    void begin();
    void setSSID(string SSID);
    void setSSIDPassword(string password);
    void setWifiHostname(string hostname);
    void setWebsocketPort(int port);
    void setAuthorisation(string user, string pass);
    void loop();
    void printIP();
    IPAddress getLocalIP();
    WebSocketsServer websocket = WebSocketsServer(80);
    void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length);
    void onMessageCallback(uint8_t num, string message);
    vector<string> parsecpp(string data, string delim);
    
    Joystick joystick;
};

Controller::Controller(){
  this->connectionType = "websocket"; // Default to websocket
}

Controller::Controller(string connectionType){
  this->connectionType = connectionType;
  
}

void Controller::begin(){
  if(this->connectionType == "websocket"){
    // Begin Wifi connection routine

    // Set device as station mode
    WiFi.mode(WIFI_STA);

    #ifdef ESP32
      // WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
      WiFi.setHostname(this->hostname.c_str());
    #else 
      WiFi.hostname(this->hostname.c_str());
    #endif

    Serial.printf("\nConnecting to %s\n", this->SSID.c_str());
    WiFi.disconnect();
    WiFi.begin(this->SSID.c_str(), this->password.c_str());
    while ( WiFi.status() != WL_CONNECTED ) {
      delay(1000);
      Serial.print(".");
    }
    getLocalIP();
    Serial.println("");
    Serial.print("RRSI: ");
    Serial.println(WiFi.RSSI());

    // Set Websocket server
    this->websocket = WebSocketsServer(this->websocketPort);

    // Begin websocket routine
    this->websocket.begin();
    this->websocket.onEvent(std::bind(&Controller::onWebSocketEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
  }
}

void Controller::setSSID(string SSID){
  this->SSID = SSID;
}

void Controller::setSSIDPassword(string password){
  this->password = password;
}

void Controller::setWifiHostname(string hostname){
  this->hostname = hostname;
}

void Controller::setWebsocketPort(int port){
  this->websocketPort = port;
}

IPAddress Controller::getLocalIP(){
  this->localIP = WiFi.localIP();
  return WiFi.localIP();
}

void Controller::onWebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  // Figure out the type of WebSocket event
  switch(type) {

    // Client has disconnected
    case WStype_DISCONNECTED:
      Serial.printf("Client [%u] Disconnected!\n", num);
      break;

    // New client has connected
    case WStype_CONNECTED:
      {
        IPAddress ip = this->websocket.remoteIP(num);
        Serial.printf("Client [%u] Connection from ", num);
        Serial.println(ip.toString());
      }
      break;

    // Message Received
    case WStype_TEXT:
      // Cast payload to string
      this->rawData = string(reinterpret_cast<char*>(const_cast<uint8_t*>(payload)));
      
      if(this->rawData.compare("PING") == 0){
        // Heartbeat routine
        this->websocket.sendTXT(num, "PONG");
      } else {
        // Call callback function to process message
        // Parse the message

        #ifdef DEBUG
          Serial.printf("Raw data is %s \n", this->rawData.c_str());
        #endif

        vector<string> parsedDataVector{};
        parsedDataVector.reserve(10);
        parsedDataVector = parsecpp(this->rawData, ",");

        string command = parsedDataVector[0];
        
        if(command.compare("cms") == 0){
          // this->response.clear();
          this->response = "sms," + parsedDataVector[1];
          this->websocket.sendTXT(num, response.c_str());
          this->response.clear();
          #ifdef DEBUG
            onMessageCallback(num, parsedDataVector[1]);
          #endif
        } else if (command.compare("joystick") == 0){
          // Update Joystick Data
          joystick.updateData(parsedDataVector);
        }
      }
      break;

    // For everything else: do nothing
    case WStype_PING:
    case WStype_BIN:
    case WStype_ERROR:
    case WStype_FRAGMENT_TEXT_START:
    case WStype_FRAGMENT_BIN_START:
    case WStype_FRAGMENT:
    case WStype_FRAGMENT_FIN:
    default:
      break;
  }
}

void Controller::onMessageCallback(uint8_t num, string message){
  Serial.printf("Channel [%d], Message is %s, echoed to client.\n", num, message.c_str());
}

void Controller::loop(){
  if(this->connectionType == "websocket"){
    this->websocket.loop();
  }
}

void Controller::printIP(){
  Serial.print("Connected IP Address ");
  Serial.println(this->localIP);
}

void Controller::setAuthorisation(string user, string pass){
  this->websocket.setAuthorization(user.c_str(), pass.c_str());
}

vector<string> Controller::parsecpp(string data, string delim){
  vector<string> myVector{};
  myVector.reserve(NUM_OF_DATA);
  int pos = 0;

  while((pos = data.find(delim)) != string::npos){
    myVector.push_back(data.substr(0, pos));
    data.erase(0, pos + delim.length());
  }
  // Push last substring to vector
  myVector.push_back(data.substr(0));

  return myVector;
}

#endif