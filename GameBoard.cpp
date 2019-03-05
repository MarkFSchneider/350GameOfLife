#include "GameBoard.h"
using namespace std;

  GameBoard::GameBoard(int xSize, int ySize, string inputBoard, string inputMode)
{

   xLength = xSize;
   yLength = ySize;
   mode = inputMode;
   board = inputBoard;
   generation = 0;

   cout << "board created" << endl;

   populate();

   cout << "board populated" << endl;

   setState(board);

   cout <<"board state updated with string" << endl;


 }

GameBoard::~GameBoard()
{
}

int GameBoard::getXYCordIndex(int x, int y)
{
  /*
  Visual of how this works. More for me really
  Counts from 0. Just like arrays do

  [
  ---
  --x -> [-----x---]
  --- .. [012345678]
  ]

  2,1 -> 2 + 3*1 = 5

  x0 and y0 is bottom left

  */
  return (x + (yLength * y));
}

void GameBoard::populate()
{




  for(int y = 0; y < yLength; y++)
  {
    for(int x = 0; x < xLength; x++)
    {
      currentBoard.push_back(GameSquare(x,y));
      updateNeigbors(currentBoard[getXYCordIndex(x,y)]);
    }
  }
  //this creates an extra empty box to be referenced in classic mode
  currentBoard.push_back(GameSquare(0,yLength));
}

void GameBoard::setState(string inputBoard)
{

    for (unsigned int i = 0; i < inputBoard.size(); i++)
    {

      if(inputBoard[i] == 'X')
      {
        currentBoard[i].occupied = true;

      }

      if(inputBoard[i] == '-')
      {
        currentBoard[i].occupied = false;
      }

    }

}

void GameBoard::setState()
{
  string setString = "";
  generation++;
  //iterates over each game square
  for(int i = 0; i < xLength * yLength; i++)
  {
    int trueCount = 0;
    //iterates over each neighbor in this square
    for(int j = 0; j < 8; j++)
    {
      int xCord = currentBoard[i].neighbors[j][0];
      int yCord = currentBoard[i].neighbors[j][1];

      if(currentBoard[getXYCordIndex(xCord, yCord)].occupied)
      {

        trueCount +=1;

      }
    }

    if(trueCount <= 1)
    {
      setString += '-';
    }
    if(trueCount == 2)
    {
      if(currentBoard[i].occupied)
      {
        setString += 'X';
      }
      else
      {
        setString += '-';
      }
    }
    if(trueCount == 3)
    {
      setString += 'X';
    }
    if(trueCount >= 4)
    {
      setString += '-';
    }
  }

  setState(setString);
}

string GameBoard::writeBoard()
{
  string output = "";

  //output += "Generation ";
  output += to_string(generation) + '\n';



//Genereates a read file
//output += to_string(xLength) + '\n';
//output += to_string(yLength) + '\n';

  for(int y = 0; y < yLength; y++)
  {
    for(int x = 0; x < xLength; x++)
    {
      if(currentBoard[getXYCordIndex(x,y)].occupied)
      {
        output += 'X';
      }
      if(!currentBoard[getXYCordIndex(x,y)].occupied)
      {
        output += '-';
      }

    }
    output += '\n';
  }
  return output;
}

