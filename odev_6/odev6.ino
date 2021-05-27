/////////////////////////////
///////// ARDUİNO 1 /////////
/////////////////////////////

#include <LiquidCrystal.h> 

LiquidCrystal lcd(13, 12, 11, 10, 9, 8); 

int sistemButon = 3;
int sensorButon = 2;

int girisLed = 7;

bool sistemDurum = false;
bool sensorDurum = true;

int sensorInterrupt = 1;
int sistemInterrupt = 0;

void setup()
{
  lcd.begin(16,2);
  pinMode(sistemButon, INPUT);
  pinMode(sensorButon, INPUT);
  pinMode(girisLed, OUTPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(sistemButon), sistemKontrol, FALLING);
  attachInterrupt(digitalPinToInterrupt(sensorButon), sensorKontrol, FALLING);
}

void loop()
{
  if(Serial.available()){
  sensorInterrupt = Serial.read();
  sensorDurum = false;
  }
  lcd.clear();
  if(!sistemDurum){
    lcd.setCursor(0, 0);
  	lcd.print("Sistemi Aktif");
    lcd.setCursor(0, 1);
    lcd.print("Ediniz.");
    delay(100);
  }else{
    if(sensorDurum==false){
  		lcd.setCursor(0, 0);
  		lcd.print("Tehlike !");
    	delay(100);
    }else {
      	lcd.setCursor(0, 0);
  		lcd.print("Tehlike Yok.");
    	delay(100);
    }
  }
}


void sensorKontrol(){
  
  sensorDurum = true;
  Serial.write(sensorInterrupt);
  
}

void sistemKontrol(){
	sistemDurum = true;
  	Serial.write(sistemInterrupt);
  	digitalWrite(girisLed, HIGH);
    lcd.clear();
  	lcd.setCursor(0, 0);
  	lcd.print("Sistemi Giris");
    lcd.setCursor(0, 1);
    lcd.print("Yapildi.");
}

/////////////////////////////
///////// ARDUİNO 2 /////////
/////////////////////////////

int sensor =3;
int girisLed = 13;
int buzzer = 12;

bool sistemDurum = false;
bool sensorDurum = true;

int sistemInterrupt;
int sensorInterrupt;

void setup()
{
  pinMode(sensor, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(girisLed, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(sensor),sensorKontrol,RISING);
  Serial.begin(9600);
}

void loop()
{
  if(sistemDurum==false){
    while(!Serial.available());
  	sistemInterrupt = Serial.read();
	sistemDurum = true;
    digitalWrite(girisLed, HIGH);
  }else{
    if(sensorDurum==false){
       tone(buzzer, 15);
       delay(200);
  	   while(!Serial.available());
       sensorInterrupt = Serial.read();
       sensorDurum = true;
    }else{
       noTone(buzzer);
       delay(200);
    }
  }
  

}

void sensorKontrol(){
  sensorDurum = false;
  Serial.write(sensorDurum);
}
