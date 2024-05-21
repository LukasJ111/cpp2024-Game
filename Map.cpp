#include "Map.h"
#include "game_loop.h"
#include <fstream>
#include "ECS\ECS.h"
#include "ECS\Components.h"

extern Manager manager;

Map::Map(const char* mfp, int ms, int ts) : mapFilePath(mfp), mapScale(ms), tileSize(ts)
{
    scaledSize = ms*ts;
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
            srcY=atoi(&c)*tileSize;
            mapFile.get(c);
            srcX=atoi(&c)*tileSize;
            AddTile(srcX, srcY, x * scaledSize, y * scaledSize);
            mapFile.ignore();

        }
    }


    mapFile.ignore();

    for (int y = 0; y < sizeY; y++)
    {
        for(int x = 0; x < sizeX; x++)
        {
            mapFile.get(c);
            if (atoi(&c) != 0)
            {
                auto& tcol(manager.addEntity());
                
                mapFile.get(c);
                srcY=atoi(&c)*tileSize;
                mapFile.get(c);
                srcX=atoi(&c)*tileSize;
                
                //tcol.addComponent<TileComponent>(srcX, srcY, x * scaledSize, y * scaledSize, tileSize, mapScale, mapFilePath);
                
                tcol.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
                tcol.addGroup(game_loop::groupColliders);
            }
            mapFile.ignore();
        }
    }


    mapFile.close();
}

void Map::AddTile(int srcX, int srcY, int xpos, int ypos)
{
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, mapFilePath);
    tile.addGroup(game_loop::groupMap);
}

int Map::getScaledSize() {
    return scaledSize;
}