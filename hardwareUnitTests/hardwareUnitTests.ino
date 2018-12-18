/** Author: Tim Lindquist
 *  Rev: 0.0
 *
 *  NOTES: This program tests to see if hardware connections are correct. 
 */

//pin assignment
#define LED_0 0
#define LED_1 14
#define LED_2 15
#define LED_3 16
#define LED_4 27
#define PWR 1
#define A 20
#define B 24
#define X_BUTTON 23
#define Y_BUTTON 21
#define UP 8
#define DOWN 11
#define RIGHT_BUTTON 4
#define LEFT_BUTTON 9
#define START 7
#define SELECT 5
#define ANALOG_LEFT_VERT 38
#define ANALOG_LEFT_HORZ 39
#define ANALOG_RIGHT_VERT 41
#define ANALOG_RIGHT_HORZ 40
#define LEFT_BUMPER 3
#define RIGHT_BUMPER 26
#define LEFT_TRIGGER 2
#define RIGHT_TRIGGER 25
#define HOME 22



void setup() {
  Serial.begin(9600);
  pinMode(LED_0,OUTPUT);            
  pinMode(LED_1,OUTPUT);           
  pinMode(LED_2,OUTPUT);           
  pinMode(LED_3,OUTPUT);           
  pinMode(LED_4,OUTPUT);           
  pinMode(PWR,INPUT_PULLUP);      
  pinMode(A,INPUT_PULLUP);      
  pinMode(B,INPUT_PULLUP);     
  pinMode(X_BUTTON,INPUT_PULLUP);     
  pinMode(Y_BUTTON,INPUT_PULLUP);     
  pinMode(UP,INPUT_PULLUP);       
  pinMode(DOWN,INPUT_PULLUP);      
  pinMode(RIGHT_BUTTON,INPUT_PULLUP);      
  pinMode(LEFT_BUTTON,INPUT_PULLUP);      
  pinMode(START,INPUT_PULLUP);      
  pinMode(SELECT,INPUT_PULLUP);      
  pinMode(ANALOG_LEFT_VERT,INPUT);     
  pinMode(ANALOG_LEFT_HORZ,INPUT);     
  pinMode(ANALOG_RIGHT_VERT,INPUT);     
  pinMode(ANALOG_RIGHT_HORZ,INPUT);     
  pinMode(LEFT_BUMPER,INPUT_PULLUP);      
  pinMode(RIGHT_BUMPER,INPUT_PULLUP);     
  pinMode(LEFT_TRIGGER,INPUT_PULLUP);      
  pinMode(RIGHT_TRIGGER,INPUT_PULLUP);     
  pinMode(HOME,INPUT_PULLUP);

}

