#include <LiquidCrystal.h> 

LiquidCrystal lcd(12,11,10,9,8,7); 
int eko = 5;
int tetikleme = 6;
int buzzer = 13;

float sure, mesafe;

void setup() {
  pinMode(eko,INPUT);
  pinMode(tetikleme,OUTPUT);
  pinMode(buzzer,OUTPUT);
  lcd.begin(16,2); 
}

void loop() {
  digitalWrite(tetikleme,LOW); //İlk olarak trip pinimizi low durumunda başlatıyoruz.
  delayMicroseconds(5); //5 Mikrosaniye(saniyenin milyonda biri) beklemesini belirtiyoruz.
  digitalWrite(tetikleme, HIGH); //Daha sonra pinimizin ses dalgası göndermesi için emir veriyoruz.
  delayMicroseconds(5); 
  digitalWrite(tetikleme,LOW); //Yeni ses dalgası üretebilmesi için trig pinimizi pasif durumuna getiriyoruz.
  sure = pulseIn(eko, HIGH); //Gönderilen ses dalgasının geri dönmesindeki süre ölçülüyor. 
  mesafe = (sure / 29) /2;   
  
  lcd.setCursor(0,0);  
  lcd.print("Mesafe :"); 
  lcd.setCursor(9,0);  
  lcd.print(mesafe);
    
  delay(300);
  
  if (mesafe > 150 && mesafe <300 ){
 	tone(buzzer, 15); // 15 hertzlik sinyal gönderiyoruz.
    delay(200); // 200 ms de bir
	noTone(buzzer);	// sinyali kapatıyoruz
    delay(200);
  }else if (mesafe > 40 && mesafe <=150 ){
 	tone(buzzer, 15); // 15 hertzlik sinyal gönderiyoruz.
    delay(100); // 100 msde bir
    noTone(buzzer);	// sinyali kapatıyoruz
    delay(100); 
  }else if(mesafe > 0 && mesafe <=40){
 	tone(buzzer, 15); // 15 hertzlik sinyal gönderiyoruz.
    delay(50); 
  }
  
  lcd.clear();
  
}