int val;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(6, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Enter the Intensity: ");
  while(Serial.available() <= 1)
    ;
  val = Serial.parseInt();
  Serial.println(val);
  analogWrite(6, val); // 0 - 255, 0 = 0% duty cycle, 255 = 100% duty cycle
}
