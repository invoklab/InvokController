/*
  Class definition for InvokController.h library.
  Created by Thoby L. Noorhalim
  26 August 2021
  Last Update 8 May 2023
*/

#include <InvokController.h>

#define WEBSOCKET_POLL 5000

// LED Blinker Timer
double startTimeLED;
double elapsedTimeLED;
bool ledState = false;
double watchWsTime;


// ------------------------------ Constructor ------------------------------

/**
 *Construct controller object with following parameters:
 *- Connection Type, default to websocket
 *- Websocket Port, default to 80
 *- Debug mode, default to false
 */
Controller::Controller(std::string connectionType, int websocketPort, bool debug){
  this->connectionType = connectionType;
  this->websocketPort = websocketPort;
  this->debug = debug;
}

/// Begin Controller routine, setting up Wifi Manager
void Controller::begin(){
  if(this->connectionType == "websocket"){
    // Begin Wifi connection routine
    if(debug) Serial.println(F("\n[DEBUG] Starting Controller ...\n"));

    wm.setDebugOutput(debug);

    // Set device as station mode
    WiFi.mode(WIFI_STA);

    // Set Internal LED Pin
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LED_ON);

    // Set IP Address
    if(debug) Serial.println(F("[DEBUG] Wi-Fi configuration mode, connect to ESP Wi-Fi, and begin setup"));
    wm.setAPStaticIPConfig(IPAddress(1,1,1,1), IPAddress(1,1,1,1), IPAddress(255,255,255,0));
    wm.setTimeout(60);
    wm.setTitle("ESP Controller");
    bool res = wm.autoConnect(); // auto generated AP name from chipid
    
    if(!res) {
      if(debug) Serial.println(F("[DEBUG] Failed to connect, Entering DEEP SLEEP, Reset to Wake Up"));
      ESP.deepSleep(0);
    } 
    else {
      //if you get here you have connected to the WiFi    
      if(debug){
        Serial.printf("[DEBUG] Connected to Wi-Fi, AP [%s], SSID [%s], IP [%s]\n",
          wm.getDefaultAPName().c_str(), WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
      }

      getLocalIP();

      // Start MDNS Service
      mdnsBegin();

      // Start WebSocket server and assign callback
      // Set Websocket server
      this->websocket = WebSocketsServer(this->websocketPort);

      // Begin websocket routine
      this->websocket.begin();
      this->websocket.onEvent(std::bind(&Controller::onWebSocketEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));

      digitalWrite(LED_BUILTIN, LED_OFF);
      startTimeLED = millis();
    }
  }
}

/// Loop routine of controller, Websocket loop executed in this function.
void Controller::loop(){
  if(this->connectionType == "websocket"){

    // Watch WebSocket Ping
    if(millis() - watchWsTime > WEBSOCKET_POLL){
      // No ping detected
      if(debug) Serial.print(F("[DEBUG] No Ping detected\n"));
      websocket.disconnect();
      watchWsTime = millis();
    }

    this->websocket.loop();

  }

  // Built in LED blinker
  if(!_isConnected){
    #ifdef ESP8266
      MDNS.update();
    #endif
    elapsedTimeLED = millis() - startTimeLED;
    if(elapsedTimeLED > 500){
      ledState = !ledState;
      digitalWrite(LED_BUILTIN, ledState);
      startTimeLED = millis();
    }
  }

}

// ------------------------------ Setters ------------------------------

void Controller::setWebsocketPort(int port){
  this->websocketPort = port;
}

void Controller::setDataArrived(bool state){
  this->dataArrived = state;
}

void Controller::setIncomingCommand(std::string command){
  this->incomingCommand = command;
}

void Controller::setHostname(std::string name){
  this->hostname = name;
}

void Controller::setDebugMode(bool state){
  this->debug = state;
}

// ------------------------------ Getters ------------------------------

IPAddress Controller::getLocalIP(){
  this->localIP = WiFi.localIP();
  return WiFi.localIP();
}

bool Controller::isConnected(){
  return this->_isConnected;
}

bool Controller::isDataArrived(){
  return this->dataArrived;
}

void Controller::print(std::string toPrint){
  if(_isConnected){
    printString = "monitor," + toPrint;
    this->websocket.sendTXT(connectedIndex, printString.c_str());
  }
}

// Return command from controller app serial monitor tool.
std::string Controller::getIncomingCommand(){
  std::string buffer = incomingCommand;
  return buffer;
}

std::string Controller::getHostname(){
  return this->hostname;
}

