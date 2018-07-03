/** Author: Tim Lindquist
 *  Rev: 2.2
 *
 *  NOTES: PID fan_speed controller is implemented but not used/tested (commented out in loop()). Default is fan will run at a continuous speed after boot.
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
#define FAN 44
#define TEMP 42
#define TEMP_VDD 18
#define SPEAKER 13
#define BATT_NMOS 19
#define BATTERY 43

//GLOBAL VARIABLES
int analogLV=512;		//idea analog center reading
int analogLH=512;
int analogRV=512;
int analogRH=512;
int GAIN=2;				//analog stick sensitivity adjustment
int LVC=480;			//actual measured analog values (left vertical center)
int LHC=500;
int RVC=502;
int RHC=503;
int led_lvl=1;			//brightness of LED's 0-255
int batt_delay=100;		//delay for battery growth annimation
int i;
int vol_lvl=0;			//boot volume level (muted)
int prev_vol=vol_lvl;
int counter=0;			//cycle counter used to call funtions less frequenctly with % function
int timeout=0;			//initialized to 0 for timeout of led annimations
int backlight_lvl=2;	//backlight value
float battery_lvl;		//voltage read value from the battery
float battery_full=4.1;                //voltage read of "full" battery 
float battery_dead=3;					//voltage read of "dead" battery
float voltage_step=(battery_full-battery_dead)/5.0;	//voltage step size for LED's displaying battery level
double proc_temp;							//temperature read of proc
double fan_speed=128;							//default fan_speed speed
double ideal_proc_temp=45;						//ideal proc temp in celcius for the PID to calculate error

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
  pinMode(FAN,OUTPUT);            
  pinMode(TEMP,INPUT);            
  pinMode(TEMP_VDD,OUTPUT);           
  pinMode(SPEAKER,OUTPUT);           
  pinMode(BATT_NMOS,OUTPUT);           
  pinMode(BATTERY,INPUT);  
  boot();  							//start boot sequence
}

void loop() {
	analogSticks();
	buttonsPressed();
	//fanControl();	//add Kp & Ki values to function to implement. (tell me which work best for you, I haven't tried it yet) 
	lightCheck();
}






//--------------FUNCTIONS--------------------------------------------------------------------------------

void analogSticks(){
	 analogLV=-1*(-511+GAIN*(analogRead(38)-LVC)); //invert 
     if(analogLV>1023) analogLV=1023;
     else if(analogLV<0) analogLV=0;
     Joystick.Y(analogLV);
     
	 analogLH=512+GAIN*(analogRead(39)-LHC);
     if(analogLH>1023)analogLH=1023;
     else if(analogLH<0) analogLH=0;
     Joystick.X(analogLH);
     
	 analogRV=512+GAIN*(analogRead(41)-RVC);
     if(analogRV>1023)analogRV=1023;
     else if(analogRV<0)analogRV=0;
     Joystick.Z(analogRV);
     
	 analogRH=512+GAIN*(analogRead(40)-RHC);
     if(analogRH>1023) analogRH=1023;
     else if(analogRH<0) analogRH=0;
     Joystick.Zrotate(analogRH);
}

void buttonsPressed(){
	(digitalRead(A))?Joystick.button(1,0):Joystick.button(1,1);
	(digitalRead(B))?Joystick.button(2,0):Joystick.button(2,1);
	(digitalRead(X_BUTTON))?Joystick.button(3,0):Joystick.button(3,1);
	(digitalRead(Y_BUTTON))?Joystick.button(4,0):Joystick.button(4,1);
    (digitalRead(UP))?Joystick.button(5,0):Joystick.button(5,1);
    (digitalRead(DOWN))?Joystick.button(6,0):Joystick.button(6,1);
	(digitalRead(RIGHT_BUTTON))?Joystick.button(7,0):Joystick.button(7,1);
    (digitalRead(LEFT_BUTTON))?Joystick.button(8,0):Joystick.button(8,1);
	(digitalRead(START))?Joystick.button(9,0):Joystick.button(9,1);
	(digitalRead(RIGHT_BUMPER))?Joystick.button(12,0):Joystick.button(12,1);
    (digitalRead(LEFT_BUMPER))?Joystick.button(13,0):Joystick.button(13,1);
   
    if(!digitalRead(SELECT)){      				//select
        while(!digitalRead(SELECT)){            //hotkey hold
          if(!digitalRead(HOME)){             //desktop enviroment
            Keyboard.press(KEY_G);
            Keyboard.release(KEY_G);
            
          }
          if(!digitalRead(LEFT_TRIGGER)){    //left=brightness lower
            if(counter%8==0){
              display_lvl(-1);
              timeout=0;
            }
          }
          if(!digitalRead(RIGHT_TRIGGER)){   //right=brightness higher
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
            analogWrite(LED_0,0);
            analogWrite(LED_1,0);
            analogWrite(LED_2,0); 
            analogWrite(LED_3,0); 
            analogWrite(LED_4,0);
          }
        }
      Joystick.button(10,1);
      }
    else{
      Joystick.button(10,0);
      }
	  
    if(!digitalRead(LEFT_TRIGGER)){   
      if(counter%8==0){
      volume_lvl(-1);
      timeout=0;
      }
    }
   
    if(!digitalRead(RIGHT_TRIGGER)){   
      if(counter%8==0){
      volume_lvl(1);
      timeout=0;
      }
    }

	  
    if(!digitalRead(HOME)){ //home=press start and select  
      while(!digitalRead(HOME)); //debounce
      Joystick.button(9,1);
      Joystick.button(10,1);
      }
    else{
      Joystick.button(9,0);
      Joystick.button(10,0);
      }


  if(!digitalRead(PWR)){ 
    battery();
    counter=0;
    timeout=0;
    while(!digitalRead(PWR)){
      if(counter>100){
        pwr_down();  
      }
      counter++;
      delay(15);
    }
   }
}

/*
void fanControl(){
	//SYNTAX: PID(&Input, &Output, &Setpoint, Kp, Ki, Kd, Direction) 
	//input: variable we are trying to control=proc_temp
	//output: variable to be adjusted=fan_speed
	//setpoint: value we want the input to maintain=ideal_proc_temp
	//Kp Ki Kd: tuning peramiters for the controller
	//Kp=controls the output in proportion to the error (if the error gets bigger the control action gets bigger).
	//Ki=produces an output based on how much error is present. (error small= small changes, large error=big changes).
	//Kd=produces an output basied on the rate of change of the error. (d/dt(error) small=small changes, d/dt(error) large=big changes)
  double Kp=1;	//not sure tune this to be correct
  double Ki=1;	//not sure tune this to be correct
  double Kd=0;	//turn off derivative most likey will make it oscillate
	
  if(counter%50==0){
	  digitalWrite(TEMP_VDD,HIGH);				//turn on temperature sensor
	  proc_temp=(analogRead(TEMP)-650)/10.0;	//take temperature reading and convert to celcius
	  PID(&proc_temp, &fan_speed, &ideal_proc_temp, Kp, Ki, Kd, DIRECT) 
	  analogWrite(FAN,fan_speed);
	  digitalWrite(TEMP_VDD,LOW);				//adjust fan speed
  }
}
*/

