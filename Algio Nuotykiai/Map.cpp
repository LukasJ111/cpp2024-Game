#include "Map.h"
#include "GameLoop.h"
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
                int c1=atoi(&c);
                srcY=atoi(&c)*tileSize;
                mapFile.get(c);
                srcX=atoi(&c)*tileSize;
                
                //tcol.addComponent<TileComponent>(srcX, srcY, x * scaledSize, y * scaledSize, tileSize, mapScale, mapFilePath);
                
                if((c1==3 &&  atoi(&c)==6) || (c1==3 &&  atoi(&c)==5) || (c1==3 &&  atoi(&c)==7))
                {   
                    tcol.addComponent<ColliderComponent>("door", srcX, srcY,  x * scaledSize, y * scaledSize, tileSize, mapScale, mapFilePath);
                }
                else{
                    tcol.addComponent<ColliderComponent>("terrain", srcX, srcY,  x * scaledSize, y * scaledSize, tileSize, mapScale, mapFilePath);
                }
                tcol.addGroup(game_loop::groupColliders);
            } else {
                mapFile.ignore();
            }
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
                
                srcY=atoi(&c)*tileSize;
                mapFile.get(c);
                srcX=atoi(&c)*tileSize;
                
                //tcol.addComponent<TileComponent>(srcX, srcY, x * scaledSize, y * scaledSize, tileSize, mapScale, mapFilePath);
                
                tcol.addComponent<ColliderComponent>("collectible", srcX, srcY,  x * scaledSize, y * scaledSize, tileSize, mapScale, mapFilePath);
                tcol.addGroup(game_loop::groupColliders);
            } else {
                mapFile.ignore();
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

const char* Map::getMapFilePath() {
    return mapFilePath;
}