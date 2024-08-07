const int LED=13;
int state;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(38400);
}

void loop() {
  delay(1000);
  if(Serial.available()>0){
    state=Serial.read();
    Serial.println(state);
    if(state==248){
      digitalWrite(LED, HIGH);
    }else if(state==0){
      digitalWrite(LED, LOW);
    }
  }

}
