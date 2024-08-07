#include <Arduino.h>
#include <WiFi.h>

String ssidString = "12connect";
String passwordString = "";

const char* ssid = ssidString.c_str();
const char* password = passwordString.c_str();


const uint16_t port=8888;
const char *host="192.168.201.68";
enum State{
  WAITING,
  MOVE_TO,
  AT_LOCATION,
  MOVE_BACK
};

State state=WAITING;

String command;
String data;
int checksum;
String confirm;

//waiting, move to, at location, move back
String getCommand(const String& input) {
  int startIndex = input.indexOf('$') + 1; // Skip over the '$'
  int endIndex = input.indexOf('|');
  if (startIndex != -1 && endIndex != -1) {
    return input.substring(startIndex, endIndex);
  }
  return ""; // Return an empty String if the delimiters are not found
}

String getData(const String& input) {
  int startIndex = input.indexOf('|') + 1;
  int endIndex = input.indexOf('|', startIndex);
  if (endIndex != -1) {
    return input.substring(startIndex, endIndex);
  }
  return ""; // Return an empty String if the delimiter is not found
}

int getChecksum(const String& input) {
  int startIndex = input.lastIndexOf('|') + 1;
  int endIndex = input.indexOf('#', startIndex);
  if (endIndex != -1) {
    return input.substring(startIndex, endIndex).toInt();
  }
  return 0; // Return 0 if the delimiter is not found
}

int calculateChecksum(const String& input) {
  int sum = 0;
  for (int i = 0; i < input.length(); i++) {
    sum += input.charAt(i);
  }
  return sum; 
}

void setup() {
  
  Serial.begin(38400);
  WiFi.begin(ssid, password); 
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.println("...");
  }
  Serial.println("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
}



void loop() {
  WiFiClient client;
  if(!client.connect(host, port)){
    Serial.println("Connection ot host failed");
    delay(1000);
    return;
  }

  Serial.println("Connected to server successfully!");
  client.println("Master");

  while (true) {

    if (client.available()) {
      String message=client.readStringUntil('\n');
      message.trim();
      if(message!=""){
        Serial.println(message);
        command = getCommand(message);
        data = getData(message);
        checksum = getChecksum(message);

        String commandAndData = "$"+ command + "|" + data + "|";
        int expectedChecksum = calculateChecksum(commandAndData);

        Serial.print("Command: ");
        Serial.println(command);
        Serial.print("Data: ");
        Serial.println(data);
        Serial.print("Checksum: ");
        Serial.println(checksum);

        if (expectedChecksum == checksum) {
          Serial.println("Checksums match!");
        } else {
          Serial.println(expectedChecksum);
          Serial.println(checksum);
        }
      }
    }
     

  //   switch (state)
  //   {
  //   case WAITING:
  //     if(command=="MOVE_TO"){
  //       state=MOVE_TO;
        
  //     }
  //     break;
  //   case MOVE_TO:  
  //   //in this state the robot should move to the desired location, when it reaches it, the state should change to AT_LOCATION
  //     if(command=="STOP"){
  //       state=WAITING;
  //     }
  //     break;
  //   case AT_LOCATION:
  //   //in this state the robot should be at the location and the arm should be activated
  //     confirm=Serial.readStringUntil('\n'); 
  //     if(confirm=="AT_LOCATION"){
  //       state=MOVE_BACK;
  //     }
  //     break;
  //   case MOVE_BACK:
  //   //in this state the robot should move back to the original location when the object is picked up
  //     if(command=="STOP"){
  //       state=WAITING;
  //     }
  //     break;

  //   default:
  //     break;
  //   }
  }
}