#include <iostream>
#include <sstream>
#include "mapgen.cpp"
#include "stringsplit.cpp"

using namespace std;

int width     = 80;
int height    = 30;
int walls     = 40;
int smooth    = 9;
int seed      = time(NULL);
int density   = 5;
int isolation = 2;
string prompt;
void reBuild(int menu);

int main(int argc, char* argv[])
{
  //first map
  reBuild(1);
  bool menuGetDimensions = false;
  bool menuGetThree      = false;
  bool menuGetWalls      = false;
  bool menuGetSeed       = false;

  while(true)
  {
    // note...this does no checking of input
    // enter exactly what it wants!
    cout << prompt;
    string cmd;
    getline(cin,cmd);
                                   
    // go into a submenu and stay there if that menu was choosen
    if (menuGetDimensions){
      vector<string> x  = split(cmd, ',');
      width             = atoi(x[0].c_str());
      height            = atoi(x[1].c_str());
      menuGetDimensions = false;
      reBuild(1);
    }
    else if (menuGetThree){
      vector<string> x = split(cmd, ',');
      smooth           = atoi(x[0].c_str());
      density          = atoi(x[1].c_str());
      isolation        = atoi(x[2].c_str());
      menuGetThree     = false;
      reBuild(1);
    }
    else if (menuGetWalls){
      walls        = atoi(cmd.c_str());
      menuGetWalls = false;
      reBuild(1);
    }
    else if (menuGetSeed){
      seed        = atoi(cmd.c_str());
      menuGetSeed = false;
      reBuild(1);
    }
    // main menu commands...
    else if (cmd == "n") {
      smooth    = 1;
      density   = 1;
      isolation = 1;
      reBuild(1);
    }
    else if (cmd == "r") {
      smooth    = 1;
      density   = 1;
      isolation = 1;
      seed      = time(NULL);
      reBuild(1);
    }
    else if (cmd == "w") {
      menuGetDimensions = true;
      reBuild(2);
    }
    else if (cmd == "t") {
      menuGetThree = true;
      reBuild(3);
    }
    else if (cmd == "e") {
      menuGetWalls = true;
      reBuild(4);
    }
    else if (cmd == "s") {
      menuGetSeed = true;
      reBuild(5);
    }
    else if (cmd == "z") {
      smooth++;
      reBuild(1);
    }
    else if (cmd == "x") {
      density++;
      reBuild(1);
    }
    else if (cmd == "c") {
      isolation++;
      reBuild(1);
    }
    else if (cmd == "q")
      break;
    else {
      reBuild(1);
    }
  }
  return 0;
}

void reBuild(int menu)
{
  switch (menu) {
    case 1:
      prompt = "Enter menu command: ";
      break;
    case 2:
      prompt = "Enter as width,height...ex 80,30: ";
      break;
    case 3:
      prompt = "Enter Smoothing, Density, Isolation as x,y,z: ";
      break;
    case 4:
      prompt = "Enter a number for % of walls: ";
      break;
    case 5:
      prompt = "Enter a number for random seed: ";
      break;
    default:
      break;
  }

  vector<int> iterations;
  // note, we can actually have multiple sets of density, isolation, smooth
  // but I find with good values entered to begin with its not needed
  iterations.push_back(density);
  iterations.push_back(isolation);
  iterations.push_back(smooth);
  MapGen map = MapGen(seed, width, height, walls, iterations);

  cout << "(q)Quit " << "(r)Reset " << "(s)Seed  " << "(w)Width,Height  " <<
          "(e)Wall% " << endl;
  cout << "(t)Set All Three  " << "(n)New" << endl;
  cout << "(z)Smooth +1  " << "(x)Density +1  "  <<  "(c)Isolation +1" << endl; 
}
