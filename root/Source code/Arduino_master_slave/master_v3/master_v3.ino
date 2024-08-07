#include <WiFi.h>

const char *ssid="12connect";
const char *password="";

const uint16_t port=8888;
const char *host="192.168.201.250";

void setup() {
  
  Serial.begin(38400);
  WiFi.begin(ssid);
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.println("...");
  }
  Serial.println("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
}

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
        String command = getCommand(message);
        String data = getData(message);
        int checksum = getChecksum(message);

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
  }
}
