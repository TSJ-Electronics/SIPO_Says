#include "CheatCodes.h"
#include "Lights.h"
#include "Notes.h"
#include "Arduino.h"
#include "GameFunctions.h"
#include "PinDefinitions.h"

void listenForCheatCodeActivation(){
  delay(10); // 10ms delay to fight mechanical bouncing, do not have debounce capacitors on board
  int timer = 0;// keep track of how long button is held down for
  int sleepTime = 20;// update timer every 20ms
  while(digitalRead(BUTTON_NEWGAME) == HIGH){
    delay(sleepTime);
    timer +=sleepTime;
    if(timer > 2000){ // if button is held down longer than 2 seconds
      enterCheatCode();
      break;
    }
  }
}

void enterCheatCode(){

  gameDirections currentKeyPressed = NONE;

  int konamiCode [] = {UP,UP,DOWN,DOWN,LEFT,RIGHT,LEFT,RIGHT};
  int konamiCodeSequenceCounter = 0;
  bool konamiCodeSuccess = true;
  bool enteringCode = true;
  tone(BUZZER, NOTE_D6, 100);
  noTone(BUZZER);
  delay(100);
  tone(BUZZER, NOTE_D6, 100);
  spinLED(200);
  
  while (konamiCodeSuccess && konamiCodeSequenceCounter <= 7){
    
    while(digitalRead(BUTTON_UP) && digitalRead(BUTTON_RIGHT) && //While no buttons are pressed
      digitalRead(BUTTON_LEFT) && digitalRead(BUTTON_DOWN)){
        //do nothing while no buttons pressed
    }
    
    currentKeyPressed = checkForPlayerInput();
    waitForPlayerButtonRelease();
    noTone(BUZZER); // turn off sound
    all_LEDs_Off(); // turn off LED
    
    if(currentKeyPressed != konamiCode[konamiCodeSequenceCounter]){
      konamiCodeSuccess = false;
    }
    konamiCodeSequenceCounter++;
  }

  if(konamiCodeSuccess)
    hardMode();//if konami code entered correctly start game in hard mode :)
  else
    playTune(); // play random tune
}


void playTune(){
  //play random tune
  for(int x = 0; x < random(25,55); x++){
    tone(BUZZER,random(100,1800), random(75, 550));
    randomLight();
    delay(random(0,300));
  }
  noTone(BUZZER);
}


void hardMode(){
  tone(BUZZER, NOTE_DS4, 100);
  tone(BUZZER, NOTE_DS4, 100);
  tone(BUZZER, NOTE_DS3, 600);
  for(int x = 0; x < 25; x++){
    incrementScoreCounter();
    spinLED(10);
  }
  setWinningScore(49);//set new score condition to higher than starting score so you dont auto win upon cheat unlock
}
