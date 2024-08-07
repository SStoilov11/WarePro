#include <Wifi.h>


void setup() {
  
  Serial.begin(38400);
}

void loop() {
  Serial.println("ON");
  delay(1000);
  Serial.println("OFF");
  delay(1000); 
}
