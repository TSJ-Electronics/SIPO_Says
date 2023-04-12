#ifndef GAMEFUNCTIONS_H
#define GAMEFUNCTIONS_H

  enum gameDirections{
    UP, RIGHT, DOWN, LEFT, NONE };
    
  enum songSelect{//currently not used
   IMPERIAL_MARCH, MARIO, SONIC, GAME_OVER };
   
  #define sequenceArrayLength 50 // had to lower from 99 because used too much memory
  static int sudoSaysSequenceArray[sequenceArrayLength];//Simon Says Sequence Array
  static int currentScore;//Score counter variable
  static bool gameInProgress; //Game in progress boolean
  static int winningScore;
    
  void powerOnInitialize();
  void computerTurn(int,int);
  void initializeRandomGameSequence();
  void computerTurn();
  void waitForPlayerButtonRelease();
  gameDirections checkForPlayerInput();
  bool playerTurn();
  void incrementScoreCounter();
  bool getGameStatus();
  void setGameStatus(bool);
  void resetScoreCounter();
  int getCurrentScore();
  void winGame();
  void setWinningScore(int);
  int getWinningScore();
 
  //SIPO Says Directional Notes
  void playUp(int);
  void playLeft(int);
  void playDown(int);
  void playRight(int);

  void gameOver();

  //play any song from the song library!
  void playSong();

#endif