void GameBoard::updateNeigbors(GameSquare &location)
{
  //First Check if it is an edge part
  //The bottom left cordinate is [0,0], and the top is [max X - 1, max Y - 1]

  //These are categorized by:
  //   an X or Y value of 0
  //   an X or Y value of max X - 1 or max Y - 1

  //these if-else statements detirmine where the square is on the board

  bool leftEdge = false;
  bool rightEdge = false;
  bool topEdge = false;
  bool botEdge = false;

  if(location.x == 0)
  {
    leftEdge = true;
  }
  if(location.x == (xLength - 1))
  {
    rightEdge = true;
  }
  if(location.y == 0)
  {
    botEdge = true;
  }
  if(location.y == (yLength - 1))
  {
    topEdge = true;
  }

  //cout << "left edge: " << leftEdge <<endl << "right edge: " << rightEdge << endl << "top edge: " << topEdge <<endl<<"bottom edge: " << botEdge << endl;

  //Now we know where the square is, and supposedly, what mode we are on.

  //Array Reference
  /*
    0,1,2
    3,X,4
    5,6,7


  */

  //Still need to do classic for all

  if(leftEdge && !topEdge && !botEdge)
  {
    location.neighbors[1][0] = location.x;
    location.neighbors[1][1] = location.y + 1;

    location.neighbors[2][0] = location.x + 1;
    location.neighbors[2][1] = location.y + 1;



    location.neighbors[4][0] = location.x + 1;
    location.neighbors[4][1] = location.y;



    location.neighbors[6][0] = location.x;
    location.neighbors[6][1] = location.y - 1;

    location.neighbors[7][0] = location.x + 1;
    location.neighbors[7][1] = location.y - 1;

    //Missing 0, 3, 5

    if(mode == "CLASSIC")
    {
      location.neighbors[0][0] = 0;
      location.neighbors[0][1] = yLength;

      location.neighbors[3][0] = 0;
      location.neighbors[3][1] = yLength;

      location.neighbors[5][0] = 0;
      location.neighbors[5][1] = yLength;

    }

    if(mode == "DOUGHNUT")
    {
      location.neighbors[0][0] = xLength - 1;
      location.neighbors[0][1] = location.y + 1;

      location.neighbors[3][0] = xLength - 1;
      location.neighbors[3][1] = location.y;

      location.neighbors[5][0] = xLength - 1;
      location.neighbors[5][1] = location.y - 1;

    }

    if(mode == "MIRROR")
    {
      location.neighbors[0][0] = location.x;
      location.neighbors[0][1] = location.y + 1;

      location.neighbors[3][0] = location.x;
      location.neighbors[3][1] = location.y;

      location.neighbors[5][0] = location.x;
      location.neighbors[5][1] = location.y - 1;
    }
  }

  if(rightEdge && !topEdge && !botEdge)
  {


    location.neighbors[0][0] = location.x - 1;
    location.neighbors[0][1] = location.y + 1;

    location.neighbors[1][0] = location.x;
    location.neighbors[1][1] = location.y + 1;



    location.neighbors[3][0] = location.x - 1;
    location.neighbors[3][1] = location.y;



    location.neighbors[5][0] = location.x - 1;
    location.neighbors[5][1] = location.y - 1;

    location.neighbors[6][0] = location.x;
    location.neighbors[6][1] = location.y - 1;

    //missing 2,4,7

    if(mode == "CLASSIC")
    {
      location.neighbors[2][0] = 0;
      location.neighbors[2][1] = yLength;

      location.neighbors[4][0] = 0;
      location.neighbors[4][1] = yLength;

      location.neighbors[7][0] = 0;
      location.neighbors[7][1] = yLength;

    }

    if(mode == "DOUGHNUT")
    {
      location.neighbors[2][0] = 0;
      location.neighbors[2][1] = location.y + 1;

      location.neighbors[4][0] = 0;
      location.neighbors[4][1] = location.y;

      location.neighbors[7][0] = 0;
      location.neighbors[7][1] = location.y - 1;
    }

    if(mode == "MIRROR")
    {
      location.neighbors[2][0] = location.x;
      location.neighbors[2][1] = location.y + 1;

      location.neighbors[4][0] = location.x;
      location.neighbors[4][1] = location.y;

      location.neighbors[7][0] = location.x;
      location.neighbors[7][1] = location.y - 1;
    }
  }

  if(topEdge && !leftEdge && !rightEdge)
  {

    location.neighbors[3][0] = location.x - 1;
    location.neighbors[3][1] = location.y;

    location.neighbors[4][0] = location.x + 1;
    location.neighbors[4][1] = location.y;



    location.neighbors[5][0] = location.x - 1;
    location.neighbors[5][1] = location.y - 1;

    location.neighbors[6][0] = location.x;
    location.neighbors[6][1] = location.y - 1;

    location.neighbors[7][0] = location.x + 1;
    location.neighbors[7][1] = location.y - 1;

    //missing 0,1,2

    if(mode == "CLASSIC")
    {
      location.neighbors[0][0] = 0;
      location.neighbors[0][1] = yLength;

      location.neighbors[1][0] = 0;
      location.neighbors[1][1] = yLength;

      location.neighbors[2][0] = 0;
      location.neighbors[2][1] = yLength;

    }

    if(mode == "DOUGHNUT")
    {
      location.neighbors[0][0] = location.x - 1;
      location.neighbors[0][1] = 0;

      location.neighbors[1][0] = location.x;
      location.neighbors[1][1] = 0;

      location.neighbors[2][0] = location.x + 1;
      location.neighbors[2][1] = 0;

    }

    if(mode == "MIRROR")
    {
      location.neighbors[0][0] = location.x - 1;
      location.neighbors[0][1] = location.y;

      location.neighbors[1][0] = location.x;
      location.neighbors[1][1] = location.y;

      location.neighbors[2][0] = location.x + 1;
      location.neighbors[2][1] = location.y;
    }
  }

  if(botEdge && !leftEdge && !rightEdge)
  {
    location.neighbors[0][0] = location.x - 1;
    location.neighbors[0][1] = location.y + 1;

    location.neighbors[1][0] = location.x;
    location.neighbors[1][1] = location.y + 1;

    location.neighbors[2][0] = location.x + 1;
    location.neighbors[2][1] = location.y + 1;



    location.neighbors[3][0] = location.x - 1;
    location.neighbors[3][1] = location.y;

    location.neighbors[4][0] = location.x + 1;
    location.neighbors[4][1] = location.y;



    location.neighbors[5][0] = location.x - 1;
    location.neighbors[5][1] = location.y - 1;

    location.neighbors[6][0] = location.x;
    location.neighbors[6][1] = location.y - 1;

    location.neighbors[7][0] = location.x + 1;
    location.neighbors[7][1] = location.y - 1;

    //missing 5,6,7

    if(mode == "CLASSIC")
    {
      location.neighbors[5][0] = 0;
      location.neighbors[5][1] = yLength;

      location.neighbors[6][0] = 0;
      location.neighbors[6][1] = yLength;

      location.neighbors[7][0] = 0;
      location.neighbors[7][1] = yLength;

    }

    if(mode == "DOUGHNUT")
    {
      location.neighbors[5][0] = location.x - 1;
      location.neighbors[5][1] = yLength - 1;

      location.neighbors[6][0] = location.x;
      location.neighbors[6][1] = yLength - 1;

      location.neighbors[7][0] = location.x + 1;
      location.neighbors[7][1] = yLength - 1;

    }

    if(mode == "MIRROR")
    {
      location.neighbors[5][0] = location.x - 1;
      location.neighbors[5][1] = location.y - 1;

      location.neighbors[6][0] = location.x;
      location.neighbors[6][1] = location.y - 1;

      location.neighbors[7][0] = location.x + 1;
      location.neighbors[7][1] = location.y - 1;
    }
  }

  if(topEdge && leftEdge)
  {






    location.neighbors[4][0] = location.x + 1;
    location.neighbors[4][1] = location.y;





    location.neighbors[6][0] = location.x;
    location.neighbors[6][1] = location.y - 1;

    location.neighbors[7][0] = location.x + 1;
    location.neighbors[7][1] = location.y - 1;

    //0,1,2,3,5



    if(mode == "CLASSIC")
    {
      location.neighbors[0][0] = 0;
      location.neighbors[0][1] = yLength;

      location.neighbors[1][0] = 0;
      location.neighbors[1][1] = yLength;

      location.neighbors[2][0] = 0;
      location.neighbors[2][1] = yLength;

      location.neighbors[3][0] = 0;
      location.neighbors[3][1] = yLength;

      location.neighbors[5][0] = 0;
      location.neighbors[5][1] = yLength;

    }

    if(mode == "DOUGHNUT")
    {
      location.neighbors[0][0] = xLength - 1;
      location.neighbors[0][1] = 0;

      location.neighbors[1][0] = location.x;
      location.neighbors[1][1] = 0;

      location.neighbors[2][0] = location.x + 1;
      location.neighbors[2][1] = 0;

      location.neighbors[3][0] = xLength - 1;
      location.neighbors[3][1] = location.y;

      location.neighbors[5][0] = xLength - 1;
      location.neighbors[5][1] = location.y - 1;

    }

    if(mode == "MIRROR")
    {
      location.neighbors[0][0] = location.x;
      location.neighbors[0][1] = location.y;

      location.neighbors[1][0] = location.x;
      location.neighbors[1][1] = location.y;

      location.neighbors[2][0] = location.x + 1;
      location.neighbors[2][1] = location.y;

      location.neighbors[3][0] = location.x;
      location.neighbors[3][1] = location.y;

      location.neighbors[5][0] = location.x;
      location.neighbors[5][1] = location.y - 1;

    }
  }

  if(topEdge && rightEdge)
  {




    location.neighbors[3][0] = location.x - 1;
    location.neighbors[3][1] = location.y;



    location.neighbors[5][0] = location.x - 1;
    location.neighbors[5][1] = location.y - 1;

    location.neighbors[6][0] = location.x;
    location.neighbors[6][1] = location.y - 1;


    //0,1,2,4,7

    if(mode == "CLASSIC")
    {
      location.neighbors[0][0] = 0;
      location.neighbors[0][1] = yLength;

      location.neighbors[1][0] = 0;
      location.neighbors[1][1] = yLength;

      location.neighbors[2][0] = 0;
      location.neighbors[2][1] = yLength;

      location.neighbors[4][0] = 0;
      location.neighbors[4][1] = yLength;

      location.neighbors[7][0] = 0;
      location.neighbors[7][1] = yLength;

    }

    if(mode == "DOUGHNUT")
    {
      location.neighbors[0][0] = location.x - 1;
      location.neighbors[0][1] = 0;

      location.neighbors[1][0] = location.x;
      location.neighbors[1][1] = 0;

      location.neighbors[2][0] = 0;
      location.neighbors[2][1] = 0;

      location.neighbors[4][0] = 0;
      location.neighbors[4][1] = location.y;

      location.neighbors[7][0] = 0;
      location.neighbors[7][1] = location.y - 1;

    }

    if(mode == "MIRROR")
    {
      location.neighbors[0][0] = location.x - 1;
      location.neighbors[0][1] = location.y;

      location.neighbors[1][0] = location.x;
      location.neighbors[1][1] = location.y;

      location.neighbors[2][0] = location.x;
      location.neighbors[2][1] = location.y;

      location.neighbors[4][0] = location.x;
      location.neighbors[4][1] = location.y;

      location.neighbors[7][0] = location.x;
      location.neighbors[7][1] = location.y - 1;

    }
  }

  if(botEdge && leftEdge)
  {


    location.neighbors[1][0] = location.x;
    location.neighbors[1][1] = location.y + 1;

    location.neighbors[2][0] = location.x + 1;
    location.neighbors[2][1] = location.y + 1;





    location.neighbors[4][0] = location.x + 1;
    location.neighbors[4][1] = location.y;




    //0,3,5,6,7

    if(mode == "CLASSIC")
    {
      location.neighbors[0][0] = 0;
      location.neighbors[0][1] = yLength;

      location.neighbors[3][0] = 0;
      location.neighbors[3][1] = yLength;

      location.neighbors[5][0] = 0;
      location.neighbors[5][1] = yLength;

      location.neighbors[6][0] = 0;
      location.neighbors[6][1] = yLength;

      location.neighbors[7][0] = 0;
      location.neighbors[7][1] = yLength;

    }

    if(mode == "DOUGHNUT")
    {
      location.neighbors[0][0] = xLength - 1;
      location.neighbors[0][1] = location.y + 1;

      location.neighbors[3][0] = xLength - 1;
      location.neighbors[3][1] = location.y;

      location.neighbors[5][0] = xLength - 1;
      location.neighbors[5][1] = yLength - 1;

      location.neighbors[6][0] = location.x;
      location.neighbors[6][1] = yLength - 1;

      location.neighbors[7][0] = location.x + 1;
      location.neighbors[7][1] = yLength - 1;
    }

    if(mode == "MIRROR")
    {
      location.neighbors[0][0] = location.x;
      location.neighbors[0][1] = location.y + 1;

      location.neighbors[3][0] = location.x;
      location.neighbors[3][1] = location.y;

      location.neighbors[5][0] = location.x;
      location.neighbors[5][1] = location.y;

      location.neighbors[6][0] = location.x;
      location.neighbors[6][1] = location.y;

      location.neighbors[7][0] = location.x + 1;
      location.neighbors[7][1] = location.y;

    }
  }

  if(botEdge && rightEdge)
  {
    location.neighbors[0][0] = location.x - 1;
    location.neighbors[0][1] = location.y + 1;

    location.neighbors[1][0] = location.x;
    location.neighbors[1][1] = location.y + 1;





    location.neighbors[3][0] = location.x - 1;
    location.neighbors[3][1] = location.y;







    //2,4,5,6,7
    if(mode == "CLASSIC")
    {
      location.neighbors[2][0] = 0;
      location.neighbors[2][1] = yLength;

      location.neighbors[4][0] = 0;
      location.neighbors[4][1] = yLength;

      location.neighbors[5][0] = 0;
      location.neighbors[5][1] = yLength;

      location.neighbors[6][0] = 0;
      location.neighbors[6][1] = yLength;

      location.neighbors[7][0] = 0;
      location.neighbors[7][1] = yLength;

    }

    if(mode == "DOUGHNUT")
    {
      location.neighbors[2][0] = 0;
      location.neighbors[2][1] = location.y + 1;

      location.neighbors[4][0] = 0;
      location.neighbors[4][1] = location.y;

      location.neighbors[5][0] = location.x - 1;
      location.neighbors[5][1] = yLength - 1;

      location.neighbors[6][0] = location.x;
      location.neighbors[6][1] = yLength - 1;

      location.neighbors[7][0] = 0;
      location.neighbors[7][1] = yLength - 1;

    }

    if(mode == "MIRROR")
    {
      location.neighbors[2][0] = location.x;
      location.neighbors[2][1] = location.y + 1;

      location.neighbors[4][0] = location.x;
      location.neighbors[4][1] = location.y;

      location.neighbors[5][0] = location.x - 1;
      location.neighbors[5][1] = location.y;

      location.neighbors[6][0] = location.x;
      location.neighbors[6][1] = location.y;

      location.neighbors[7][0] = location.x ;
      location.neighbors[7][1] = location.y;

    }
  }

  if(!leftEdge && !rightEdge && !topEdge && !botEdge)
  {
    location.neighbors[0][0] = location.x - 1;
    location.neighbors[0][1] = location.y + 1;

    location.neighbors[1][0] = location.x;
    location.neighbors[1][1] = location.y + 1;

    location.neighbors[2][0] = location.x + 1;
    location.neighbors[2][1] = location.y + 1;



    location.neighbors[3][0] = location.x - 1;
    location.neighbors[3][1] = location.y;

    location.neighbors[4][0] = location.x + 1;
    location.neighbors[4][1] = location.y;



    location.neighbors[5][0] = location.x - 1;
    location.neighbors[5][1] = location.y - 1;

    location.neighbors[6][0] = location.x;
    location.neighbors[6][1] = location.y - 1;

    location.neighbors[7][0] = location.x + 1;
    location.neighbors[7][1] = location.y - 1;

  }



}
