/*
 * SIPO Says Code
 * By: Tyler Jacobs
 * TSJElectronics.com
 * v1.0 Finished 12/27/2022
 * Dedicated to Lucy, Wyatt, and Tristan <3
*/

#include "Notes.h"
#include "Lights.h"
#include "CheatCodes.h"
#include "PinDefinitions.h"
#include "GameFunctions.h"
#include <Arduino.h>

const int noteDuration = 400; //How long each note will be played in milliseconds. The lower this number the faster the computer sequence will be played. 400 is default setting
const int noteDelay = 150; //Pause time between each note, the higher this note the longer the delay between notes, 150 is default setting
const int noteDurationReductionPerTurn = 20;// Each turn, note duration is reduced by this amount

const int minimumNoteDuration = 100;// note duration cannot fall below this threshold
const int minimumNoteDelay = 50;// delay between notes cannot fall below this threshhold

int noteDuration = noteDuration;//These are the values the code will change and manipulate, then reset to origional values every new game
int noteDelay = noteDelay;

bool winnable = false; // for infinite play set to false, for end game condition at set score amount set to true
int winningScore = 12; // you can set the score so when this score is achieved, a song is played and you win!

/*
Color Directionals:
      RED = UP
      GREEN = RIGHT
      BLUE = DOWN
      YELLOW = LEFT
*/

void setup() {
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_LEFT, INPUT_PULLUP);
  pinMode(BUTTON_NEWGAME, INPUT);

  pinMode(LED_UP, OUTPUT);
  pinMode(LED_RIGHT, OUTPUT);
  pinMode(LED_DOWN, OUTPUT);
  pinMode(LED_LEFT, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER,LOW);//make sure buzzer is off.

  pinMode(SCORE_CLK, OUTPUT);

  all_LEDs_Off();
  tone(BUZZER, 1500, 500);// test tone
  powerOnInitialize();
  delay(1000);
  setWinningScore(winningScore);
}

void loop() {

  if(digitalRead(BUTTON_NEWGAME) == HIGH){// You dont need == HIGH but left to make code easier to read
    resetScoreCounter();
    listenForCheatCodeActivation();
    setGameStatus(true);
  }
  
  if(getGameStatus()){
    initializeRandomGameSequence();
    while(getGameStatus()){
      incrementScoreCounter();
      delay(500);//delay between computer turn start and player turn end.
      computerTurn(noteDuration,noteDelay);
      
      if(noteDuration > minimumNoteDuration)  //reduce note duration 
        noteDuration -= noteDurationReductionPerTurn;

      if(noteDelay > minimumNoteDelay)  //reduce note delay duration
        noteDelay -= (noteDurationReductionPerTurn/3);
        
      if(playerTurn() == false)// if player fails his turn end game, otherwise continue
        gameOver();

      if(winnable && getCurrentScore() >= getWinningScore())// check if game is won
        winGame();

    }
  }
  
  //ability to just play the notes with lights here while not in a game
  checkForPlayerInput();
  waitForPlayerButtonRelease();

  //adding song library here in future versions so you can select songs on win
}
