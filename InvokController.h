#ifdef ESP32
  #include <WiFi.h>
#else 
  #include <ESP8266WiFi.h>
#endif

#include <WebSocketsServer.h>
#include <Joystick.h>
#include <string>

using namespace std;

#define NUM_OF_DATA 10
#define DATA_LENGTH 10

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
    Controller(char *connectionType);
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
     // websocket object
    void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length);
    void onMessageCallback(uint8_t num, char* message);
    void parse(unsigned char *myString, char *&pointer, int *idy, int col);
    vector<string> parsecpp(string data, string delim);
    
    Joystick joystick;
};

Controller::Controller(){
  this->connectionType = "websocket"; // Default to websocket
}

Controller::Controller(char *connectionType){
  this->connectionType = connectionType;
  
}

void Controller::begin(){
  if(this->connectionType == "websocket"){
    // Begin Wifi connection routine
    // Serial.begin(9600);
    Serial.println("");
    Serial.print("Connecting ");
    WiFi.hostname(this->hostname.c_str());
    WiFi.begin(this->SSID.c_str(), this->password.c_str());
    while ( WiFi.status() != WL_CONNECTED ) {
      delay(500);
      Serial.print(".");
    }
    getLocalIP();
    Serial.println("");

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

// Called when receiving any WebSocket message
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
        Serial.printf("raw data is %s \n", rawData.c_str());
        char parsedData[NUM_OF_DATA][DATA_LENGTH];
        memset((void*)parsedData, 0, sizeof(parsedData));
        // char* pch = (char*)payload;
        char* ptr = &parsedData[0][0];
        int idy = 0;

        parse(payload, ptr, &idy, DATA_LENGTH);
        vector<string> parsedDataVector{};
        parsedDataVector.reserve(10);
        parsedDataVector = parsecpp(this->rawData, ",");
        Serial.printf("vector is %d \n", parsedDataVector.size());
        Serial.printf("Parsed data 0 is %s\n", parsedDataVector.at(0).c_str());
        Serial.printf("Parsed data 1 is %s\n", parsedDataVector.at(1).c_str());
        Serial.printf("Parsed data 2 is %s\n", parsedDataVector.at(2).c_str());
        // Serial.println("PCB is [" + String(pch) +"]");
        // Serial.println("Parsed data 0 is " + parsedData[0][0]); // Use this to check authentication
        // Serial.println("Parsed data 0 is " + String(parsedData[0]));
        const char* command = parsedData[0];
        if(strcmp(command, "cms") == 0){
          this->response.clear();
          this->response = "sms," + string(parsedData[1]);
          this->websocket.sendTXT(num, response.c_str());
          this->response.clear();
        } else if (strcmp(command, "joystick") == 0){
          // Update Joystick Data
          joystick.updateData(parsedData);
        }
        
        // this->onMessageCallback(num, (char *) payload);
        // Serial.printf("Client [%u] Text: %s\n", num, payload);
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

void Controller::onMessageCallback(uint8_t num, char* message){
  Serial.println("Channel "+ String(num) + ", Message is "+ message);
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

void Controller::parse(unsigned char *myString, char *&pointer, int *idy, int col){
  char *pch = (char *)myString;
  int idx = 0;
  int index = 0;
  int diff = 0;
  int counter = 1;
  
  while(*pch != NULL){
    if(*pch != ','){
        index = index + idx;
        *(pointer+index) = *pch;
        idx = 1;
        diff = col * counter - index;
    } else {
        diff = col * counter - index;
        index = index + diff;
        idx = 0;
        counter++;
        *idy = *idy + 1;
    }
    pch++;
  }
  *idy++;
}

void Controller::setAuthorisation(string user, string pass){
  this->websocket.setAuthorization(user.c_str(), pass.c_str());
}

vector<string> Controller::parsecpp(string data, string delim){
  vector<string> myVector{};
  myVector.reserve(NUM_OF_DATA);
  int pos = 0;

  // Serial.printf("Raw data is %s\n", data.c_str());

  while((pos = data.find(delim)) != string::npos){
    myVector.push_back(data.substr(0, pos));
    data.erase(0, pos + delim.length());
  }
  // Push last substring to vector
  myVector.push_back(data.substr(0));

  return myVector;
}