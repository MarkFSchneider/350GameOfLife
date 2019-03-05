#include "GameManager.h"
#include "LifeReader.h"
#include <iostream>
#include <string>
#include <time.h>
using namespace std;

int main(int argc, char const *argv[]) {

srand(time(0));

  /*
    Input file looks like:

    5 //height of grid
    5 //width of grid
    XXXXX
    -----
    XXXXX
    -----
    XXXXX

    CURRENT FUNCTIONALITY:
      Board Is Generated
      Board can write out current statements
      Board can update itself through generations.
      Rules engine for all 3 modes



    Create function that will:
    Return X and Y from file read

    Second function that will:
    Return a string from bottom up, excluding newlines from file read.
    starting from 0,0 or bottom left, left to right, bottom to top

    Create a rules engine class. See notes
  */

  int x = 5;
  int y = 5;

  string board = "----------XXXXX-----XXXXX";
  string mode = "CLASSIC";
  string runMode = "ENTER";
  string fpath = "zinput.txt";
  bool exit = false;
  bool fileOutput = false;


  while(!exit)
  {
  bool startLoop = false;
  while(!startLoop)
  {
    int option;
  cout << "Start with: \n (1) random board \n (2) file" << endl;
  cin >> option;
  if(option == 1)
  {
    float occChance;
    cout << "Chance of occupancy (.XX): ";
    cin >> occChance;
    cout << endl << "X dimention: ";
    cin >> x;
    cout << endl << "Y dimention: ";
    cin >> y;

    LifeReader readFile = LifeReader(fpath);
    board = readFile.randomGeneration(occChance, x, y);

    startLoop = true;
  }

  if(option == 2)
  {

    cout << "Filename: ";
    cin >> fpath;
    LifeReader readFile = LifeReader(fpath);
    board = readFile.fileLines;
    x = readFile.x;
    y = readFile.y;
    startLoop = true;
  }
}

startLoop = false;

while (!startLoop)
 {
   int inMode;
  cout << endl << "Run mode: \n (1) Classic \n (2) Mirror \n (3) Doughnut" << endl;
  cin >> inMode;

  if(inMode == 1)
  {
    runMode = "CLASSIC";
    startLoop = true;
  }

  if(inMode == 2)
  {
    runMode = "MIRROR";
    startLoop = true;
  }

  if(inMode == 3)
  {
    runMode = "DOUGHNUT";
    startLoop = true;
  }
}

startLoop = false;

while(!startLoop)
{
  int inMode;
  cout << "Pauses: \n (1) No Pause \n (2) Timed Pause \n (3) Hit Key" << endl;
  cin >> inMode;

  if(inMode == 1)
  {
    runMode = "UNBOUND";
      startLoop = true;
  }

  if(inMode == 2)
  {
    runMode = "PAUSE";
      startLoop = true;
  }

  if(inMode == 3)
  {
    runMode = "ENTER";
      startLoop = true;
  }
}

startLoop = false;
while(!startLoop)
{
  char inChar;
  cout << "write to file (y/n)" << endl;

  cin >> inChar;

  if(inChar == 'y' || inChar == 'Y')
  {
    fileOutput = true;
    startLoop = true;
  }

  if(inChar == 'n' || inChar == 'N')
  {
    fileOutput = false;
    startLoop = true;
  }
}




  GameBoard gameOfLife = GameBoard(x, y, board, mode);

  GameManager gameRunner(runMode, fileOutput); //= GameManager(runMode, fileOutput);

  gameRunner.beginGameLoop(gameOfLife);




  return 0;
}
}
