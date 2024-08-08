void setup() {
  // put your setup code here, to run once:
  pinMode(4, OUTPUT);

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (analogRead(A0) >= 30) { 
    digitalWrite(4, HIGH); 
  } else { 
    digitalWrite(4, LOW); 
  }
  Serial.println(analogRead(A0)); 
  delay(300);
}
