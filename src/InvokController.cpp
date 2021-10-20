/*
  Class definition for InvokController.h library.
  Created by Thoby L. Noorhalim
  26 August 2021
*/

#include <InvokController.h>

// LED Blinker Timer
double startTimeLED;
double elapsedTimeLED;
bool ledState = false;

// ------------------------------ Constructor ------------------------------
Controller::Controller(){
  this->connectionType = "websocket"; // Default to websocket
  Serial.begin(115200);
}

Controller::Controller(std::string connectionType){
  this->connectionType = connectionType;
  Serial.begin(115200);
}

void Controller::begin(){
  if(this->connectionType == "websocket"){
    // Begin Wifi connection routine
    Serial.println("\nStarting Controller ...\n");
    #ifdef DEBUG
      wm.setDebugOutput(true);
    #else
      wm.setDebugOutput(false);
    #endif

    // Set device as station mode
    WiFi.mode(WIFI_STA);

    // Set Internal LED Pin
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LED_ON);

    // Set IP Address
    Serial.printf("Wi-Fi configuration mode, connect to ESP Wi-Fi, and begin setup");
    wm.setAPStaticIPConfig(IPAddress(1,1,1,1), IPAddress(1,1,1,1), IPAddress(255,255,255,0));
    bool res;
    res = wm.autoConnect(); // auto generated AP name from chipid
    
    if(!res) {
      #ifdef DEBUG
        Serial.println("Failed to connect");
      #endif
        // ESP.restart();
    } 
    else {
      //if you get here you have connected to the WiFi    
      #ifdef DEBUG
        Serial.println("Connected to Wi-Fi");
        Serial.println(wm.getDefaultAPName());
        Serial.println(WiFi.SSID());  
        Serial.println(WiFi.localIP());
      #endif

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

void Controller::loop(){
  if(this->connectionType == "websocket"){
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

void Controller::setSSID(std::string SSID){
  this->SSID = SSID;
}

void Controller::setSSIDPassword(std::string password){
  this->password = password;
}

void Controller::setWifiHostname(std::string hostname){
  this->hostname = hostname;
}

void Controller::setWebsocketPort(int port){
  this->websocketPort = port;
}

void Controller::setMessage(std::string data){
  this->message = data;
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

// ------------------------------ Getters ------------------------------

IPAddress Controller::getLocalIP(){
  this->localIP = WiFi.localIP();
  return WiFi.localIP();
}

bool Controller::isConnected(){
  return this->_isConnected;
}

std::string Controller::getMessage(){
  return this->message;
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

std::string Controller::getIncomingCommand(){
  std::string buffer = incomingCommand;
  // setIncomingCommand("");
  return buffer;
}

std::string Controller::getHostname(){
  return this->hostname;
}

// ---------------------------------------- Callback ---------------------------------------------

void Controller::onWebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  // Figure out the type of WebSocket event
  switch(type) {

    // Client has disconnected
    case WStype_DISCONNECTED:
      Serial.printf("Client [%u] Disconnected!\n", num);
      mdnsBegin();
      this->_isConnected = false;
      break;

    // New client has connected
    case WStype_CONNECTED:
      if(!_isConnected){
        this->connectedIndex = num;
        IPAddress ip = this->websocket.remoteIP(num);
        Serial.printf("Client [%u] Connection from ", num);
        Serial.println(ip.toString());
        this->_isConnected = true;

        //  Close mDNS
        #ifdef ESP8266
          MDNS.close();
        #else 
          MDNS.end();
        #endif
        
        digitalWrite(LED_BUILTIN, LED_OFF);
      } else {
        Serial.printf("Connection refused, already connected to client\n");
      }
      break;

    // Message Received
    case WStype_TEXT:
      // Cast payload to string
      this->rawData = std::string(reinterpret_cast<char*>(const_cast<uint8_t*>(payload)));
      this->message = this->rawData;
      this->dataArrived = true;
      
      #ifdef DEBUG
        Serial.printf("Message data is %s \n", this->message.c_str());
      #endif

      this->parsedDataVector.reserve(10);
      this->parsedDataVector = parsecpp(this->message, ",");
      this->command = parsedDataVector[0];

      if(command.compare("cms") == 0){
        this->response = "sms," + parsedDataVector[1];
        this->websocket.sendTXT(num, response.c_str());
        this->response.clear();
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
          String initResponse = "Connected to Server " + this->localIP.toString();
          this->print(initResponse.c_str());
        } else {
          setIncomingCommand(rawData.substr(parsedDataVector[0].length()+1));
          if(getIncomingCommand() == "reset"){
            wm.resetSettings();
            ESP.restart();
          }
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

void Controller::onMessageCallback(uint8_t num, std::string message){
  Serial.printf("Channel [%d], Message is %s, echoed to client.\n", num, message.c_str());
}

void Controller::printIP(){
  Serial.print("\nConnected to Wi-Fi, IP Address: ");
  Serial.println(this->localIP);
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

void Controller::mdnsBegin(){
  std::string mdnsHostname = std::string(getHostname().c_str());
  if (!MDNS.begin(mdnsHostname.c_str())) {  // Start the mDNS responder for esp8266.local
  #ifdef DEBUG
    Serial.println("Error setting up MDNS responder!");
  #endif
  }
  #ifdef DEBUG
    Serial.println("mDNS responder started");
  #endif
  MDNS.addService("invc", "tcp", 80);
  startTime = millis();
}

