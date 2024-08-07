
int LED=13;
void setup() {
  Serial.begin(38400);
  pinMode(LED, OUTPUT);

}

void loop() {

  if(Serial.available()>0){
    String str=Serial.readStringUntil('\n');
    str.trim();
    Serial.println("Received:"+str);
    if(str=="ON"){
      digitalWrite(LED, HIGH);
    }else if(str=="OFF"){
      digitalWrite(LED, LOW);
    }
  }
}