void loop() {
  unsigned long time_now = 0;
  unsigned long wait_time=3000;
  byte led_lvl=50;
  int LVC;
  int LHC;
  int RVC;
  int RHC;
  
  Serial.println("For each of the following tests you have 3 sec to complete the action");
  Serial.print("Begin Testing");
  delay(500);
  Serial.print(".");
  delay(500);
  Serial.print(".");
  delay(500);
  Serial.println(".");
  delay(500);
  Serial.println("\n");

  Serial.println("\n------BUTTON TESTS-----");
  //A TEST
  Serial.print("Press Button A: ");
  time_now=millis();
   while(millis() < time_now + wait_time){
    if(!digitalRead(A)) break;
   }
  (!digitalRead(A)) ? Serial.println("pass"): Serial.println("fail");
  delay(500);
  
  //B TEST
  Serial.print("Press Button B: ");
  time_now=millis();
    while(millis() < time_now + wait_time){
    if(!digitalRead(B)) break;
   }
  (!digitalRead(B)) ? Serial.println("pass"): Serial.println("fail");
  delay(500);

  //X TEST
  Serial.print("Press Button X: ");
  time_now=millis();
  while(millis() < time_now + wait_time){
    if(!digitalRead(X_BUTTON)) break;
   }
  (!digitalRead(X_BUTTON)) ? Serial.println("pass"): Serial.println("fail");
  delay(500);
  

  //Y TEST
  Serial.print("Press Button Y: ");
  time_now=millis();
  while(millis() < time_now + wait_time){
    if(!digitalRead(Y_BUTTON)) break;
   }
  (!digitalRead(Y_BUTTON)) ? Serial.println("pass"): Serial.println("fail");
  delay(500);
  
  //UP TEST
  Serial.print("Press D-pad UP: ");
  time_now=millis();
  while(millis() < time_now + wait_time){
    if(!digitalRead(UP)) break;
   }
  (!digitalRead(UP)) ? Serial.println("pass"): Serial.println("fail");
  delay(500);

  //DOWN TEST
  Serial.print("Press D-pad DOWN: ");
  time_now=millis();
  while(millis() < time_now + wait_time){
    if(!digitalRead(DOWN)) break;
   }
  (!digitalRead(DOWN)) ? Serial.println("pass"): Serial.println("fail");
  delay(500);

   //RIGHT TEST
  Serial.print("Press D-pad RIGHT: ");
  time_now=millis();
  while(millis() < time_now + wait_time){
    if(!digitalRead(RIGHT_BUTTON)) break;
   }
  (!digitalRead(RIGHT_BUTTON)) ? Serial.println("pass"): Serial.println("fail");
  delay(500);
  
    //LEFT TEST
   Serial.print("Press D-pad LEFT: ");
  time_now=millis();
  while(millis() < time_now + wait_time){
    if(!digitalRead(LEFT_BUTTON)) break;
   }
  (!digitalRead(LEFT_BUTTON)) ? Serial.println("pass"): Serial.println("fail");
  delay(500);

  //START TEST
  Serial.print("Press button START: ");
  time_now=millis();
  while(millis() < time_now + wait_time){
    if(!digitalRead(START)) break;
   }
  (!digitalRead(START)) ? Serial.println("pass"): Serial.println("fail");
  delay(500);

  //SELECT TEST
  Serial.print("Press button SELECT: ");
  time_now=millis();
  while(millis() < time_now + wait_time){
    if(!digitalRead(SELECT)) break;
   }
  (!digitalRead(SELECT)) ? Serial.println("pass"): Serial.println("fail");
  delay(500);

  //HOME TEST
  Serial.print("Press button HOME: ");
  time_now=millis();
  while(millis() < time_now + wait_time){
    if(!digitalRead(HOME)) break;
   }
  (!digitalRead(HOME)) ? Serial.println("pass"): Serial.println("fail");
  delay(500);

    //POWER TEST
  Serial.print("Press Button POWER: ");
  time_now=millis();
   while(millis() < time_now + wait_time){
    if(!digitalRead(PWR)) break;
   }
  (!digitalRead(PWR)) ? Serial.println("pass"): Serial.println("fail");
  delay(500);
  

    //LEFT_BUMPER TEST
  Serial.print("Press Button LEFT BUMPER: ");
  time_now=millis();
   while(millis() < time_now + wait_time){
    if(!digitalRead(LEFT_BUMPER)) break;
   }
  (!digitalRead(LEFT_BUMPER)) ? Serial.println("pass"): Serial.println("fail");
  delay(500);


    //RIGHT_BUMPER TEST
  Serial.print("Press Button RIGHT BUMPER: ");
  time_now=millis();
   while(millis() < time_now + wait_time){
    if(!digitalRead(RIGHT_BUMPER)) break;
   }
  (!digitalRead(RIGHT_BUMPER)) ? Serial.println("pass"): Serial.println("fail");
  delay(500);


   //LEFT_TRIGGER TEST
  Serial.print("Press Button LEFT TRIGGER: ");
  time_now=millis();
   while(millis() < time_now + wait_time){
    if(!digitalRead(LEFT_TRIGGER)) break;
   }
  (!digitalRead(LEFT_TRIGGER)) ? Serial.println("pass"): Serial.println("fail");
  delay(500);


    //RIGHT_TRIGGER TEST
  Serial.print("Press Button RIGHT TRIGGER: ");
  time_now=millis();
   while(millis() < time_now + wait_time){
    if(!digitalRead(RIGHT_TRIGGER)) break;
   }
  (!digitalRead(RIGHT_TRIGGER)) ? Serial.println("pass"): Serial.println("fail");
  delay(500);



  Serial.println("\n------LED TESTS-----");
  delay(500);
  Serial.println("LED 0 ON");
  analogWrite(LED_0,led_lvl);
  analogWrite(LED_1,0);
  analogWrite(LED_2,0); 
  analogWrite(LED_3,0); 
  analogWrite(LED_4,0);
  delay(1000);
  Serial.println("LED 1 ON");
  analogWrite(LED_0,0);
  analogWrite(LED_1,led_lvl);
  analogWrite(LED_2,0); 
  analogWrite(LED_3,0); 
  analogWrite(LED_4,0);
  delay(1000);
  Serial.println("LED 2 ON");
  analogWrite(LED_0,0);
  analogWrite(LED_1,0);
  analogWrite(LED_2,led_lvl); 
  analogWrite(LED_3,0); 
  analogWrite(LED_4,0);
  delay(1000);
  Serial.println("LED 3 ON");
  analogWrite(LED_0,0);
  analogWrite(LED_1,0);
  analogWrite(LED_2,0); 
  analogWrite(LED_3,led_lvl); 
  analogWrite(LED_4,0);
  delay(1000);
  Serial.println("LED 4 ON");
  analogWrite(LED_0,0);
  analogWrite(LED_1,0);
  analogWrite(LED_2,0); 
  analogWrite(LED_3,0); 
  analogWrite(LED_4,led_lvl);
  delay(1000);
  analogWrite(LED_0,0);
  analogWrite(LED_1,0);
  analogWrite(LED_2,0); 
  analogWrite(LED_3,0); 
  analogWrite(LED_4,0);
  Serial.println("LED 0-4 OFF");
  delay(500);

  Serial.println("\n------ANALOG TESTS-----");
  Serial.print("Touch nothing measurement in progress");
  delay(500);
  Serial.print(".");
  delay(500);
  Serial.print(".");
  delay(500);
  Serial.println(".");
  LVC=analogRead(ANALOG_LEFT_VERT);
  LHC=analogRead(ANALOG_LEFT_HORZ);
  RVC=analogRead(ANALOG_RIGHT_VERT);
  RHC=analogRead(ANALOG_RIGHT_HORZ);
  delay(1000);
  Serial.print("\n");
  Serial.print("Now rotate the LEFT JOYSTICK: ");
  time_now=millis();
  boolean pass=false;
   while(millis() < time_now + wait_time){
    if(analogRead(ANALOG_LEFT_VERT)>LVC+100 && analogRead(ANALOG_LEFT_HORZ)>LHC+100) pass=true;
   }
   (pass)?Serial.println("pass"):Serial.println("fail");
   delay(500);
  Serial.print("Now rotate the RIGHT JOYSTICK: ");
  time_now=millis();
  pass=false;
   while(millis() < time_now + wait_time){
    if(analogRead(ANALOG_RIGHT_VERT)>RVC+100 && analogRead(ANALOG_RIGHT_HORZ)>RHC+100) pass=true;
   }
   (pass)?Serial.println("pass"):Serial.println("fail");
  delay(500);
  Serial.print("\n");
  Serial.println("Update GLOBAL VARIABLES in Nintimdo_RP_controller_board.ino with the following:");
  Serial.print("LVC=");
  Serial.println(LVC);
  Serial.print("LHC=");
  Serial.println(LHC); 
  Serial.print("RVC=");
  Serial.println(RVC);
  Serial.print("RHC=");
  Serial.println(RHC);
  
  
  
  
  //hault
  for(;;);

}
