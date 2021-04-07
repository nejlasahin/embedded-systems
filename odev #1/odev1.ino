//buton 
int buton1 = 7;
int buton2 = 6;
int buton3 = 5;

//led
int led[5]={13, 12, 11, 10, 9};

void setup()
{
  pinMode(buton1, INPUT);
  pinMode(buton2, INPUT);
  pinMode(buton3, INPUT);
  pinMode(led[0], OUTPUT);
  pinMode(led[1], OUTPUT);
  pinMode(led[2], OUTPUT);
  pinMode(led[3], OUTPUT);
  pinMode(led[4], OUTPUT);
}

void loop()
{
  // buton 1 kontrol
  if(digitalRead(buton1) == 1){
    buton1islem();
  }
    
  // buton 2 kontrol
  if(digitalRead(buton2) == 1){
    buton2islem();
  }  
  
  // buton 3 kontrol
  if(digitalRead(buton3) == 1){
    buton3islem();
  }
}

//buton 1 işlemleri
void buton1islem(){
  
    for(int j = 0; j <= 4; j++){ 
      digitalWrite(led[j], 1);
        delay(1000);
    } 
  
    for(int j = 0; j <= 4; j++){ 
      digitalWrite(led[j], 0);
    }     
    delay(1000);
  
}

//buton2 işlemleri
void buton2islem(){ 
  
    for(int j = 4; j >= 0; j--){ 
      digitalWrite(led[j], 1);
        delay(1000);
    } 
  
    for(int j = 0; j <= 4; j++){ 
      digitalWrite(led[j], 0);
    }     
    delay(1000);
  
}

// buton 3 işlemleri
void buton3islem(){
    for(int i = 1; i <= 10; i++){ 
      for(int j = 0; j<=4; j++){ 
        digitalWrite(led[j], 1);
      }
      delay(1000);
      
    for(int j = 0; j<=4; j++){ 
        digitalWrite(led[j], 0);
      }
      delay(1000);
    }
}
