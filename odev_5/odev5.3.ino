/////////////////////////////
///////// ARDUİNO 1 /////////
/////////////////////////////

#define CLK 10
#define SS 11
#define MOSI 12
#define MISO 13

#define FALSE 0
#define TRUE !FALSE

void setBits(char keypressed);


unsigned long prevTick = 0.0;
unsigned long lastTime = 0.0;
int clockState = LOW;
int prevClkState = LOW;
unsigned int clkCounter = 0;
unsigned int pressTime;
char keypressed;
int bitNum[4];
int bitSent[] = {FALSE, FALSE, FALSE, FALSE};
int bitsToSend = 0;
int ii;

int hiz = A0; 
int hizDevir; 
int hizDeger;
char hizKarakter;


int yon = A1;
int yonDevir;
int yonDeger;
char yonKarakter;

bool durum=false;

void setup() {
  
  	pinMode(CLK, OUTPUT);
	pinMode(MOSI, OUTPUT);
    pinMode(MISO, INPUT);
	pinMode(SS, OUTPUT);
  
	digitalWrite(CLK, LOW);
	digitalWrite(MOSI, LOW);
  	digitalWrite(SS, HIGH);
  
  	Serial.begin(9600);
  
}
void loop() {
  
  hizDevir = analogRead(hiz);
  hizDeger=map(hizDevir, 1023, 0, 0, 255);
  
  yonDevir = analogRead(yon);
  yonDeger=map(yonDevir, 1023, 0, 0, 180);
    
  //Saat durumu
  if ((millis() - prevTick ) >= 1000) //1000ms'yi geçti mi
  	{
    	clockState = !clockState; //tersini al
    	digitalWrite(CLK, clockState);
      	prevTick = millis(); //zamanlamayı yeniden başlat
      	clkCounter++;
    }
  	
  	//Veri gönderme
  	if(bitsToSend > 0)
    {
    	if (!(bitSent[bitsToSend - 1])) //sonraki bitin gönderilip gönderilmediği kontrolü
        {  
            if((clkCounter - pressTime) > (-1 * bitsToSend + 5)) // bitin gönderilmesi için zaman kontrolü
            {
            	if((clockState == LOW) && ((millis() - lastTime) > 1000)) 
                {
    	    		digitalWrite(SS, LOW); // Slave e mesaj geldiğini bildirir
                  	digitalWrite(MOSI, bitNum[bitsToSend - 1]); //mevcut biti MOSI satırına yazar
          			bitSent[bitsToSend - 1] = TRUE; // bitin gönderildigini kaydeder
          			bitsToSend--; 
                  	lastTime = millis(); // bitin gönderildigi zamanı atar
                } 
            } 
        }
    }
	else 
    {
  		if(digitalRead(MISO) == HIGH) // Slaveden alındı onayı
        {
      		if((millis() - lastTime) > 2000)
            {
          		digitalWrite(SS, HIGH); // mesaj gonderilip onaylandıysa iletimi sonlandırma
              	digitalWrite(MOSI, LOW); // MOSI yı kapatma - sıfırlama
            }
        }
      
        if(yonDeger <= 20){
  			yonKarakter = '1';
  		}else if(yonDeger >= 80){
    		yonKarakter = '0';
  		}
  
  	    if(hizDeger <= 55){
  			hizKarakter = '3';
  		}else if(hizDeger >= 200){
    		hizKarakter = '2';
  		}
      	
      	if(durum){
        	setBits(yonKarakter); // hex kodlarını bite dönüştürme işlemi
          	durum=!durum;
      	}else{ 
        	setBits(hizKarakter); // hex kodlarını bite dönüştürme işlemi
          	durum=!durum;
      	}
        
  		pressTime = clkCounter;
  		lastTime = millis();
  		bitsToSend = 4; // gönderilen bit sayısı
  		for(ii = 0 ; ii < 4 ; ii++) bitSent[ii] = FALSE;
      	Serial.print(yonKarakter);

      	
    } 	
  	delay(10); 
}

