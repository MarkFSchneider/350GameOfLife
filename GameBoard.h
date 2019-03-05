#include <iostream>
#include <string>
#include <vector>
#include "GameSquare.h"
using namespace std;

class GameBoard
{

public:
  GameBoard(int xSize, int ySize, string inputBoard, string inputMode);
  ~GameBoard();

//translates an X and Y into a 1d index
  int getXYCordIndex(int x, int y);
  void populate();
  void updateNeigbors(GameSquare &location);
  string writeBoard();
  void setState();
  void setState(string inputBoard);

  int xLength;
  int yLength;


  string mode;
  string board;
  string outBoard;

  int generation;

  vector<GameSquare> currentBoard;
  //GameSquare *currentBoard;




};
