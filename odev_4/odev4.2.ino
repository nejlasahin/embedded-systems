#include <Servo.h>
#include <LiquidCrystal.h> 
#include <SoftwareSerial.h>

LiquidCrystal lcd(13,12,11,10,9,8); 

Servo myservo;

int forceS;
int fotoS;
int sicaklikS;

int deger;
int sensor;

void setup()
{
  myservo.attach(6);
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);
  Serial.begin(9600);
  lcd.begin(16,2);

}

void loop()
{
  if(Serial.available()){
    deger= Serial.read();
    while(!Serial.available());
    sensor= Serial.read();
    if(deger==65){
    	forceS=sensor;
    }else if(deger==66){
      	fotoS=sensor;
    }else if(deger==67){
      	sicaklikS=sensor;
    }
    Serial.print(deger);
    Serial.print(sensor);
  }               
  
  if(forceS <= 5){
    digitalWrite(7, LOW);
  }else if(forceS > 5 ){
    digitalWrite(7, HIGH);
  	lcd.print("Titresim Motoru");
    lcd.setCursor(0, 1);
    lcd.print("Calisti");
  }
  
  if(fotoS > 50){
    myservo.write(45); 
    lcd.print("Servo Motoru");
    lcd.setCursor(0, 1);
    lcd.print("Calisti");
  }else if(fotoS <= 50 ){
    myservo.write(0);   
  }
  
  if(sicaklikS > 30){
    digitalWrite(5, HIGH);
    lcd.print("DC Motoru");
    lcd.setCursor(0, 1);
    lcd.print("Calisti");
  }else if(sicaklikS <= 30 ){
    digitalWrite(5, LOW);
  }
  
  delay(500);
  lcd.clear();
}