void lightCheck(){ 
	  counter++;
	  timeout++;
	  if (counter>100){
		counter=0;
	  }
	  if(timeout>50){
		analogWrite(LED_0,0);
		analogWrite(LED_1,0);
		analogWrite(LED_2,0); 
		analogWrite(LED_3,0); 
		analogWrite(LED_4,0);
	  }
}

void boot(){
  digitalWrite(SPEAKER,HIGH);    //turn speakers off
  digitalWrite(BATT_NMOS,LOW);     //turn battery read off
  digitalWrite(TEMP_VDD,LOW);     //turn temp sensor off
  for(i=0;i<100;i++){
  analogWrite(LED_0,random(0,2)*led_lvl);
  analogWrite(LED_1,random(0,2)*led_lvl);
  analogWrite(LED_2,random(0,2)*led_lvl);
  analogWrite(LED_3,random(0,2)*led_lvl);
  analogWrite(LED_4,random(0,2)*led_lvl);
  delay(100);
  }
  for(i=0;i<150;i++){
  analogWrite(LED_0,i);
  analogWrite(LED_1,i);
  analogWrite(LED_2,i);
  analogWrite(LED_3,i);
  analogWrite(LED_4,i); 
  delay(10);
  }
  for(i=150;i>-1;i--){
  analogWrite(LED_0,i);
  analogWrite(LED_1,i);
  analogWrite(LED_2,i);
  analogWrite(LED_3,i);
  analogWrite(LED_4,i); 
  delay(5);
  }
  delay(1000);
  analogWrite(FAN,fan_speed);
}

