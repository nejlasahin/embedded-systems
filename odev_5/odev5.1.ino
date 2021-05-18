/////////////////////////////
///////// ARDUİNO 1 /////////
/////////////////////////////

int hiz = A0; 
int hizDevir; 
int hizDeger;

int yon = A1;
int yonDevir;
int yonDeger;

void setup() {
    Serial.begin(9600); // UART işlemi 
}
void loop() {
  
  
  
  hizDevir = analogRead(hiz);
  hizDeger=map(hizDevir, 1023, 0, 0, 255);
  delay(200);
  Serial.write(hizDeger);
     
  yonDevir = analogRead(yon);
  yonDeger=map(yonDevir, 1023, 0, 0, 180);
  delay(200);
  Serial.write(yonDeger);
}

/////////////////////////////
///////// ARDUİNO 2 /////////
/////////////////////////////

int hiz = A0; 
int hizDevir; 
int hizDeger;

int yon = A1;
int yonDevir;
int yonDeger;

void setup() {
    Serial.begin(9600); // UART işlemi 
}
void loop() {
  
  
  
  hizDevir = analogRead(hiz);
  hizDeger=map(hizDevir, 1023, 0, 0, 255);
  delay(200);
  Serial.write(hizDeger);
     
  yonDevir = analogRead(yon);
  yonDeger=map(yonDevir, 1023, 0, 0, 180);
  delay(200);
  Serial.write(yonDeger);
}
