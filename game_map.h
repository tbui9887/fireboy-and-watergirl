
#ifndef GAME_MAP_H_
#define GAME_MAP_H_

#include "common_func.h"
#include "BaseObject.h"


class TileMap : public BaseObject
{
public:

    TileMap(){}
    ~TileMap(){}
};

class GameMap
{
public:
    GameMap() {}
    ~GameMap() {}

    void LoadMap(const char* name);
    void LoadTiles(SDL_Renderer* gRenderer);
private:
    Map game_map_
    TileMap tile_map[MAX_MAP_Y][MAX_MAP_X];
};

#endif // GAME_MAP_H_
