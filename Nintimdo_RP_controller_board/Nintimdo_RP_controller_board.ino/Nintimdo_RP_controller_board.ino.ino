int analogLV=512;
int analogLH=512;
int analogRV=512;
int analogRH=512;
int GAIN=2;
//calabrate analog
int LVC=480;
int LHC=500;
int RVC=502;
int RHC=503;
int i=1;
int j=100;
int k=0;
int vol_lvl=0;
int prev_vol=vol_lvl;
int counter=0;
int timeout=0;
bool right=LOW;
bool left=LOW;
int BL_lvl=2;
float battery_lvl;
float battery_full=4.1;                // read 4.62
float battery_dead=3;
float range=(battery_full-battery_dead)/5;
float tempC=0;
float fan=128;
int proc_temp=25;

void setup() {
  Serial.begin(9600);
  pinMode(0,OUTPUT);            //LED0
  pinMode(14,OUTPUT);           //LED1
  pinMode(15,OUTPUT);           //LED2
  pinMode(16,OUTPUT);           //LED3
  pinMode(27,OUTPUT);           //LED4
  pinMode(1,INPUT_PULLUP);      //PWR
  pinMode(20,INPUT_PULLUP);     //A 
  pinMode(24,INPUT_PULLUP);     //B
  pinMode(23,INPUT_PULLUP);     //X
  pinMode(21,INPUT_PULLUP);     //Y
  pinMode(8,INPUT_PULLUP);      //UP 
  pinMode(11,INPUT_PULLUP);      //DOWN
  pinMode(4,INPUT_PULLUP);      //RIGHT
  pinMode(9,INPUT_PULLUP);      //LEFT
  pinMode(7,INPUT_PULLUP);      //START
  pinMode(5,INPUT_PULLUP);      //SELECT
  pinMode(38,INPUT);     //ANALOG LEFT VERTICAL
  pinMode(39,INPUT);     //ANALOG LEFT HORIZONTAL
  pinMode(41,INPUT);     //ANALOG RIGHT VERTICAL
  pinMode(40,INPUT);     //ANALOG RIGHT HORIZONTAL
  pinMode(3,INPUT_PULLUP);      //LEFT BUMPER
  pinMode(26,INPUT_PULLUP);     //RIGHT BUMPER
  pinMode(2,INPUT_PULLUP);      //LEFT TRIGGER
  pinMode(25,INPUT_PULLUP);     //RIGHT TRIGGER
  pinMode(22,INPUT_PULLUP);     //HOME
  pinMode(44,OUTPUT);            //FAN
  pinMode(42,INPUT);            //TEMP
  pinMode(18,OUTPUT);           //TEMP VDD
  pinMode(13,OUTPUT);           //Speaker
  pinMode(19,OUTPUT);           //NMOS for battery read
  pinMode(43,INPUT);            //Battery voltage read
}

