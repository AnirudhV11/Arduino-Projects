// 0 - green 
// 1 - red

int status = 0; 

void setup() {
  // put your setup code here, to run once:
pinMode(9, OUTPUT);
pinMode(8, OUTPUT);
pinMode(7, OUTPUT);

Serial.begin(9600);
pinMode(6, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(6) == HIGH) { 
    delay(40);

    if(status == 0) { 
      switch_to_red();  
    } 
    else { 
      switch_to_green();
    }
    while(digitalRead(6) != LOW)
      ;
  }
}
void switch_to_red() { 
  digitalWrite(7, LOW); 
  digitalWrite(9, HIGH);
  status = 1;
}

void switch_to_green() { 
  digitalWrite(9, LOW);
  digitalWrite(7, HIGH); 
  status = 0;
}