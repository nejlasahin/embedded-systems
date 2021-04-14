//7 segment display pin ataması
int display[] = {11, 10, 9, 8, 7, 6, 5};

//buton
int buton1 = 4;
int buton2 = 3;
int buton3 = 2;

//baslat durdur
bool durum = false;

//zaman akısı
int zaman=0;

//transistör pin ataması
int transistors[] = {13, 12};

//display yönünü belirleme
int yon = 1;
int sol = 0;
int sag = 0;

//display sayı tanımlaması
int arr[][7] = {
// a, b, c, d, e, f, g
  {0, 0, 0, 0, 0, 0, 1}, //0
  {1, 0, 0, 1, 1, 1, 1}, //1
  {0, 0, 1, 0, 0, 1, 0}, //2
  {0, 0, 0, 0, 1, 1, 0}, //3
  {1, 0, 0, 1, 1, 0, 0}, //4
  {0, 1, 0, 0, 1, 0, 0}, //5
  {0, 1, 0, 0, 0, 0, 0}, //6
  {0, 0, 0, 1, 1, 1, 1}, //7
  {0, 0, 0, 0, 0, 0, 0}, //8
  {0, 0, 0, 0, 1, 0, 0}  //9  
};

//potansiyometre için hız tanımı
int hiz=0;

void setup()
{  
  for(int i=0; i<7; i++){
    pinMode(display[i], OUTPUT);
  }
  
  pinMode(transistors[0], OUTPUT);
  pinMode(transistors[1], OUTPUT);
  
  pinMode(buton1, INPUT);
  pinMode(buton2, INPUT);
  pinMode(buton3, INPUT);

  Serial.begin(9600);
}

void loop() {
  hiz = abs(analogRead(A0)) + 200;
  Serial.println(hiz);
  
  // BAŞLAT - DURDUR
  if(digitalRead(buton1) == HIGH){
    durum=!durum; 
  }
  
  //GERİ
  if(digitalRead(buton2) == HIGH || abs(analogRead(A1)) <= 300 ){
    yon = -1; 
  }
  
  //İLERİ
  if(digitalRead(buton3) == HIGH || abs(analogRead(A1)) >= 900 ){
    yon = 1; 
  }
  
  //DURDUĞU ANDA
  if(!durum){
     sol = zaman%10; 
     sag = (zaman/10)%10;
     rakamYaz(sol, sag);
  }
  
  //BAŞLADIĞI ANDA
  if(durum){
     sol = zaman%10; 
     sag = (zaman/10)%10;
     rakamYaz(sol, sag);
  	 zaman=zaman + yon;
  	if(zaman>99 || zaman < 0){
    	zaman=0;
  	}  
  }
}

void rakamYaz(int sol, int sag)
{
  digitalWrite(transistors[1], LOW);
  digitalWrite(transistors[0], HIGH);
  yaz(sol);
  delay(50);
  digitalWrite(transistors[0], LOW);
  digitalWrite(transistors[1], HIGH);
  yaz(sag);   
  
  delay(hiz);
}

void yaz(int j){
  for(int i=0; i<7; i++){
    digitalWrite(display[i], arr[j][i]);
  }
}
