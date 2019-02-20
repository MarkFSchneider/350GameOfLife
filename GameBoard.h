#include <iostream>
#include "GameSquare.h"
using namespace std;

class GameBoard
{
public:
  GameBoard(int xSize, int ySize, char inputBoard[])
  {

  }

  ~GameBoard()
  {
    
  }

  int xLength;
  int yLength;

  GameSquare currentBoard[xLength][yLength];
  bool newBoard[xLength][yLength];




};
