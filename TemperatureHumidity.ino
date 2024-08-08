#include <DHT.h>
#include <LiquidCrystal_I2C.h>

DHT dht(4, DHT11); 
LiquidCrystal_I2C lcd(0x27, 16, 2);

float temp, hum;
String x,y = ""; 


void setup() {
  // put your setup code here, to run once:
  pinMode(6, OUTPUT);
  
  Serial.begin(9600);
  dht.begin();

  lcd.init();
  lcd.backlight();
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  lcd.setCursor(0,0);

  if (digitalRead(6) == HIGH) {
    temp = dht.readTemperature();
    x = "temp = " + String(temp) + " C";
  } else { 
    temp = dht.readTemperature(true);
    x = "temp = " + String(temp) + " F";
  }

  hum = dht.readHumidity();
  
  y = " hum = " + String(hum) + "%";
  
  Serial.println(x);
  Serial.println(y);
  lcd.print(x);

  lcd.setCursor(0,1);
  lcd.print(y);

  delay(500);
  
}
