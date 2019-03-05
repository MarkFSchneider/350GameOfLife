#include <iostream>
using namespace std;

class GameSquare
{
public:
  GameSquare(int xCord, int yCord);
  ~GameSquare();


  int x;
  int y;

  int neighbors[8][2];

  bool occupied;

};
