#include <LiquidCrystal.h> 

LiquidCrystal lcd(12,11,10,9,8,7); 

int mavi = 6;
int yesil = 5;
int kirmizi = 4;
float deger = 0;
float sicaklik = 0;
float sicaklik_gerilim = 0;
void setup() {
  pinMode(mavi,OUTPUT);
  pinMode(yesil,OUTPUT);
  pinMode(kirmizi,OUTPUT);
  lcd.begin(16,2); 
  Serial.begin(9600);
}

void loop() {
  deger = analogRead(A0);
  sicaklik_gerilim = deger*0.004882814; //mV dönüştürüyoruz.
  sicaklik_gerilim-=0.5;
  sicaklik = sicaklik_gerilim*100;
  
  
  lcd.setCursor(0,0);  
  lcd.print("Sicaklik :"); 
  lcd.setCursor(11,0);  
  lcd.print(sicaklik); 
  delay(500);
  
  if(sicaklik <= 20) {
    digitalWrite(mavi, HIGH);
    digitalWrite(yesil, LOW);
    digitalWrite(kirmizi, LOW);
  }else if(sicaklik <= 40 ) {
    digitalWrite(mavi, LOW);
    digitalWrite(yesil, HIGH);
    digitalWrite(kirmizi, LOW);
  }else if(sicaklik > 40 ) {
    digitalWrite(mavi, LOW);
    digitalWrite(yesil, LOW);
    digitalWrite(kirmizi, HIGH);
  }
  
  lcd.clear();
  
}