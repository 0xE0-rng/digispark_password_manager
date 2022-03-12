#include "DigiKeyboard.h"

int analogInPin2 = 1;

void setup() {
  // don't need to set anything up to use DigiKeyboard
}

 String PASSWORDS[] = {"sample_password", "slot2", "slot3", "slot4", "slot5", "slot6"};


void loop() {
    static unsigned long timer = 0;
    static unsigned long time_since = 0;
    static unsigned long last_press = 0;
    static unsigned short pressed = 0;
    static boolean pressing = false;
    static boolean to_do = true;

    if(analogRead(analogInPin2) > 100){
      last_press = timer;
      pressing = true;
    }else{
      to_do = true;
      pressing = false;
    }
    time_since = timer - last_press;

    if (to_do && pressing && time_since < 5){
      to_do = false;
      pressed = pressed + 1;
     // write(pressed);
    }else if (!pressing && pressed > 0 && time_since > 5){
      print_pwd(pressed);
      pressed = 0;
    }

    timer =  timer + 1;
    DigiKeyboard.delay(100);
}

void print_pwd(short pressed){
      short int pwd_index = pressed - 1;
      if ((pwd_index < sizeof(PASSWORDS)/sizeof(PASSWORDS[0]))){
        write(PASSWORDS[pwd_index]);
      }
}

int write(String text){
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.println(text);
  }