void loop() {
  
   boot();

   for(;;){
     analogLV=-1*(-511+GAIN*(analogRead(38)-LVC)); //invert 
     if(analogLV>1023){
      analogLV=1023;
     }
     else if(analogLV<0){
      analogLV=0;
     }
     Joystick.Y(analogLV);
     analogLH=512+GAIN*(analogRead(39)-LHC);
     if(analogLH>1023){
      analogLH=1023;
     }
     else if(analogLH<0){
      analogLH=0;
     }
     Joystick.X(analogLH);
     analogRV=512+GAIN*(analogRead(41)-RVC);
     if(analogRV>1023){
      analogRV=1023;
     }
     else if(analogRV<0){
      analogRV=0;
     }
     Joystick.Z(analogRV);
     analogRH=512+GAIN*(analogRead(40)-RHC);
     if(analogRH>1023){
      analogRH=1023;
     }
     else if(analogRH<0){
      analogRH=0;
     }
     Joystick.Zrotate(analogRH);

    if(digitalRead(20)==LOW){   
      Joystick.button(1,1);
      }
    else{
      Joystick.button(1,0);
      }
    if(digitalRead(24)==LOW){   
      Joystick.button(2,1);
      }
    else{
      Joystick.button(2,0);
      }
    if(digitalRead(23)==LOW){   
      Joystick.button(3,1);
      }
    else{
      Joystick.button(3,0);
      }
    if(digitalRead(21)==LOW){   
      Joystick.button(4,1);
      }
    else{
      Joystick.button(4,0);
      }
     if(digitalRead(8)==LOW){   
      Joystick.button(5,1);
      }
    else{
      Joystick.button(5,0);
      }
    if(digitalRead(11)==LOW){   
      Joystick.button(6,1);
      }
    else{
      Joystick.button(6,0);
      }
    if(digitalRead(4)==LOW){   
      Joystick.button(7,1);
      }
    else{
      Joystick.button(7,0);
      }
    if(digitalRead(9)==LOW){   
      Joystick.button(8,1);
      }
    else{
      Joystick.button(8,0);
      }
    if(digitalRead(7)==LOW){  
      while(digitalRead(7)==LOW){ //Test to see if this debounces
        
        }
      Joystick.button(9,1);
      }
    else{
      Joystick.button(9,0);
      }
    if(digitalRead(5)==LOW){      //select
        while(digitalRead(5)==LOW){            //hotkey hold
          if(digitalRead(2)==LOW){    //left=brightness lower
            if(counter%8==0){
              display_lvl(-1);
              timeout=0;
            }
          }
          if(digitalRead(25)==LOW){   //right=brightness higher
            if(counter%8==0){
              display_lvl(1);
              timeout=0;
            }
          }
          delay(50);
          counter++;
          timeout++;
          if (counter>100){
            counter=0;
          }
          if(timeout>50){
            analogWrite(0,0);
            analogWrite(14,0);
            analogWrite(15,0); 
            analogWrite(16,0); 
            analogWrite(27,0);
          }
        }
      Joystick.button(10,1);
      }
    else{
      Joystick.button(10,0);
      }
    if(digitalRead(3)==LOW){   
      Joystick.button(13,1);
      }
    else{
      Joystick.button(13,0);
      }
    if(digitalRead(26)==LOW){   
      Joystick.button(12,1);
      }
    else{
      Joystick.button(12,0);
      }
    if(digitalRead(2)==LOW){   
      Joystick.button(11,1);
      if(counter%8==0){
      volume_lvl(-1);
      timeout=0;
      }
    }
    else{
      Joystick.button(11,0);
      left=LOW;
      }
    if(digitalRead(25)==LOW){   
      Joystick.button(14,1);
      if(counter%8==0){
      volume_lvl(1);
      timeout=0;
      }
    }
    else{
      Joystick.button(14,0);
      }
    if(digitalRead(22)==LOW){ //home=press start and select  
      while(digitalRead(22)==LOW){
        //debounce
      }
      Joystick.button(9,1);
      Joystick.button(10,1);
      }
    else{
      Joystick.button(9,0);
      Joystick.button(10,0);
      }


  if(digitalRead(1)==LOW){ 
    battery();
    counter=0;
    timeout=0;
    while(digitalRead(1)==LOW){
      if(counter>100){
        pwr_down();  
      }
      counter++;
      delay(15);
    }
   }
  //FAN
  /*
  if(counter%8==0){
  digitalWrite(18,HIGH);
  tempC=(analogRead(42)-650)/10.0;
  Serial.println(tempC);
  if(tempC>proc_temp){
    fan=(tempC-proc_temp)*1000.0;
    Serial.println(fan);
    if(fan>255){
      fan=255;
    }
    if(fan<0){
      fan=0;
    }
    analogWrite(44,fan);
  }
  digitalWrite(18,LOW);
  }
  */
  //Light checks     
  counter++;
  timeout++;
  if (counter>100){
    counter=0;
  }
  if(timeout>50){
    analogWrite(0,0);
    analogWrite(14,0);
    analogWrite(15,0); 
    analogWrite(16,0); 
    analogWrite(27,0);
  }
  }
}


//--------------FUNCTIONS--------------------------------------------------------------------------------



void boot(){
  digitalWrite(13,HIGH);    //turn speakers off
  digitalWrite(19,LOW);     //turn battery read off
  digitalWrite(18,LOW);     //turn temp sensor off
  for(k=0;k<100;k++){
  analogWrite(0,random(0,2)*i);
  analogWrite(14,random(0,2)*i);
  analogWrite(15,random(0,2)*i);
  analogWrite(16,random(0,2)*i);
  analogWrite(27,random(0,2)*i);
  delay(100);
  }
  for(k=0;k<150;k++){
  analogWrite(0,k);
  analogWrite(14,k);
  analogWrite(15,k);
  analogWrite(16,k);
  analogWrite(27,k); 
  delay(10);
  }
  for(k=150;k>-1;k--){
  analogWrite(0,k);
  analogWrite(14,k);
  analogWrite(15,k);
  analogWrite(16,k);
  analogWrite(27,k); 
  delay(5);
  }
  delay(1000);
  analogWrite(44,fan);
}

void volume_lvl(int dir){
  vol_lvl=vol_lvl+dir;
  if(vol_lvl<=0){
    vol_lvl=0;
    digitalWrite(13,HIGH);    //turn speakers off
    Keyboard.press(KEY_0);    //send level to triggerhappy daemon
    analogWrite(0,0);
    analogWrite(14,0);
    analogWrite(15,0); 
    analogWrite(16,0); 
    analogWrite(27,0);
  }
  if(vol_lvl==1){
    digitalWrite(13,LOW);     //turn speakers on
    Keyboard.press(KEY_1);    //send level to triggerhappy daemon
    analogWrite(0,i);
    analogWrite(14,0);
    analogWrite(15,0); 
    analogWrite(16,0); 
    analogWrite(27,0);
  }
  if(vol_lvl==2){
    Keyboard.press(KEY_2);    //send level to triggerhappy daemon
    analogWrite(0,i);
    analogWrite(14,i);
    analogWrite(15,0); 
    analogWrite(16,0); 
    analogWrite(27,0);
  }
  if(vol_lvl==3){
    Keyboard.press(KEY_3);    //send level to triggerhappy daemon
    analogWrite(0,i);
    analogWrite(14,i);
    analogWrite(15,i);
    analogWrite(16,0); 
    analogWrite(27,0);
  }
  if(vol_lvl==4){
    Keyboard.press(KEY_4);    //send level to triggerhappy daemon
    analogWrite(0,i);
    analogWrite(14,i);
    analogWrite(15,i); 
    analogWrite(16,i); 
    analogWrite(27,0);
  }
  if(vol_lvl>=5){
    vol_lvl=5;
    Keyboard.press(KEY_5);    //send level to triggerhappy daemon
    analogWrite(0,i);
    analogWrite(14,i);
    analogWrite(15,i); 
    analogWrite(16,i); 
    analogWrite(27,i);
  }
  Keyboard.release(KEY_0);
  Keyboard.release(KEY_1);
  Keyboard.release(KEY_2);
  Keyboard.release(KEY_3);
  Keyboard.release(KEY_4);
  Keyboard.release(KEY_5);
}


