int x;
float v;
int brightness; 

void setup() {
  // put your setup code here, to run once:  
  Serial.begin(9600);
  pinMode(6, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  x = analogRead(A0);  
  brightness = map(x, 0, 1024, 0, 255);

  if(brightness >200) {
  analogWrite(6, brightness);
  Serial.println(brightness);
  delay(200);
  } else { 
    analogWrite(6, 0); 
  }
}
