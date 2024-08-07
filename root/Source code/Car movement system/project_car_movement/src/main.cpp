#include <Arduino.h>
#include <WiFi.h>
#include <SoftwareSerial.h>

const char *ssid="12connect";
const char *password="";

const uint16_t port=8888;
const char *host="192.168.201.35";

const int motor1Pin1 = 9;    // IN1 on the L298N
const int motor1Pin2 = 8;    // IN2 on the L298N
const int motor2Pin1 = 7;    // IN3 on the L298N
const int motor2Pin2 = 6;    // IN4 on the L298N
const int enable1Pin = 5;    // ENA on the L298N
const int enable2Pin = 3;    // ENB on the L298N

int targetDistance = 10;

SoftwareSerial Serial1(2, 10); // define software serial port name as Serial1 and define pin2 as RX & pin3 as TX

int dist;                    // actual distance measurements of LiDAR
int strength;                // signal strength of LiDAR
int check;                   // save check value
int uart[9];                 // save data measured by LiDAR
const int HEADER = 0x59;     // frame header of data package

enum State {
  WAITING,
  MOVE_TO,
  AT_LOCATION,
  MOVE_BACK
};

State state = WAITING;
String command;
String data;
int checksum;

void setup() {
  
  Serial.begin(38400);
  Serial1.begin(115200);     // set bit rate of serial port connecting LiDAR with Arduino
  WiFi.begin(ssid);
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.println("...");
  }
  Serial.println("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());

  // Initialize motor pins as outputs
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  pinMode(enable2Pin, OUTPUT);

  // Initialize motors to be off
  stopMotors();
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
          client.println("AILQK");
        } else {
          command = "";
          data = "";
          checksum = 0;
        }
      }
    }
    switch (state)
        {
        case WAITING:
        
          if(command=="MOVE_TO"){
            state=MOVE_TO;
          }
          break;
        case MOVE_TO:  
          readLiDAR();
          if (dist > targetDistance) {
            forwardMotors();
          } else {
            stopMotors();
            state=AT_LOCATION;
          }


          if(command=="STOP"){
            state=WAITING;
          }
          break;
        case AT_LOCATION:
        //in this state the robot should be at the location and the arm should be activated
          Serial.println(data);
          if(Serial.available()>0){
            String confirmation=Serial.readString();
            confirmation.trim();
            if(confirmation=="OK"){
              state=MOVE_BACK;
            }
          }
          break;
        case MOVE_BACK:
        //in this state the robot should move back to the original location when the object is picked up
          if(command=="STOP"){
            //TBD
            state=WAITING;
          }
          break;

        default:
          break;
        }
  }
}

void forwardMotors() {
  digitalWrite(enable1Pin, HIGH);
  digitalWrite(enable2Pin, HIGH);
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void stopMotors() {
  digitalWrite(enable1Pin, LOW);
  digitalWrite(enable2Pin, LOW);
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}

void readLiDAR() {
  if (Serial1.available()) {
    if (Serial1.read() == HEADER) {
      uart[0] = HEADER;
      if (Serial1.read() == HEADER) {
        uart[1] = HEADER;
        for (int i = 2; i < 9; i++) {
          uart[i] = Serial1.read();
        }
        check = uart[0] + uart[1] + uart[2] + uart[3] + uart[4] + uart[5] + uart[6] + uart[7];
        if (uart[8] == (check & 0xff)) {
          dist = uart[2] + uart[3] * 256;     // calculate distance value
          strength = uart[4] + uart[5] * 256; // calculate signal strength value
          Serial.print("distance = ");
          Serial.print(dist);                 // output measured distance value of LiDAR
          Serial.print('\t');
          Serial.print("strength = ");
          Serial.print(strength);             // output signal strength value
          Serial.print('\n');
        }
      }
    }
  }
}