#include "Lights.h"
#include "PinDefinitions.h"
#include "Notes.h"
#include "Arduino.h"
#include "GameFunctions.h"


int getCurrentScore(){ 
  return currentScore;
}
  
void setWinningScore(int scoreSet){
  winningScore = scoreSet;
}
  
int getWinningScore(){ 
  return winningScore;
}

void resetScoreCounter(){
  currentScore = 0;
}

bool getGameStatus(){
  return gameInProgress;
}

void setGameStatus(bool setStatus){
  gameInProgress = setStatus;
}

void powerOnInitialize(){// This function justlets the user know the board is powering on and prevents accidental starts
  for (int x = 0; x < 3; x++){
    all_LEDs_On();
    delay(400);
    all_LEDs_Off();
    delay(200);
  }
}

void initializeRandomGameSequence(){//generate the simon says sequence
  for(int x = 0; x < sequenceArrayLength; x++)
    sudoSaysSequenceArray[x] = random(0,4);// each number corresponds to a simon says color / direction, value is 0 to 4 because min is inclusive and max is exclusive
}

void computerTurn(int noteDuration, int interNoteDelay){
  for(int x = 0; x < currentScore; x++){
    switch(sudoSaysSequenceArray[x]){
      case UP: playUp(noteDuration); break;
      case RIGHT: playRight(noteDuration); break;
      case DOWN: playDown(noteDuration); break;
      case LEFT: playLeft(noteDuration); break;
      default: break;
    }
    delay(interNoteDelay);//delay after note
  }
}

