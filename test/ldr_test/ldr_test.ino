const int ldr0=A7;

void setup() {
 Serial.begin(9600);
 pinMode(ldr0, OUTPUT); 
}

void loop() {
  int ldrStatus = analogRead(ldr0);
  Serial.println(ldrStatus);
  delay(1000);
}
