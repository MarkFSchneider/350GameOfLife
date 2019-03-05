#include "LifeReader.h"

using namespace std;

LifeReader::LifeReader(string filepath)
{
   ifstream inFile;
  inFile.open(filepath);
  if (!inFile) {
      cerr << "Unable to open file";
      exit(1);
  }
string line = "";
  int y , x;

  inFile >> y >> x;

  fileLines = "";
  while(getline(inFile, line))
    {
      fileLines += line;
    }
  inFile.close();

}

LifeReader::~LifeReader()
{

}

string LifeReader::randomGeneration(float percent, int x, int y)
{
  string setBoard = "";
  for(int i = 0; i < x * y; i++)
  {
    float choice = rand() % 100;
    if(choice < (percent * 100))
    {
      setBoard += "X";
    }
    else
    {
      setBoard += "-";
    }
  }

  return setBoard;
}
