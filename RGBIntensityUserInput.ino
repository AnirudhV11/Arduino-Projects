int b = 194, g = 87, r = 148;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Enter Intensity for Red: ");
  while(Serial.available() <= 1)
    ; 
  r = Serial.parseInt();
  Serial.println(r);
  analogWrite(6, r);

  Serial.println("Enter Intensity for Green: ");
  while(Serial.available() <= 1)
    ; 
  g = Serial.parseInt();
  Serial.println(g);
  analogWrite(5, g);

  Serial.println("Enter Intensity for Blue: ");
  while(Serial.available() <= 1)
    ; 
  b = Serial.parseInt();
  Serial.println(b);
  analogWrite(3, b);
}
