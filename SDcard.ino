#include <SPI.h> 
#include <SD.h>

int chip_select = 10;

#include <DHT.h>
#include <LiquidCrystal_I2C.h>

DHT dht(6, DHT11); 
LiquidCrystal_I2C lcd(0x27, 16, 2);

float temp, hum;
String x,y,z = ""; 


void setup() {
  // put your setup code here, to run once:
  pinMode(6, OUTPUT);
  
  Serial.begin(9600);
  dht.begin();

  if (!SD.begin(chip_select)) { 
    Serial.println("SD Card Error!");
    while(1); 
  }
  Serial.println("SD Card Initialised!");
  lcd.init();
  lcd.backlight();
}
// csv file 
// comma separated value
/* 
25, 67; 
25.1, 65; 
*/ 

void loop() {
  // put your main code here, to run repeatedly:
  File data = SD.open("climate.csv", FILE_WRITE);
  if (data) { 
    z = String(temp) + "," + String(hum);
    data.println(z);
    data.close();
  }
  else { 
    Serial.println("File open error!");

    delay(2000);
  }


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
