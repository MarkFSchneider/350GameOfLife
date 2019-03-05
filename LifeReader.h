#include <iostream>
#include <fstream>

using namespace std;

class LifeReader
 {

 public:

   LifeReader(string filepath);
   ~LifeReader();

   string randomGeneration(float percent, int x, int y);


   int y;
   int x;
   string fileLines;

};
