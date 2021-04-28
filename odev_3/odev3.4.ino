#include <LiquidCrystal.h> 

LiquidCrystal lcd(12,11,10,9,8,7); 

int kirmizi = 4;
int yesil = 5;
int buton = 6;
int sensor = 3;
int buzzer = 13;

bool durum = true;

void setup() {
  pinMode(kirmizi,OUTPUT);
  pinMode(yesil,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(buton,INPUT);
  pinMode(sensor,INPUT);
  lcd.begin(16,2); 
}

void loop() {
  
  if(digitalRead(sensor)) {
    while(durum){
      lcd.setCursor(0,0);  
      lcd.print("Tehlike var."); 
      digitalWrite(kirmizi, HIGH);
      digitalWrite(yesil, LOW);
      tone(buzzer, 15);
      delay(200);
      if(digitalRead(buton)){
        durum = !durum;
      }
    }
    noTone(buzzer);
    delay(200);
  }else {
    lcd.setCursor(0,0);  
    lcd.print("Tehlike yok."); 
    digitalWrite(kirmizi, LOW);
    digitalWrite(yesil, HIGH);
  
  }
  durum = true;
  delay(500);
  lcd.clear();

  
}