#include "Map.h"
#include "game_loop.h"
#include <fstream>

Map::Map()
{

}

Map::~Map()
{

}

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
    char c;
    std::fstream mapFile;
    mapFile.open(path);

    int srcX, srcY;

    for(int y = 0; y < sizeY; y++)
    {
        for(int x = 0; x < sizeX; x++)
        {
            mapFile.get(c);
            srcY=atoi(&c)*16;
            mapFile.get(c);
            srcX=atoi(&c)*16;
            game_loop::AddTile(srcX, srcY, x*32, y*32);
            mapFile.ignore();

        }
    }

    mapFile.close();
}
