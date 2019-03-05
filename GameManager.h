#include <iostream>
#include "GameBoard.h"
#include "fstream"
using namespace std;


class GameManager
{
public:
  GameManager(string runMode, bool writeToFile);
  ~GameManager();

  void runGeneration(GameBoard& inGame);

  void beginGameLoop(GameBoard& game);

  void manageArray(string boardState);

  bool checkLoop();

  string recentBoards[9] = {"nn","mmm","oooo","ppppp","qqqqqq","rrrrrrr","ssssssss","ttttttttt","uuuuuuuuuu"};
  int recent = -1;

  bool fileWrite;
  bool fileRun;
  bool writeToFile;
  bool pause;
  bool enter;
  bool unbound;
  bool exit;
  ofstream outFile;


};