void volume_lvl(int dir){
  vol_lvl=vol_lvl+dir;
  if(vol_lvl<=0){
    vol_lvl=0;
    digitalWrite(SPEAKER,HIGH);    //turn speakers off
    Keyboard.press(KEY_0);    //send level to triggerhappy daemon
    analogWrite(LED_0,0);
    analogWrite(LED_1,0);
    analogWrite(LED_2,0); 
    analogWrite(LED_3,0); 
    analogWrite(LED_4,0);
  }
  if(vol_lvl==1){
    digitalWrite(13,LOW);     //turn speakers on
    Keyboard.press(KEY_1);    //send level to triggerhappy daemon
    analogWrite(LED_0,led_lvl);
    analogWrite(LED_1,0);
    analogWrite(LED_2,0); 
    analogWrite(LED_3,0); 
    analogWrite(LED_4,0);
  }
  if(vol_lvl==2){
    Keyboard.press(KEY_2);    //send level to triggerhappy daemon
    analogWrite(LED_0,led_lvl);
    analogWrite(LED_1,led_lvl);
    analogWrite(LED_2,0); 
    analogWrite(LED_3,0); 
    analogWrite(LED_4,0);
  }
  if(vol_lvl==3){
    Keyboard.press(KEY_3);    //send level to triggerhappy daemon
    analogWrite(LED_0,led_lvl);
    analogWrite(LED_1,led_lvl);
    analogWrite(LED_2,led_lvl);
    analogWrite(LED_3,0); 
    analogWrite(LED_4,0);
  }
  if(vol_lvl==4){
    Keyboard.press(KEY_4);    //send level to triggerhappy daemon
    analogWrite(LED_0,led_lvl);
    analogWrite(LED_1,led_lvl);
    analogWrite(LED_2,led_lvl); 
    analogWrite(LED_3,led_lvl); 
    analogWrite(LED_4,0);
  }
  if(vol_lvl>=5){
    vol_lvl=5;
    Keyboard.press(KEY_5);    //send level to triggerhappy daemon
    analogWrite(LED_0,led_lvl);
    analogWrite(LED_1,led_lvl);
    analogWrite(LED_2,led_lvl); 
    analogWrite(LED_3,led_lvl); 
    analogWrite(LED_4,led_lvl);
  }
  Keyboard.release(KEY_0);
  Keyboard.release(KEY_1);
  Keyboard.release(KEY_2);
  Keyboard.release(KEY_3);
  Keyboard.release(KEY_4);
  Keyboard.release(KEY_5);
}