void battery(){
  digitalWrite(19,HIGH);                //turn battery read on
  delay(100);
  battery_lvl=(analogRead(43)+analogRead(43)+analogRead(43)+analogRead(43)+analogRead(43))/1023.0;      //read battery voltage 
  digitalWrite(19,LOW);                   //turn battery read off
  //Serial.println(battery_lvl);
  if(battery_lvl>(battery_full-range)){
    analogWrite(0,i);
    delay(j);
    analogWrite(14,i);
    delay(j);
    analogWrite(15,i);
    delay(j);
    analogWrite(16,i);
    delay(j);
    analogWrite(27,i);
    delay(j);
  }
  else if(battery_lvl>(battery_full-2*range)){
    analogWrite(0,i);
    delay(j);
    analogWrite(14,i);
    delay(j);
    analogWrite(15,i);
    delay(j);
    analogWrite(16,i);
    delay(j);
    analogWrite(27,0);
    delay(j);
  }
  else if(battery_lvl>(battery_full-3*range)){
    analogWrite(0,i);
    delay(j);
    analogWrite(14,i);
    delay(j);
    analogWrite(15,i);
    delay(j);
    analogWrite(16,0);
    delay(j);
    analogWrite(27,0);
    delay(j);
  }
  else if(battery_lvl>(battery_full-4*range)){
    analogWrite(0,i);
    delay(j);
    analogWrite(14,i);
    delay(j);
    analogWrite(15,0);
    delay(j);
    analogWrite(16,0);
    delay(j);
    analogWrite(27,0);
    delay(j);
  }
  else{
    analogWrite(0,i);
    delay(j);
    analogWrite(14,0);
    delay(j);
    analogWrite(15,0);
    delay(j);
    analogWrite(16,0);
    delay(j);
    analogWrite(27,0);
    delay(j);
  }

}


void display_lvl(int dir){
  BL_lvl=BL_lvl+dir;
  if(BL_lvl<=0){
    BL_lvl=0;
    Keyboard.press(KEY_A);    //send level to triggerhappy daemon
    analogWrite(0,0);
    analogWrite(14,0);
    analogWrite(15,0); 
    analogWrite(16,0); 
    analogWrite(27,0);
  }
  if(BL_lvl==1){
    Keyboard.press(KEY_B);    //send level to triggerhappy daemon
    analogWrite(0,i);
    analogWrite(14,0);
    analogWrite(15,0); 
    analogWrite(16,0); 
    analogWrite(27,0);
  }
  if(BL_lvl==2){
    Keyboard.press(KEY_C);    //send level to triggerhappy daemon
    analogWrite(0,i);
    analogWrite(14,i);
    analogWrite(15,0); 
    analogWrite(16,0); 
    analogWrite(27,0);
  }
  if(BL_lvl==3){
    Keyboard.press(KEY_D);    //send level to triggerhappy daemon
    analogWrite(0,i);
    analogWrite(14,i);
    analogWrite(15,i);
    analogWrite(16,0); 
    analogWrite(27,0);
  }
  if(BL_lvl==4){
    Keyboard.press(KEY_E);    //send level to triggerhappy daemon
    analogWrite(0,i);
    analogWrite(14,i);
    analogWrite(15,i); 
    analogWrite(16,i); 
    analogWrite(27,0);
  }
  if(BL_lvl>=5){
    BL_lvl=5;
    Keyboard.press(KEY_F);    //send level to triggerhappy daemon
    analogWrite(0,i);
    analogWrite(14,i);
    analogWrite(15,i); 
    analogWrite(16,i); 
    analogWrite(27,i);
  }
  Keyboard.release(KEY_A);
  Keyboard.release(KEY_B);
  Keyboard.release(KEY_C);
  Keyboard.release(KEY_D);
  Keyboard.release(KEY_E);
  Keyboard.release(KEY_F);
  
}


void pwr_down(){
  for(k=0;k<150;k++){
    analogWrite(0,k);
    analogWrite(14,k);
    analogWrite(15,k);
    analogWrite(16,k);
    analogWrite(27,k); 
    delay(10);
    }
  Keyboard.press(KEY_X);    //send level to triggerhappy daemon 
  delay(1000);
  Keyboard.release(KEY_X);
}

