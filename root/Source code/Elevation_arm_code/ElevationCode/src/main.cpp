
#include <Arduino.h>
#include <AccelStepper.h>

// Stepper Motor Setup
#define motorPin1 8
#define motorPin2 9
#define motorPin3 10
#define motorPin4 11

AccelStepper stepper(AccelStepper::FULL4WIRE, motorPin1, motorPin3, motorPin2, motorPin4);

const int stepsPerRevolution = 200;
const int stepsPerCm = stepsPerRevolution * 2;
const int bottomShelfHeight = 2; // cm
const int higherShelfHeight = 16; // cm
const int homePosition = 0;
const int magnet = 7;

int printCounter = 0;

unsigned long waitStartTime;
const unsigned long waitDuration = 3000;

enum States
{
  WAITING,
  ELEVATE,
  AT_LOCATION,
  WAIT_BEFORE_DELEVATE,
  DELEVATE,
  HOLD
};

String str;
States state = WAITING;

void setup()
{
  Serial.begin(38400);
  // pinMode(LED_BUILTIN, OUTPUT);
  pinMode(magnet, OUTPUT);
  stepper.setMaxSpeed(550);
  stepper.setAcceleration(350);
  // waitStartTime = millis();
  stepper.setCurrentPosition(homePosition);
  stepper.runToNewPosition(homePosition);
}

void goToShelf(String shelf)
{
  int targetPosition = 0;

  if (shelf == "0")
  {
    targetPosition = bottomShelfHeight * stepsPerCm;
  }
  else if (shelf == "1")
  {
    targetPosition = higherShelfHeight * stepsPerCm;
  }

  stepper.runToNewPosition(targetPosition);
}

void loop()
{
   //str = "1";
  if (Serial.available() > 0)
  {
    String temp = Serial.readStringUntil('\n');
    temp.trim();
    if (temp != "")
    {
      // Serial.println("Received:" + temp);
      str = temp;
      state = ELEVATE;
    }
    // the messsage that is received here is in the following format:A1 from this message you only need the part with the number
    // map the motor according to values like 0 and 1
  }
  switch (state)
  {
  case WAITING:
   /*if (str = !"")
    {
      state = ELEVATE;
    }*/
    break;
  case ELEVATE:
    // in this state the arm should move to the desired location.
    goToShelf(str);
    // Serial.println("Going up");
    state = AT_LOCATION;
    break;
  case AT_LOCATION:
    // in this state the arm has already reached the desired location and the magnetic head is turned on
    digitalWrite(magnet, HIGH);
    // waitStartTime = millis();
    state = WAIT_BEFORE_DELEVATE;
    break;
  case WAIT_BEFORE_DELEVATE:
    // wait for the 3 secs before delevating
    delay(3000);
    state = DELEVATE;
    break;
  case DELEVATE:
    // in this state the arm retracts and goes back to the default position while the magnet is on
    stepper.runToNewPosition(homePosition);
    state = HOLD;
    break;
  case HOLD:
    if(printCounter==0){
      Serial.println("OK");
      printCounter++;
    }
    
    // in this state the magnet is on until the slave receives a message that confirms that the car is at the drop off location
    if (str == "HOME")
    {
      str = "";
      digitalWrite(magnet, LOW);
      printCounter=0;
      state = WAITING;
    }
    break;
  }
}