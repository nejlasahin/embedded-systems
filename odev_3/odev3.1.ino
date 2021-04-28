#include <LiquidCrystal.h> 

LiquidCrystal lcd(12,11,10,9,8,7); 
int deger;
int led = 13;

void setup() {
  pinMode(led,OUTPUT);
  lcd.begin(16,2); //Satır ve sütunların sayısı 
  				   //lcd.begin (sütunlar, satırlar) olarak belirtilir.
}

void loop() {
 
  deger = analogRead(A0);
  if(deger <= 900){
    lcd.setCursor(0,0);  
    lcd.print("Ortam Karanlik"); 
    lcd.setCursor(0,1);  
    lcd.print("Isik acik"); 
    digitalWrite(led, 1);
  }else if(deger > 900){
    lcd.setCursor(0,0);  
    lcd.print("Ortam Aydinlik"); 
    lcd.setCursor(0,1);  
    lcd.print("Isik kapali"); 
    digitalWrite(led, 0);
  }
  delay(500);
  lcd.clear();
}