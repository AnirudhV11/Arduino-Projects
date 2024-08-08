// ph = A1; TDS = A0; button = D6; led green = 8; led red = 9; lcd = I2C; turbidity =  A3; potentiometer = A2; 
#include<SD.h>
#include<SPI.h>

int cs = 10; // chip select pin
int sd_active = 1; 

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

float ph, TDS, turbidity; 
float calib_value = 0.0; 

int green = 8, red = 9;

float TDS_thresh = 300, ph_range = 1.5, turbidity_thresh = 400;
int res; 

void setup() {
  // put your setup code here, to run once:
  pinMode(6, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);

  Serial.begin(9600);

  init_sd();

  lcd.init();
  lcd.backlight();
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Welcome User!");
  while(digitalRead(6) == LOW);
  delay(200);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Press the button");
  lcd.setCursor(0,1);
  lcd.print("to scan pH!");
  while(digitalRead(6) == LOW);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Scanning...");
  ph = read_ph();
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Press the button");
  lcd.setCursor(0,1);
  lcd.print("to scan TDS!");
  while(digitalRead(6) == LOW);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Scanning...");
  TDS = read_TDS(); 
  lcd.clear(); 

/*
  lcd.setCursor(0,0);
  lcd.print("Press the button");
  lcd.setCursor(0,1);
  lcd.print("scan turbidity!");
  while(digitalRead(6) == LOW); 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Scanning...");
  turbidity = read_turbidity();
  lcd.clear(); 
  delay(500);*/

  if(ph > 7 - ph_range && ph < 7 + ph_range /*&& turbidity < turbidity_thresh*/ && TDS < TDS_thresh) { 
    digitalWrite(green, HIGH);
    digitalWrite(red, LOW); 
    res = 1;
  } else{ 
    digitalWrite(red, HIGH); 
    digitalWrite(green, LOW);
    res = 0; 
  }

  Serial.print(String(ph) + " " + String(TDS) + " " + String(turbidity));
  store_data(ph, TDS, turbidity); 
  show_results(res, ph, TDS, turbidity);
}

void init_sd() { 
  if(!SD.begin(cs)) { 
    Serial.println("SD initialising failed!");
    sd_active = 0;
  } else {
    Serial.println("SD connected!");
  }
}

void show_results(int result, float ph, float TDS, float turbidity) { 
  // Line 1 - quality - good/bad 
  // line 2 - ph results
  // line 3 - tds results 
  // line 4 - turbidity results 
  int opt, opt_prev = -1;
  while(digitalRead(6) == LOW) { 
      int x = analogRead(A2); 

      if(x >= 0 && x < 250) { 
        opt = 0;
      } else if(x >= 250 && x < 500) { 
        opt = 1;
      } else if(x >= 500 && x < 750) { 
        opt = 2;
      } else { 
        opt = 3;
      }

      Serial.println(String(opt) + " " + String(x)); 

      if(opt == opt_prev) { 
        delay(200); 
        continue;
      }

      opt_prev = opt; 

      
      if(opt == 0) { 
        lcd.clear(); 
        lcd.setCursor(0,0); 
        lcd.print("Water Quality: "); 
        lcd.setCursor(0,1); 
        if(result == 1) {
          lcd.print("Good");
        } else { 
          lcd.print("Bad");
        }
      } else if(opt == 1) {
        lcd.clear(); 
        lcd.setCursor(0,0); 
        lcd.print("pH value: "); 
        lcd.setCursor(0,1); 
        lcd.print(ph);
      } else if(opt == 2) {
        lcd.clear(); 
        lcd.setCursor(0,0); 
        lcd.print("TDS Value: "); 
        lcd.setCursor(0,1); 
        lcd.print(TDS);
    } else if(opt == 3) { 
      lcd.clear(); 
        lcd.setCursor(0,0); 
        lcd.print("Turbidity Value: "); 
        lcd.setCursor(0,1); 
        lcd.print(turbidity);
    }
    delay(200);
  }
}

void store_data(float ph, float TDS, float turbidity) { 
  if(sd_active == 0) { 
    return;
  }
  
  File file = SD.open("Water.csv", FILE_WRITE); 
  if(file) { 
    file.print(ph); 
    file.print(","); 
    file.print(TDS);
    file.print(",");
    file.println(turbidity);
    file.close();

    Serial.println("Data stored!"); 
  } else { 
    Serial.println("Data store error!");
  }
}


  float read_ph()
{
    float s1, s2, d;
    float threshold = 0.15;

    while(1)
    {
      s1 = read_ph_once();
      delay(5000);
      s2 = read_ph_once();
      d = s1 - s2; 
      Serial.println(String(s1)+ " "+String(s2) + " " + String(d));

      if(abs(d) > threshold)
        Serial.println("Bad Data, Wait longer");
      else
      {
        Serial.println(s1);
        return s1;
}
    }
}
float read_ph_once()
{
  float volt, ph, x, avg = 0.0;
  for(int i = 0 ; i < 10 ; i++)
  {
    x = analogRead(A1);
    volt = x / 1024.0 * 5.0;
    ph = 3.5 * volt + calib_value;
    avg += ph;
    delay(500);
  }
  avg = avg / 10;
  return avg;
}

float read_TDS() { 
  float avg = 0.0, volt, x, TDS; 
  for(int i = 0 ; i < 10 ; i++)
  {
    x = analogRead(A0);
    volt = x / 1024.0 * 5.0;
    avg += volt;
    delay(500);
  }
  avg = avg / 10;
  TDS = 318.38 * avg - 7.054;
  Serial.println(TDS);
  Serial.println(avg);
  return TDS;
}

float read_turbidity() { 
  float avg = 0.0;
  for(int i = 0 ; i < 50 ; i++)
  {
    int x = analogRead(A3);
    x = x + 3; 
    Serial.println(String(x) + "hello");
    float v = x / 1024.0 * 5.0;
    float ntu = -1120.4*square(v)+5742.3*v-4353.8;
    ntu *= -1;

    if(ntu < 0) { 
      ntu = 0;
    }
    
    avg += ntu;
    delay(100);
  } 
  avg = avg / 50;
 

  if(avg < 0) { 
    return 0;
  } else {
    return avg;
  }
  
}

