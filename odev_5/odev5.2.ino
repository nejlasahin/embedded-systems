/////////////////////////////
///////// ARDUİNO 1 /////////
/////////////////////////////

#include <Wire.h>

int hiz = A0; 
int hizDevir; 
int hizDeger;

int yon = A1;
int yonDevir;
int yonDeger;

void setup() {
    Wire.begin(1);
    Wire.onRequest(veri_gonderim);
}
void loop() {
  delay(100);  
}

void veri_gonderim(){
  hizDevir = analogRead(hiz);
  hizDeger=map(hizDevir, 1023, 0, 0, 255);
  delay(200);
  
     
  yonDevir = analogRead(yon);
  yonDeger=map(yonDevir, 1023, 0, 0, 180);
  delay(200);
  Wire.write(hizDeger);
  Wire.write(yonDeger);

}

/////////////////////////////
///////// ARDUİNO 2 /////////
/////////////////////////////

#include <LiquidCrystal.h> 
#include <Servo.h>
#include <Wire.h>

Servo myservo;
LiquidCrystal lcd(13,12,11,10,9,8); 

int rpm;

int ileriLED = 6;
int geriLED = 5;

int hizDevir;
int yonDevir;

int DCmotor = 3; 

int aci;
int yon = 2;

void setup() {
  Wire.begin(); 
  lcd.begin(16,2);
  pinMode(DCmotor, OUTPUT); 
  pinMode(ileriLED, OUTPUT); 
  pinMode(geriLED, OUTPUT); 
  myservo.attach(7);
  myservo.write(0);
  
}
void loop() {
  Wire.requestFrom(1,2);
  delay(2);
  while(!Wire.available());
  hizDevir = Wire.read();
  yonDevir = Wire.read();
  
  //İleri - Geri Hareketi Belirleme
  if(yonDevir <= 20){
  	yon = -2;
  }else if(yonDevir >= 80){
    yon = 2;
  }
    
  lcd.setCursor(0, 0);
  lcd.print("yon :");
  lcd.setCursor(6, 0);
  
  //İleri - Geri Hareketiyle LED Yakma 
  if(yon > 0){
    digitalWrite(ileriLED, HIGH);
    digitalWrite(geriLED, LOW);
    lcd.print("ileri");
  }else{
    digitalWrite(ileriLED, LOW);
    digitalWrite(geriLED, HIGH);
    lcd.print("geri");
  }
    
  rpm=map(hizDevir,0,255.0,0,8447.0);
  lcd.setCursor(0, 1);
  lcd.print("rpm :");
  lcd.setCursor(6, 1);
  lcd.print(rpm);
  
  aci += yon;
       
  if(aci <= 0){
   aci = 0;
  }else if(aci >= 180){
  	aci = 180;
  }
  
  
  analogWrite(DCmotor, hizDevir); 
  myservo.write(aci);
  
  delay(300);
  lcd.clear();

}
