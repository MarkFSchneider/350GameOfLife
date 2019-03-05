#include "GameManager.h"
using namespace std;


GameManager::GameManager(string runMode, bool writeToFile)
{
  pause = false;
  enter = false;
  unbound = false;
  exit = false;
  fileRun = true;
  fileWrite = writeToFile;


  if(writeToFile)
  {
      if(fileRun)
      {
        string fNamePath;
        cout << "Output file name: ";
        cin >> fNamePath;

        outFile.open(fNamePath);
        fileRun = false;
      }
  }

/*
  for(int i = 0; i < 9; i++)
  {
    recentBoards[i] = "nnn";
      if(i > 0){
        recentBoards[i] +=recentBoards[i - 1];
      }
  }*/

  if(runMode == "PAUSE")
  {
    pause = true;
  }

  if(runMode == "ENTER")
  {
    enter = true;
  }

  if(runMode == "UNBOUND")
  {
    unbound = true;
  }

cout << "manager made" << endl;



}

GameManager::~GameManager()
{

}

void GameManager::runGeneration(GameBoard& game)
{

  game.setState();
  manageArray(game.writeBoard());

}

void GameManager::manageArray(string boardState)
{
  if(recent==8)
  {
    recent = -1;
  }
  recentBoards[++recent] = boardState;
}

bool GameManager::checkLoop()
{
  /*
//This code was the loop check, which ends the program if a loop is Established.
//It kept glitching and ending the program prematurely, and I couldn't find the error.

  for(int i = 0; i < 8; i++)
  {
    for(int j = i+1; j < 9; j++)
    {

      if(0 == recentBoards[i].substr(2, (recentBoards[i].length() - 2)).compare(recentBoards[i].substr(2, (recentBoards[j].length() - 2))))
      {


        cout << "match at " << i << "," << j << endl;
        if(i != j)
        {
          cout << "Loop Established. Program terminated" << endl;


          return true;
        }

      }
    }
  }
  */

  return false;
}

void GameManager::beginGameLoop(GameBoard& game)
{

  for(int i = 0; i < 1000; i++) //while(!exit)
  {

    runGeneration(game);
    cout << recentBoards[recent];
    if(writeToFile)
    {
      outFile << recentBoards[recent];
    }
    exit = checkLoop();

    if(pause)
    {
      //add pause code
    }
    if(enter)
    {
      do
        {
            cout << '\n' << "Press a key to continue...";
        } while (cin.get() != '\n');
    }

  }
}
