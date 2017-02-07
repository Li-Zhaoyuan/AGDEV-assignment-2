#include "Map.h"

CMap::CMap(void)
    : theScreen_Height(0)
    , theScreen_Width(0)
    , theNumOfTiles_Height(0)
    , theNumOfTiles_Width(0)
    , theMap_Height(0)
    , theMap_Width(0)
    , theNumOfTiles_MapHeight(0)
    , theNumOfTiles_MapWidth(0)
    , theTileSize(0)
{
    //theScreenMap.clear();
}

CMap::~CMap(void)
{
    //theScreenMap.clear();
}

void CMap::Init(const int theScreen_Height, const int theScreen_Width,
    int theTileSize)
{
    this->theScreen_Height = theScreen_Height;
    this->theScreen_Width = theScreen_Width;

    this->theTileSize = theTileSize;
}

bool CMap::LoadMap(const string mapName)
{
    if (LoadFile(mapName) == true)
    {
        printf("Map (%s) has been successfully loaded!\n", mapName.c_str());
        return true;
    }

    return false;
}

bool CMap::LoadFile(const string mapName)
{
    int theLineCounter = 0;
    int theMaxNumOfColumns = 0;

    ifstream file(mapName.c_str());
    if (file.is_open())
    {
        int i = 0, k = 0;
        while (file.good())
        {
            string aLineOfText = "";
            getline(file, aLineOfText);

            if (aLineOfText == "")
                continue;
            //if (theLineCounter >= theNumOfTiles_MapHeight)
            //    break;

            // If this line is not a comment line, then process it
            if (!(aLineOfText.find("//*") == NULL) && aLineOfText != "")
            {
                if (theLineCounter == 0)
                {
                    // This is the first line of the map data file
                    string token;
                    std::istringstream iss(aLineOfText);
                    while (getline(iss, token, ','))
                    {
                        // Count the number of columns
                        theMaxNumOfColumns = atoi(token.c_str());
                    }
                    //if (theMaxNumOfColumns != theNumOfTiles_MapWidth)
                    //    return false;
                }
                else
                {
                    int theColumnCounter = 0;

                    string token;
                    std::istringstream iss(aLineOfText);
                    while (getline(iss, token, ','))
                    {
                        //map<int, vector<int>>::iterator it = theScreenMap.find(theLineCounter);
                        //if (it != theScreenMap.end()) {
                        //    it->second.push_back(atoi(token.c_str()));
                        //}
                        //else {
                        //    theScreenMap.insert(std::pair< int, vector<int> >(theLineCounter, vector<int>()));
                        //    theScreenMap.find(theLineCounter)->second.push_back(atoi(token.c_str()));
                        //}
                        //theScreenMap[theLineCounter][theColumnCounter++] = atoi(token.c_str());
                    }
                }
            }

            theLineCounter++;
        }
    }
    theNumOfTiles_MapWidth = theNumOfTiles_Width = theMaxNumOfColumns;
    theNumOfTiles_Height = theNumOfTiles_MapHeight = theLineCounter - 1;
    theMap_Height = theNumOfTiles_Height * GetTileSize();
    theMap_Width = theNumOfTiles_Width * GetTileSize();
    return true;
}

int CMap::GetNumOfTiles_Height(void)
{
    return theNumOfTiles_Height;
}

int CMap::GetNumOfTiles_Width(void)
{
    return theNumOfTiles_Width;
}

int CMap::GetTileSize(void)
{
    return theTileSize;
}

// Get the number of tiles for height of the map
int CMap::getNumOfTiles_MapHeight(void)
{
    return theNumOfTiles_MapHeight;
}

// Get the number of tiles for width of the map
int CMap::getNumOfTiles_MapWidth(void)
{
    return theNumOfTiles_MapWidth;
}

int CMap::getScreenWidth()
{
    return theScreen_Width;
}

int CMap::getScreenHeight()
{
    return theScreen_Height;
}