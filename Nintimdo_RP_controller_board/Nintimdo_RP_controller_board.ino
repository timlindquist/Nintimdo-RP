void setup() {
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);

}

void loop() {
  if(digitalRead(3)==LOW){   //button pushed
    //Keyboard.press(KEY_T);
    Joystick.button(1,1);
    }
  else{
    //Keyboard.release(KEY_T);
    Joystick.button(1,0);
    }
  if(digitalRead(4)==LOW){   //button pushed
    //Keyboard.press(KEY_T);
    Joystick.button(2,1);
    }
  else{
    //Keyboard.release(KEY_T);
    Joystick.button(2,0);
    }
}
