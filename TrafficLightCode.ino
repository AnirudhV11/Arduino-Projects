/*
blinker function of LED
1. turn on the LED
2. wait for some time       delay(1000)  1000 ms = 1s
3. turn it off
4. wait for some time
*/

void setup() {
  // put your setup code here, to run once:
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(7, HIGH);
  delay(5000);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  delay(2000);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  delay(5000);
  digitalWrite(9, LOW);
}

