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
  digitalWrite(LED_UP, HIGH);
}
void right_LED_On(){
  digitalWrite(LED_RIGHT, HIGH);
}
void down_LED_On(){
  digitalWrite(LED_DOWN, HIGH);
}
void left_LED_On(){
  digitalWrite(LED_LEFT, HIGH);
}

void randomLight(){
  all_LEDs_Off();// turn off any light that may be on
  int light = random(0,4); // 0 to 4 because min is inclusive, max is exclusive
  switch(light){
    case UP: digitalWrite(LED_UP, HIGH); break;
    case RIGHT: digitalWrite(LED_RIGHT, HIGH); break;
    case DOWN: digitalWrite(LED_DOWN, HIGH); break;
    case LEFT: digitalWrite(LED_LEFT, HIGH); break;
  }
}

void all_LEDs_Off(){
  digitalWrite(LED_UP, LOW);
  digitalWrite(LED_RIGHT, LOW);
  digitalWrite(LED_DOWN, LOW);
  digitalWrite(LED_LEFT, LOW);
}

void spinLED(int timer){
  digitalWrite(LED_UP, HIGH);
  delay(timer);
  digitalWrite(LED_UP, LOW);
  
  digitalWrite(LED_RIGHT, HIGH);
  delay(timer);
  digitalWrite(LED_RIGHT, LOW);
  
  digitalWrite(LED_DOWN, HIGH);
  delay(timer);
  digitalWrite(LED_DOWN, LOW);
  
  digitalWrite(LED_LEFT, HIGH);
  delay(timer);
  digitalWrite(LED_LEFT, LOW);
}
