#pragma once

#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

using std::vector;
using std::ifstream;
using std::string;
using std::map;

class CMap
{
public:
    CMap(void);
    ~CMap(void);

    void Init(const int theScreen_Height, const int theScreen_Width,
        const int theTileSize = 25);
    bool LoadMap(const string mapName);
    int GetNumOfTiles_Height(void);		// Get the number of tiles for height of the screen
    int GetNumOfTiles_Width(void);		// Get the number of tiles for width of the screen
    int GetTileSize(void);

    int getNumOfTiles_MapHeight(void);		// Get the number of tiles for height of the map
    int getNumOfTiles_MapWidth(void);		// Get the number of tiles for width of the map

    //vector<vector<int> > theScreenMap;
    //map<int, vector<int>> theScreenMap;

    int getScreenWidth();
    int getScreenHeight();

private:
    int theScreen_Height;
    int theScreen_Width;
    int theNumOfTiles_Height;		// Number of tiles in the screen's height
    int theNumOfTiles_Width;		// Number of tiles in the screen's width
    int theTileSize;

    int theMap_Height;				// The map's height
    int theMap_Width;				// The map's width
    int theNumOfTiles_MapHeight;	// Number of tiles in the map's height
    int theNumOfTiles_MapWidth;		// Number of tiles in the map's width

    bool LoadFile(const string mapName);
};
