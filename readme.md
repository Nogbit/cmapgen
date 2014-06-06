This is a map generator for roguelikes or any game really that needs random
caves, rivers, lakes, mountains etc.  Blog post about it [over here](http://marcellusmiles.com/c-cellular-automation-for-roguelike-map-generation).

## Building
Known to work on Linux, not tested on Windows but shouldn't have a problem compiling there at all.

    g++ -std=c++11 maps.cpp -o mapper
    ./mapper

## Interactive
It's got a menu!  "r" will set all the values to 1.  "n" will do the same but keep the same seed.  The main thing you will want to use is "t" to change the seed, density and isolation all at once.  I find values close to 9,5,2 to work good for caves.  You can dig through the code to see why those work well.  For quick iteration simply press "s" and type in a random number.  For the wall% "e" anything between 40-50 works good.  Try large maps with "w", 160,60 is cool!

![Screenshot](/screenshot.png?raw=true)

## Non Interactive
No menu needed?  No problem!

```c++
#include "mapgen.cpp"

vector<int> iterations;
iterations.push_back(5);
iterations.push_back(2);
iterations.push_back(4);

//another set, optional, the Interactive program does not provide for this
iterations.push_back(5);
iterations.push_back(0);
iterations.push_back(3);

MapGen map = MapGen(1234567, 80, 30, 40, iterations);
```

## Source
``mapgen.cpp`` originally came from the c code found at this posting on [roguebasin.com](http://www.roguebasin.com/index.php?title=Cellular_Automata_Method_for_Generating_Random_Cave-Like_Levels). I converted it to c++, changed the formatting, cleaned up a few things and made it safer to use (no malloc).  ``maps.cpp`` is the menu system you see in the screenshot.

Currently, this does not fill areas that are disconnected from the open areas. That may or may not be desired depending on your use.