void battery(){
  digitalWrite(BATT_NMOS,HIGH);                //turn battery read on
  delay(100);
  battery_lvl=(analogRead(BATTERY)+analogRead(BATTERY)+analogRead(BATTERY)+analogRead(BATTERY)+analogRead(BATTERY))/1023.0;      //read battery voltage 
  digitalWrite(BATT_NMOS,LOW);                   //turn battery read off
  //Serial.println(battery_lvl);
  if(battery_lvl>(battery_full-voltage_step)){
    analogWrite(LED_0,led_lvl);
    delay(batt_delay);
    analogWrite(LED_1,led_lvl);
    delay(batt_delay);
    analogWrite(LED_2,led_lvl);
    delay(batt_delay);
    analogWrite(LED_3,led_lvl);
    delay(batt_delay);
    analogWrite(LED_4,led_lvl);
    delay(batt_delay);
  }
  else if(battery_lvl>(battery_full-2*voltage_step)){
    analogWrite(LED_0,led_lvl);
    delay(batt_delay);
    analogWrite(LED_1,led_lvl);
    delay(batt_delay);
    analogWrite(LED_2,led_lvl);
    delay(batt_delay);
    analogWrite(LED_3,led_lvl);
    delay(batt_delay);
    analogWrite(LED_4,0);
    delay(batt_delay);
  }
  else if(battery_lvl>(battery_full-3*voltage_step)){
    analogWrite(LED_0,led_lvl);
    delay(batt_delay);
    analogWrite(LED_1,led_lvl);
    delay(batt_delay);
    analogWrite(LED_2,led_lvl);
    delay(batt_delay);
    analogWrite(LED_3,0);
    delay(batt_delay);
    analogWrite(LED_4,0);
    delay(batt_delay);
  }
  else if(battery_lvl>(battery_full-4*voltage_step)){
    analogWrite(LED_0,led_lvl);
    delay(batt_delay);
    analogWrite(LED_1,led_lvl);
    delay(batt_delay);
    analogWrite(LED_2,0);
    delay(batt_delay);
    analogWrite(LED_3,0);
    delay(batt_delay);
    analogWrite(LED_4,0);
    delay(batt_delay);
  }
  else{
    analogWrite(LED_0,led_lvl);
    delay(batt_delay);
    analogWrite(LED_1,0);
    delay(batt_delay);
    analogWrite(LED_2,0);
    delay(batt_delay);
    analogWrite(LED_3,0);
    delay(batt_delay);
    analogWrite(LED_4,0);
    delay(batt_delay);
  }

}


void display_lvl(int dir){
  backlight_lvl=backlight_lvl+dir;
  if(backlight_lvl<=0){
    backlight_lvl=0;
    Keyboard.press(KEY_A);    //send level to triggerhappy daemon
    analogWrite(LED_0,0);
    analogWrite(LED_1,0);
    analogWrite(LED_2,0); 
    analogWrite(LED_3,0); 
    analogWrite(LED_4,0);
  }
  if(backlight_lvl==1){
    Keyboard.press(KEY_B);    //send level to triggerhappy daemon
    analogWrite(LED_0,led_lvl);
    analogWrite(LED_1,0);
    analogWrite(LED_2,0); 
    analogWrite(LED_3,0); 
    analogWrite(LED_4,0);
  }
  if(backlight_lvl==2){
    Keyboard.press(KEY_C);    //send level to triggerhappy daemon
    analogWrite(LED_0,led_lvl);
    analogWrite(LED_1,led_lvl);
    analogWrite(LED_2,0); 
    analogWrite(LED_3,0); 
    analogWrite(LED_4,0);
  }
  if(backlight_lvl==3){
    Keyboard.press(KEY_D);    //send level to triggerhappy daemon
    analogWrite(LED_0,led_lvl);
    analogWrite(LED_1,led_lvl);
    analogWrite(LED_2,led_lvl);
    analogWrite(LED_3,0); 
    analogWrite(LED_4,0);
  }
  if(backlight_lvl==4){
    Keyboard.press(KEY_E);    //send level to triggerhappy daemon
    analogWrite(LED_0,led_lvl);
    analogWrite(LED_1,led_lvl);
    analogWrite(LED_2,led_lvl); 
    analogWrite(LED_3,led_lvl); 
    analogWrite(LED_4,0);
  }
  if(backlight_lvl>=5){
    backlight_lvl=5;
    Keyboard.press(KEY_F);    //send level to triggerhappy daemon
    analogWrite(LED_0,led_lvl);
    analogWrite(LED_1,led_lvl);
    analogWrite(LED_2,led_lvl); 
    analogWrite(LED_3,led_lvl); 
    analogWrite(LED_4,led_lvl);
  }
  Keyboard.release(KEY_A);
  Keyboard.release(KEY_B);
  Keyboard.release(KEY_C);
  Keyboard.release(KEY_D);
  Keyboard.release(KEY_E);
  Keyboard.release(KEY_F);
  
}


void pwr_down(){
  for(i=0;i<150;i++){
    analogWrite(LED_0,i);
    analogWrite(LED_1,i);
    analogWrite(LED_2,i);
    analogWrite(LED_3,i);
    analogWrite(LED_4,i); 
    delay(10);
    }
  Keyboard.press(KEY_X);    //send level to triggerhappy daemon 
  delay(1000);
  Keyboard.release(KEY_X);
}


