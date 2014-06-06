#include <iostream>
#include <vector>

#define TILE_FLOOR 0
#define TILE_WALL 1

using namespace std;

typedef struct {
  int r1Cutoff, r2Cutoff, smoothing;
} GenerationParams;

class MapGen {
 public:
  vector<vector<int>> mapA;
  vector<vector<int>> mapB;

  int fillprob   = 40,
      r1Cutoff   = 5, 
      r2Cutoff   = 2, 
      width      = 64,
      height     = 20, 
      mapSeed    = 0;

  int generations;

  GenerationParams *params;
  vector<GenerationParams> paramsSet;

  MapGen(int seed, int w, int h, int fill, vector<int> iterations) 
  {
    width    = w;
    height   = h;
    fillprob = fill;
    mapSeed  = seed;

    if (mapSeed == 0) {
      mapSeed = time(NULL);
    }

    for (int x = 0; x < iterations.size(); x+=3) {
      GenerationParams p;
      p.r1Cutoff  = iterations[x];
      p.r2Cutoff  = iterations[x+1];
      p.smoothing = iterations[x+2];
      paramsSet.push_back(p);
    }

    InitMap();

    for (int x = 0; x < paramsSet.size(); x++) {
      params = &paramsSet[x];
      for (int y = 0; y < params->smoothing; y++)
        Generation();
    }

    PrintMap();
    PrintFooter();
  }

  int RandPick(void) 
  {
    if(rand() % 100 < fillprob)
      return TILE_WALL;
    else
      return TILE_FLOOR;
  }

  void InitMap(void) 
  {
    int x, y;
    srand(mapSeed);

    for (x = 0; x < height; x++) {
      vector<int> j;
      j.resize(width);
      mapA.push_back(j);
      mapB.push_back(j);
    }

    for (y = 1; y < height - 1; y++)
      for (x= 1; x < width - 1; x++)
        mapA[y][x] = RandPick();

    for (y = 0; y < height; y++)
      for (x = 0; x < width; x++)
        mapB[y][x] = TILE_WALL;

    for (y = 0; y < height; y++)
      mapA[y][0] = mapA[y][width - 1] = TILE_WALL;

    for(x = 0; x < width; x++)
      mapA[0][x] = mapA[height - 1][x] = TILE_WALL;
  }

  void Generation(void) 
  {
    int x, y, i, j;

    for(y = 1; y < height - 1; y++) {
      for(x = 1; x <width - 1; x++) {
        int adjCountR1 = 0, adjCountR2 = 0;

        for(i = -1; i <= 1; i++)
          for(j = -1; j <= 1; j++) {
            if(mapA[y+i][x+j] != TILE_FLOOR)
              adjCountR1++;
          }

        for(i = y-2; i <= y+2; i++)
          for(j = x-2; j <= x+2; j++) {
            if(abs(i-y) == 2 && abs(j-x) == 2)
              continue;
            if(i < 0 || j < 0 || i >= height || j >= width)
              continue;
            if(mapA[i][j] != TILE_FLOOR)
              adjCountR2++;
          }

        if(adjCountR1 >= params->r1Cutoff || adjCountR2 <= params->r2Cutoff)
          mapB[y][x] = TILE_WALL;
        else
          mapB[y][x] = TILE_FLOOR;
      }
    }

    for(y = 1; y < height - 1; y++)
      for(x = 1; x < width - 1; x++)
        mapA[y][x] = mapB[y][x];
  }


  void PrintFooter(void) 
  {
    //ugly mess using cout like this, printf in this case would be better
    cout << "Width: " << width << "    Height: " << height << "     Walls: "
      << fillprob << "%    Seed: " << mapSeed << endl;

    for(int x = 0; x < paramsSet.size(); x++) {
      cout << "Smoothing: " << paramsSet[x].smoothing << "     " <<
              "Density Cutoff: " <<  paramsSet[x].r1Cutoff; 

      if(paramsSet[x].r2Cutoff >= 0)
        cout << "     "  << "Isolation Cutoff: " << 
          paramsSet[x].r2Cutoff << endl;
      else
        cout << endl;
    }
  }

  void PrintMap(void) 
  {
    for(int x = 0; x < height; x++) {
      for(int y = 0; y < width; y++) {
        switch(mapA[x][y]) {
          case TILE_WALL:
            cout << "#";
            break;
          case TILE_FLOOR:
            cout << ".";
            break;
        }
      }
      cout << endl;
    }
  }

  ~MapGen() {}
};
