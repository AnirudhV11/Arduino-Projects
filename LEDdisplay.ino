#include<Wire.h>
#include<LiquidCrystal_I2C.h> 


LiquidCrystal_I2C lcd(0x27, 16, 2);
// first parameter is the address in hexa decimal
// second one is the no. of characters per row 
// third one is the number of rows 
int t;
void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0,0);
  lcd.print("Hello");
  randomSeed(analogRead(0));
  t = random(1,7);
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(t);
  delay(1000);
  t = t+1;
}

// connect a button 
// sound buzzer maybe for 50 ms
// when you press the switch - show a random number between 1 - 6 

// ambient light monitor 
// it will use the ldr and show the data on the display
