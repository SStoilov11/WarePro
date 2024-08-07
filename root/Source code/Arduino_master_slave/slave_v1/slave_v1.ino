int message=0;
int LED=13;
void setup() {
  Serial.begin(38400);
  pinMode(LED, OUTPUT);

}

void loop() {
  Serial.println(1);
  delay(1000);
  Serial.println(0);
  delay(1000);
}