// ---------------------------------------- Callback ---------------------------------------------

/// WebSocket callback routine, any websocket related event will be processed in this function.
void Controller::onWebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  // Figure out the type of WebSocket event
  switch(type) {

    // Client has disconnected
    case WStype_DISCONNECTED:
      if(debug) Serial.printf("[DEBUG] Client [%u] Disconnected!\n", num);
      mdnsBegin();
      this->_isConnected = false;
      break;

    // New client has connected
    case WStype_CONNECTED:
      this->connectedIndex = num;
      if(debug){
        IPAddress ip = websocket.remoteIP(num);
        Serial.printf("[DEBUG] [%u] Connection from ", num);
        Serial.println(ip.toString());
      }

      this->_isConnected = true;
      watchWsTime = millis();

      //  Close mDNS
      #ifdef ESP8266
        MDNS.removeService(getHostname().c_str(), "invc", "tcp");
      #else 
        mdns_free();
      #endif
      
      digitalWrite(LED_BUILTIN, LED_OFF);
      break;

    // Message Received
    case WStype_TEXT:
    {
      // Cast payload to string
      this->message = std::string(reinterpret_cast<char*>(const_cast<uint8_t*>(payload)));
      this->dataArrived = true;
      
      if(debug) Serial.printf("[DEBUG] Message from client: [%s] \n", this->message.c_str());

      this->parsedDataVector.reserve(10);
      this->parsedDataVector = parsecpp(message, ",");
      this->command = parsedDataVector[0];

      if(command.compare("cms") == 0){
        std::string response = "sms," + parsedDataVector[1];
        this->websocket.sendTXT(num, response.c_str());
        response.clear();
        #ifdef DEBUG
          onMessageCallback(num, parsedDataVector[1]);
        #endif
      } else if (command.compare("joystick") == 0){
        // Update Joystick Data
        joystick.updateData(parsedDataVector);
      } else if (command.compare("cpk") == 0 ){
        // Update Color Data
        colorPicker.updateData(parsedDataVector);
      } else if (command.compare("bar") == 0 ){
        // Update Button Array Data
        buttonArray.updateData(parsedDataVector);
      } else if (command.compare("slider") == 0){
        // Update Slider Data
        slider.updateData(parsedDataVector);
      } else if (command.compare("serial") == 0){
        // Update Incoming Command
        if(parsedDataVector[1].compare("initrequest") == 0){
          std::string ip = this->localIP.toString().c_str();
          std::string initResponse = "Connected to Server " + ip;
          this->print(initResponse.c_str());
        } else {
          setIncomingCommand(message.substr(parsedDataVector[0].length()+1));
          if(getIncomingCommand() == "reset"){
            wm.resetSettings();
            ESP.restart();
          }
        }
      } else if (command.compare("motion") == 0){
        // Update Motion Data
        motion.updateData(parsedDataVector);
      }
    }
      break;

    // For everything else: do nothing
    case WStype_PING:
      if(debug) Serial.print(F("[DEBUG] Ping from client\n"));
      watchWsTime = millis();
      break;
    default:
      break;
  }
}

void Controller::onMessageCallback(uint8_t num, std::string message){
  if(debug) Serial.printf("[DEBUG] Channel [%d], Message is %s, echoed to client.\n", num, message.c_str());
}

void Controller::printIP(){
  Serial.printf("[DEBUG] Connected to Wi-Fi, IP Address: %s\n", getLocalIP().toString().c_str());
}

void Controller::setAuthorisation(std::string user, std::string pass){
  this->websocket.setAuthorization(user.c_str(), pass.c_str());
}

std::vector<std::string> Controller::parsecpp(std::string data, std::string delim){
  std::vector<std::string> myVector{};
  
  myVector.reserve(NUM_OF_DATA);
  size_t pos = 0;

  while((pos = data.find(delim)) != std::string::npos){
    myVector.push_back(data.substr(0, pos));
    data.erase(0, pos + delim.length());
  }
  // Push last substring to vector
  myVector.push_back(data.substr(0));
  return myVector;
}

/// Begin multicast dns service by registering the hostname, and service type to the network.
void Controller::mdnsBegin(){
  if (!MDNS.begin(getHostname().c_str())) {  // Start the mDNS responder for esp8266.local
    if(debug) Serial.print(F("[DEBUG] Error setting up MDNS responder!\n"));
  }
    if(debug) Serial.print(F("[DEBUG] mDNS responder started\n"));
  MDNS.addService("invc", "tcp", 80);
  startTime = millis();
}

