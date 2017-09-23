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
int vol_lvl=3;
int counter=0;
int timeout=0;

void setup() {
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
    /*
     Serial.print("left vertical:");
     Serial.print(analogLV);
     Serial.print("   left horizontal:");
     Serial.print(analogLH);
     Serial.print("   right vertical:");
     Serial.print(analogRV);
     Serial.print("   right horizontal:");
     Serial.println(analogRH);
   */
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
      Joystick.button(9,1);
      }
    else{
      Joystick.button(9,0);
      }
    if(digitalRead(5)==LOW){   
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
      Joystick.button(9,1);
      Joystick.button(10,1);
      }
    else{
      Joystick.button(9,0);
      Joystick.button(10,0);
      }
  
  //Light checks
  if(digitalRead(1)==LOW){   
      battery();
      timeout=0;
      }
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



void boot(){
  for(k=0;k<300;k++){
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
}

void volume_lvl(int dir){
  vol_lvl=vol_lvl+dir;
  if(vol_lvl<=0){
    vol_lvl=0;
    analogWrite(0,0);
    analogWrite(14,0);
    analogWrite(15,0); 
    analogWrite(16,0); 
    analogWrite(27,0);
  }
  if(vol_lvl==1){
    analogWrite(0,i);
    analogWrite(14,0);
    analogWrite(15,0); 
    analogWrite(16,0); 
    analogWrite(27,0);
  }
  if(vol_lvl==2){
    analogWrite(0,i);
    analogWrite(14,i);
    analogWrite(15,0); 
    analogWrite(16,0); 
    analogWrite(27,0);
  }
  if(vol_lvl==3){
    analogWrite(0,i);
    analogWrite(14,i);
    analogWrite(15,i);
    analogWrite(16,0); 
    analogWrite(27,0); 
  }
  if(vol_lvl==4){
    analogWrite(0,i);
    analogWrite(14,i);
    analogWrite(15,i); 
    analogWrite(16,i); 
    analogWrite(27,0); 
  }
  if(vol_lvl>=5){
    vol_lvl=5;
    analogWrite(0,i);
    analogWrite(14,i);
    analogWrite(15,i); 
    analogWrite(16,i); 
    analogWrite(27,i);
  }
}


void battery(){
  analogWrite(0,i);
  delay(j);
  analogWrite(14,i);
  delay(j);
  analogWrite(15,i);
  delay(j);
  analogWrite(16,i);
  delay(j);

}