void setBits(char deger)
{
  	switch(deger)
    {
    	case '0': // 0  - ileri yön
           	bitNum[3] = 0;
      		bitNum[2] = 0;
      		bitNum[1] = 0;
      		bitNum[0] = 0;
      		break;
    	case '1': // 1 - geri yön
           	bitNum[3] = 0;
      		bitNum[2] = 0;
      		bitNum[1] = 0;
      		bitNum[0] = 1;
      		break;      
    	case '2': // 2 - hız arttırma
           	bitNum[3] = 0;
      		bitNum[2] = 0;
      		bitNum[1] = 1;
      		bitNum[0] = 0;
      		break;      	
    	case '3': // 3 - hız yavaşlatma
           	bitNum[3] = 0;
      		bitNum[2] = 0;
      		bitNum[1] = 1;
      		bitNum[0] = 1;
      		break;      	
    }
}

/////////////////////////////
///////// ARDUİNO 2 /////////
/////////////////////////////

#include <LiquidCrystal.h> 
#include <Servo.h>

#define CLK 10
#define SS 11
#define MOSI 12
#define MISO 13

Servo myservo;
LiquidCrystal lcd(9,8,4,2,1,0); 

int clkState = LOW;
int prevClkState = LOW;
byte data = 0x00; // bitlerin depolandıgı adres
int bitPos = 3; // bit konumu
unsigned long timerStart;

int deger;
int rpm;

int ileriLED = 6;
int geriLED = 5;

int DCmotor = 3; 

int aci = 0;
int yon = 0;

void setup() {
  pinMode(CLK, INPUT);
  pinMode(MOSI, INPUT);
  pinMode(MISO, OUTPUT);
  pinMode(SS, INPUT);
  
  digitalWrite(MISO, LOW);
  
  lcd.begin(16,2);
  pinMode(DCmotor, OUTPUT); 
  pinMode(ileriLED, OUTPUT); 
  pinMode(geriLED, OUTPUT);   
  myservo.attach(7);
  myservo.write(0);

}
void loop() {
  clkState = digitalRead(CLK); // clock degerini alıyoruz
  	if (clkState != prevClkState) // degişip degişmedigini kontrol ediyoruz
    {
       	prevClkState = clkState;
      	if (digitalRead(SS) == LOW) // slave mesaj alıcak mı
      	{
          	if (clkState == HIGH) // clock değişikligi düşükten yüksege ise
            {
            	if (digitalRead(MOSI) == LOW) // MOSI düşükse lowsa bit 0
                {
                	data &= ~(0x01 << bitPos); 
                  	bitPos--; 
                }
              	else // MOSI yüksekse
                {
                  	data |= (0x01 << bitPos); 
                  	bitPos--;
                }
              	if (bitPos < 0) // tüm bitler okunduysa
                {  	
                  	delay(500);
                  	digitalWrite(MISO, HIGH); // alındı sinyali gönderilir
                    delay(1000);
                  	digitalWrite(MISO, LOW);
                    bitPos = 3; // başlangıç pozisyonuna döner
                    deger = (int)data;

                  if(deger == 1){
  						yon = -2;
  					}else if(deger == 0){
   					 yon = 2;
  					}else if(deger == 3){
  						rpm=1732;
  					}else{
    					rpm = 3960;
  					}					
                }
            }
        }
    }
  
  
  //İleri - Geri Hareketi Belirleme

    
  lcd.setCursor(0, 0);
  lcd.print("yon :");
  lcd.setCursor(6, 0);
  
  //İleri - Geri Hareketiyle LED Yakma 
  if(yon == 2){
    digitalWrite(ileriLED, HIGH);
    digitalWrite(geriLED, LOW);
    lcd.print("ileri");
  }else{
    digitalWrite(ileriLED, LOW);
    digitalWrite(geriLED, HIGH);
    lcd.print("geri");
  }
     
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
  
  
  analogWrite(DCmotor, rpm); 
  myservo.write(aci);
  
  delay(300);
  lcd.clear();

}
