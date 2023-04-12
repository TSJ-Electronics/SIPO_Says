#include "Lights.h"
#include <Arduino.h>
#include "PinDefinitions.h"
#include "GameFunctions.h"

void all_LEDs_On(){
  up_LED_On();
  right_LED_On();
  down_LED_On();
  left_LED_On();
}

void up_LED_On(){
  digitalWrite(upLED, HIGH);
}
void right_LED_On(){
  digitalWrite(rightLED, HIGH);
}
void down_LED_On(){
  digitalWrite(downLED, HIGH);
}
void left_LED_On(){
  digitalWrite(leftLED, HIGH);
}

void randomLight(){
  all_LEDs_Off();// turn off any light that may be on
  int light = random(0,4); // 0 to 4 because min is inclusive, max is exclusive
  switch(light){
    case UP: digitalWrite(upLED, HIGH); break;
    case RIGHT: digitalWrite(rightLED, HIGH); break;
    case DOWN: digitalWrite(downLED, HIGH); break;
    case LEFT: digitalWrite(leftLED, HIGH); break;
  }
}

void all_LEDs_Off(){
  digitalWrite(upLED, LOW);
  digitalWrite(rightLED, LOW);
  digitalWrite(downLED, LOW);
  digitalWrite(leftLED, LOW);
}

void spinLED(int timer){
  digitalWrite(upLED, HIGH);
  delay(timer);
  digitalWrite(upLED, LOW);
  
  digitalWrite(rightLED, HIGH);
  delay(timer);
  digitalWrite(rightLED, LOW);
  
  digitalWrite(downLED, HIGH);
  delay(timer);
  digitalWrite(downLED, LOW);
  
  digitalWrite(leftLED, HIGH);
  delay(timer);
  digitalWrite(leftLED, LOW);
}
