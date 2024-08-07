#include <Arduino.h>

enum States
{
  WAITING,
  ELEVATE,
  AT_LOCATION,
  DELEVATE,
  HOLD
};

String str;
States state=WAITING;

void setup() {
  Serial.begin(38400);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

  if(Serial.available()>0){
    String temp=Serial.readStringUntil('\n');
    temp.trim();
    if(temp!=""){
      Serial.println("Received:"+temp);
      str=temp;
    }
    
  }
  switch(state)
    {
    case WAITING:
      if(str=!""){
        state=ELEVATE;
      }
      break;
    case ELEVATE:
    //in this state the arm should move to the desired location.
      break;
    case AT_LOCATION:
    //in this state the arm has already reached the desired location and the magnetic head is turned on
      break;
    case DELEVATE:
    //in this state the arm retracts and goes back to the default position while the magnet is on
      break;
    case HOLD:
    //in this state the magnet is on until the slave receives a message that confirms that the car is at the drop off location
      if(str=="OK"){
        str="";
        state=WAITING;
      }
      break;
    }
} 