void waitForPlayerButtonRelease(){
  //while any button is pressed do nothing
  while(!digitalRead(BUTTON_UP) || !digitalRead(BUTTON_RIGHT) ||
    !digitalRead(BUTTON_LEFT) || !digitalRead(BUTTON_DOWN)){
  while(!digitalRead(BUTTON_UP) || !digitalRead(BUTTON_RIGHT) ||
    !digitalRead(BUTTON_LEFT) || !digitalRead(BUTTON_DOWN)){
      //do nothing
    }
  delay(30);// delay to combat button release mechanical bouncing, not sure if this is really the problem but there has been an issue with misreading relase signals
  //When button released turn off lights and sound
  noTone(BUZZER); // turn off sound
  all_LEDs_Off(); // turn off LED
}

gameDirections checkForPlayerInput(){ //Check if button is pressed, play corresponding notes and lights
  gameDirections currentKeyPressed = NONE;
  //delay because of mechanical bouncing, i did not add debounce capacitors because wanted to save board space
  delay(30);
  if(digitalRead(BUTTON_UP) == LOW){
        currentKeyPressed = UP;
        tone(BUZZER,TONE_UP);
        up_LED_On();
        return currentKeyPressed;
      }
        if(digitalRead(BUTTON_RIGHT) == LOW){
        if(digitalRead(BUTTON_RIGHT) == LOW){
          currentKeyPressed = RIGHT;
          tone(BUZZER,TONE_RIGHT);
          right_LED_On();
          return currentKeyPressed;
      }
        if(digitalRead(BUTTON_DOWN) == LOW){
        if(digitalRead(BUTTON_DOWN) == LOW){
          currentKeyPressed = DOWN;
          tone(BUZZER,TONE_DOWN);
          down_LED_On();
          return currentKeyPressed;
      }
        if(digitalRead(BUTTON_LEFT) == LOW){
        if(digitalRead(BUTTON_LEFT) == LOW){
          currentKeyPressed = LEFT;
          tone(BUZZER,TONE_LEFT);
          left_LED_On();
          return currentKeyPressed;
      }
  return currentKeyPressed;
}

bool playerTurn(){
  gameDirections currentKeyPressed = NONE;
  for(int x = 0; x < currentScore; x++){
    
    while(digitalRead(BUTTON_UP) && digitalRead(BUTTON_RIGHT) && //While no buttons are pressed
    digitalRead(BUTTON_LEFT) && digitalRead(BUTTON_DOWN)){
    while(digitalRead(BUTTON_UP) && digitalRead(BUTTON_RIGHT) && //While no buttons are pressed
    digitalRead(BUTTON_LEFT) && digitalRead(BUTTON_DOWN)){
      //do nothing while no buttons are pressed
    }
      currentKeyPressed = checkForPlayerInput();
      waitForPlayerButtonRelease();
      //noTone(buzzer); //think these are duplicates, delete if so
      //all_LEDs_Off(); // possible duplicate
      if(currentKeyPressed != sudoSaysSequenceArray[x]) // if player enters sequence incorrectly
        return false;
  }
  return true;
}

void incrementScoreCounter(){
  currentScore++;
  digitalWrite(SCORE_CLK, HIGH); // update scoreboard to == number of turns
  digitalWrite(SCORE_CLK, HIGH); // update scoreboard to == number of turns
  delay(25);
  digitalWrite(SCORE_CLK, LOW);
}

void playUp(int sequenceDelay){
  up_LED_On();
  tone(BUZZER, TONE_UP);
  delay(sequenceDelay);
  noTone(BUZZER);
  digitalWrite(LED_UP, LOW);
  noTone(BUZZER);
  digitalWrite(LED_UP, LOW);
}

void playRight(int sequenceDelay){
  right_LED_On();
  tone(BUZZER, TONE_RIGHT);
  delay(sequenceDelay);
  noTone(BUZZER);
  digitalWrite(LED_RIGHT, LOW);
  noTone(BUZZER);
  digitalWrite(LED_RIGHT, LOW);
}

void playDown(int sequenceDelay){
  down_LED_On();
  tone(BUZZER,TONE_DOWN);
  delay(sequenceDelay);
  noTone(BUZZER);
  digitalWrite(LED_DOWN, LOW);
  noTone(BUZZER);
  digitalWrite(LED_DOWN, LOW);
}

void playLeft(int sequenceDelay){
  left_LED_On();
  tone(BUZZER, TONE_LEFT);
  delay(sequenceDelay);
  noTone(BUZZER);
  digitalWrite(LED_LEFT, LOW);
  noTone(BUZZER);
  digitalWrite(LED_LEFT, LOW);
}

void winGame(){
  setGameStatus(false);
  for(int x = currentScore; currentScore < 99; ++x)// send score counter to 99 just for fun
    incrementScoreCounter();
  playSong();
}

void gameOver(){
  setGameStatus(false);
  all_LEDs_On();
  tone(BUZZER,NOTE_A2,400);
  tone(BUZZER,NOTE_A2,400);
  all_LEDs_Off();
  tone(BUZZER,NOTE_D3,120);
  tone(BUZZER,NOTE_D3,120);
  all_LEDs_On();
  tone(BUZZER,NOTE_A2,120);
  tone(BUZZER,NOTE_A2,120);
  all_LEDs_Off();
  tone(BUZZER,NOTE_D3,120);
  tone(BUZZER,NOTE_D3,120);
  all_LEDs_On();
  tone(BUZZER,NOTE_CS4,300);
  tone(BUZZER,NOTE_CS4,300);
  all_LEDs_Off();
  spinLED(155);
}


void playSong(){

  //songs were provided by: https://github.com/robsoncouto/arduino-songs
  //Some Songs take up too much RAM and cause issues. So keep songs short or just a peice of a longer song.
  //dont forget to change tempo to correct setting!
  
  //Happy Birthday
  int melody[] = {
    NOTE_C4,4, NOTE_C4,8, 
    NOTE_D4,-4, NOTE_C4,-4, NOTE_F4,-4,
    NOTE_E4,-2, NOTE_C4,4, NOTE_C4,8, 
    NOTE_D4,-4, NOTE_C4,-4, NOTE_G4,-4,
    NOTE_F4,-2, NOTE_C4,4, NOTE_C4,8,

    NOTE_C5,-4, NOTE_A4,-4, NOTE_F4,-4, 
    NOTE_E4,-4, NOTE_D4,-4, NOTE_AS4,4, NOTE_AS4,8,
    NOTE_A4,-4, NOTE_F4,-4, NOTE_G4,-4,
    NOTE_F4,-2,
  };
  // change this to make the song slower or faster
  int tempo = 140;

  int notes = sizeof(melody) / sizeof(melody[0]) / 2;

  // this calculates the duration of a whole note in ms
  int wholenote = (60000 * 4) / tempo;

  int divider = 0, noteDuration = 0;

  // iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }
    //Light up a random light to go with music
    randomLight();

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(BUZZER, melody[thisNote], noteDuration * 0.9);
    tone(BUZZER, melody[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(BUZZER);
    noTone(BUZZER);
  }
  
  all_LEDs_Off();
}
