#include "Map.h"
#include "texture_manager.h"

//Placeholder map
int lvl1[20][25]={
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

Map::Map(){

    //Siuo metu sudeti placeholder'iai, change as needed
    dirt=texture_manager::LoadTexture("assets/Map/dirt.png");
    grass=texture_manager::LoadTexture("assets/Map/grass.png");
    water=texture_manager::LoadTexture("assets/Map/water.png");

    LoadMap(lvl1); //Siuo metu mapas apibreztas paciame Map.cpp faile, tad LoadMap() kvieciame cia. Kai/jei map'a iskelsim i atskira faila, callinsim game_loop'e.

    src.x=src.y=0;
    src.w=dest.w=32;
    src.h=dest.h=32;

    dest.x=dest.y=0;
}

void Map::LoadMap(int arr[20][25])
{
    for(int row=0; row<20; row++)
    {
        for(int col=0; col<25; col++)
        {
            map[row][col]=arr[row][col];
        }
    }
}

void Map::DrawMap()
{
    int type=0;
    for(int row=0; row<20; row++)
    {
        for(int col=0; col<25; col++)
        {
            type=map[row][col];

            dest.x=col*32;
            dest.y=row*32;

            //Map'e 0 atspindi water.png, 1 - grass.png, 2 - dirt.png. Change as needed.
            switch(type)
            {
                case 0:
                    texture_manager::Draw(water, src, dest);
                    break;
                case 1:
                    texture_manager::Draw(grass, src, dest);
                    break;
                case 2:
                    texture_manager::Draw(dirt, src, dest);
                    break;

                default:
                    break;
            }
        }
    }
}