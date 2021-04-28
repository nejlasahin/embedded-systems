#include <LiquidCrystal.h> 
#include <Keypad.h>
#include <SoftwareSerial.h>

LiquidCrystal lcd(13,12,11,10,9,8); 

const byte satir=4; // Satır sayımız
const byte kolon=4; // Sütun/kolon sayımız

char tus_takimi[4][4]={
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}  
};
byte satirPinleri[satir]={7,6,5,4};
byte kolonPinleri[kolon]={3,2,18,19};
Keypad tuslar=Keypad(makeKeymap(tus_takimi),satirPinleri,kolonPinleri,satir,kolon);


int forceSensor = A0;
int fotoSensor = A1;
int sicaklikSensor = A2;

int force=0;
String Sforce;
int foto=0;
String Sfoto;
int sicaklik=25;
String Ssicaklik;

char tus;
  
void setup()
{
  lcd.begin(16,2);
  Serial.begin(9600);
}

void loop()
{
  lcd.clear();
  lcd.print(force);
  lcd.print("N");
  lcd.setCursor(4,0);
  lcd.print(foto);
  lcd.print("LDR");
  lcd.setCursor(10,0);
  lcd.print(sicaklik);
  lcd.print("C");
  delay(100);
  lcd.clear();
  tus=tuslar.getKey();
  switch(tus){
  	case 'A':
    Serial.write('A');
    	lcd.print("Guc : ");
    	lcd.setCursor(6,0);
    	while(tuslar.getKey() != 'D'){
      	tus=tuslar.getKey();
      		if(tus != 'D' && tus){
        		Sforce += tus;
    			lcd.print(tus);
      		}
    	}
    force = Sforce.toInt();
    Serial.write(force);
    Sforce="";
    break;
    case 'B':
    Serial.write('B');
    	lcd.print("LDR : ");
    	lcd.setCursor(6,0);
    	while(tuslar.getKey() != 'D'){
      		tus=tuslar.getKey();
      		if(tus != 'D' && tus){
        		Sfoto += tus;
    			lcd.print(tus);
      		}
    	}
    foto = Sfoto.toInt();
    Serial.write(foto);
    Sfoto="";
    break;
    case 'C':
    Serial.write('C');
    	lcd.print("Sicaklik : ");
    	lcd.setCursor(11,0);
    	while(tuslar.getKey() != 'D'){
      		tus=tuslar.getKey();
      		if(tus != 'D' && tus){
        		Ssicaklik += tus;
    			lcd.print(tus);
      		}
    	}
    sicaklik = Ssicaklik.toInt();
    Serial.write(sicaklik);
    Ssicaklik="";
    break;
  }
}